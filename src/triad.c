
/*
 * This is the triad program for benchmarking. Just interesting to see what happens
 */

#define _POSIX_C_SOURCE  199309L
#ifndef TYPE
    #define TYPE int
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>


double triad(TYPE *A, TYPE *B, TYPE *C, TYPE *D, uintptr_t len, int runs)
{
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME,&start);
    for(int count=0; count<runs; count++)
    {
        for(uintptr_t i=0; i<len; i++)
        {
            A[i]=B[i]+C[i]*D[i];
        }
    }
    clock_gettime(CLOCK_REALTIME,&end);
    double delta=(end.tv_sec*1e9+end.tv_nsec)-(start.tv_sec*1e9+start.tv_nsec);
    return delta/runs;
}


TYPE* allocateMem(uintptr_t len)
{
    return (TYPE*)malloc(len*sizeof(TYPE));
}


int main(int argc, char *argv[])
{
    uintptr_t len  = (uintptr_t)(atol(argv[1]));
    int       runs = atoi(argv[2]);

    TYPE *A=allocateMem(len);
    TYPE *B=allocateMem(len);
    TYPE *C=allocateMem(len);
    TYPE *D=allocateMem(len);

    double time=triad(A,B,C,D,len,runs);

    printf("Time taken: %lf nanoseconds\n",time);

    return 0;
}
