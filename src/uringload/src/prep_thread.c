#include "uring_thread.h"
#include "prep_thread.h"
#include <liburing.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

static u64 generate_user_data( uring_thread_t* ut );

void *ut_prep_thread(void *args)
{
        uring_thread_t *ut = (uring_thread_t *)args;
        prep_stats_t *ps = &ut->ps;

        size_t block_size = 0;
        block_size = ut->file_stats.block_size;

        while (ps->read_offset < ut->file_stats.block_count)
        {
                u8* buff_offset;
                // If we're on the last block, remember, this is a partial filled block
                if (ps->read_offset == ut->file_stats.block_count){
                        block_size = ut->file_stats.last_block_size;
                }

                //Generate data for the read
                off_t offset = ps->read_offset * block_size;
                buff_offset = &(ut->buff[offset]);

                u64 user_data = generate_user_data( ut );
                printf("user data: %lu\n", user_data);


                struct io_uring_sqe *sqe = io_uring_get_sqe(&ut->ring);


                io_uring_prep_read(
                    sqe,
                    ut->file_stats.fno,
                    (void *)buff_offset,
                    block_size,
                    offset);
                io_uring_sqe_set_data(sqe, (void*)(u64)ps->read_offset);
                

                s32 ret = 0;
                ret = io_uring_submit(&ut->ring);
                if (ret < 0)
                {
                        printf("io_uring_submit error: %d\n", ret);
                        ut->join_now = 1;
                }

                ps->read_offset++;

                if (ut->join_now)
                {
                        goto UNEXPECTED_QUIT;
                }
        }

        

        printf("\e[32mprep_thread success\e[0m\n");
        printf("%lu\n", generate_user_data( ut ) );
        printf("Filesize: %lu\n", ut->file_stats.file_size);

        return NULL;

UNEXPECTED_QUIT:;
        printf("\e[91mPrep thread unexpected quit\e[0m\n");
        printf("Read_offset: %" PRId32 "\n", ps->read_offset);
        printf("Filesize: %lu\n", ut->file_stats.file_size);

        return NULL;
}

static u64 generate_user_data( uring_thread_t* ut ){
        u64 user_data = 0;
        user_data = ut->ps.read_offset;
        

        return user_data;
}
