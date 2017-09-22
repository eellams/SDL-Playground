#include "macros.h"

#include <stdio.h>

#include <stdarg.h>
#include <stdio.h>

/*void dbg_printf(const char *fmt, ...)
{
        va_list args;
            va_start(args, fmt);
                vfprintf(stderr, fmt, args);
                    va_end(args);
}*/

void printf_level(const int level,
        const FILE* file,
        const char* tag,
        const char* fmt,
        ...)
{
    va_list args;

    vs_start(args, fmt);

    if (level <= REPORT_LEVEL)
    {
        vfprintf(file, tagfmt, args); 
    }
}

