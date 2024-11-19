#include "pch.h"

#include "gtest/gtest.h"

#include "H_Matrix.h"

static const double EPSILON = 1e-2;

TEST(H_MatrixTest, GeneratesValidHMatrixForFirstIntegrationPoint)
{
    // Given
    Node point1(0, 0), point2(0.025, 0), point3(0.025, 0.025), point4(0, 0.025);

    std::map<int, Node> points = {
        { 1, point1 },
        { 2, point2 },
        { 3, point3 },
        { 4, point4 }
    };

    std::vector<int> nodes = { 1, 2, 3, 4 };

    Jacobian jacobian;
    jacobian.Calculate(points, nodes, 1);

    Derivatives derivatives;
    derivatives.Calculate(jacobian, 1);

    // When
    H_Matrix h_matrix;
    h_matrix.Calculate(30, jacobian.GetMatrixDeterminant(), derivatives);
    
    // Then
    Matrix h = h_matrix.GetMatrix();

    EXPECT_NEAR(h.GetElement(0, 0), 9.33, EPSILON);
    EXPECT_NEAR(h.GetElement(0, 1), -3.41, EPSILON);
    EXPECT_NEAR(h.GetElement(0, 2), -2.5, EPSILON);
    EXPECT_NEAR(h.GetElement(0, 3), -3.41, EPSILON);

    EXPECT_NEAR(h.GetElement(1, 0), -3.41, EPSILON);
    EXPECT_NEAR(h.GetElement(1, 1), 5.0, EPSILON);
    EXPECT_NEAR(h.GetElement(1, 2), 0.91, EPSILON);
    EXPECT_NEAR(h.GetElement(1, 3), -2.5, EPSILON);

    EXPECT_NEAR(h.GetElement(2, 0), -2.5, EPSILON);
    EXPECT_NEAR(h.GetElement(2, 1), 0.91, EPSILON);
    EXPECT_NEAR(h.GetElement(2, 2), 0.66, EPSILON);
    EXPECT_NEAR(h.GetElement(2, 3), 0.91, EPSILON);

    EXPECT_NEAR(h.GetElement(3, 0), -3.41, EPSILON);
    EXPECT_NEAR(h.GetElement(3, 1), -2.5, EPSILON);
    EXPECT_NEAR(h.GetElement(3, 2), 0.91, EPSILON);
    EXPECT_NEAR(h.GetElement(3, 3), 5.0, EPSILON);
}
