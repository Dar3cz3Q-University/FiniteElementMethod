#include "pch.h"
#include "Matrix.h"

Matrix::Matrix(size_t width, size_t height)
{
	m_Data.resize(height);

	for (auto& vector : m_Data) vector.resize(width);
}

void Matrix::SetElement(size_t row, size_t col, double value)
{
	CheckBounds(row, col);

	m_Data[row][col] = value;
}

double Matrix::GetElement(size_t row, size_t col) const
{
	CheckBounds(row, col);

	return m_Data[row][col];
}

double Matrix::GetDeterminant() const
{
    // For now only for 2x2
    if (m_Data.size() != 2 || m_Data[0].size() != 2) throw std::invalid_argument("Only determinant for 2x2 matrix is supported");

    return m_Data[0][0] * m_Data[1][1] - (m_Data[0][1] * m_Data[1][0]);
}

Matrix Matrix::Transpose() const
{
    size_t newWidth = m_Data.size();
    size_t newHeight = m_Data[0].size();

    Matrix transposed(newWidth, newHeight);

    for (size_t row = 0; row < newWidth; row++) for (size_t col = 0; col < newHeight; col++)
		transposed.SetElement(col, row, GetElement(row, col));

    return transposed;
}

Matrix Matrix::operator*(const Matrix& matrix) const
{
    if (m_Data[0].size() != matrix.m_Data.size())
        throw std::invalid_argument("Cannot multiply matricies");

    size_t newWidth = matrix.m_Data[0].size();
    size_t newHeight = m_Data.size();
    Matrix result(newWidth, newHeight);

    for (size_t row = 0; row < newHeight; row++)
    {
        for (size_t col = 0; col < newWidth; col++)
        {
            double sum = 0.0;
            for (size_t k = 0; k < m_Data[0].size(); k++)
                sum += GetElement(row, k) * matrix.GetElement(k, col);

            result.SetElement(row, col, sum);
        }
    }

    return result;
}

Matrix Matrix::operator+(const Matrix& other) const
{
    if (m_Data.size() != other.m_Data.size() || m_Data[0].size() != other.m_Data[0].size())
        throw std::invalid_argument("Matrices must have the same dimensions for addition.");

    Matrix result(m_Data.size(), m_Data[0].size());

    for (size_t row = 0; row < m_Data.size(); row++)
        for (size_t col = 0; col < m_Data[0].size(); col++)
            result.SetElement(row, col, GetElement(row, col) + other.GetElement(row, col));

    return result;
}

Matrix Matrix::operator*(double scalar) const
{
    Matrix result(m_Data.size(), m_Data[0].size());

    for (size_t row = 0; row < m_Data.size(); row++)
        for (size_t col = 0; col < m_Data[0].size(); col++)
            result.SetElement(row, col, GetElement(row, col) * scalar);

    return result;
}

void Matrix::CheckBounds(size_t row, size_t col) const
{
	if (row >= m_Data.size() || col >= m_Data[0].size())
		throw std::out_of_range("Index out of bound\n");
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    for (auto& row : matrix.m_Data)
    {
        for (auto& value : row)
            os << value << "\t";
        os << "\n";
    }

    return os;
}
