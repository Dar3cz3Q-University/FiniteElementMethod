#pragma once

namespace NumericalMethods
{
	double gauss(uint32_t n, double(*function)(double));
	double gauss(uint32_t n, double(*function)(double, double));
}
