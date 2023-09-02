#include "s21_matrix_oop.h"

#include <math.h>

#include <iostream>

/// @brief Стандарный конструктор (создаёт нулевую матрицу)
S21Matrix::S21Matrix() noexcept { CreateNullMatrix(); }

/// @brief Конструктор с параметрами размера матрицы
/// @param rows Входящее число строк
/// @param cols Входящее число колонок
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 0 || cols < 0)
    CreateNullMatrix();
  else {
    AlocateMem(rows, cols);
  }
}

/// @brief Конструктор копирования - создаёт новый объект через конструктор с
/// параметрами и копирует значения атрибутов из объекта other
/// @param other объект, из которого копируются атрибуты
S21Matrix::S21Matrix(const S21Matrix &other) {
  AlocateMem(other.rows_, other.cols_);
  CopyMatrixData(other);
}

/// @brief Конструктор перемещения - копирует данные в новый объект и удаляет в
/// старом. Через swap меняются местами указатели у атрибутов
/// @param other объект, из которого перемещаются атрибуты
S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(0), cols_(0), matrix_(nullptr) {
  std::swap(other.cols_, cols_);
  std::swap(other.rows_, rows_);
  std::swap(other.matrix_, matrix_);
}

/// @brief Деструктор - очищает двумерный массив matrix_ и обнуляет
/// атрибуты
S21Matrix::~S21Matrix() {
  DeleteMem();
  rows_ = 0;
  cols_ = 0;
}

// геттеры и сеттеры
/* В SetRows и SetCols реализуется алгоритм: если число строк/столбцов
увеличивается, в качестве новых элементов ставятся нули, если уменьшается, то
матрица урезается */

void S21Matrix::SetRows(int numb) {
  if (numb < 0)
    throw std::length_error("число строк не может быть отрицательным");

  if (rows_ != numb) {
    S21Matrix temp = S21Matrix(numb, cols_);
    for (int i = 0; i < temp.rows_; ++i) {
      for (int j = 0; j < temp.cols_; ++j) {
        if (i < rows_) temp(i, j) = matrix_[i][j];
      }
    }
    DeleteMem();
    AlocateMem(temp.rows_, temp.cols_);
    CopyMatrixData(temp);
  }
}

void S21Matrix::SetCols(int numb) {
  if (numb < 0)
    throw std::length_error("число столбцов не может быть отрицательным");

  if (cols_ != numb) {
    S21Matrix temp = S21Matrix(rows_, numb);
    for (int i = 0; i < temp.rows_; ++i) {
      for (int j = 0; j < temp.cols_; ++j) {
        if (j < cols_) temp(i, j) = matrix_[i][j];
      }
    }
    DeleteMem();
    AlocateMem(temp.rows_, temp.cols_);
    CopyMatrixData(temp);
  }
}
/// @brief Метод изменяет значение конкретного элемента матрицы
/// @param numb значение
/// @param row номер строки
/// @param col номер столбца
void S21Matrix::SetMatrix(int numb, int row, int col) {
  if (row < 0 || col < 0)
    throw std::length_error(
        "число столбцов и строк не может быть отрицательным");
  matrix_[row][col] = numb;
}
int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }
double S21Matrix::GetMatrix(int row, int col) const {
  return matrix_[row][col];
}

