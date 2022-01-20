#pragma once

#include "../base/base_utildefines.h"

#include <cstdio>

#define IMPL_EMPTY_ERR(f)		fprintf(stderr,"Implementation for function %s is empty.\n",f)

unsigned int GPU_hash_string ( const char * , int length , unsigned int base , unsigned int offset ) ;

#pragma once

/* hint to make sure function result is actually used */
#ifdef __GNUC__
#  define ATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#  define ATTR_WARN_UNUSED_RESULT
#endif

/* hint to mark function arguments expected to be non-null
 * if no arguments are given to the macro, all of pointer
 * arguments would be expected to be non-null
 */
#ifdef __GNUC__
#  define ATTR_NONNULL(args...) __attribute__((nonnull(args)))
#else
#  define ATTR_NONNULL(...)
#endif

 /* never returns NULL */
#if (__GNUC__ * 100 + __GNUC_MINOR__) >= 409 /* gcc4.9+ only */
#  define ATTR_RETURNS_NONNULL __attribute__((returns_nonnull))
#else
#  define ATTR_RETURNS_NONNULL
#endif

/* hint to mark function as it wouldn't return */
#if defined(__GNUC__) || defined(__clang__)
#  define ATTR_NORETURN __attribute__((noreturn))
#else
#  define ATTR_NORETURN
#endif

/* hint to treat any non-null function return value cannot alias any other pointer */
#if (defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 403))
#  define ATTR_MALLOC __attribute__((malloc))
#else
#  define ATTR_MALLOC
#endif

/* the function return value points to memory (2 args for 'size * tot') */
#if (defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 403))
#  define ATTR_ALLOC_SIZE(args...) __attribute__((alloc_size(args)))
#else
#  define ATTR_ALLOC_SIZE(...)
#endif

/* ensures a NULL terminating argument as the n'th last argument of a variadic function */
#ifdef __GNUC__
#  define ATTR_SENTINEL(arg_pos) __attribute__((sentinel(arg_pos)))
#else
#  define ATTR_SENTINEL(arg_pos)
#endif

/* hint to compiler that function uses printf-style format string */
#ifdef __GNUC__
#  define ATTR_PRINTF_FORMAT(format_param, dots_param) \
    __attribute__((format(printf, format_param, dots_param)))
#else
#  define ATTR_PRINTF_FORMAT(format_param, dots_param)
#endif

/* Use to suppress '-Wimplicit-fallthrough' (in place of 'break'). */
#ifndef ATTR_FALLTHROUGH
#  if defined(__GNUC__) && (__GNUC__ >= 7) /* gcc7.0+ only */
#    define ATTR_FALLTHROUGH __attribute__((fallthrough))
#  else
#    define ATTR_FALLTHROUGH ((void)0)
#  endif
#endif

/* Declare the memory alignment in Bytes. */
#if defined(_WIN32) && !defined(FREE_WINDOWS)
#  define ATTR_ALIGN(x) __declspec(align(x))
#else
#  define ATTR_ALIGN(x) __attribute__((aligned(x)))
#endif

/* -------------------------------------------------------------------- */
/** \name Min/Max Macros
 * \{ */

#define _VA_NARGS_GLUE(x, y) x y
#define _VA_NARGS_RETURN_COUNT(\
  _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, \
  _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, \
  _33_, _34_, _35_, _36_, _37_, _38_, _39_, _40_, _41_, _42_, _43_, _44_, _45_, _46_, _47_, _48_, \
  _49_, _50_, _51_, _52_, _53_, _54_, _55_, _56_, _57_, _58_, _59_, _60_, _61_, _62_, _63_, _64_, \
  count, ...) count
#define _VA_NARGS_EXPAND(args) _VA_NARGS_RETURN_COUNT args
#define _VA_NARGS_OVERLOAD_MACRO2(name, count) name##count
#define _VA_NARGS_OVERLOAD_MACRO1(name, count) _VA_NARGS_OVERLOAD_MACRO2(name, count)
#define _VA_NARGS_OVERLOAD_MACRO(name,  count) _VA_NARGS_OVERLOAD_MACRO1(name, count)
 /* --- expose for re-use --- */
 /* 64 args max */
#define VA_NARGS_COUNT(...) _VA_NARGS_EXPAND((__VA_ARGS__, \
  64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, \
  48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, \
  32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, \
  16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  2, 1, 0))
#define VA_NARGS_CALL_OVERLOAD(name, ...) \
  _VA_NARGS_GLUE(_VA_NARGS_OVERLOAD_MACRO(name, VA_NARGS_COUNT(__VA_ARGS__)), (__VA_ARGS__))

 /* useful for finding bad use of min/max */
