#include "pch.h"

#include "gtest/gtest.h"

#include "numerical_methods/Integrals.h"

static double one_dimension_fixture(double x)
{
	return 2.0 * pow(x, 2) + 0.1 * x + 3.0;
}

static double two_dimension_fixture(double x, double y)
{
	return -2.0 * pow(x, 2) * y + 2.0 * x * y + 4.0;
}

static double second_two_dimension_fixture(double x, double y)
{
	return -5.0 * pow(x, 2) * y + 2.0 * x * y + 10.0;
}

const double EPSILON = 1e-2;
TEST(GaussLegendreTest, HandlesOneDimension)
{
	// Given
	double expected_result = 7.0 + 1.0 / 3.0;

	// When
	double actual_result = NumericalMethods::gauss(5, &one_dimension_fixture);

	// Then
	EXPECT_NEAR(expected_result, actual_result, EPSILON);
}

TEST(GaussLegendreTest, HandlesTwoDimensions)
{
	// Given
	double expected_result = 16.0;

	// When
	double actual_result = NumericalMethods::gauss(5, &two_dimension_fixture);

	// Then
	EXPECT_NEAR(expected_result, actual_result, EPSILON);

	// Given
	expected_result = 40.0;

	// When
	actual_result = NumericalMethods::gauss(5, &second_two_dimension_fixture);

	// Then
	EXPECT_NEAR(expected_result, actual_result, EPSILON);
}