#include <mpi.h>
#include <stdio.h>

int main( int argc, char *argv[]) {
    int rank, msg, size;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank( MPI_COMM_WORLD, &rank ); // gets this process rank
    MPI_Comm_size( MPI_COMM_WORLD, &size ); 
    /* Process 0 sends and Process 1 receives */
    if (rank == 0) {
        msg = 123456;
        MPI_Send( &msg, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        printf( "%d:Send %d\n", rank, msg);
    } // (buf, count, datatype, dest, tag, comm)
    else if (rank == size - 1) {
        MPI_Recv( &msg, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status );
        printf( "%d:Received %d\n", rank, msg);
    }
    else {
        MPI_Recv( &msg, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status );
        printf( "%d:Received %d\n", rank, msg);
        MPI_Send( &msg, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        printf( "%d:Send %d\n", rank, msg);
    }
    MPI_Finalize();
    return 0;
}
