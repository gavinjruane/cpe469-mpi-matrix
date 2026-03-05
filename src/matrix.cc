#include <cstdlib>
#include <random>
#include <string>
#include <vector>
#include <iostream>

#include "matrix.hpp"
#include <mpi.h>

Matrix::Matrix(std::size_t size, bool randomize)
  : size_(size),
    matrix_(empty_matrix(size)) {
      if (randomize) {
        fill_random();
      }
    }

std::size_t Matrix::size() const { return size_; }
int *Matrix::data() { return matrix_.data(); }
const int *Matrix::data() const { return matrix_.data(); }

std::string Matrix::to_string() const {
  std::string out = "[\n";
  for (int r = 0; r < size_; r++) {
    out += "[";
    for (int c = 0; c < size_; c++) {
      if (c <= size_ - 2) {
        out += std::to_string(value_at(r, c)) + ", ";
      } else {
        out += std::to_string(value_at(r, c));
      }
    }
    out += "]\n";
  }
  out += "]\n";

  return out;
}

int Matrix::value_at(
  int row,
  int col
) const {
  return matrix_[row * size() + col];
}

void Matrix::set(
  int row,
  int col,
  int value
) {
  matrix_[row * size() + col] = value;
}

Matrix Matrix::sequential_multiply(
  const Matrix &m2
) const {
  Matrix result(this->size(), false);

  for (int r = 0; r < size(); r++) {
    for (int c = 0; c < size(); c++) {
      int sum = 0;
      for (int i = 0; i < size(); i++) {
        sum += value_at(r, i) * m2.value_at(i, c);
      }

      result.set(r, c, sum);
    }
  }

  return result;
}

Matrix Matrix::MPI_multiply(
  const Matrix &m2,
  MPIArguments arguments
) const {
  int numprocs = arguments.numprocs;
  int rank = arguments.rank;

  int rows = N / numprocs;
  std::vector<int> loc_a(rows * N);
  std::vector<int> loc_c(rows * N);
  Matrix b_copy = (rank == 0) ? m2 : Matrix{N, false};

  MPI_Scatter((rank == 0) ? const_cast<int *>(data()) : nullptr, rows * N, MPI_INT, loc_a.data(), rows * N, MPI_INT, 0, MPI_COMM_WORLD);
  std::cout << "rank " << rank << " loc_a[0] = " << loc_a[0] << std::endl;
  MPI_Bcast(b_copy.data(), N * N, MPI_INT, 0, MPI_COMM_WORLD);

  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < N; c++) {
      int sum = 0;

      for (int i = 0; i < N; i++) {
        sum += loc_a[r * N + i] * b_copy.value_at(i, c);
      }

      loc_c[r * N + c] = sum;
    }
  }
  std::cout << "rank " << rank << " loc_c[0] = " << loc_c[0] << std::endl;

  Matrix result{N, false};
  MPI_Gather(loc_c.data(), rows * N, MPI_INT, (rank == 0) ? result.data() : nullptr, rows * N, MPI_INT, 0, MPI_COMM_WORLD);

  return result;
}

Matrix::MatrixVector Matrix::empty_matrix(
  std::size_t size
) {
  Matrix::MatrixVector m(size * size, 0);

  return m;
}

void Matrix::fill_random() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dist(0, 1000);

  for (int r = 0; r < size(); r++) {
    for (int c = 0; c < size(); c++) {
      matrix_[r * size() + c] = dist(gen);
    }
  }
}
