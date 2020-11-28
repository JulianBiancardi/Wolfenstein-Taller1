#ifndef MATRIX_H
#define MATRIX_H

#include <algorithm>
#include <vector>

template <class T>
class Matrix {
 private:
  std::vector<std::vector<T>> matrix;
  size_t rows;
  size_t columns;

 public:
  Matrix(size_t rows, size_t columns) : rows(rows), columns(columns) {
    matrix.resize(columns, std::vector<T>(rows));
  }

  explicit Matrix(size_t rows, size_t columns, const T& val)
      : rows(rows), columns(columns) {
    matrix.resize(columns, std::vector<T>(rows));
    fill(val);
  }

  ~Matrix() {}

  /* Returns the amount of rows in the matrix. */
  size_t get_rows() { return rows; }

  /* Returns the amount of columns in the matrix. */
  size_t get_columns() { return columns; }

  /* Fills the entire matrix with the value given. */
  void fill(const T& val) {
    for (size_t i = 0; i < columns; ++i) {
      std::fill(matrix[i].begin(), matrix[i].end(), val);
    }
  }

  /* Return the element in the position x,y. */
  T& operator()(int x, int y) { return matrix[x][y]; }
};

#endif
