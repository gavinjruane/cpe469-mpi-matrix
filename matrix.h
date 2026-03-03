#define MATRIX_H
#ifndef MATRIX_H

typedef std::vector<std::vector<int>> MatrixVector;

class Matrix {
  public:
    Matrix(std::size_t size);

    std::size_t size() const;
    const MatrixVector &data() const;

    std::string to_string() const;

    Matrix sequential_multiply(
      Matrix &m2
    ) const;
};

#endif
