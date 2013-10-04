#ifndef __SYNCHRONIZED_HPP_INCLUDED__
#define __SYNCHRONIZED_HPP_INCLUDED__

#include <mutex>
#include <memory>
#include <utility>

#define synchronized(val) for (auto it = __synchronized::__lock_value((void *) val); \
                              it.first; \
                               __synchronized::__release_lock(it))
namespace __synchronized {

std::pair<bool, std::shared_ptr<std::mutex>> __lock_value(void *val);

void __release_lock(std::pair<bool, std::shared_ptr<std::mutex>> &lock);

}

#endif
