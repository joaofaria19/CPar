#include <mpi.h>
#include <stdio.h>

int main( int argc, char *argv[]) {
    int rank, msg, size, i, N=10, rank_sender;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank( MPI_COMM_WORLD, &rank ); // gets this process rank
    MPI_Comm_size( MPI_COMM_WORLD, &size ); 
    /* Process 0 sends and Process 1 receives */
    if (rank == 0) {
        msg = 123456;
        int tasks = 10*size;
        int tasks_send = 0;

        for (i=1; i<size; i++) {
            MPI_Send( &msg, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            tasks_send++;
            printf( "i=%d -> %d:Send %d to %d\n", i, rank, msg, i);
        }

        while (tasks_send < tasks) {
            MPI_Recv( &msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status );
            rank_sender = status.MPI_SOURCE;
            printf( "i=%d -> %d:Received %d from %d\n", i, rank, msg, rank_sender);

            MPI_Send( &msg, 1, MPI_INT, rank_sender, 0, MPI_COMM_WORLD);
            tasks_send++;
            printf( "i=%d -> %d:Send %d to %d\n", i, rank, msg, rank_sender);

            i++;
        }

        for (i=1; i<size; i++) {
            MPI_Send( &msg, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
            tasks_send++;
            printf( "i=%d -> %d:Send %d to %d\n", i, rank, msg, i);
        }

    } // (buf, count, datatype, dest, tag, comm)
    else {
        int tag;

        while (1) {
            MPI_Recv( &msg, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
            printf( "%d:Received %d\n", rank, msg);

            tag = status.MPI_TAG;
            printf( "%d:Tag = %d\n", rank, tag);

            if (tag == 1) {
                printf("Break; rank = %d\n", rank);
                break;
            }

            msg = rank;

            MPI_Send( &msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            printf( "%d:Send %d\n", rank, msg);
        }
    }
    MPI_Finalize();
    return 0;
}
