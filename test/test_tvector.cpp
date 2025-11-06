#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  TDynamicVector<int> v1(v);
  EXPECT_TRUE(v == v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  TDynamicVector<int> v1(v);
  v1[0] = 10;
  EXPECT_NE(v[0], v1[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(4);
  ASSERT_ANY_THROW(v.at(-1) = 5);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(4);
  ASSERT_ANY_THROW(v.at(100) = 5);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  ASSERT_NO_THROW(v = v);
  EXPECT_EQ(1, v[0]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> a(3), b(3);
  a[0] = 1; a[1] = 2; a[2] = 3;
  b[0] = 4; b[1] = 5; b[2] = 6;
  ASSERT_NO_THROW(a = b);
  EXPECT_TRUE(a == b);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> a(5), b(3);
  a = b;
  EXPECT_EQ(b.size(), a.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> a(2), b(5);
  for (size_t i = 0; i < b.size(); i++) b[i] = (int)i;
  ASSERT_NO_THROW(a = b);
  EXPECT_TRUE(a == b);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> a(2), b(2);
  a[0] = 7; a[1] = 8; b[0] = 7; b[1] = 8;
  EXPECT_TRUE(a == b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> a(2);
  EXPECT_TRUE(a == a);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> a(2), b(3);
  EXPECT_TRUE(a != b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> a(3);
  a[0] = 1; a[1] = 2; a[2] = 3;
  TDynamicVector<int> r = a + 1;
  EXPECT_EQ(2, r[0]);
  EXPECT_EQ(3, r[1]);
  EXPECT_EQ(4, r[2]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> a(3);
  a[0] = 5; a[1] = 6; a[2] = 7;
  TDynamicVector<int> r = a - 2;
  EXPECT_EQ(3, r[0]);
  EXPECT_EQ(4, r[1]);
  EXPECT_EQ(5, r[2]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> a(3);
  a[0] = 1; a[1] = 2; a[2] = 3;
  TDynamicVector<int> r = a * 2;
  EXPECT_EQ(2, r[0]);
  EXPECT_EQ(4, r[1]);
  EXPECT_EQ(6, r[2]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> a(2), b(2);
  a[0] = 1; a[1] = 2; b[0] = 3; b[1] = 4;
  TDynamicVector<int> r = a + b;
  EXPECT_EQ(4, r[0]);
  EXPECT_EQ(6, r[1]);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(2), b(3);
  ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> a(2), b(2);
  a[0] = 5; a[1] = 7; b[0] = 1; b[1] = 2;
  TDynamicVector<int> r = a - b;
  EXPECT_EQ(4, r[0]);
  EXPECT_EQ(5, r[1]);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(2), b(3);
  ASSERT_ANY_THROW(a - b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> a(3), b(3);
  a[0] = 1; a[1] = 2; a[2] = 3;
  b[0] = 4; b[1] = 5; b[2] = 6;
  int res = a * b; // 1*4+2*5+3*6 = 32
  EXPECT_EQ(32, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> a(2), b(3);
  ASSERT_ANY_THROW(a * b);
}

