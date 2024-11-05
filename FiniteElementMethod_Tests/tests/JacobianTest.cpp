#include "gtest/gtest.h"

#include "Jacobian.h"

static const double EPSILON = 1e-4;
TEST(JacobianTest, GeneratesValidMatrixForFirstIntegrationPoint) {
    // Given
    Node point1(0, 0), point2(0.025, 0), point3(0.025, 0.025), point4(0, 0.025);

    std::unordered_map<int, Node> points = {
        { 1, point1 },
        { 2, point2 },
        { 3, point3 },
        { 4, point4 }
    };

    // When
    Jacobian jacobian;
    jacobian.Calculate(points, 1);

    // Then
    EXPECT_NEAR(jacobian.m_JacobianMatrix.GetElement(0, 0), 0.0125, EPSILON);
    EXPECT_NEAR(jacobian.m_JacobianMatrix.GetElement(0, 1), 0.0, EPSILON);
    EXPECT_NEAR(jacobian.m_JacobianMatrix.GetElement(1, 0), 0.0, EPSILON);
    EXPECT_NEAR(jacobian.m_JacobianMatrix.GetElement(1, 1), 0.0125, EPSILON);

    EXPECT_NEAR(jacobian.GetMatrixDeterminant(), 0.00015625, EPSILON);

    EXPECT_NEAR(jacobian.m_InversedJacobianMatrix.GetElement(0, 0), 80.0, EPSILON);
    EXPECT_NEAR(jacobian.m_InversedJacobianMatrix.GetElement(0, 1), 0.0, EPSILON);
    EXPECT_NEAR(jacobian.m_InversedJacobianMatrix.GetElement(1, 0), 0.0, EPSILON);
    EXPECT_NEAR(jacobian.m_InversedJacobianMatrix.GetElement(1, 1), 80.0, EPSILON);
}
