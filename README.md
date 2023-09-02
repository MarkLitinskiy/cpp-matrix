# s21_matrix+
Realization of own version of library for working with matrices s21_matrix.a in c++ language  
Project date: 07-2023

## Project Build

The project is built with the `make` command in the `src` folder, there are the following targets:  
- `s21_math.a` - build the library itself,  
- `test` - start testing,  
- `gcov_report` - view test coverage (the lcov utility is required),  
- `valgrind` - check for leaks with valgrind utility,  
- `leaks` - check for leaks with the leaks utility on Mac OS,  
- `rebuild` - rebuild the project,  
- `style` - check for compliance with clang format,  
- `to_style` - bring style to clang format,  
- `docker_check` - test and check for leaks through docker on ubuntu system,  
- `clean` - clean the project from temporary files.

## Functions for working with matrices

| Operation | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `bool EqMatrix(const S21Matrix& other)` | Checks matrices for equality with each other |  |
| `void SumMatrix(const S21Matrix& other)` | Adds the second matrix to the current one | different matrix dimensions |
| `void SubMatrix(const S21Matrix& other)` | Subtracts another matrix from the current one | different matrix dimensions |
| `void MulNumber(const double num) ` | Multiplies the current matrix by a number |  |
| `void MulMatrix(const S21Matrix& other)` | Multiplies the current matrix by the second matrix | the number of columns of the first matrix is not equal to the number of rows of the second matrix |
| `S21Matrix Transpose()` | Creates a new transposed matrix from the current one and returns it |  |
| `S21Matrix CalcComplements()` | Calculates the algebraic addition matrix of the current one and returns it | the matrix is not square |
| `double Determinant()` | Calculates and returns the determinant of the current matrix | the matrix is not square |
| `S21Matrix InverseMatrix()` | Calculates and returns the inverse matrix | matrix determinant is 0 |


In addition to operations, constructors and destructors are also implemented:

| Method | Description |
| ----------- | ----------- |
| `S21Matrix()` | A basic constructor that initializes a matrix of some predefined dimension |
| `S21Matrix(int rows, int cols)` | Parameterized constructor with number of rows and columns |
| `S21Matrix(const S21Matrix& other)` | Copy constructor |
| `S21Matrix(S21Matrix&& other)` | Transfer constructor |
| `~S21Matrix()` | Destructor |

And the following operators are overloaded, partially corresponding to the operations above:

| Operator | Description | Exceptional Situations |
| ----------- | ----------- | ----------- |
| `+` | adding two matrices | different dimensionality of matrices |
| `-` | Subtracting one matrix from another | different matrix dimension | |
| `*` | Multiplying matrices and multiplying a matrix by a number | the number of columns of the first matrix is not equal to the number of rows of the second matrix | |
| `==` | Checking for matrix equality (`EqMatrix`) | | |
| `=` | Assigning to a matrix the values of another matrix | | |
| `+=` | Assignment of addition (`SumMatrix`) | different matrix dimension | | |
| `-=` | Assignment of difference (`SubMatrix`) | different matrix dimension | |
| `*=` | Multiplication assignment (`MulMatrix`/`MulNumber`) | the number of columns of the first matrix does not equal the number of rows of the second matrix | |
| ``(int i, int j)`` | Index by matrix elements (row, column) | index outside the matrix |


## Description

- The program is developed in C++ language of C++17 standard using gcc compiler
- The program code is located in the src folder
- When writing the code, Google Style is followed
- The matrix is implemented as a class `S21Matrix`.
- Only private fields `matrix_`, `rows_` and `cols_` are stored.
- Access to private fields `rows_` and `cols_` through accessor and mutator is realized. When the size is increased - the matrix is supplemented with zero elements, when the size is decreased - the excess is simply discarded
- The solution is designed as a static library (with header file s21_matrix_oop.h).
- Full coverage of unit-tests of library functions is prepared with the help of GTest library.
- Makefile for building the library and tests (with targets all, clean, test, s21_matrix_oop.a).