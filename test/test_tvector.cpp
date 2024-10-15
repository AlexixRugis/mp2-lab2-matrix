#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
    EXPECT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
    EXPECT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, cant_create_zero_length_vector)
{
    EXPECT_ANY_THROW(TDynamicVector<int> v(0));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
    EXPECT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
    TDynamicVector<int> v(10);

    EXPECT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    TDynamicVector<int> v(10), v2(v);

    EXPECT_EQ(v.size(), v2.size());
    for (size_t i = 0; i < v.size(); ++i)
    {
        EXPECT_EQ(v[i], v2[i]);
    }
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(10), v2(v);

    v2[2] = 1;
    EXPECT_EQ(v[0], v2[0]);
    EXPECT_NE(v[2], v2[2]);
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

    EXPECT_ANY_THROW(v.at(-100) = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(4);

    EXPECT_ANY_THROW(v.at(4) = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(2);
    v[1] = 1;
    EXPECT_NO_THROW(v = v);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 1);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> v1(3), v2(3);
    v1[0] = 1;
    v1[1] = 3;
    v1[2] = 2;
    EXPECT_NO_THROW(v2 = v1);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 3);
    EXPECT_EQ(v2[2], 2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> v1(3), v2;
    EXPECT_EQ(v2.size(), 1);
    v2 = v1;
    EXPECT_EQ(v2.size(), v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v1(3), v2(5);
    v1[0] = 1;
    v1[1] = 3;
    v1[2] = 2;
    EXPECT_NO_THROW(v2 = v1);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 3);
    EXPECT_EQ(v2[2], 2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> v(10), v2(v);
    EXPECT_EQ(v, v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(3);
    EXPECT_EQ(v, v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v(3), v2(4);
    EXPECT_NE(v, v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;
    EXPECT_NO_THROW(v = v + 1);
    EXPECT_EQ(v[0], 2);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 4);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;
    EXPECT_NO_THROW(v = v - 1);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v[1], 1);
    EXPECT_EQ(v[2], 2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;
    EXPECT_NO_THROW(v = v * 3);
    EXPECT_EQ(v[0], 3);
    EXPECT_EQ(v[1], 6);
    EXPECT_EQ(v[2], 9);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> v(3), v2(3), v3;
    v[0] = 1; v[1] = 2; v[2] = 3;
    v2[0] = 423; v2[1] = 122; v2[2] = 13;
    EXPECT_NO_THROW(v3 = v + v2);
    EXPECT_EQ(v3[0], 424);
    EXPECT_EQ(v3[1], 124);
    EXPECT_EQ(v3[2], 16);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(2), v2(10);
    EXPECT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> v(3), v2(3), v3;
    v[0] = 1; v[1] = 2; v[2] = 3;
    v2[0] = 423; v2[1] = 122; v2[2] = 13;
    EXPECT_NO_THROW(v3 = v - v2);
    EXPECT_EQ(v3[0], -422);
    EXPECT_EQ(v3[1], -120);
    EXPECT_EQ(v3[2], -10);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(2), v2(10);
    EXPECT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> v1(2), v2(2);
    v1[0] = 12; v1[1] = 13;
    v2[0] = 9; v2[1] = 53;
    int v3;

    EXPECT_NO_THROW(v3 = v1 * v2);
    EXPECT_EQ(v3, 797);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(2), v2(10);
    EXPECT_ANY_THROW(v1 * v2);
}

