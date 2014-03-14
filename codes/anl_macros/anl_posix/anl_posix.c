/*
 * Copyright (c) 2014 Andreas Sandberg
 * All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#define _POSIX_C_SOURCE 200112L

#include "anl_posix.h"

#include <sys/time.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

unsigned anl_num_threads = 0;
pthread_t anl_threads[ANL_MAX_THREADS];

static long page_size = 0;
static unsigned long long anl_clock_base = 0;

static unsigned long long _anl_clock();

#define ANL_E_PTH(s)                            \
    do {                                        \
        int _err = s;                           \
        if (_err)                               \
            anl_handle_error(_err, # s);        \
    } while(0)

static void anl_handle_error(int err, const char *fmt, ...)
{
    char buf[1024];
    va_list ap;

    if (fmt && fmt[0] != '\0') {
        va_start(ap, fmt);
        vfprintf(stderr, fmt, ap);
        va_end(ap);
    }

    if (strerror_r(err, buf, sizeof(buf)) == 0) {
        fprintf(stderr, ": %s\n", buf);
    } else {
        fprintf(stderr, ": Unknown error (%i)\n", err);
    }
    abort();
}

/**********************************************************************/

void anl_main_init()
{
    page_size = sysconf(_SC_PAGESIZE);
}

void anl_main_end()
{
    exit(0);
}

/**********************************************************************/

static void *anl_thread_main(void *_func)
{
    anl_thread_main_t func = (anl_thread_main_t)_func;

    func();

    return NULL;
}

void anl_thread_create(anl_thread_main_t tmain)
{
    ANL_E_PTH(pthread_create(&anl_threads[anl_num_threads], NULL,
                             &anl_thread_main, (void*)tmain));
    ++anl_num_threads;
}

void anl_thread_join_all()
{
    int i;
    for (i = 0; i < anl_num_threads; i++) {
        ANL_E_PTH(pthread_join(anl_threads[i], NULL));
    }
}

/**********************************************************************/

void anl_lock_init(anl_lock_t *lock)
{
    ANL_E_PTH(pthread_mutex_init(lock, NULL));
}

void anl_lock(anl_lock_t *lock)
{
    ANL_E_PTH(pthread_mutex_lock(lock));
}

void anl_unlock(anl_lock_t *lock)
{
    ANL_E_PTH(pthread_mutex_unlock(lock));
}

/**********************************************************************/

void anl_alock_init(anl_lock_t locks[], int count)
{
    int i;
    for (i = 0; i < count; i++) {
        ANL_E_PTH(pthread_mutex_init(&locks[i], NULL));
    }
}

void anl_alock(anl_lock_t locks[], int idx)
{
    ANL_E_PTH(pthread_mutex_lock(&locks[idx]));
}

void anl_aulock(anl_lock_t locks[], int idx)
{
    ANL_E_PTH(pthread_mutex_unlock(&locks[idx]));
}

/**********************************************************************/


void anl_pause_init(anl_pause_t *pause)
{
    ANL_E_PTH(pthread_mutex_init(&pause->mutex, NULL));
    ANL_E_PTH(pthread_cond_init(&pause->cond, NULL));
    pause->flag = 0;
}

void anl_pause_clear(anl_pause_t *pause)
{
    pause->flag = 0;
    ANL_E_PTH(pthread_mutex_unlock(&pause->mutex));
}

void anl_pause_set(anl_pause_t *pause)
{
    pthread_mutex_lock(&pause->mutex);
    pause->flag = 1;
    pthread_cond_broadcast(&pause->cond);
    pthread_mutex_unlock(&pause->mutex);
}

void anl_pause_wait(anl_pause_t *pause)
{
    pthread_mutex_lock(&pause->mutex);
    while (pause->flag == 0) {
        pthread_cond_wait(&pause->cond, &pause->mutex);
    }
}

/**********************************************************************/

void anl_barrier_init(anl_barrier_t *bar)
{
    ANL_E_PTH(pthread_mutex_init(&bar->mutex, NULL));
    ANL_E_PTH(pthread_cond_init(&bar->cond, NULL));
    bar->generation = 0;
    bar->count = 0;
}

void anl_barrier_wait(anl_barrier_t *bar, int count)
{
    ANL_E_PTH(pthread_mutex_lock(&bar->mutex));
    if (++bar->count < count) {
        int generation = bar->generation;
        while (bar->generation == generation) {
            pthread_cond_wait(&bar->cond, &bar->mutex);
        }
    } else {
        ++bar->generation;
        ANL_E_PTH(pthread_cond_broadcast(&bar->cond));
    }
    ANL_E_PTH(pthread_mutex_unlock(&bar->mutex));
}

/**********************************************************************/

void *anl_alloc(size_t size)
{
    void *mem;
    int e;

    if (page_size == 0) {
        fprintf(stderr, "anl_alloc called before anl_main_init().\n");
        abort();
    }

#if 0
    e = posix_memalign(&mem, page_size, size);
    if (e)
        anl_handle_error(e, "anl_alloc");
#else
    mem = malloc(size);
#endif

    return mem;
}

void anl_free(void *obj)
{
    //free(obj);
}


static unsigned long long _anl_clock()
{
    struct timeval ts;

    if (gettimeofday(&ts, NULL) == -1)
        anl_handle_error(errno, "anl_clock");

    return (unsigned long long)(ts.tv_usec + ts.tv_sec * 1000000ULL);
}

unsigned long anl_clock()
{
    unsigned long long t = _anl_clock();
    if (anl_clock_base == 0)
        anl_clock_base = t;

    return (unsigned long)(t - anl_clock_base);
}
