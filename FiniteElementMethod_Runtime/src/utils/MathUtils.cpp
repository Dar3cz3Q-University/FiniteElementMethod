#include "pch.h"
#include "MathUtils.h"

std::pair<double, double> GetMinMax(const Matrix& matrix)
{
	size_t height = matrix.GetHeight();

	double min = matrix.GetElement(0, 0);
	double max = matrix.GetElement(0, 0);

	for (size_t i = 0; i < height; i++)
	{
		double value = matrix.GetElement(i, 0);

		if (value > max)
		{
			max = value;
			continue;
		}

		if (value < min)
		{
			min = value;
			continue;
		}
	}

	return std::pair<double, double>(min, max);
}
