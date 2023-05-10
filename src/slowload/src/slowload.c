#include "../slowload.h"
#include "../../utils/utils.h"
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#include <time.h>
// #include <sys/time.h>

int slowload(const char* path, uint8_t** buff, void (*hook)(uint8_t* elem) ){
        if( access( path, R_OK ) != 0 ){
                printf("slowload path not valid\n");
                return 0;
        }

        size_t filelen;

        FILE *fp = fopen( path, "r" );

        fseek( fp, 0, SEEK_END );
        filelen = ftell( fp );
        rewind( fp );

        struct timespec tm_start, tm_end;
        memset( &tm_start, 0, sizeof( struct timespec ) );
        memset( &tm_end, 0, sizeof( struct timespec ) );
        clock_gettime( CLOCK_REALTIME, &tm_start );

        // struct timespec waittime;
        // waittime.tv_sec = 0;
        // waittime.tv_nsec = 235000000;
        // nanosleep( &waittime, NULL );


        (*buff) = (uint8_t*)malloc( filelen );

        fread(  
                (*buff),        /* Dest */
                sizeof(uint8_t),/* elem size */
                filelen,        /* elem count */
                fp              /* file stream */
        );


        for( size_t i = 0; i < filelen; i++){
                hook( &(*buff)[i] );
        }
        







        clock_gettime( CLOCK_REALTIME, &tm_end );

        fclose( fp );

        printf("Filelen: %ld\n", filelen );
        struct timespec tm_diff = timediff( &tm_start, &tm_end );
        printf("Seconds: %lu\n", tm_diff.tv_sec );
        printf("Nsec  : %lu\n", tm_diff.tv_nsec );
        // printf("Milli  : %lu\n", (tm_end.tv_nsec - tm_start.tv_nsec)/1000 );


        return 1;
}


int slowload_lh(const char* path, uint8_t** buff, void (*longhook)(uint8_t* elem, size_t len) ){
        if( access( path, R_OK ) != 0 ){
                printf("slowload path not valid\n");
                return 0;
        }

        size_t filelen;

        FILE *fp = fopen( path, "r" );

        fseek( fp, 0, SEEK_END );
        filelen = ftell( fp );
        rewind( fp );

        struct timespec tm_start, tm_end;
        memset( &tm_start, 0, sizeof( struct timespec ) );
        memset( &tm_end, 0, sizeof( struct timespec ) );
        clock_gettime( CLOCK_REALTIME, &tm_start );

        // struct timespec waittime;
        // waittime.tv_sec = 0;
        // waittime.tv_nsec = 235000000;
        // nanosleep( &waittime, NULL );


        (*buff) = (uint8_t*)malloc( filelen );

        fread(  
                (*buff),        /* Dest */
                sizeof(uint8_t),/* elem size */
                filelen,        /* elem count */
                fp              /* file stream */
        );


        longhook( (*buff), filelen );
        







        clock_gettime( CLOCK_REALTIME, &tm_end );

        fclose( fp );

        printf("Filelen: %ld\n", filelen );
        struct timespec tm_diff = timediff( &tm_start, &tm_end );
        printf("Seconds: %lu\n", tm_diff.tv_sec );
        printf("Nsec  : %lu\n", tm_diff.tv_nsec );
        // printf("Milli  : %lu\n", (tm_end.tv_nsec - tm_start.tv_nsec)/1000 );


        return 1;
}
