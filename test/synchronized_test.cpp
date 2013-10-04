#include "gtest/gtest.h"
#include "synchronized/synchronized.hpp"

using namespace __synchronized;

class SynchronizedTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
        __synchronized_map.clear();
    }
};

TEST_F(SynchronizedTest, ShouldLockValue) {
    // when
    __lock_value((void *) 42);

    // then
    ASSERT_FALSE(__synchronized_lock.isLocked());

    auto it = __synchronized_map.find((void *) 42);
    ASSERT_NE(it, __synchronized_map.end());
    ASSERT_TRUE((bool) it->second);
    ASSERT_TRUE(it->second->isLocked());
}

TEST_F(SynchronizedTest, ShouldReturnTrueWhenLocked) {
    // given
    __lock_value((void *) 42);
    
    // when
    bool locked = __is_locked((void *) 42);

    // then
    ASSERT_FALSE(__synchronized_lock.isLocked());
    ASSERT_TRUE(locked);
}

TEST_F(SynchronizedTest, ShouldReturnFalseWhenNotLocked) {
    // when
    bool locked = __is_locked((void *) 42);

    // then
    ASSERT_FALSE(__synchronized_lock.isLocked());
    ASSERT_FALSE(locked);
}

TEST_F(SynchronizedTest, ShouldReleaseLock) {
    // given
    __lock_value((void *) 42);

    // when
    __release_lock((void *) 42);

    // then
    ASSERT_FALSE(__synchronized_lock.isLocked());

    auto it = __synchronized_map.find((void *) 42);
    bool locked = it != __synchronized_map.end() 
        && it->second && it->second->isLocked();
    ASSERT_FALSE(locked);
}

