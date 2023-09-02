#include <gtest/gtest.h>
#include <math.h>

#include "s21_matrix_oop.h"

TEST(Conctructor, defaultConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
}

TEST(Conctructor, defaultConstructor1) {
  S21Matrix matrix;
  EXPECT_ANY_THROW(matrix(3, 3));
}

TEST(Conctructor, defaultConstructor2) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
}

TEST(Conctructor, parameterConstructor) {
  S21Matrix matrix(3, 4);
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 4);
}

TEST(Conctructor, copyConstructor) {
  S21Matrix matrix(3, 4);
  S21Matrix result_matrix(matrix);
  EXPECT_EQ(result_matrix.GetRows(), 3);
  EXPECT_EQ(result_matrix.GetCols(), 4);
  EXPECT_EQ(matrix == result_matrix, true);
}

TEST(Conctructor, moveConstructor) {
  S21Matrix matrix(3, 4);
  S21Matrix result_matrix(std::move(matrix));
  EXPECT_EQ(result_matrix.GetRows(), 3);
  EXPECT_EQ(result_matrix.GetCols(), 4);
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
}

TEST(Conctructor, negative_meaning) {
  S21Matrix matrix(-3, 4);
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
}

TEST(Conctructor, moveOperator) {
  S21Matrix matrix(4, 4);
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetCols(); j++) {
      matrix(i, j) = 4;
    }
  }
  S21Matrix matrixMove;
  matrixMove = std::move(matrix);
  EXPECT_EQ(matrixMove.GetRows(), 4);
  EXPECT_EQ(matrixMove.GetCols(), 4);
  EXPECT_EQ(matrix.GetRows(), 0);
  EXPECT_EQ(matrix.GetCols(), 0);
}

TEST(Setter, SetRows_cols) {
  S21Matrix matrix(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix(i, j) = 1;
    }
  }
  matrix.SetCols(4);
  matrix.SetRows(4);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1);
  EXPECT_DOUBLE_EQ(matrix(3, 3), 0);
  EXPECT_ANY_THROW(matrix.SetCols(-4));
}

TEST(Setter, SetCols_error) {
  S21Matrix matrix(3, 3);
  EXPECT_ANY_THROW(matrix.SetRows(-4));
}

TEST(Setter, SetMatrix) {
  S21Matrix matrix(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix(i, j) = 1;
    }
  }
  EXPECT_DOUBLE_EQ(matrix(0, 0), 1);
  matrix.SetMatrix(2, 0, 0);
  EXPECT_DOUBLE_EQ(matrix(0, 0), 2);
  EXPECT_ANY_THROW(matrix.SetMatrix(2, -1, 0));
}

TEST(Getter, GetMatrix) {
  S21Matrix matrix(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix(i, j) = 1;
    }
  }
  EXPECT_DOUBLE_EQ(matrix.GetMatrix(0, 0), 1);
}

TEST(Sum, Sum_test_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
      matrix2(i, j) = 2;
    }
  }
  matrix1.SumMatrix(matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), 3);
    }
  }
}

TEST(Sum, Sum_test_2) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(4, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix2(i, j) = 2;
    }
  }
  EXPECT_ANY_THROW(matrix1.SumMatrix(matrix2));
}

TEST(Sum, Sum_test_3) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
    }
  }
  matrix1.SumMatrix(matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), 1);
    }
  }
}

TEST(Sub, Sub_test_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
      matrix2(i, j) = 2;
    }
  }
  matrix1.SubMatrix(matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), -1);
    }
  }
}

TEST(Sub, Sub_test_2) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(4, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix2(i, j) = 2;
    }
  }
  EXPECT_ANY_THROW(matrix1.SubMatrix(matrix2));
}

TEST(Sub, Sub_test_3) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
    }
  }
  matrix1.SubMatrix(matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), 1);
    }
  }
}

