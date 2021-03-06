/*
 * Copyright 2017, Data61
 * Commonwealth Scientific and Industrial Research Organisation (CSIRO)
 * ABN 41 687 119 230.
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(DATA61_BSD)
 */

#include <assert.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <utils/util.h>

int clk_get_time(void) __attribute__((weak));
long camkes_sys_clock_gettime(va_list ap)
{
    clockid_t clk = va_arg(ap, clockid_t);
    struct timespec *ts = va_arg(ap, struct timespec *);
    uint32_t curtime;

    if (clk_get_time && clk == CLOCK_REALTIME && ts) {
        curtime = clk_get_time();
        ts->tv_sec = curtime / MS_IN_S;
        ts->tv_nsec = curtime % MS_IN_S * NS_IN_MS;
    } else {
        assert(!"sys_clock_gettime not implemented");
        return -ENOSYS;
    }

    return 0;
}
