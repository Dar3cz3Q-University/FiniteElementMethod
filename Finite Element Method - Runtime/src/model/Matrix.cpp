#include "pch.h"
#include "Matrix.h"

Matrix::Matrix(uint32_t width, uint32_t height)
{
	m_Data.reserve(height);

	for (auto& vector : m_Data) vector.reserve(width);
}

void Matrix::SetElement(uint32_t row, uint32_t col, double value)
{
	CheckBounds(row, col);

	m_Data[row][col] = value;
}

double Matrix::GetElement(uint32_t row, uint32_t col) const
{
	CheckBounds(row, col);

	return m_Data[row][col];
}

Matrix Matrix::Transpose() const
{
    uint32_t newWidth = m_Data.size();
    uint32_t newHeight = m_Data[0].size();

    Matrix transposed(newWidth, newHeight);

    for (uint32_t row = 0; row < newWidth; row++) for (uint32_t col = 0; col < newHeight; col++)
		transposed.SetElement(row, col, GetElement(col, row));

    return transposed;
}

Matrix Matrix::operator*(const Matrix& matrix) const
{
    if (m_Data[0].size() != matrix.m_Data.size())
        throw std::invalid_argument("Cannot multiply matricies");

    uint32_t newWidth = matrix.m_Data[0].size();
    uint32_t newHeight = m_Data.size();
    Matrix result(newWidth, newHeight);

    for (uint32_t row = 0; row < newHeight; row++)
    {
        for (uint32_t col = 0; col < newWidth; col++)
        {
            double sum = 0.0;
            for (uint32_t k = 0; k < m_Data[0].size(); k++)
                sum += GetElement(row, k) * matrix.GetElement(k, col);

            result.SetElement(row, col, sum);
        }
    }

    return result;
}

void Matrix::CheckBounds(uint32_t row, uint32_t col) const
{
	if (row >= m_Data.size() || col >= m_Data[0].size())
		throw std::out_of_range("Index out of bound\n");
}

