#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

// #include "matrix.hpp"
#include "matrix.hpp"
#include <mpi.h>

int main (int argc, char *argv[]) {
  int numprocs = 0, rank = 0;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

  double start_time = MPI_Wtime();

  MPIArguments arguments{rank, numprocs};

  if (rank == 0) {
	  std::cout << numprocs << std::endl;
  }

  Matrix a{N, false};
  Matrix b{N, false};

  if (rank == 0) {
    a = Matrix{N, true};
    std::cout << "Matrix A" << std::endl;
    std::cout << a.to_string() << std::endl;
    b = Matrix{N, true};
    std::cout << "Matrix B" << std::endl;
    std::cout << b.to_string() << std::endl;
  }

  Matrix c = a.MPI_multiply(b, arguments);
  if (rank == 0) {
    std::cout << c.to_string() << std::endl;
  }

  double end_time = MPI_Wtime();

  double time = end_time - start_time;
  std::cout << "Time: " << time << std::endl;

  MPI_Finalize();

  return 0;
}

void sample_mpi (
  MPIArguments arguments
) {
  int numprocs = arguments.numprocs;
  int rank = arguments.rank;

  std::printf("Hello from process %d of %d!\n", rank, numprocs);

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
