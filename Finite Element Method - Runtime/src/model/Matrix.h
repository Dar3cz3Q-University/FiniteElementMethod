#pragma once

class Matrix
{
public:
	Matrix(uint32_t width, uint32_t height);

public:
	void SetElement(uint32_t row, uint32_t col, double value);
	double GetElement(uint32_t row, uint32_t col) const;

	Matrix Transpose() const;

public:
	Matrix operator*(const Matrix& matrix) const;

private:
	void CheckBounds(uint32_t row, uint32_t col) const;

private:
	std::vector<std::vector<double>> m_Data;
};

