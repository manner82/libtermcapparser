/*
 * timing.c
 *
 * This module tracks any timers set up by schedule_timer(). It
 * keeps all the currently active timers in a list; it informs the
 * front end of when the next timer is due to go off if that
 * changes; and, very importantly, it tracks the context pointers
 * passed to schedule_timer(), so that if a context is freed all
 * the timers associated with it can be immediately annulled.
 */

#include <assert.h>
#include <stdio.h>

#include <putty.h>


long schedule_timer(int ticks, timer_fn_t fn, void *ctx)
{
    return 0;
}

/*
 * Call to run any timers whose time has reached the present.
 * Returns the time (in ticks) expected until the next timer after
 * that triggers.
 */
int run_timers(long anow, long *next)
{
    return 0;
}

/*
 * Call to expire all timers associated with a given context.
 */
void expire_timer_context(void *ctx)
{ }
