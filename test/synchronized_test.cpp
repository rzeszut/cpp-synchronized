#include "gtest/gtest.h"
#include "synchronized/synchronized.hpp"

using namespace __synchronized;
using namespace std;

class SynchronizedTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
        for (auto &el : __synchronized_map) {
            if (el.second) {
                el.second->unlock();
            }
        }
        __synchronized_map.clear();
    }
};

TEST_F(SynchronizedTest, ShouldLockValue) {
    // when
    pair<bool, shared_ptr<mutex>> ret = __lock_value((void *) 42);

    // then
    ASSERT_TRUE(ret.first);
    ASSERT_TRUE((bool) ret.second);

    auto it = __synchronized_map.find((void *) 42);
    ASSERT_EQ(it->second, ret.second);
}

TEST_F(SynchronizedTest, ShouldReleaseLock) {
    // given
    pair<bool, shared_ptr<mutex>> lock = __lock_value((void *) 42);

    // when
    __release_lock(lock);

    // then
    ASSERT_FALSE(lock.first);
    ASSERT_FALSE((bool) lock.second);
}
