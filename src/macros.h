#ifndef MACROS_H__
#define MACROS_H__

/* NOTE: should only be included in source files
 *  (not in headers) */

/* Setting __file__ correctly
 *  according to https://gcc.gnu.org/onlinedocs/gcc-4.8.1/gcc/Function-Names.html
 */
#if __STDC_VERSION__ < 199901L
# if __GNUC__ >= 2
#  define __func__ __FUNCTION__
# else
#  define __func__ "<unknown>"
# endif
#endif

/* Set report level (each includes all below):
 *  0 - All off
 *  1 - Errors
 *  2 - Warnings
 *  3 - Info
 *  4 - Debug
 */
#define REPORT_LEVEL 3

#define PRINTF_LEVEL(level, file, tag, fmt,  msg) \
    do { if (REPORT_LEVEL >= level) fprintf(file, tag ":%s:%d%s(): " fmt, __FILE__, \
            __LINE__, __func__, msg); } while (0)

#define  printf_error   (fmt, msg)  PRINTF_LEVEL(1, stderr, "ERROR", fmt, msg)
#define  printf_warning (fmt, msg)  PRINTF_LEVEL(2, stderr, "WARN",  fmt, msg)
#define  printf_info    (fmt, msg)  PRINTF_LEVEL(3, stderr, "INFO",  fmt, msg)
#define  printf_debug   (fmt, msg)  PRINTF_LEVEL(4, stderr, "DEBUG", fmt, msg)

#endif

