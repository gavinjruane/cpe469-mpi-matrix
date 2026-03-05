# cpe469-mpi-matrix
Matrix Multiplication with MPI &bullet; Gavin Ruane &bullet; CPE 469-01

## Running & Compiling
To run the sequential matrix multiplication, run the following make rule: `make matrixseq`. You can then run `./matrixseq` at the shell prompt.

To run the MPI matrix multiplication, run the following make rule: `make matrixmpi`. You can then use a job script or `mpiexec` to run it.

By default, the size of the matrices is 64&times;64, and this value is set in the `matrix.hpp` file in the `include/` directory. You can change this to another value if you would like.

Note that the source files and Makefile are setup to be compiled on the SDSC supercomputer currently. If you wish to compile the sequential version on your local machine, you will need to change the `CC` and `LD` variables in the Makefile to `clang` or `gcc`. (It is probably just easier to compile on the SDSC supercomputer!)

## Runtime Comparisons
The following tests were performed on square matrices of size 64&times;64

| Program | 0 Nodes | 2 Nodes | 4 Nodes |
|:----|:---:|:--:|:--:|
| Sequential | 0.071s | - | - |
| MPI | 0.203s | 0.00497s | 0.00462s |