#include "synchronized/synchronized.hpp"

using namespace std;
using namespace __synchronized;

namespace __synchronized {

Lock __synchronized_lock;
map<void *, shared_ptr<Lock> > __synchronized_map;

void __lock_value(void *val) {
    // first, lock the map
    __synchronized_lock.lock();

    // find the lock for a given address in the map
    auto it = __synchronized_map.find(val);
    shared_ptr<Lock> lock;
    if (it == __synchronized_map.end()) {
        // if the address wasn't present in the map, create a new lock
        lock = shared_ptr<Lock>(new Lock());
        __synchronized_map[val] = lock;
    } else {
        // if it was present, check whether the shared_ptr contains any value
        // if not, reset
        lock = it->second;
        if (!lock) {
            lock.reset(new Lock());
        }
    }

    // finally, unlock the map and lock the memory address
    // IMPORTANT: the sequence is important, otherwise deadlocks appear
    __synchronized_lock.unlock();
    lock->lock();
}

bool __is_locked(void *val) {
    // lock the map
    __synchronized_lock.lock();

    // find the value in the map
    auto it = __synchronized_map.find(val);
    // the address is locked when:
    // 1. it is present in the map
    // 2. the shared_ptr contains data
    // 3. the Lock object is locked
    bool ret = it != __synchronized_map.end()
        && it->second
        && it->second->isLocked();

    // unlock the map before returning
    __synchronized_lock.unlock();

    return ret;
}

void __release_lock(void *val) {
    // lock the map
    __synchronized_lock.lock();

    // find the value in the map
    auto it = __synchronized_map.find(val);
    // if the address is present and locked,
    if (it != __synchronized_map.end()
        && it->second 
        && it->second->isLocked()) {
        // unlock
        it->second->unlock();
    }

    // finally, unlock the map
    __synchronized_lock.unlock();
}

}