#if 0
/* gcc only */
#  define _TYPECHECK(a, b) ((void)(((typeof(a) *)0) == ((typeof(b) *)0)))
#  define MIN2(x, y) (_TYPECHECK(x, y), (((x) < (y) ? (x) : (y))))
#  define MAX2(x, y) (_TYPECHECK(x, y), (((x) > (y) ? (x) : (y))))
#endif

/* hint to make sure function result is actually used */
#ifdef __GNUC__
#  define ATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#  define ATTR_WARN_UNUSED_RESULT
#endif

/* hint to mark function arguments expected to be non-null
 * if no arguments are given to the macro, all of pointer
 * arguments would be expected to be non-null
 */
#ifdef __GNUC__
#  define ATTR_NONNULL(args...) __attribute__((nonnull(args)))
#else
#  define ATTR_NONNULL(...)
#endif

 /* never returns NULL */
#if (__GNUC__ * 100 + __GNUC_MINOR__) >= 409 /* gcc4.9+ only */
#  define ATTR_RETURNS_NONNULL __attribute__((returns_nonnull))
#else
#  define ATTR_RETURNS_NONNULL
#endif

/* hint to mark function as it wouldn't return */
#if defined(__GNUC__) || defined(__clang__)
#  define ATTR_NORETURN __attribute__((noreturn))
#else
#  define ATTR_NORETURN
#endif

/* hint to treat any non-null function return value cannot alias any other pointer */
#if (defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 403))
#  define ATTR_MALLOC __attribute__((malloc))
#else
#  define ATTR_MALLOC
#endif

/* the function return value points to memory (2 args for 'size * tot') */
#if (defined(__GNUC__) && ((__GNUC__ * 100 + __GNUC_MINOR__) >= 403))
#  define ATTR_ALLOC_SIZE(args...) __attribute__((alloc_size(args)))
#else
#  define ATTR_ALLOC_SIZE(...)
#endif

/* ensures a NULL terminating argument as the n'th last argument of a variadic function */
#ifdef __GNUC__
#  define ATTR_SENTINEL(arg_pos) __attribute__((sentinel(arg_pos)))
#else
#  define ATTR_SENTINEL(arg_pos)
#endif

/* hint to compiler that function uses printf-style format string */
#ifdef __GNUC__
#  define ATTR_PRINTF_FORMAT(format_param, dots_param) \
    __attribute__((format(printf, format_param, dots_param)))
#else
#  define ATTR_PRINTF_FORMAT(format_param, dots_param)
#endif

/* Use to suppress '-Wimplicit-fallthrough' (in place of 'break'). */
#ifndef ATTR_FALLTHROUGH
#  if defined(__GNUC__) && (__GNUC__ >= 7) /* gcc7.0+ only */
#    define ATTR_FALLTHROUGH __attribute__((fallthrough))
#  else
#    define ATTR_FALLTHROUGH ((void)0)
#  endif
#endif

/* Declare the memory alignment in Bytes. */
#if defined(_WIN32) && !defined(FREE_WINDOWS)
#  define ATTR_ALIGN(x) __declspec(align(x))
#else
#  define ATTR_ALIGN(x) __attribute__((aligned(x)))
#endif

/* min/max */
#if defined(__GNUC__) || defined(__clang__)

#  define MIN2(a, b) \
    __extension__({ \
      typeof(a) a_ = (a); \
      typeof(b) b_ = (b); \
      ((a_) < (b_) ? (a_) : (b_)); \
    })

#  define MAX2(a, b) \
    __extension__({ \
      typeof(a) a_ = (a); \
      typeof(b) b_ = (b); \
      ((a_) > (b_) ? (a_) : (b_)); \
    })

#  define MIN3(a, b, c) \
    __extension__({ \
      typeof(a) a_ = (a); \
      typeof(b) b_ = (b); \
      typeof(c) c_ = (c); \
      ((a_ < b_) ? ((a_ < c_) ? a_ : c_) : ((b_ < c_) ? b_ : c_)); \
    })

#  define MAX3(a, b, c) \
    __extension__({ \
      typeof(a) a_ = (a); \
      typeof(b) b_ = (b); \
      typeof(c) c_ = (c); \
      ((a_ > b_) ? ((a_ > c_) ? a_ : c_) : ((b_ > c_) ? b_ : c_)); \
    })