TEST(Eq, Eq_test_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
      matrix2(i, j) = 1;
    }
  }
  EXPECT_EQ(matrix1.EqMatrix(matrix2), true);
}

TEST(Eq, Eq_test_2) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
      matrix2(i, j) = 2;
    }
  }
  EXPECT_EQ(matrix1.EqMatrix(matrix2), false);
}

TEST(Eq, Eq_test_3) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(4, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      matrix2(i, j) = 1;
    }
  }
  EXPECT_EQ(matrix1.EqMatrix(matrix2), false);
}

TEST(MulNumber, MulNumber_test_1) {
  S21Matrix matrix1(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 2;
    }
  }
  matrix1.MulNumber(2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), 4);
    }
  }
}

TEST(MulNumber, MulNumber_test_2) {
  double inf = INFINITY;
  S21Matrix matrix1(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 2;
    }
  }
  EXPECT_ANY_THROW(matrix1.MulNumber(inf));
}

TEST(MulNumber, MulNumber_test_4) {
  S21Matrix matrix0 = S21Matrix();
  EXPECT_ANY_THROW(matrix0.MulNumber(2));
}

TEST(MulMatrix, MulMatrix_test_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 2;
      matrix2(i, j) = 4;
    }
  }
  matrix1.MulMatrix(matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), 24);
    }
  }
}
TEST(MulMatrix, MulMatrix_test_2) {
  S21Matrix matrix1(3, 4);
  S21Matrix matrix2(4, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      matrix1(i, j) = 2;
    }
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      matrix2(i, j) = 4;
    }
  }
  matrix1.MulMatrix(matrix2);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), 32);
    }
  }
  EXPECT_EQ(matrix1.GetCols(), 3);
  EXPECT_EQ(matrix1.GetRows(), 3);
}

TEST(MulMatrix, MulMatrix_test_3) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(4, 4);

  EXPECT_ANY_THROW(matrix1.MulMatrix(matrix2));
}

TEST(Transpose, Transpose_test_1) {
  S21Matrix matrix1(3, 2);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 5;
  matrix1(1, 1) = 7;
  matrix1(2, 0) = 9;
  matrix1(2, 1) = 10;

  S21Matrix matrix2 = matrix1.Transpose();
  EXPECT_DOUBLE_EQ(matrix2.GetRows(), 2);
  EXPECT_DOUBLE_EQ(matrix2.GetCols(), 3);
  EXPECT_DOUBLE_EQ(matrix2(0, 0), 1);
  EXPECT_DOUBLE_EQ(matrix2(0, 1), 5);
  EXPECT_DOUBLE_EQ(matrix2(0, 2), 9);
  EXPECT_DOUBLE_EQ(matrix2(1, 0), 3);
  EXPECT_DOUBLE_EQ(matrix2(1, 1), 7);
  EXPECT_DOUBLE_EQ(matrix2(1, 2), 10);
}

TEST(Transpose, Transpose_test_2) {
  S21Matrix matrix1;
  EXPECT_ANY_THROW(matrix1.Transpose());
}

TEST(Determinant, Determinant_test_1) {
  S21Matrix matrix1(3, 4);
  EXPECT_ANY_THROW(matrix1.Determinant());
}

TEST(Determinant, Determinant_test_2) {
  S21Matrix matrix1(3, 3);
  int count = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = count;
      count++;
    }
  }
  EXPECT_DOUBLE_EQ(matrix1.Determinant(), 0);
}

TEST(Determinant, Determinant_test_3) {
  S21Matrix matrix1(4, 4);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;
  matrix1(0, 3) = 4;

  matrix1(1, 0) = 1;
  matrix1(1, 1) = 2;
  matrix1(1, 2) = 5;
  matrix1(1, 3) = 7;

  matrix1(2, 0) = 1;
  matrix1(2, 1) = 0;
  matrix1(2, 2) = 6;
  matrix1(2, 3) = 8;

  matrix1(3, 0) = 1;
  matrix1(3, 1) = 0;
  matrix1(3, 2) = 6;
  matrix1(3, 3) = 6;
  EXPECT_EQ(matrix1.Determinant(), -8);
}

