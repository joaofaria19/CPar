#include <mpi.h>
#include <stdio.h>

int main( int argc, char *argv[]) {
    int rank, msg, size, i, N=10;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank( MPI_COMM_WORLD, &rank ); // gets this process rank
    MPI_Comm_size( MPI_COMM_WORLD, &size ); 
    /* Process 0 sends and Process 1 receives */
    if (rank == 0) {
        msg = 123456;
        for (i=1; i<size; i++) {
            MPI_Send( &msg, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf( "i=%d -> %d:Send %d\n", i, rank, msg);
        }

        for (i=1; i<size; i++) {
            MPI_Recv( &msg, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status );
            printf( "i=%d -> %d:Received %d\n", i, rank, msg);
        }
    } // (buf, count, datatype, dest, tag, comm)
    else {
        MPI_Recv( &msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status );
        printf( "%d:Received %d\n", rank, msg);
        msg = rank;
        MPI_Send( &msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf( "%d:Send %d\n", rank, msg);
    }
    MPI_Finalize();
    return 0;
}
