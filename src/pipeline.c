/*
 * This program is to see the effects of pipeline in the FPU
 */

#define _POSIX_C_SOURCE  199309L
#ifndef TYPE
    #define TYPE   float
#endif
#ifndef OFFSET
    #define OFFSET 3
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// A = c*A
double scalarMult(TYPE *A, int c, uintptr_t len, long int iterations) 
{
    struct timespec start, end;

    clock_gettime(CLOCK_REALTIME, &start);
    for(int iter=0; iter<iterations; iter++) {
        for(uintptr_t i=OFFSET; i<len+OFFSET; i++) {
            A[i] = c * A[i-OFFSET];
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
    uintptr_t maxlen   = (uintptr_t)atol(argv[1]);
    long int  stepSize = atoi(argv[2]);
    long int  runs;
    double    totalTime=0.0d;

    for(uintptr_t len=10; len<maxlen; len+=stepSize) {
        runs=100*900000/len;
        TYPE *A = memAllocator(len+OFFSET);
        int c   = rand()%10;
        totalTime = scalarMult(A,c,len,runs);
        printf("%ld , %lf , %lf\n", (long int)len, totalTime, totalTime/len);
        free(A);
    }
}
