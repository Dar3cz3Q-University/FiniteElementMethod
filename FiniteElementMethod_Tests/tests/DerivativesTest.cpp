#include "gtest/gtest.h"

#include "Derivatives.h"

static const double EPSILON = 1e-4;

TEST(DerivativesTest, GeneratesValidDerivativesForFirstIntegrationPoint)
{
    // Given
    Node point1(0, 0), point2(0.025, 0), point3(0.025, 0.025), point4(0, 0.025);

    std::map<int, Node> points = {
        { 1, point1 },
        { 2, point2 },
        { 3, point3 },
        { 4, point4 }
    };

    Jacobian jacobian;
    jacobian.Calculate(points, 1);

    // When
    Derivatives derivatives;
    derivatives.Calculate(jacobian, 1);

    // Then
    Matrix x = derivatives.GetXDerivatives();
    Matrix y = derivatives.GetYDerivatives();

    EXPECT_NEAR(x.GetElement(0, 0), -31.547, EPSILON);
    EXPECT_NEAR(x.GetElement(0, 1), 31.54701, EPSILON);
    EXPECT_NEAR(x.GetElement(0, 2), 8.452995, EPSILON);
    EXPECT_NEAR(x.GetElement(0, 3), -8.452995, EPSILON);

    EXPECT_NEAR(y.GetElement(0, 0), -31.547, EPSILON);
    EXPECT_NEAR(y.GetElement(0, 1), -8.453, EPSILON);
    EXPECT_NEAR(y.GetElement(0, 2), 8.45299, EPSILON);
    EXPECT_NEAR(y.GetElement(0, 3), 31.547, EPSILON);
}
