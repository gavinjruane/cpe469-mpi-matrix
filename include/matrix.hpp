#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <string>
#include <vector>

#define N 5

struct MPIArguments {
  int rank;
  int numprocs;
};

class Matrix {
  public:
    using MatrixVector = std::vector<int>;
  
    Matrix(std::size_t size, bool randomize);

    std::size_t size() const;
    const MatrixVector &data() const;

    std::string to_string() const;

    int value_at(int row, int col) const;

    void set(int row, int col, int value);

    Matrix sequential_multiply(
      const Matrix &m2
    ) const;

    Matrix MPI_multiply(
      const Matrix &m2,
      MPIArguments arguments
    ) const;

  private:
    std::size_t size_;
    std::vector<int> matrix_;

    MatrixVector empty_matrix(
      std::size_t size
    );

    void fill_random();
};

#endif
