#ifndef PREP_THREAD_H
#define PREP_THREAD_H

#include "types.h"
#include <pthread.h>

/*
        this prepares read requests for the requests buffer in liburing
*/

/*
        pass a void* cast uring_thread_t as args
        
*/

void* ut_prep_thread( void* args );

#endif
