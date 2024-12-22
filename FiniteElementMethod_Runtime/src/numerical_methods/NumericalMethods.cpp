#include "pch.h"
#include "NumericalMethods.h"

namespace NumericalMethods
{
    Matrix GaussElimination(const Matrix& L, const Matrix& U, const Matrix& B)
    {
        size_t n = L.GetHeight();

        if (L.GetWidth() != n || U.GetHeight() != n || U.GetWidth() != n || B.GetHeight() != n || B.GetWidth() != 1)
            throw std::invalid_argument("Invalid dimensions for Gaussian Elimination");

        Matrix Y(n, 1);
        Matrix X(n, 1);

        for (size_t i = 0; i < n; i++)
        {
            double sum = 0.0;
            for (size_t j = 0; j < i; j++)
                sum += L.GetElement(i, j) * Y.GetElement(j, 0);

            Y.SetElement(i, 0, B.GetElement(i, 0) - sum);
        }

        for (int i = n - 1; i >= 0; i--)
        {
            double sum = 0.0;
            for (int j = i + 1; j < static_cast<int>(n); j++)
                sum += U.GetElement(i, j) * X.GetElement(j, 0);

            double denominator = U.GetElement(i, i);
            if (denominator == 0.0)
                throw std::runtime_error("Division by zero encountered in U matrix (matrix is singular)");

            X.SetElement(i, 0, (Y.GetElement(i, 0) - sum) / denominator);
        }

        return X;
    }

    void LUDecomposition(const Matrix& A, Matrix& L, Matrix& U)
    {
        size_t n = A.GetHeight();

        if (A.GetWidth() != n)
            throw std::invalid_argument("LU decomposition requires a square matrix.");

        L = Matrix(n);
        U = Matrix(n);

        for (size_t i = 0; i < n; i++)
        {
            for (size_t k = i; k < n; k++)
            {
                double sum = 0.0;
                for (size_t j = 0; j < i; j++)
                    sum += L.GetElement(i, j) * U.GetElement(j, k);

                U.SetElement(i, k, A.GetElement(i, k) - sum);
            }

            for (size_t k = i; k < n; k++)
            {
                if (U.GetElement(i, i) == 0.0)
                    throw std::runtime_error("Zero pivot encountered during LU decomposition");

                if (i == k)
                {
                    L.SetElement(i, i, 1.0);
                }
                else
                {
                    double sum = 0.0;
                    for (size_t j = 0; j < i; j++)
                        sum += L.GetElement(k, j) * U.GetElement(j, i);

                    L.SetElement(k, i, (A.GetElement(k, i) - sum) / U.GetElement(i, i));
                }
            }
        }
    }
}
