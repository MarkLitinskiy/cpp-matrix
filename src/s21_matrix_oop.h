#ifndef S21_MATRIX_OOP
#define S21_MATRIX_OOP

class S21Matrix {
 private:
  const double kzero = 1e-9;
  int rows_, cols_;  // Строки и колонки
  double** matrix_;  // Указатель, где в памяти расположена матрица

 public:
  S21Matrix() noexcept;  // Default constructor
  explicit S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  // геттеры и сеттеры для private атрибутов
  void SetRows(int numb);
  void SetCols(int numb);
  void SetMatrix(int numb, int row, int col);
  int GetRows() const;
  int GetCols() const;
  double GetMatrix(int row, int col) const;

  // основные функции
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  bool EqMatrix(const S21Matrix& other) const;
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // перегрузка операторов
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  friend S21Matrix operator*(double, const S21Matrix&);
  friend S21Matrix operator*(const S21Matrix&, double);
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double numb);
  double operator()(int i, int j) const;
  double& operator()(int i, int j);

  void PrintMatrix() const noexcept;

 private:
  // вспомогательные методы для работы с матрицами
  void CopyMatrixData(const S21Matrix& other) noexcept;
  void CheckMatrix(const S21Matrix& other) const;
  void CreateNullMatrix() noexcept;
  void AlocateMem(int other_rows, int other_cols) noexcept;
  void DeleteMem() noexcept;

  // вспомогательные методы для нахождения определителя
  void CheckDet(double* result) noexcept;
  void DetOverThree(double* result) noexcept;
  void Minorchik(S21Matrix* matrix, int n, int m) noexcept;
};
#endif  // S21_MATRIX_OOP