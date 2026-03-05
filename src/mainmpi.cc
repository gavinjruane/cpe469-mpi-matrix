#include <cstdio>
#include <cstdlib>
#include <cstring>

// #include "matrix.hpp"
#include "matrix.hpp"
#include "mpi.h"

int main (int argc, char *argv[]) {
  int numprocs = 0, rank = 0;
  
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  MPIArguments arguments{rank, numprocs};

  Matrix a{N, false};
  Matrix b{N, false};

  if (rank == 0) {
    a = Matrix{N, true};
    b = Matrix{N, true};
  }

  Matrix c = a.MPI_multiply(b, arguments);

  MPI_Finalize();

  return 0;
}

void sample_mpi (
  MPIArguments arguments
) {
  int numprocs = arguments.numprocs;
  int rank = arguments.rank;
  int chunk_size = arguments.chunk_size;
  
  std::printf("Hello from process %d of %d!\n", rank, numprocs);

  chunk_size = 800 / numprocs;

  char greeting[100];
  if (rank != 0) {
    std::snprintf(greeting, 50, "Greetings from process %d of %d!", rank, numprocs);
    MPI_Send(greeting, std::strlen(greeting) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  } else {
    std::printf("Greetings from process %d of %d!\n", rank, numprocs);
    for (int q = 1; q < numprocs; q++) {
      MPI_Recv(greeting, 100, MPI_CHAR, q, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      std::printf("%s\n", greeting);
    }
  }
}