#  define MIN4(a, b, c, d) \
    __extension__({ \
      typeof(a) a_ = (a); \
      typeof(b) b_ = (b); \
      typeof(c) c_ = (c); \
      typeof(d) d_ = (d); \
      ((a_ < b_) ? ((a_ < c_) ? ((a_ < d_) ? a_ : d_) : ((c_ < d_) ? c_ : d_)) : \
                   ((b_ < c_) ? ((b_ < d_) ? b_ : d_) : ((c_ < d_) ? c_ : d_))); \
    })

#  define MAX4(a, b, c, d) \
    __extension__({ \
      typeof(a) a_ = (a); \
      typeof(b) b_ = (b); \
      typeof(c) c_ = (c); \
      typeof(d) d_ = (d); \
      ((a_ > b_) ? ((a_ > c_) ? ((a_ > d_) ? a_ : d_) : ((c_ > d_) ? c_ : d_)) : \
                   ((b_ > c_) ? ((b_ > d_) ? b_ : d_) : ((c_ > d_) ? c_ : d_))); \
    })

#else
#  define MIN2(a, b) ((a) < (b) ? (a) : (b))
#  define MAX2(a, b) ((a) > (b) ? (a) : (b))

#  define MIN3(a, b, c) (MIN2(MIN2((a), (b)), (c)))
#  define MIN4(a, b, c, d) (MIN2(MIN2((a), (b)), MIN2((c), (d))))

#  define MAX3(a, b, c) (MAX2(MAX2((a), (b)), (c)))
#  define MAX4(a, b, c, d) (MAX2(MAX2((a), (b)), MAX2((c), (d))))
#endif

/* min/max that return a value of our choice */
#define MAX3_PAIR(cmp_a, cmp_b, cmp_c, ret_a, ret_b, ret_c) \
  ((cmp_a > cmp_b) ? ((cmp_a > cmp_c) ? ret_a : ret_c) : ((cmp_b > cmp_c) ? ret_b : ret_c))

#define MIN3_PAIR(cmp_a, cmp_b, cmp_c, ret_a, ret_b, ret_c) \
  ((cmp_a < cmp_b) ? ((cmp_a < cmp_c) ? ret_a : ret_c) : ((cmp_b < cmp_c) ? ret_b : ret_c))

#define INIT_MINMAX(min, max) \
  { \
    (min)[0] = (min)[1] = (min)[2] = 1.0e30f; \
    (max)[0] = (max)[1] = (max)[2] = -1.0e30f; \
  } \
  (void)0
#define INIT_MINMAX2(min, max) \
  { \
    (min)[0] = (min)[1] = 1.0e30f; \
    (max)[0] = (max)[1] = -1.0e30f; \
  } \
  (void)0

/** \} */

/* -------------------------------------------------------------------- */
/** \name Swap/Shift Macros
 * \{ */

#define SWAP(type, a, b) \
  { \
    type sw_ap; \
    CHECK_TYPE(a, type); \
    CHECK_TYPE(b, type); \
    sw_ap = (a); \
    (a) = (b); \
    (b) = sw_ap; \
  } \
  (void)0

 /* swap with a temp value */
#define SWAP_TVAL(tval, a, b) \
  { \
    CHECK_TYPE_PAIR(tval, a); \
    CHECK_TYPE_PAIR(tval, b); \
    (tval) = (a); \
    (a) = (b); \
    (b) = (tval); \
  } \
  (void)0

/* shift around elements */
#define SHIFT3(type, a, b, c) \
  { \
    type tmp; \
    CHECK_TYPE(a, type); \
    CHECK_TYPE(b, type); \
    CHECK_TYPE(c, type); \
    tmp = a; \
    a = c; \
    c = b; \
    b = tmp; \
  } \
  (void)0

#define SHIFT4(type, a, b, c, d) \
  { \
    type tmp; \
    CHECK_TYPE(a, type); \
    CHECK_TYPE(b, type); \
    CHECK_TYPE(c, type); \
    CHECK_TYPE(d, type); \
    tmp = a; \
    a = d; \
    d = c; \
    c = b; \
    b = tmp; \
  } \
  (void)0

/** \} */

/* -------------------------------------------------------------------- */
/** \name Equal to Any Element (ELEM) Macro
 * \{ */

 /* Manual line breaks for readability. */
 /* clang-format off */

 /* ELEM#(v, ...): is the first arg equal any others? */
 /* internal helpers. */
#define _VA_ELEM2(v, a) ((v) == (a))
#define _VA_ELEM3(v, a, b) \
  (_VA_ELEM2(v, a) || _VA_ELEM2(v, b))
#define _VA_ELEM4(v, a, b, c) \
  (_VA_ELEM3(v, a, b) || _VA_ELEM2(v, c))
