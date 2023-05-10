#include "../uringload.h"
#include "../../utils/utils.h"
#include "uring_thread.h"
#include "types.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <inttypes.h>
#include <liburing.h>

// struct timer{
//         struct timespec start, end;
// };

// typedef struct uring_args_t{
//         u64 *udata;
//         struct timer timers;
// }uring_args_t;

#define TEST_QUEUE_INIT(retval)\
do{\
        if( retval != 0 ){\
                printf("io_uring_queue_init fail. %i\n", retval );\
                return 0;\
        }\
}while(0);\

// void seq_udata(uring_args_t* uargs, int len);
// void set_timer(uring_args_t* uargs);
// void start_timer(uring_args_t* uargs);
// void stop_timer(uring_args_t* uargs);
// struct timespec uargs_get_diff(uring_args_t* uargs);
// void uargs_print_time(uring_args_t* uargs);

size_t get_file_len( FILE* fp );


int ur_open_file( filestats_t* fs, const char *path, int blocksize ){
        FILE *fp = fopen( path, "r" );
        if( fp == NULL ){
                printf("File open fail:\n%s\n", path);
                return -1;
        }

        fs->fp = fp;
        fs->fno = fileno( fp );

        size_t flen = get_file_len( fp );

        fs->file_size = flen;
        fs->block_size = blocksize;
        fs->block_count = flen/blocksize;
        fs->last_block_size = flen % blocksize;

        if( fs->last_block_size != 0 ){ //amount of indices, a partial block still needs alloc
                fs->block_count++;
        }

        return 0;
}

void ur_print_filestat( filestats_t* fs ){
        printf("fno: %"PRId32"\n", fs->fno );
        printf("file_size: %"PRIu64"\n", fs->file_size );
        printf("block_size: %"PRIu64"\n", fs->block_size );
        printf("block_count: %"PRIu64"\n", fs->block_count );
        printf("last_block_size: %"PRIu64"\n", fs->last_block_size );
}


int uringload(const char* path, uint8_t** buff, uring_args_t args, void (*hook)(uint8_t* elem) ){
        uring_thread_t _ut;
        uring_thread_t *ut = &_ut;
        s32 ret = 0;

        ur_open_file( &ut->fs, path, args.block_size);
        ur_print_filestat( &ut->fs );

        ret = io_uring_queue_init(
                args.sq_entries,
                &ut->ring,
                0
        );
        TEST_QUEUE_INIT(ret);

        ut->setup_args = args;
        *buff = (u8*)malloc( ut->fs.file_size );
        ut->buff = (*buff);

        // printf("Len: %lu\n", ut->fs.

        ut_init( ut );

        ut_fini( ut );




        


        return 1;
}

// void seq_udata(uring_args_t* uargs, int len){
//         size_t size;
//         size = len * sizeof(u64);
//         uargs->udata = (u64*)malloc( size );

//         for(int i = 0; i < len; i++){
//                 uargs->udata[i] = i;
//         }

// }

// void set_timer(uring_args_t* uargs){
//         memset( &uargs->timers, 0, sizeof( struct timer ) );
// }
// void start_timer(uring_args_t* uargs){
//         clock_gettime( CLOCK_REALTIME, &uargs->timers.start );
// }
// void stop_timer(uring_args_t* uargs){
//         clock_gettime( CLOCK_REALTIME, &uargs->timers.end );
// }
// struct timespec uargs_get_diff(uring_args_t* uargs){
//         return timediff( &uargs->timers.start, &uargs->timers.end );  
// }

size_t get_file_len( FILE* fp ){
        size_t filelen = 0;
        fseek( fp, 0, SEEK_END );
        filelen = ftell( fp );
        rewind( fp );

        return filelen;
}

// void uargs_print_time(uring_args_t* uargs){
//         struct timespec tm_diff = uargs_get_diff( uargs );
//         printf("Seconds: %lu\n", tm_diff.tv_sec );
//         printf("Nsec  : %lu\n", tm_diff.tv_nsec );
// }
