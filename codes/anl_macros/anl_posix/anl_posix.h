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

#ifndef ANL_POSIX_H
#define ANL_POSIX_H

#include <pthread.h>

#define ANL_MAX_THREADS 128

typedef struct {
    int generation;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} anl_barrier_t;

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    unsigned long flag;
} anl_pause_t;

typedef pthread_mutex_t anl_lock_t;

typedef void (*anl_thread_main_t)();

extern unsigned anl_num_threads;
extern pthread_t anl_threads[];

extern void anl_main_end();

extern void anl_barrier_wait(anl_barrier_t *bar, int count);

extern void anl_thread_create(anl_thread_main_t tmain);
extern void anl_thread_join_all();

extern void anl_lock_init(anl_lock_t *lock);
extern void anl_lock(anl_lock_t *lock);
extern void anl_unlock(anl_lock_t *lock);

extern void anl_alock_init(anl_lock_t locks[], int count);
extern void anl_alock(anl_lock_t locks[], int idx);
extern void anl_aulock(anl_lock_t locks[], int idx);

extern void anl_pause_init(anl_pause_t *pause);
extern void anl_pause_clear(anl_pause_t *pause);
extern void anl_pause_set(anl_pause_t *pause);
extern void anl_pause_wait(anl_pause_t *pause);

extern unsigned long anl_clock();

#endif