#define _VA_ELEM5(v, a, b, c, d) \
  (_VA_ELEM4(v, a, b, c) || _VA_ELEM2(v, d))
#define _VA_ELEM6(v, a, b, c, d, e) \
  (_VA_ELEM5(v, a, b, c, d) || _VA_ELEM2(v, e))
#define _VA_ELEM7(v, a, b, c, d, e, f) \
  (_VA_ELEM6(v, a, b, c, d, e) || _VA_ELEM2(v, f))
#define _VA_ELEM8(v, a, b, c, d, e, f, g) \
  (_VA_ELEM7(v, a, b, c, d, e, f) || _VA_ELEM2(v, g))
#define _VA_ELEM9(v, a, b, c, d, e, f, g, h) \
  (_VA_ELEM8(v, a, b, c, d, e, f, g) || _VA_ELEM2(v, h))
#define _VA_ELEM10(v, a, b, c, d, e, f, g, h, i) \
  (_VA_ELEM9(v, a, b, c, d, e, f, g, h) || _VA_ELEM2(v, i))
#define _VA_ELEM11(v, a, b, c, d, e, f, g, h, i, j) \
  (_VA_ELEM10(v, a, b, c, d, e, f, g, h, i) || _VA_ELEM2(v, j))
#define _VA_ELEM12(v, a, b, c, d, e, f, g, h, i, j, k) \
  (_VA_ELEM11(v, a, b, c, d, e, f, g, h, i, j) || _VA_ELEM2(v, k))
#define _VA_ELEM13(v, a, b, c, d, e, f, g, h, i, j, k, l) \
  (_VA_ELEM12(v, a, b, c, d, e, f, g, h, i, j, k) || _VA_ELEM2(v, l))
#define _VA_ELEM14(v, a, b, c, d, e, f, g, h, i, j, k, l, m) \
  (_VA_ELEM13(v, a, b, c, d, e, f, g, h, i, j, k, l) || _VA_ELEM2(v, m))
#define _VA_ELEM15(v, a, b, c, d, e, f, g, h, i, j, k, l, m, n) \
  (_VA_ELEM14(v, a, b, c, d, e, f, g, h, i, j, k, l, m) || _VA_ELEM2(v, n))
#define _VA_ELEM16(v, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o) \
  (_VA_ELEM15(v, a, b, c, d, e, f, g, h, i, j, k, l, m, n) || _VA_ELEM2(v, o))
#define _VA_ELEM17(v, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) \
  (_VA_ELEM16(v, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o) || _VA_ELEM2(v, p))
/* clang-format on */

/* reusable ELEM macro */
#define ELEM(...) VA_NARGS_CALL_OVERLOAD(_VA_ELEM, __VA_ARGS__)

/** \} */

/* -------------------------------------------------------------------- */
/** \name Simple Math Macros
 * \{ */

 /* avoid multiple access for supported compilers */
#if defined(__GNUC__) || defined(__clang__)

#  define ABS(a) \
    ({ \
      typeof(a) a_ = (a); \
      ((a_) < 0 ? (-(a_)) : (a_)); \
    })
#  define SQUARE(a) \
    ({ \
      typeof(a) a_ = (a); \
      ((a_) * (a_)); \
    })
#  define CUBE(a) \
    ({ \
      typeof(a) a_ = (a); \
      ((a_) * (a_) * (a_)); \
    })

#else

#  define ABS(a) ((a) < 0 ? (-(a)) : (a))
#  define SQUARE(a) ((a) * (a))
#  define CUBE(a) ((a) * (a) * (a))

#endif

/* Float equality checks. */

#define IS_EQ(a, b) \
  (CHECK_TYPE_INLINE(a, double), \
   CHECK_TYPE_INLINE(b, double), \
   ((fabs((double)((a) - (b))) >= (double)FLT_EPSILON) ? false : true))

#define IS_EQF(a, b) \
  (CHECK_TYPE_INLINE(a, float), \
   CHECK_TYPE_INLINE(b, float), \
   ((fabsf((float)((a) - (b))) >= (float)FLT_EPSILON) ? false : true))

#define IS_EQT(a, b, c) (((a) > (b)) ? ((((a) - (b)) <= (c))) : (((((b) - (a)) <= (c)))))
#define IN_RANGE(a, b, c) (((b) < (c)) ? (((b) < (a) && (a) < (c))) : (((c) < (a) && (a) < (b))))
#define IN_RANGE_INCL(a, b, c) \
  (((b) < (c)) ? (((b) <= (a) && (a) <= (c))) : (((c) <= (a) && (a) <= (b))))

