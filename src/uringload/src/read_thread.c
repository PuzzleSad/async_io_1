#include "uring_thread.h"
#include "read_thread.h"
#include "types.h"
#include <liburing.h>

void* ut_read_thread( void* args ){
        uring_thread_t* ut = (uring_thread_t*)args;
        s32 ret = 0;

        while(1){
                struct io_uring_cqe* cqe;
                ret = io_uring_wait_cqe( &ut->ring, &cqe ); 
                if( ret < 0 ){
                        printf("io_uring_wait error: %i\n", ret );
                        goto UNEXPECTED_QUIT;
                }

                if( cqe == NULL ){
                        break;
                }

                u64 data = (u64)io_uring_cqe_get_data( cqe );
                printf("Data: %lu\n", data );
                
                io_uring_cqe_seen( &ut->ring, cqe );

        }

        printf("Read_thread success\n");

        return NULL;

        UNEXPECTED_QUIT: ;
        printf("read_thread unexpected quit\n");


        return NULL;
}
