#ifndef MATRIX_H
#define MATRIX_H

#include <cstdlib>
#include <string>
#include <vector>


class Matrix {
  public:
    using MatrixVector = std::vector<std::vector<int>>;
  
    Matrix(std::size_t size);

    std::size_t size() const;
    const MatrixVector &data() const;

    std::string to_string() const;

    Matrix sequential_multiply(
      Matrix &m2
    ) const;

  private:
    std::size_t size_;
    std::vector<std::vector<int>> matrix_;

    MatrixVector empty_matrix(
      std::size_t size
    );

    std::vector<int> column_at(
      int column
    ) const;
    
    int dot_product(
      std::size_t size,
      std::vector<int> v1,
      std::vector<int> v2
    ) const;

    MatrixVector random_matrix(std::size_t size);
};

#endif
