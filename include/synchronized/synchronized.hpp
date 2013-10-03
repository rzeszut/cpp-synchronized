#ifndef __SYNCHRONIZED_HPP_INCLUDED__
#define __SYNCHRONIZED_HPP_INCLUDED__

#include <mutex>
#include <map>
#include <memory>

#define synchronized(val) for (__synchronized::__lock_value(val); \
                               __synchronized::__is_locked(val); \
                               __synchronized::__release_lock(val))

namespace __synchronized {

class Lock {
private:
    std::mutex mt;
    bool locked;

public:
    Lock();
    Lock(const Lock &other) = delete;
    ~Lock(); 

    bool isLocked() const;

    void lock();

    void unlock();
};

extern Lock __synchronized_lock;
extern std::map<void *, std::shared_ptr<Lock> > __synchronized_map;

void __lock_value(void *val);

bool __is_locked(void *val);

void __release_lock(void *val);

}

// inline definitions
inline __synchronized::Lock::Lock() : locked(false) {}

inline __synchronized::Lock::~Lock() {
    if (locked) {
        mt.unlock();
    }
}

inline void __synchronized::Lock::lock() {
    // this actually makes sense, let me explain:
    // 1. set the 'locked' property to true before performing the lock:
    // when isLocked() is called, it returns true (as it should, the lock 
    // is about to happen)
    // 2. lock
    // 3. set the 'locked' property to true again:
    // when this thread was blocked while the lock() call lasted, the value
    // of the 'locked' property may have changed - therefore, set 'locked' to
    // true again
    locked = true;
    mt.lock();
    locked = true;
}

inline void __synchronized::Lock::unlock() {
    mt.unlock();
    locked = false;
}

inline bool __synchronized::Lock::isLocked() const {
    return locked;
}

#endif