/// @brief Создание пустой матрицы
void S21Matrix::CreateNullMatrix() noexcept {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

/// @brief Функция выделения памяти для массива матрицы и заполнения её нулями
/// через()
/// @param other_rows число строк
/// @param other_cols число столбцов
void S21Matrix::AlocateMem(int other_rows, int other_cols) noexcept {
  rows_ = other_rows;
  cols_ = other_cols;
  matrix_ = new double *[rows_];

  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}

/// @brief Очистка памяти матрицы и установка значений указателей nullptr
void S21Matrix::DeleteMem() noexcept {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      if (matrix_[i] != nullptr) delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  int result = true;
  CheckMatrix(*this);
  CheckMatrix(other);
  if (rows_ == other.rows_ && cols_ == other.cols_ && matrix_ != nullptr) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if ((int)(matrix_[i][j] * pow(10, 7)) !=
            (int)(other(i, j) * pow(10, 7))) {
          result = false;
        }
      }
    }
  } else {
    result = false;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::length_error("Разная размерность матриц");
  CheckMatrix(*this);
  CheckMatrix(other);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (cols_ != other.cols_ || rows_ != other.rows_)
    throw std::length_error("Разная размерность матриц");
  CheckMatrix(*this);
  CheckMatrix(other);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  CheckMatrix(*this);
  if (num == INFINITY || num == NAN)
    throw std::length_error("Недопустимое число");

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_)
    throw std::length_error(
        "число столбцов первой матрицы не равно числу строк второй матрицы");
  CheckMatrix(*this);
  CheckMatrix(other);

  S21Matrix temp = S21Matrix(rows_, other.cols_);
  for (int i = 0; i < temp.rows_; ++i) {
    for (int j = 0; j < temp.cols_; ++j) {
      for (int k = 0; k < cols_; k++) {
        temp(i, j) += (matrix_[i][k] * other(k, j));
      }
    }
  }
  *this = temp;
}

/// @brief Транспонирование матрица (создаётся новая)
S21Matrix S21Matrix::Transpose() {
  CheckMatrix(*this);

  S21Matrix result_matrix = S21Matrix(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result_matrix(j, i) = matrix_[i][j];
    }
  }
  return result_matrix;
}

double S21Matrix::Determinant() {
  if (cols_ != rows_) throw std::length_error("матрица не является квадратной");
  CheckMatrix(*this);

  double result = 0;
  CheckDet(&result);
  return result;
}

S21Matrix S21Matrix::CalcComplements() {
  if (cols_ != rows_) throw std::length_error("матрица не является квадратной");
  CheckMatrix(*this);

  double min = 0;
  S21Matrix result_matrix = S21Matrix(rows_, cols_);
  if (cols_ == 1) {
    result_matrix(0, 0) = matrix_[0][0];
  } else {
    S21Matrix current_matrix = S21Matrix(cols_ - 1, rows_ - 1);
    for (int i = 0; i < result_matrix.rows_; ++i) {
      for (int j = 0; j < result_matrix.cols_; ++j) {
        min = 0;
        Minorchik(&current_matrix, j, i);
        current_matrix.CheckDet(&min);
        result_matrix(i, j) = min * pow(-1, i + j);
      }
    }
  }
  return result_matrix;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (abs(det) < kzero) throw std::length_error("определитель матрицы равен 0");
  CheckMatrix(*this);
  S21Matrix result_matrix;

  if (cols_ == 1) {
    result_matrix = S21Matrix(cols_, rows_);
    result_matrix(0, 0) = 1.0 / matrix_[0][0];
  } else {
    result_matrix = CalcComplements().Transpose();
    for (int i = 0; i < result_matrix.rows_; ++i) {
      for (int j = 0; j < result_matrix.cols_; ++j) {
        result_matrix(i, j) *= (1 / det);
      }
    }
  }
  return result_matrix;
}

// Перерузка операторов
/* Перегруженные операторы возвращают ссылки, чтобы реализовать возможность
работы более чем с двумя переменными в одной команде. Например, a = b = c;  // b
= c; a = b; */

/// @brief Перегруженный оператор присваивания, реализованный как конструктор
/// копирования
S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    DeleteMem();
    AlocateMem(other.rows_, other.cols_);
    CopyMatrixData(other);
  }
  return *this;
}

