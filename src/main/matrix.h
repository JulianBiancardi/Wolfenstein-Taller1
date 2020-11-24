#ifndef MATRIX_H
#define MATRIX_H

#include <array>

template <class T, size_t X, size_t Y>
class Matrix {
 private:
  std::array<std::array<T, Y>, X> matrix;

 public:
  Matrix() {}
  explicit Matrix(const T& val) { fill(val); }
  ~Matrix() {}

  size_t sizeX() { return X; }
  size_t sizeY() { return Y; }
  void fill(const T& val) {
    for (size_t i = 0; i < X; ++i) {
      matrix[i].fill(val);
    }
  }
  T& operator()(int x, int y) { return matrix[x][y]; }
};

#endif
