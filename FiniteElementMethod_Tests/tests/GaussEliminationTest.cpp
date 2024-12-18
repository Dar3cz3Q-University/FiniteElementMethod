#include "pch.h"

#include "gtest/gtest.h"

#include "numerical_methods/NumericalMethods.h"

TEST(GaussEliminationTest, CalculatesValidXForFirstIntegrationPoint)
{
    // Given
    Matrix A(3, 3);
    A.SetElement(0, 0, 2); A.SetElement(0, 1, -1); A.SetElement(0, 2, -2);
    A.SetElement(1, 0, -4); A.SetElement(1, 1, 6); A.SetElement(1, 2, 3);
    A.SetElement(2, 0, -4); A.SetElement(2, 1, -2); A.SetElement(2, 2, 8);

    Matrix B(3, 1);
    B.SetElement(0, 0, -3);
    B.SetElement(1, 0, 9);
    B.SetElement(2, 0, 12);

    // When
    Matrix L(3), U(3);
    NumericalMethods::LUDecomposition(A, L, U);
    Matrix X = NumericalMethods::GaussElimination(L, U, B);

    // Then
    EXPECT_EQ(X.GetElement(0, 0), 2.25);
    EXPECT_EQ(X.GetElement(1, 0), 1.5);
    EXPECT_EQ(X.GetElement(2, 0), 3);
}