#pragma once

class Matrix
{
public:
	Matrix() = default;
	Matrix(size_t size);
	Matrix(size_t width, size_t height);

public:
	void SetElement(size_t row, size_t col, double value);
	double GetElement(size_t row, size_t col) const;
	void AddToElement(size_t row, size_t col, double value);

	double GetDeterminant() const;

	Matrix Transpose() const;

public:
	Matrix operator*(const Matrix& matrix) const;
	Matrix operator+(const Matrix& matrix) const;
	Matrix operator*(double scalar) const;

private:
	void CheckBounds(size_t row, size_t col) const;

private:
	std::vector<std::vector<double>> m_Data;

public:
	friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