TEST(Determinant, Determinant_test_4) {
  S21Matrix matrix1(1, 1);
  matrix1(0, 0) = 2.0;
  EXPECT_EQ(matrix1.Determinant(), 2);
}

TEST(CalcComplements, CalcComplements_test_1) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 1;
  matrix1(0, 1) = 2;
  matrix1(0, 2) = 3;

  matrix1(1, 0) = 0;
  matrix1(1, 1) = 4;
  matrix1(1, 2) = 2;

  matrix1(2, 0) = 5;
  matrix1(2, 1) = 2;
  matrix1(2, 2) = 1;

  matrix1 = matrix1.CalcComplements();

  EXPECT_EQ(matrix1(0, 0), 0);
  EXPECT_EQ(matrix1(0, 1), 10);
  EXPECT_EQ(matrix1(0, 2), -20);
  EXPECT_EQ(matrix1(1, 0), 4);
  EXPECT_EQ(matrix1(1, 1), -14);
  EXPECT_EQ(matrix1(1, 2), 8);
  EXPECT_EQ(matrix1(2, 0), -8);
  EXPECT_EQ(matrix1(2, 1), -2);
  EXPECT_EQ(matrix1(2, 2), 4);
}

TEST(CalcComplements, CalcComplements_test_2) {
  S21Matrix matrix1(4, 5);
  EXPECT_ANY_THROW(matrix1.CalcComplements());
}

TEST(CalcComplements, CalcComplements_test_3) {
  S21Matrix matrix1(1, 1);
  matrix1(0, 0) = 2.0;
  S21Matrix matrix2 = matrix1.CalcComplements();
  EXPECT_EQ(matrix2(0, 0), 2);
}

TEST(InverseMatrix, InverseMatrix_test_1) {
  S21Matrix matrix1(3, 3);
  int count = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = count;
      count++;
    }
  }
  EXPECT_ANY_THROW(matrix1.InverseMatrix());
}

TEST(InverseMatrix, InverseMatrix_test_2) {
  S21Matrix matrix1(3, 3);
  matrix1(0, 0) = 2.0;
  matrix1(0, 1) = 5.0;
  matrix1(0, 2) = 7.0;
  matrix1(1, 0) = 6.0;
  matrix1(1, 1) = 3.0;
  matrix1(1, 2) = 4.0;
  matrix1(2, 0) = 5.0;
  matrix1(2, 1) = -2.0;
  matrix1(2, 2) = -3.0;

  S21Matrix matrix_res(3, 3);
  matrix_res(0, 0) = 1.0;
  matrix_res(0, 1) = -1.0;
  matrix_res(0, 2) = 1.0;
  matrix_res(1, 0) = -38.0;
  matrix_res(1, 1) = 41.0;
  matrix_res(1, 2) = -34.0;
  matrix_res(2, 0) = 27.0;
  matrix_res(2, 1) = -29.0;
  matrix_res(2, 2) = 24.0;

  S21Matrix matrix2 = matrix1.InverseMatrix();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(matrix2(i, j), matrix_res(i, j));
    }
  }
}

TEST(InverseMatrix, InverseMatrix_test_3) {
  S21Matrix matrix1(1, 1);
  matrix1(0, 0) = 2.0;
  S21Matrix matrix2 = matrix1.InverseMatrix();
  EXPECT_EQ(matrix2(0, 0), 0.5);
}

TEST(operator_overloading, assignment_test_1) {
  S21Matrix matrix1(3, 3);
  int count = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = count;
      count++;
    }
  }
  S21Matrix matrix2 = matrix1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_EQ(matrix1(i, j), matrix2(i, j));
    }
  }
}

