#include "synchronized/synchronized.hpp"

using namespace std;
using namespace __synchronized;

namespace __synchronized {

mutex __synchronized_lock;
map<void *, shared_ptr<mutex>> __synchronized_map;

pair<bool, shared_ptr<mutex>> __lock_value(void *val) {
    // first, lock the map
    __synchronized_lock.lock();

    // find the lock for a given address in the map
    auto it = __synchronized_map.find(val);
    shared_ptr<mutex> lock;
    if (it == __synchronized_map.end()) {
        // if the address wasn't present in the map, create a new lock
        lock = shared_ptr<mutex>(new mutex());
        __synchronized_map[val] = lock;
    } else {
        // if it was present, check whether the shared_ptr contains any value
        // if not, reset
        lock = it->second;
        if (!lock) {
            lock.reset(new mutex());
        }
    }

    // finally, unlock the map and lock the memory address
    // IMPORTANT: the sequence is important, otherwise deadlocks appear
    __synchronized_lock.unlock();
    lock->lock();

    return make_pair(true, lock);
}

void __release_lock(pair<bool, shared_ptr<mutex>> &lock) {
    // lock the map
    __synchronized_lock.lock();

    if (lock.first && lock.second) {
        // unlock and reset the pointer
        lock.second->unlock();
        lock.second.reset();
        // set locked to false
        lock.first = false;
    }

    // finally, unlock the map
    __synchronized_lock.unlock();
}

}