/// @brief Перегруженный оператор присваивания, реализованный как конструктор
/// перемещения
S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    DeleteMem();
    std::swap(cols_, other.cols_);
    std::swap(rows_, other.rows_);
    std::swap(matrix_, other.matrix_);
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix sum = S21Matrix(*this);
  sum.SumMatrix(other);
  return sum;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix sub = S21Matrix(*this);
  sub.SubMatrix(other);
  return sub;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix mult = S21Matrix(*this);
  mult.MulMatrix(other);
  return mult;
}

/// @brief Оператор умножения вида result = numb * matrix;
S21Matrix operator*(double numb, const S21Matrix &other) {
  S21Matrix mult = S21Matrix(other);
  mult.MulNumber(numb);
  return mult;
}

/// @brief Оператор умножения вида result = matrix * numb;
S21Matrix operator*(const S21Matrix &other, double numb) {
  S21Matrix mult = S21Matrix(other);
  mult.MulNumber(numb);
  return mult;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double numb) {
  MulNumber(numb);
  return *this;
}

// Перегрузка оператора индексации для чтения элемента (когда const)
double S21Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
    throw std::length_error("индекс за пределами матрицы");

  return matrix_[i][j];
}

// Перегрузка оператора индексации для записи элемента
double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_)
    throw std::length_error("индекс за пределами матрицы");

  return matrix_[i][j];
}

/// @brief Метод копирует данные (размерность и значения) матрицы из одного
/// объекта в другой
/// @param other Матрица, откуда копируются данные
void S21Matrix::CopyMatrixData(const S21Matrix &other) noexcept {
  cols_ = other.cols_;
  rows_ = other.rows_;
  for (int i = 0; i < rows_; ++i) {  // копирование элементов матрицы
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other(i, j);
    }
  }
}

/// @brief Проверка размерности матрицы, в зависимости от этого разные методы
/// подсчёта определителя
/// @param result
void S21Matrix::CheckDet(double *result) noexcept {
  if (cols_ == 1)  // если матрица из одного элемента
    *result = matrix_[0][0];
  if (cols_ == 2)  // если матрица из двух элементов
    *result = (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]);
  if (cols_ >= 3) {
    DetOverThree(result);
  }
}

/// @brief Метод подсчёта определителя для матриц размерностью 3 и больше
/// (рекурсивный)
/// @param result Определитель
void S21Matrix::DetOverThree(double *result) noexcept {
  int sign = -1;
  double det = 0;
  S21Matrix new_matrix = S21Matrix(rows_ - 1, cols_ - 1);
  for (int i = 0; i <= new_matrix.cols_;
       ++i) {  // определитель по первой строке
    det = 0;
    Minorchik(&new_matrix, i,
              0);  // создаём матрицу с вырезанной строчкой и столбцом (минор)
    sign *= (-1);
    new_matrix.CheckDet(&det);
    *result += sign * matrix_[0][i] * det;
  }
}

/// @brief Нахождение минора матрицы, вырезая конкретные столбцы
/// @param matrix матрица, куда будет записан минор
/// @param n вырезаемая строчка
/// @param m вырезаемый столбец
void S21Matrix::Minorchik(S21Matrix *matrix, int n, int m) noexcept {
  for (int i = 0, ki = 0, kj = 0; i < this->rows_;
       ++i) {  // ki и kj номера строк в минорной матрице
    for (int j = 0; j < this->cols_; ++j) {
      if (i == m || j == n) continue;
      matrix->matrix_[ki][kj] = matrix_[i][j];
      ++kj;
    }
    if (i == m) continue;
    kj = 0;
    ++ki;
  }
}

/// @brief Проверка матрицы на пустоту или неправильное определение
void S21Matrix::CheckMatrix(const S21Matrix &other) const {
  if (other.cols_ <= 0 || other.rows_ <= 0 || other.matrix_ == nullptr)
    throw std::length_error("матрица пустая");
}

/// @brief Процедура печати матрицы
void S21Matrix::PrintMatrix() const noexcept {
  for (int i = 0; i <= rows_ - 1; ++i) {
    for (int j = 0; j <= cols_ - 1; ++j) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
}