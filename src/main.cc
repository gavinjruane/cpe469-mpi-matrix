#include <iostream>
#include <cstdlib>

#include "matrix.h"

int main () {
  Matrix matrix1{2};
  Matrix matrix2{2};

  std::cout << matrix1.to_string();
  std::cout << matrix2.to_string();

  Matrix result_matrix = matrix1.sequential_multiply(matrix2);
  std::cout << result_matrix.to_string();
  
  return 0;
}
