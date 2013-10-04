#include "gtest/gtest.h"
#include "synchronized/synchronized.hpp"

using namespace __synchronized;
using namespace std;

TEST(SynchronizedTest, ShouldLockValue) {
    // when
    pair<bool, shared_ptr<mutex>> ret = __lock_value((void *) 42);

    // then
    ASSERT_TRUE(ret.first);
    ASSERT_TRUE((bool) ret.second);

    // cleanup
    __release_lock(ret);
}

TEST(SynchronizedTest, ShouldReleaseLock) {
    // given
    pair<bool, shared_ptr<mutex>> lock = __lock_value((void *) 42);

    // when
    __release_lock(lock);

    // then
    ASSERT_FALSE(lock.first);
    ASSERT_FALSE((bool) lock.second);
}