/**
 * Expands to an integer constant expression evaluating to a close upper bound
 * on the number the number of decimal digits in a value expressible in the
 * integer type given by the argument (if it is a type name) or the integer
 * type of the argument (if it is an expression). The meaning of the resulting
 * expression is unspecified for other arguments.
 * i.e: `DECIMAL_DIGITS_BOUND(uchar)` is equal to 3.
 */
#define DECIMAL_DIGITS_BOUND(t) (241 * sizeof(t) / 100 + 1)

 /** \} */

 /* -------------------------------------------------------------------- */
 /** \name Clamp Macros
  * \{ */

#define CLAMPIS(a, b, c) ((a) < (b) ? (b) : (a) > (c) ? (c) : (a))

#define CLAMP2(vec, b, c) \
  { \
    CLAMP((vec)[0], b, c); \
    CLAMP((vec)[1], b, c); \
  } \
  (void)0

#define CLAMP2_MIN(vec, b) \
  { \
    CLAMP_MIN((vec)[0], b); \
    CLAMP_MIN((vec)[1], b); \
  } \
  (void)0

#define CLAMP2_MAX(vec, b) \
  { \
    CLAMP_MAX((vec)[0], b); \
    CLAMP_MAX((vec)[1], b); \
  } \
  (void)0

#define CLAMP3(vec, b, c) \
  { \
    CLAMP((vec)[0], b, c); \
    CLAMP((vec)[1], b, c); \
    CLAMP((vec)[2], b, c); \
  } \
  (void)0

#define CLAMP3_MIN(vec, b) \
  { \
    CLAMP_MIN((vec)[0], b); \
    CLAMP_MIN((vec)[1], b); \
    CLAMP_MIN((vec)[2], b); \
  } \
  (void)0

#define CLAMP3_MAX(vec, b) \
  { \
    CLAMP_MAX((vec)[0], b); \
    CLAMP_MAX((vec)[1], b); \
    CLAMP_MAX((vec)[2], b); \
  } \
  (void)0

#define CLAMP4(vec, b, c) \
  { \
    CLAMP((vec)[0], b, c); \
    CLAMP((vec)[1], b, c); \
    CLAMP((vec)[2], b, c); \
    CLAMP((vec)[3], b, c); \
  } \
  (void)0

#define CLAMP4_MIN(vec, b) \
  { \
    CLAMP_MIN((vec)[0], b); \
    CLAMP_MIN((vec)[1], b); \
    CLAMP_MIN((vec)[2], b); \
    CLAMP_MIN((vec)[3], b); \
  } \
  (void)0

#define CLAMP4_MAX(vec, b) \
  { \
    CLAMP_MAX((vec)[0], b); \
    CLAMP_MAX((vec)[1], b); \
    CLAMP_MAX((vec)[2], b); \
    CLAMP_MAX((vec)[3], b); \
  } \
  (void)0

  /** \} */

  /* -------------------------------------------------------------------- */
  /** \name Array Unpacking Macros
   * \{ */

   /* unpack vector for args */
#define UNPACK2(a) ((a)[0]), ((a)[1])
#define UNPACK3(a) UNPACK2(a), ((a)[2])
#define UNPACK4(a) UNPACK3(a), ((a)[3])
/* pre may be '&', '*' or func, post may be '->member' */
#define UNPACK2_EX(pre, a, post) (pre((a)[0]) post), (pre((a)[1]) post)
#define UNPACK3_EX(pre, a, post) UNPACK2_EX(pre, a, post), (pre((a)[2]) post)
#define UNPACK4_EX(pre, a, post) UNPACK3_EX(pre, a, post), (pre((a)[3]) post)

/** \} */

/* -------------------------------------------------------------------- */
/** \name Array Macros
 * \{ */

 /* array helpers */
#define ARRAY_LAST_ITEM(arr_start, arr_dtype, arr_len) \
  (arr_dtype *)((char *)(arr_start) + (sizeof(*((arr_dtype *)NULL)) * (size_t)(arr_len - 1)))

#define ARRAY_HAS_ITEM(arr_item, arr_start, arr_len) \
  (CHECK_TYPE_PAIR_INLINE(arr_start, arr_item), \
   ((unsigned int)((arr_item) - (arr_start)) < (unsigned int)(arr_len)))

  /* assuming a static array */
