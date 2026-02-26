#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
  TDynamicMatrix<int> m(3);
  for (size_t i = 0; i < 3; i++)
    for (size_t j = 0; j < 3; j++)
      m[i][j] = (int)(i * 3 + j);
  TDynamicMatrix<int> m1(m);
  EXPECT_TRUE(m1 == m);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[0][1] = 2;
  m[1][0] = 3;
  m[1][1] = 4;
  TDynamicMatrix<int> m1(m);
  m1[0][0] = 10;
  EXPECT_NE(m1[0][0], m[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(4);
  EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(3);
  m[1][2] = 5;
  EXPECT_EQ(5, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(3);
  EXPECT_ANY_THROW(m.at(-1, 0));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(3);
  EXPECT_ANY_THROW(m.at(3, 0));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  m[1][1] = 2;
  ASSERT_NO_THROW(m = m);
  EXPECT_EQ(1, m[0][0]);
  EXPECT_EQ(2, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> m1(2);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  TDynamicMatrix<int> m2(2);
  m2 = m1;
  EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(4);
  m1 = m2;
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(3);
  ASSERT_NO_THROW(m1 = m2);
  EXPECT_EQ(m1.size(), m2.size());
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(2);
  m1[0][0] = 1; m1[0][1] = 2;
  m1[1][0] = 3; m1[1][1] = 4;
  m2[0][0] = 1; m2[0][1] = 2;
  m2[1][0] = 3; m2[1][1] = 4;
  EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> m1(2);
  m1[0][0] = 1;
  EXPECT_TRUE(m1 == m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> m1(2);
  TDynamicMatrix<int> m2(3);
  EXPECT_TRUE(m1 != m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2), c(2);
  a[0][0] = 1; a[0][1] = 2;
  a[1][0] = 3; a[1][1] = 4;
  b[0][0] = 5; b[0][1] = 6;
  b[1][0] = 7; b[1][1] = 8;
  c = a + b;
  EXPECT_EQ(6, c[0][0]);
  EXPECT_EQ(8, c[0][1]);
  EXPECT_EQ(10, c[1][0]);
  EXPECT_EQ(12, c[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> a(2), b(3);
  EXPECT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2), c(2);
  a[0][0] = 5; a[0][1] = 7;
  a[1][0] = 9; a[1][1] = 11;
  b[0][0] = 1; b[0][1] = 2;
  b[1][0] = 3; b[1][1] = 4;
  c = a - b;
  EXPECT_EQ(4, c[0][0]);
  EXPECT_EQ(5, c[0][1]);
  EXPECT_EQ(6, c[1][0]);
  EXPECT_EQ(7, c[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> a(2), b(3);
  EXPECT_ANY_THROW(a - b);
}
