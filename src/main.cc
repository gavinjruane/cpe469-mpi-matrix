#include <iostream>
#include <cstdlib>

#include "matrix.hpp"

int main () {
  Matrix matrix1{2, true};
  Matrix matrix2{2, true};

  std::cout << matrix1.to_string();
  std::cout << matrix2.to_string();

  Matrix result_matrix = matrix1.sequential_multiply(matrix2);
  std::cout << result_matrix.to_string();
  
  return 0;
}
