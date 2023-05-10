#include "uring_thread.h"
#include "types.h"
#include "prep_thread.h"
#include "read_thread.h"
#include <string.h>
#include <stdlib.h>

static int ut_setup( uring_thread_t* ut ){
        memset( &ut->ps, 0, sizeof(prep_stats_t) );
        memset( &ut->rs, 0, sizeof(read_stats_t) );
        ut->join_now = 0;

        // printf("ps ro: %u\n", ut->ps.read_offset );

        pthread_cond_init( &ut->cond, NULL );
        pthread_mutex_init( &ut->mtx, NULL );

        return 1;
}

int ut_init( uring_thread_t* ut ){
        ut_setup( ut );



        pthread_create( 
                &ut->read_thread,
                NULL,
                ut_read_thread, /*func*/
                (void*)ut
        );

        pthread_create( 
                &ut->prep_thread,
                NULL,
                ut_prep_thread, /*func*/
                (void*)ut
        );
        
        return 1;
}

int ut_fini( uring_thread_t* ut ){
        ut->join_now = 0;
        pthread_join( ut->prep_thread, NULL );
        pthread_join( ut->read_thread, NULL );

        return 1;
}
