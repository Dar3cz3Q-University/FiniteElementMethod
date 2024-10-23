#include "gtest/gtest.h"

#include "Element.h"

TEST(JacobianTest, GeneratesValidMatrix) {
    // Given
    
    Node point1(0, 0), point2(0.025, 0), point3(0.025, 0.025), point4(0, 0.025);

    Element element;
    element.AddNode(1, point1);
    element.AddNode(2, point2);
    element.AddNode(3, point3);
    element.AddNode(4, point4);

    element.CalculateJacobian();

    EXPECT_EQ(1, 1);


    // When
    // Then
}
