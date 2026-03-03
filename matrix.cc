#include <cstdlib>
#include <random>
#include <string>
#include <vector>

#include "matrix.h"

class Matrix {
  public:
    explicit Matrix(std::size_t size)
      : size_(size),
        matrix_(random_matrix(size_)) {}

    std::size_t size() const { return size_; }
    const MatrixVector &data() const { return matrix_; }

    std::string to_string() const {
      std::string out = "[\n";
      for (int r = 0; r < size_; r++) {
        out += "[";
        for (int c = 0; c < size_; c++) {
          if (c <= size_ - 2) {
            out += std::to_string(matrix_[r][c]) + ", ";
          } else {
            out += std::to_string(matrix_[r][c]);
          }
        }
        out += "]\n";
      }
      out += "]\n";

      return out;
    }

    Matrix sequential_multiply(
      Matrix &m2
    ) const {
      Matrix result(this->size());

      for (int r = 0; r < size(); r++) {
        for (int c = 0; c < size(); c++) {
          result.matrix_[r][c] = dot_product(size(), matrix_[r], m2.column_at(c));
        }
      }

      return result;
    }

  private:
    std::size_t size_;
    std::vector<std::vector<int>> matrix_;

    MatrixVector empty_matrix(std::size_t size) {
      MatrixVector m(size, std::vector<int>(size, 0));

      return m;
    }

    std::vector<int> column_at(
      int column
    ) const {
      std::vector<int> colvec(size(), 0);

      for (int i = 0; i < size(); i++) {
        colvec[i] = matrix_[i][column];
      }

      return colvec;
    }

    int dot_product(
      std::size_t size,
      std::vector<int> v1,
      std::vector<int> v2
    ) const {
      int result = 0;

      for (int i = 0; i < size; i++) {
        result += v1[i] * v2[i];
      }

      return result;
    }

    MatrixVector random_matrix(std::size_t size) {
      MatrixVector m(size, std::vector<int>(size, 0));

      std::random_device rd;
      std::mt19937 gen(rd());
      std::uniform_int_distribution<int> dist(0, 1000);
    
      for (int r = 0; r < size; r++) {
        for (int c = 0; c < size; c++) {
          m[r][c] = dist(gen);
        }
      }

      return m;
    }
};

