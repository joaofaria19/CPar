#include<stdio.h>
#include<stdlib.h>

#ifndef size
#define size 128
#endif

#define T 8

double *A, *B, *C;

void alloc() {
    A = (double *) malloc(size*size*sizeof(double));
    B = (double *) malloc(size*size*sizeof(double));
    C = (double *) malloc(size*size*sizeof(double));
}

void init() {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            A[i*size+j] = rand();
            B[i*size+j] = rand();
        }
    }
}

void mmult() {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            C[i*size+j] = 0;
            for(int k=0; k<size; k++) {
                // C[i*size+j] += A[i*size+k] * B[k*size+j];
                C[i*size+j] += A[i*size+k] * B[j*size+k]; // transposta de B
            }
        }
    }
}

void mmult2() {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j+=4) {
            C[i*size+j] = 0;
            for(int k=0; k<size; k+=4) {
                C[i*size+j] += A[i*size+k] * B[k*size+j];
                C[i*size+j+1] += A[i*size+k+1] * B[(k+1)*size+j];
                C[i*size+j+2] += A[i*size+k+2] * B[(k+2)*size+j];
                C[i*size+j+3] += A[i*size+k+3] * B[(k+3)*size+j];
            }
        }
    }
}


void Tmmult() {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            C[i*size+j] = 0;
            for(int k=0; k<size; k++) {
                C[i*size+j] += A[i*size+k] * B[j*size+k]; // transposta de B
            }
        }
    }
}



int main() {
    alloc();
    init();
    mmult2();
    printf("%f\n", C[size/2+5]);
}