#if defined(__GNUC__) && !defined(__cplusplus) && !defined(__clang__) && !defined(__INTEL_COMPILER)
#  define ARRAY_SIZE(arr) \
    ((sizeof(struct { int isnt_array : ((const void *)&(arr) == &(arr)[0]); }) * 0) + \
     (sizeof(arr) / sizeof(*(arr))))
#else
#  define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(*(arr)))
#endif

/* ARRAY_SET_ITEMS#(v, ...): set indices of array 'v'  */
/* internal helpers */
#define _VA_ARRAY_SET_ITEMS2(v, a) ((v)[0] = (a))
#define _VA_ARRAY_SET_ITEMS3(v, a, b) \
  _VA_ARRAY_SET_ITEMS2(v, a); \
  ((v)[1] = (b))
#define _VA_ARRAY_SET_ITEMS4(v, a, b, c) \
  _VA_ARRAY_SET_ITEMS3(v, a, b); \
  ((v)[2] = (c))
#define _VA_ARRAY_SET_ITEMS5(v, a, b, c, d) \
  _VA_ARRAY_SET_ITEMS4(v, a, b, c); \
  ((v)[3] = (d))
#define _VA_ARRAY_SET_ITEMS6(v, a, b, c, d, e) \
  _VA_ARRAY_SET_ITEMS5(v, a, b, c, d); \
  ((v)[4] = (e))
#define _VA_ARRAY_SET_ITEMS7(v, a, b, c, d, e, f) \
  _VA_ARRAY_SET_ITEMS6(v, a, b, c, d, e); \
  ((v)[5] = (f))
#define _VA_ARRAY_SET_ITEMS8(v, a, b, c, d, e, f, g) \
  _VA_ARRAY_SET_ITEMS7(v, a, b, c, d, e, f); \
  ((v)[6] = (g))
#define _VA_ARRAY_SET_ITEMS9(v, a, b, c, d, e, f, g, h) \
  _VA_ARRAY_SET_ITEMS8(v, a, b, c, d, e, f, g); \
  ((v)[7] = (h))
#define _VA_ARRAY_SET_ITEMS10(v, a, b, c, d, e, f, g, h, i) \
  _VA_ARRAY_SET_ITEMS9(v, a, b, c, d, e, f, g, h); \
  ((v)[8] = (i))
#define _VA_ARRAY_SET_ITEMS11(v, a, b, c, d, e, f, g, h, i, j) \
  _VA_ARRAY_SET_ITEMS10(v, a, b, c, d, e, f, g, h, i); \
  ((v)[9] = (j))
#define _VA_ARRAY_SET_ITEMS12(v, a, b, c, d, e, f, g, h, i, j, k) \
  _VA_ARRAY_SET_ITEMS11(v, a, b, c, d, e, f, g, h, i, j); \
  ((v)[10] = (k))
#define _VA_ARRAY_SET_ITEMS13(v, a, b, c, d, e, f, g, h, i, j, k, l) \
  _VA_ARRAY_SET_ITEMS12(v, a, b, c, d, e, f, g, h, i, j, k); \
  ((v)[11] = (l))
#define _VA_ARRAY_SET_ITEMS14(v, a, b, c, d, e, f, g, h, i, j, k, l, m) \
  _VA_ARRAY_SET_ITEMS13(v, a, b, c, d, e, f, g, h, i, j, k, l); \
  ((v)[12] = (m))
#define _VA_ARRAY_SET_ITEMS15(v, a, b, c, d, e, f, g, h, i, j, k, l, m, n) \
  _VA_ARRAY_SET_ITEMS14(v, a, b, c, d, e, f, g, h, i, j, k, l, m); \
  ((v)[13] = (n))
#define _VA_ARRAY_SET_ITEMS16(v, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o) \
  _VA_ARRAY_SET_ITEMS15(v, a, b, c, d, e, f, g, h, i, j, k, l, m, n); \
  ((v)[14] = (o))
#define _VA_ARRAY_SET_ITEMS17(v, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) \
  _VA_ARRAY_SET_ITEMS16(v, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o); \
  ((v)[15] = (p))

/* reusable ARRAY_SET_ITEMS macro */
#define ARRAY_SET_ITEMS(...) \
  { \
    VA_NARGS_CALL_OVERLOAD(_VA_ARRAY_SET_ITEMS, __VA_ARGS__); \
  } \
  (void)0

/** \} */

/* -------------------------------------------------------------------- */
/** \name Pointer Macros
 * \{ */

#if defined(__GNUC__) || defined(__clang__)
#  define POINTER_OFFSET(v, ofs) ((typeof(v))((char *)(v) + (ofs)))
#else
#  define POINTER_OFFSET(v, ofs) ((void *)((char *)(v) + (ofs)))
#endif

 /* Warning-free macros for storing ints in pointers. Use these _only_
  * for storing an int in a pointer, not a pointer in an int (64bit)! */
