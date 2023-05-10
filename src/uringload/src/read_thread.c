#include "uring_thread.h"
#include "read_thread.h"
#include "types.h"
#include <liburing.h>

static int wait_for_cqe( uring_thread_t* ut, struct io_uring_cqe** cqe );

void* ut_read_thread( void* args ){
        uring_thread_t* ut = (uring_thread_t*)args;

        //Since we know how many blocks will be read
        for( u64 i = 0; i < ut->file_stats.block_count; i++ ){
                struct io_uring_cqe* cqe;

                if( wait_for_cqe( ut, &cqe ) < 0 ){
                        goto UNEXPECTED_QUIT;
                }

                if( cqe == NULL ){
                        break;
                }

                u64 data = (u64)io_uring_cqe_get_data( cqe );
                printf("Data: %lu\n", data );
                
                io_uring_cqe_seen( &ut->ring, cqe );

        }

        printf("\e[32mread_thread success\e[0m\n");

        return NULL;

        UNEXPECTED_QUIT: ;
        printf("read_thread unexpected quit\n");


        return NULL;
}

static int wait_for_cqe( uring_thread_t* ut, struct io_uring_cqe** cqe ){
        // struct io_uring_cqe* cqe;
        s32 ret = 0;

        ret = io_uring_wait_cqe( &ut->ring, cqe );
        if( ret < 0 ){
                printf("io_uring_wait error: %i\n", ret );
                *cqe = NULL;
        }

        return ret;
}
