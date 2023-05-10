#ifndef UL_H
#define UL_H
// #define _POSIX_C_SOURCE 199309L
# define _POSIX_C_SOURCE 200809L
#include "src/types.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <liburing.h>

typedef struct uring_args_t{
        int sq_entries;
        int block_size;
}uring_args_t;

typedef struct uring_t{
        int block_size;
}uring_t;

typedef struct filestats_t{
        FILE* fp;
        s32 fno;

        size_t file_size;
        size_t block_size;
        size_t block_count;
        size_t last_block_size;
}filestats_t;

int uringload(const char* path, uint8_t** buff, uring_args_t args, void (*hook)(uint8_t* elem) );

int ur_open_file( filestats_t* fs, const char *path ,int blocksize );
void ur_print_filestat( filestats_t* fs );

#endif
