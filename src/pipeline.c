/*
 * This program is to see the effects of pipeline in the FPU
 */

#define _POSIX_C_SOURCE  199309L
#ifndef TYPE
    #define TYPE   float
#endif
#define OFFSET 0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// A = c*A
double scalarMult(TYPE *A, int c, uintptr_t len, int iterations) 
{
    struct timespec start, end;

    clock_gettime(CLOCK_REALTIME, &start);
    for(int iter=0; iter<iterations; iter++) {
        for(uintptr_t i=0; i<len; i++) {
            A[i] = c * A[i];
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    return (double)(((end.tv_sec*1e9+end.tv_nsec)-(start.tv_sec*1e9+start.tv_nsec))/iterations);
}


//Mem allocator
TYPE * memAllocator(uintptr_t len)
{
    return (TYPE*)malloc(len*sizeof(uintptr_t));
}

//Main
int main(int argc, char *argv[]) 
{
    uintptr_t len  = (uintptr_t)atol(argv[1]);
    int       runs = atoi(argv[2]); 
    TYPE *A = memAllocator(len);
    int c=rand()%10;
    printf("Time taken: %lf nanoseconds\n", scalarMult(A,c,len,runs));
}
