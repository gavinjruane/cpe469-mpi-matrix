#include <cstdio>
#include <cstdlib>
#include <cstring>

// #include "matrix.hpp"
#include "mpi.h"

int main (int argc, char *argv[]) {
  int numprocs, rank, chunk_size;
  
  MPI_Init(NULL, NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

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

  MPI_Finalize();

  return 0;
}
