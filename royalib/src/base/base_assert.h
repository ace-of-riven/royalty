#pragma once

#if defined(__cplusplus)
/* C++11 */
#  define CLI_STATIC_ASSERT(a, msg) static_assert(a, msg);
#elif defined(_MSC_VER)
/* Visual Studio */
#  if (_MSC_VER > 1910) && !defined(__clang__)
#    define CLI_STATIC_ASSERT(a, msg) static_assert(a, msg);
#  else
#    define CLI_STATIC_ASSERT(a, msg) _STATIC_ASSERT(a);
#  endif
#elif defined(__COVERITY__)
/* Workaround error with coverity */
#  define CLI_STATIC_ASSERT(a, msg)
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
/* C11 */
#  define CLI_STATIC_ASSERT(a, msg) _Static_assert(a, msg);
#else
/* Old unsupported compiler */
#  define CLI_STATIC_ASSERT(a, msg)
#endif

#define CLI_STATIC_ASSERT_ALIGN(st, align) \
CLI_STATIC_ASSERT((sizeof(st) % (align) == 0), "Structure must be strictly aligned")
