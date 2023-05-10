#include <stdio.h>
#include <stdint.h>

#include "src/slowload/slowload.h"
#include "src/uringload/uringload.h"
#include <stdlib.h>


void hook(uint8_t* elem);
void longhook( uint8_t* data, size_t len);

int main(){
        printf("Test\n");
        uint8_t *buff;

        uring_args_t args;
        args.sq_entries = 32;
        // args.block_size = 1024;
        args.block_size = 16;

        uringload( "words.txt", &buff, args ,hook );
        // uringload( "datafile_small", &buff, args ,hook );
        printf("%s\n", (char*)buff);
        free( buff );
}


void hook(uint8_t* elem){
        (*elem)++;
}

void longhook( uint8_t* data, size_t len){
        for( size_t i = 0; i < len; i++){
                data[i]++;
        }
}
