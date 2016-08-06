#ifndef FRAMEWORK_UNITTEST_ASSERTIONS_H
#define FRAMEWORK_UNITTEST_ASSERTIONS_H


#define TEST_FAIL(MSG) testFailed(__FILE__, __LINE__, (MSG) != 0 ? #MSG : "")

#define TEST_ASSERT(EXPR, MSG) !(EXPR) ? testFailed(__FILE__, __LINE__, (MSG) != 0 ? #MSG : "") : static_cast<void>(0)
#endif
