#include "pch.h"
#include "Matrix.h"

Matrix::Matrix(size_t size)
    : Matrix(size, size) {}

Matrix::Matrix(size_t rows, size_t columns)
{
    m_Data.resize(rows);
    for (auto& vector : m_Data) vector.resize(columns);
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

void Matrix::AddToElement(size_t row, size_t col, double value)
{
    CheckBounds(row, col);
    m_Data[row][col] += value;
}

double Matrix::GetDeterminant() const
{
    // Obliczanie wyznacznika tylko dla macierzy 2x2
    if (m_Data.size() != 2 || m_Data[0].size() != 2)
        throw std::invalid_argument("Only determinant for 2x2 matrix is supported");

    return m_Data[0][0] * m_Data[1][1] - (m_Data[0][1] * m_Data[1][0]);
}

Matrix Matrix::Transpose() const
{
    size_t newRows = m_Data[0].size();
    size_t newColumns = m_Data.size();

    Matrix transposed(newRows, newColumns);

    for (size_t row = 0; row < m_Data.size(); row++)
        for (size_t col = 0; col < m_Data[0].size(); col++)
            transposed.SetElement(col, row, GetElement(row, col));

    return transposed;
}

Matrix Matrix::operator*(const Matrix& matrix) const
{
    if (m_Data[0].size() != matrix.m_Data.size())
        throw std::invalid_argument("Cannot multiply matrices with given dimensions");

    size_t resultRows = m_Data.size();
    size_t resultColumns = matrix.m_Data[0].size();
    Matrix result(resultRows, resultColumns);

    for (size_t row = 0; row < resultRows; row++)
    {
        for (size_t col = 0; col < resultColumns; col++)
        {
            double sum = 0.0;
            for (size_t k = 0; k < m_Data[0].size(); k++)
                sum += GetElement(row, k) * matrix.GetElement(k, col);

            result.SetElement(row, col, sum);
        }
    }

    return result;
}

Matrix Matrix::operator+(const Matrix& matrix) const
{
    if (m_Data.size() != matrix.m_Data.size() || m_Data[0].size() != matrix.m_Data[0].size())
        throw std::invalid_argument("Matrices must have the same dimensions for addition");

    size_t rows = m_Data.size();
    size_t columns = m_Data[0].size();
    Matrix result(rows, columns);

    for (size_t row = 0; row < rows; row++)
        for (size_t col = 0; col < columns; col++)
            result.SetElement(row, col, GetElement(row, col) + matrix.GetElement(row, col));

    return result;
}

Matrix Matrix::operator-(const Matrix& matrix) const
{
    if (m_Data.size() != matrix.m_Data.size() || m_Data[0].size() != matrix.m_Data[0].size())
        throw std::invalid_argument("Matrices must have the same dimensions for addition");

    size_t rows = m_Data.size();
    size_t columns = m_Data[0].size();
    Matrix result(rows, columns);

    for (size_t row = 0; row < rows; row++)
        for (size_t col = 0; col < columns; col++)
            result.SetElement(row, col, GetElement(row, col) - matrix.GetElement(row, col));

    return result;
}

Matrix Matrix::operator*(double scalar) const
{
    size_t rows = m_Data.size();
    size_t columns = m_Data[0].size();
    Matrix result(rows, columns);

    for (size_t row = 0; row < rows; row++)
        for (size_t col = 0; col < columns; col++)
            result.SetElement(row, col, GetElement(row, col) * scalar);

    return result;
}

void Matrix::CheckBounds(size_t row, size_t col) const
{
    if (row >= m_Data.size() || col >= m_Data[0].size())
        throw std::out_of_range("Index out of bound");
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    for (const auto& row : matrix.m_Data)
    {
        for (const auto& value : row)
            os << value << "\t";
        os << "\n";
    }

    return os;
}
