#ifndef URING_THREAD_H
#define URING_THREAD_H

#include "types.h"
#include <pthread.h>
#include <liburing.h>
#include "../uringload.h"

typedef struct prep_stats_t{
        u32 read_offset;
}prep_stats_t;

typedef struct read_stats_t{
}read_stats_t;

typedef struct uring_thread_t{
        uring_args_t setup_args;
        
        struct io_uring ring;

        u8* buff;

        filestats_t fs;

        prep_stats_t ps;
        read_stats_t rs;

        pthread_t read_thread;
        pthread_t prep_thread;
        pthread_mutex_t mtx;
        pthread_cond_t cond;
        int join_now;

}uring_thread_t;

int ut_init( uring_thread_t* ut );
int ut_fini( uring_thread_t* ut );

#endif
