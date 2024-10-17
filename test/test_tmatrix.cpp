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
    TDynamicMatrix<int> m1(5);

    for (size_t i = 0; i < m1.size(); ++i)
    {
        for (size_t j = 0; j < m1.size(); ++j)
        {
            m1[i][j] = i * 5 + j;
        }
    }

    TDynamicMatrix<int> m2(m1);
    EXPECT_EQ(m2.size(), m1.size());

    for (size_t i = 0; i < m1.size(); ++i)
    {
        for (size_t j = 0; j < m1.size(); ++j)
        {
            EXPECT_EQ(m1[i][j], m2[i][j]);
        }
    }
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m1(2), m2(2);
    m1[0][0] = 1;
    EXPECT_NE(m1[0][0], m2[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(5);
    EXPECT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(3);
    EXPECT_NO_THROW(m[2][2] = 31);
    EXPECT_EQ(m[2][2], 31);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(2);
    EXPECT_ANY_THROW(m.at(2, 0) = 10);
    EXPECT_ANY_THROW(m.at(1, 2) = 10);
    EXPECT_ANY_THROW(m.at(2, 3) = 10);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    EXPECT_NO_THROW(m = m);
    EXPECT_EQ(m[0][0], 1);
    EXPECT_EQ(m[0][1], 2);
    EXPECT_EQ(m[1][0], 3);
    EXPECT_EQ(m[1][1], 4);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m(2), m2(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    EXPECT_NO_THROW(m2 = m);
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[0][1], 2);
    EXPECT_EQ(m2[1][0], 3);
    EXPECT_EQ(m2[1][1], 4);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m(2), m2(1);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    EXPECT_NO_THROW(m2 = m);
    EXPECT_EQ(m2.size(), 2);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m(2), m2(1);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    EXPECT_NO_THROW(m2 = m);
    EXPECT_EQ(m2[0][0], 1);
    EXPECT_EQ(m2[0][1], 2);
    EXPECT_EQ(m2[1][0], 3);
    EXPECT_EQ(m2[1][1], 4);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m(2), m2(m);
    EXPECT_EQ(m, m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(10);
    EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m(9), m2(10);
    EXPECT_NE(m, m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(2), m2(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    m2[0][0] = 3; m2[0][1] = 4;
    m2[1][0] = 5; m2[1][1] = 6;
    EXPECT_NO_THROW(m = m + m2);
    EXPECT_EQ(m[0][0], 4);
    EXPECT_EQ(m[0][1], 6);
    EXPECT_EQ(m[1][0], 8);
    EXPECT_EQ(m[1][1], 10);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(2), m2(3);
    EXPECT_ANY_THROW(m + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(2), m2(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;
    m2[0][0] = 3; m2[0][1] = 4;
    m2[1][0] = 5; m2[1][1] = 6;
    EXPECT_NO_THROW(m = m - m2);
    EXPECT_EQ(m[0][0], -2);
    EXPECT_EQ(m[0][1], -2);
    EXPECT_EQ(m[1][0], -2);
    EXPECT_EQ(m[1][1], -2);
}

TEST(TDynamicMatrix, cant_subtract_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(2), m2(3);
    EXPECT_ANY_THROW(m - m2);
}

TEST(TDynamicMatrix, can_multiply_matrices_with_equal_size)
{
    TDynamicMatrix<int> m(2), m2(2);
    m[0][0] = 5; m[0][1] = 1;
    m[1][0] = 7; m[1][1] = 45;
    m2[0][0] = -4; m2[0][1] = 0;
    m2[1][0] = 63; m2[1][1] = 4;
    EXPECT_NO_THROW(m = m * m2);
    EXPECT_EQ(m[0][0], 43);
    EXPECT_EQ(m[0][1], 4);
    EXPECT_EQ(m[1][0], 2807);
    EXPECT_EQ(m[1][1], 180);
}

TEST(TDynamicMatrix, cant_multiply_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(2), m2(3);
    EXPECT_ANY_THROW(m * m2);
}

TEST(TDynamicMatrix, can_multiply_matrix_and_vector)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 12; m[0][1] = 4;
    m[1][0] = 4; m[1][1] = 1;
    TDynamicVector<int> v(2);
    v[0] = 1; v[1] = 2;

    EXPECT_NO_THROW(v = m * v);
    EXPECT_EQ(v[0], 20);
    EXPECT_EQ(v[1], 6);
}

TEST(TDynamicMatrix, cant_multiply_matrix_and_vector_with_not_equal_size)
{
    TDynamicMatrix<int> m(2);
    TDynamicVector<int> v(3);

    EXPECT_ANY_THROW(m * v);
}