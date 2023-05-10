#include "../utils.h"
#include <stdint.h>

#define ONE_BILLION 1000000000

struct timespec timediff( struct timespec *start, struct timespec *end ){
        struct timespec tm;
        tm.tv_sec  = end->tv_sec  - start->tv_sec;

        if( start->tv_nsec > end->tv_nsec ){
                tm.tv_sec--;
                tm.tv_nsec = start->tv_nsec - end->tv_nsec;

        }else{
                tm.tv_nsec = end->tv_nsec - start->tv_nsec;
        }

        


        return tm;
}