TEST(operator_overloading, sum_test_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  S21Matrix matrix3(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
      matrix2(i, j) = 2;
      matrix3(i, j) = 3;
    }
  }
  matrix3 = matrix1 + matrix2;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix3(i, j), 3);
    }
  }
}

TEST(operator_overloading, sum_test_2) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 4);
  S21Matrix matrix3(3, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
    }
  }
  EXPECT_ANY_THROW(matrix3 = matrix1 + matrix2);
}

TEST(operator_overloading, sub_test_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  S21Matrix matrix3(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
      matrix2(i, j) = 2;
      matrix3(i, j) = 3;
    }
  }
  matrix3 = matrix1 - matrix2;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix3(i, j), -1);
    }
  }
}

TEST(operator_overloading, sub_test_2) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 4);
  S21Matrix matrix3(3, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
    }
  }
  EXPECT_ANY_THROW(matrix3 = matrix1 - matrix2);
}

TEST(operator_overloading, mult_test_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  S21Matrix matrix3(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 3;
      matrix2(i, j) = 2;
      matrix3(i, j) = 1;
    }
  }
  matrix3 = matrix1 * matrix2;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix3(i, j), 18);
    }
  }
  S21Matrix matrix4(3, 3);
  S21Matrix matrix5(4, 4);

  EXPECT_ANY_THROW(matrix3 = matrix4 * matrix5);
}

TEST(operator_overloading, mult_test_2) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  S21Matrix matrix3(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 3;
    }
  }
  matrix2 = matrix1 * 2;
  matrix3 = 2 * matrix1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix2(i, j), 6);
      EXPECT_DOUBLE_EQ(matrix3(i, j), 6);
    }
  }
}

TEST(operator_overloading, eq_test_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
      matrix2(i, j) = 1;
    }
  }
  EXPECT_EQ(matrix1 == matrix2, true);
}

TEST(operator_overloading, eq_test_2) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
      matrix2(i, j) = 2;
    }
  }
  EXPECT_EQ(matrix1 == matrix2, false);
}

TEST(operator_overloading, sum_assignment_test_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
      matrix2(i, j) = 2;
    }
  }
  matrix1 += matrix2;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), 3);
    }
  }
}

TEST(operator_overloading, sum_assignment_test_2) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(4, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
    }
  }
  EXPECT_ANY_THROW(matrix1 += matrix2);
}

TEST(operator_overloading, sub_assignment_test_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
      matrix2(i, j) = 2;
    }
  }
  matrix1 -= matrix2;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), -1);
    }
  }
}

TEST(operator_overloading, sub_assignment_test_2) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(4, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 1;
    }
  }
  EXPECT_ANY_THROW(matrix1 -= matrix2);
}

TEST(operator_overloading, mult_assignment_test_1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 3;
      matrix2(i, j) = 2;
    }
  }
  matrix1 *= matrix2;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), 18);
    }
  }
  S21Matrix matrix4(3, 3);
  S21Matrix matrix5(4, 4);

  EXPECT_ANY_THROW(matrix4 *= matrix5);
}

TEST(operator_overloading, mult_assignment_test_2) {
  S21Matrix matrix1(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 3;
    }
  }
  matrix1 *= 2;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), 6);
    }
  }
}

TEST(operators, index_const) {
  const S21Matrix matrix1(3, 3);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), 0);
    }
  }
  EXPECT_ANY_THROW(matrix1(-1, 0));
}

TEST(operator_overloading, eq) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  S21Matrix matrix3(3, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = 3;
    }
  }
  matrix2 = matrix3 = matrix1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      EXPECT_DOUBLE_EQ(matrix1(i, j), 3);
      EXPECT_DOUBLE_EQ(matrix2(i, j), 3);
      EXPECT_DOUBLE_EQ(matrix3(i, j), 3);
    }
  }
}

TEST(print, matrix) {
  S21Matrix matrix1(3, 3);
  int count = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      matrix1(i, j) = count;
      count++;
    }
  }
  matrix1.PrintMatrix();
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}