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
  TDynamicMatrix<int> m(2);
  m[0][0] = 1; m[0][1] = 2; m[1][0] = 3; m[1][1] = 4;
  TDynamicMatrix<int> m1(m);
  EXPECT_TRUE(m == m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  TDynamicMatrix<int> m1(m);
  m1[0][0] = 100;
  EXPECT_NE(m[0][0], m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
  TDynamicMatrix<int> m(4);
  EXPECT_EQ(4u, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
  TDynamicMatrix<int> m(3);
  m[1][2] = 9;
  EXPECT_EQ(9, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
  TDynamicMatrix<int> m(2);
  ASSERT_ANY_THROW(m[0].at(-1) = 5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
  TDynamicMatrix<int> m(2);
  ASSERT_ANY_THROW(m[0].at(100) = 5);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
  TDynamicMatrix<int> m(2);
  m[0][0] = 1;
  ASSERT_NO_THROW(m = m);
  EXPECT_EQ(1, m[0][0]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0] = 1; b[0][0] = 2;
  ASSERT_NO_THROW(a = b);
  EXPECT_TRUE(a == b);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
  TDynamicMatrix<int> a(3), b(1);
  a = b;
  EXPECT_EQ(b.size(), a.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
  TDynamicMatrix<int> a(2), b(3);
  ASSERT_NO_THROW(a = b);
  EXPECT_EQ(3u, a.size());
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0] = 5; b[0][0] = 5;
  EXPECT_TRUE(a == b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
  TDynamicMatrix<int> a(2);
  EXPECT_TRUE(a == a);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
  TDynamicMatrix<int> a(2), b(3);
  EXPECT_TRUE(a != b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0] = 1; b[0][0] = 2;
  TDynamicMatrix<int> c = a + b;
  EXPECT_EQ(3, c[0][0]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
  TDynamicMatrix<int> a(2), b(3);
  ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
  TDynamicMatrix<int> a(2), b(2);
  a[0][0] = 5; b[0][0] = 3;
  TDynamicMatrix<int> c = a - b;
  EXPECT_EQ(2, c[0][0]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
  TDynamicMatrix<int> a(2), b(3);
  ASSERT_ANY_THROW(a - b);
}

