#ifndef SL_H
#define SL_H
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif
#include <stdint.h>
#include <stddef.h>

int slowload(const char* path, uint8_t** buff, void (*hook)(uint8_t* elem) );
int slowload_lh(const char* path, uint8_t** buff, void (*longhook)(uint8_t* elem, size_t len) );

#endif
