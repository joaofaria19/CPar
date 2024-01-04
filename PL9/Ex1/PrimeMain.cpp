#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <mpi.h>

#include"PrimeServer.cpp"

// place number on buf (exclude evens)
void generate(int min, int max, int* buf) {
    int j=0;
    for(int i=min; i<max; i+=2) {
        buf[j++]=i;
    }
}

int main(int argc, char **argv) {

    int rank, n_messages = 10;
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    int nprocesses;
    
    MPI_Comm_size(MPI_COMM_WORLD, &nprocesses);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int MAXP = 1000000; // maximum prime to compute
    int SMAXP = 1000;   // square root of max prime
    // int pack=MAXP/10;   // process "pack" of numbers (subset of #messages)
    
    int pack = MAXP / n_messages;
    int *ar = new int[pack/2];  // alocate space (exclude evens)
    
    if (rank == 0) {
        PrimeServer *ps1 = new PrimeServer();
        ps1->initFilter(1,SMAXP/3,SMAXP);       // first 1/3

        for (int i =0; i<n_messages; i++) {
            generate(i*pack, (i+1)*pack, ar);  // place numbers on ar
            ps1->mprocess(ar,pack/2);  // remove non-primes (1st 1/3)
            MPI_Send(ar, pack/2, MPI_INT, 1, i, MPI_COMM_WORLD);
        }
    }
    else if (rank == 1) {
        PrimeServer *ps2 = new PrimeServer();
        ps2->initFilter(SMAXP/3+1,2*SMAXP/3,SMAXP);     // second 1/3
            
        for (int i =0; i<n_messages; i++) {
            MPI_Recv(ar, pack/2, MPI_INT, 0, i, MPI_COMM_WORLD, &status);
            ps2->mprocess(ar,pack/2);  // remove non-primes (2nd 1/3)
            MPI_Send(ar, pack/2, MPI_INT, 2, i, MPI_COMM_WORLD);
        }
    }
    else if (rank == 2) {
        PrimeServer *ps3 = new PrimeServer();
        ps3->initFilter(2*SMAXP/3+1,SMAXP,SMAXP);       // last 1/3
        
        for (int i =0; i<n_messages; i++) {
            MPI_Recv(ar, pack/2, MPI_INT, 1, i, MPI_COMM_WORLD, &status);
            ps3->mprocess(ar,pack/2);  // remove non-primes (3rd 1/3)
        }
        ps3->end();
      
    }

    MPI_Finalize();
    return(0);
}