#define POINTER_FROM_INT(i) ((void *)(intptr_t)(i))
#define POINTER_AS_INT(i) ((void)0, ((int)(intptr_t)(i)))

#define POINTER_FROM_UINT(i) ((void *)(uintptr_t)(i))
#define POINTER_AS_UINT(i) ((void)0, ((unsigned int)(uintptr_t)(i)))

  /** \} */

  /* -------------------------------------------------------------------- */
  /** \name Struct After Macros
   *
   * Typically used to copy/clear polymorphic structs which have a generic
   * member at the start which needs to be left as-is.
   *
   * \{ */

   /** Performs `offsetof(typeof(data), member) + sizeof((data)->member)` for non-gcc compilers. */
#define OFFSETOF_STRUCT_AFTER(_struct, _member) \
  ((((const char *)&((_struct)->_member)) - ((const char *)(_struct))) + \
   sizeof((_struct)->_member))

/**
 * memcpy helper, skipping the first part of a struct,
 * ensures 'struct_dst' isn't const and the offset can be computed at compile time.
 * This isn't inclusive, the value of \a member isn't copied.
 */
#define MEMCPY_STRUCT_AFTER(struct_dst, struct_src, member) \
  { \
    CHECK_TYPE_NONCONST(struct_dst); \
    ((void)(struct_dst == struct_src), \
     memcpy((char *)(struct_dst) + OFFSETOF_STRUCT_AFTER(struct_dst, member), \
            (const char *)(struct_src) + OFFSETOF_STRUCT_AFTER(struct_dst, member), \
            sizeof(*(struct_dst)) - OFFSETOF_STRUCT_AFTER(struct_dst, member))); \
  } \
  ((void)0)

#define MEMSET_STRUCT_AFTER(struct_var, value, member) \
  { \
    CHECK_TYPE_NONCONST(struct_var); \
    memset((char *)(struct_var) + OFFSETOF_STRUCT_AFTER(struct_var, member), \
           value, \
           sizeof(*(struct_var)) - OFFSETOF_STRUCT_AFTER(struct_var, member)); \
  } \
  ((void)0)

 /* defined
  * in memory_utils.c for now. I do not know where we should put it actually... */
#ifndef __ACE_MEMORY_UTILS_H__
extern bool ACE_memory_is_zero ( const void *arr , const size_t arr_size );
#endif

/** \} */

/* -------------------------------------------------------------------- */
/** \name String Macros
 * \{ */

 /* Macro to convert a value to string in the preprocessor
  * STRINGIFY_ARG: gives the argument as a string
  * STRINGIFY_APPEND: appends any argument 'b' onto the string argument 'a',
  *   used by STRINGIFY because some preprocessors warn about zero arguments
  * STRINGIFY: gives the argument's value as a string */
#define STRINGIFY_ARG(x) "" #x
#define STRINGIFY_APPEND(a, b) "" a #b
#define STRINGIFY(x) STRINGIFY_APPEND("", x)

  /* generic strcmp macros */
#if defined(_MSC_VER)
#  define strcasecmp _stricmp
#  define strncasecmp _strnicmp
#endif

#define STREQ(a, b) (strcmp(a, b) == 0)
#define STRCASEEQ(a, b) (strcasecmp(a, b) == 0)
#define STREQLEN(a, b, n) (strncmp(a, b, n) == 0)
#define STRCASEEQLEN(a, b, n) (strncasecmp(a, b, n) == 0)

#define STRPREFIX(a, b) (strncmp((a), (b), strlen(b)) == 0)

/** \} */

/* -------------------------------------------------------------------- */
/** \name Unused Function/Argument Macros
 * \{ */

 /* UNUSED macro, for function argument */
#if defined(__GNUC__) || defined(__clang__)
#  define UNUSED(x) UNUSED_##x __attribute__((__unused__))
#else
#  define UNUSED(x) UNUSED_##x
#endif

#if defined(__GNUC__) || defined(__clang__)
#  define UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_##x
#else
#  define UNUSED_FUNCTION(x) UNUSED_##x
#endif

/**
 * UNUSED_VARS#(a, ...): quiet unused warnings
 *
 * \code{.py}
 * for i in range(16):
 *     args = [(chr(ord('a') + (c % 26)) + (chr(ord('0') + (c // 26)))) for c in range(i + 1)]
 *     print("#define _VA_UNUSED_VARS_%d(%s) \\" % (i + 1, ", ".join(args)))
 *     print("\t((void)(%s)%s)" %
 *             (args[0], ((", _VA_UNUSED_VARS_" + str(i) + "(%s)") if i else "%s") %
 *              ", ".join((args[1:]))))
 * \endcode
 */

#define _VA_UNUSED_VARS_1(a0) ((void)(a0))
#define _VA_UNUSED_VARS_2(a0, b0) ((void)(a0), _VA_UNUSED_VARS_1(b0))
#define _VA_UNUSED_VARS_3(a0, b0, c0) ((void)(a0), _VA_UNUSED_VARS_2(b0, c0))
#define _VA_UNUSED_VARS_4(a0, b0, c0, d0) ((void)(a0), _VA_UNUSED_VARS_3(b0, c0, d0))
#define _VA_UNUSED_VARS_5(a0, b0, c0, d0, e0) ((void)(a0), _VA_UNUSED_VARS_4(b0, c0, d0, e0))
#define _VA_UNUSED_VARS_6(a0, b0, c0, d0, e0, f0) \
  ((void)(a0), _VA_UNUSED_VARS_5(b0, c0, d0, e0, f0))
#define _VA_UNUSED_VARS_7(a0, b0, c0, d0, e0, f0, g0) \
  ((void)(a0), _VA_UNUSED_VARS_6(b0, c0, d0, e0, f0, g0))
#define _VA_UNUSED_VARS_8(a0, b0, c0, d0, e0, f0, g0, h0) \
  ((void)(a0), _VA_UNUSED_VARS_7(b0, c0, d0, e0, f0, g0, h0))
#define _VA_UNUSED_VARS_9(a0, b0, c0, d0, e0, f0, g0, h0, i0) \
  ((void)(a0), _VA_UNUSED_VARS_8(b0, c0, d0, e0, f0, g0, h0, i0))
#define _VA_UNUSED_VARS_10(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0) \
  ((void)(a0), _VA_UNUSED_VARS_9(b0, c0, d0, e0, f0, g0, h0, i0, j0))
#define _VA_UNUSED_VARS_11(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0) \
  ((void)(a0), _VA_UNUSED_VARS_10(b0, c0, d0, e0, f0, g0, h0, i0, j0, k0))
#define _VA_UNUSED_VARS_12(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0) \
  ((void)(a0), _VA_UNUSED_VARS_11(b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0))
#define _VA_UNUSED_VARS_13(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0) \
  ((void)(a0), _VA_UNUSED_VARS_12(b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0))
#define _VA_UNUSED_VARS_14(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0) \
  ((void)(a0), _VA_UNUSED_VARS_13(b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0))
#define _VA_UNUSED_VARS_15(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0) \
  ((void)(a0), _VA_UNUSED_VARS_14(b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0))
#define _VA_UNUSED_VARS_16(a0, b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0) \
  ((void)(a0), _VA_UNUSED_VARS_15(b0, c0, d0, e0, f0, g0, h0, i0, j0, k0, l0, m0, n0, o0, p0))

 /* reusable ELEM macro */
#define UNUSED_VARS(...) VA_NARGS_CALL_OVERLOAD(_VA_UNUSED_VARS_, __VA_ARGS__)

/* for debug-only variables */
#ifndef NDEBUG
#  define UNUSED_VARS_NDEBUG(...)
#else
#  define UNUSED_VARS_NDEBUG UNUSED_VARS
#endif

/** \} */

/* -------------------------------------------------------------------- */
/** \name Branch Prediction Macros
 * \{ */

 /* hints for branch prediction, only use in code that runs a _lot_ where */
#ifdef __GNUC__
#  define LIKELY(x) __builtin_expect(!!(x), 1)
#  define UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
#  define LIKELY(x) (x)
#  define UNLIKELY(x) (x)
#endif

/** \} */

/* -------------------------------------------------------------------- */
/** \name Flag Macros
 * \{ */

 /* Set flag from a single test */
#define SET_FLAG_FROM_TEST(value, test, flag) \
  { \
    if (test) { \
      (value) |= (flag); \
    } \
    else { \
      (value) &= ~(flag); \
    } \
  } \
  ((void)0)

/** \} */

/* -------------------------------------------------------------------- */
/** \name Misc Macros
 * \{ */

 /** Useful for debugging. */
#define AT __FILE__ ":" STRINGIFY(__LINE__)

/** No-op for expressions we don't want to instantiate, but must remain valid. */
#define EXPR_NOP(expr) (void)(0 ? ((void)(expr), 1) : 0)

/** \} */
