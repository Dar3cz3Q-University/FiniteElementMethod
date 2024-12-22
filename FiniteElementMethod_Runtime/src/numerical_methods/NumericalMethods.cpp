#include "pch.h"
#include "NumericalMethods.h"

namespace NumericalMethods
{
    std::pair<Matrix, Matrix> LUDecomposition(const Matrix& A)
    {
        size_t n = A.GetHeight();

        if (A.GetWidth() != n)
            throw std::invalid_argument("LU decomposition requires a square matrix.");

        Matrix L(n), U(n);

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

        return { L, U };
    }

    Matrix ForwardSubstitution(const Matrix& L, const Matrix& b)
    {
        size_t n = L.GetHeight();
        Matrix y(n, 1);

        for (size_t i = 0; i < n; i++)
        {
            double sum = 0.0;
            for (size_t j = 0; j < i; j++)
                sum += L.GetElement(i, j) * y.GetElement(j, 0);

            double result = (b.GetElement(i, 0) - sum) / L.GetElement(i, i);
            y.SetElement(i, 0, result);
        }

        return y;
    }

    Matrix BackwardSubstitution(const Matrix& U, const Matrix& y)
    {
        size_t n = U.GetHeight();
        Matrix x(n, 1);

        for (int i = n - 1; i >= 0; i--)
        {
            double sum = 0.0;
            for (int j = i + 1; j < n; j++)
                sum += U.GetElement(i, j) * x.GetElement(j, 0);

            double result = (y.GetElement(i, 0) - sum) / U.GetElement(i, i);
            x.SetElement(i, 0, result);
        }

        return x;
    }

    Matrix SolveGaussianLU(const Matrix& A, const Matrix& b)
    {
        if (A.GetHeight() != b.GetHeight() || b.GetWidth() != 1)
            throw std::invalid_argument("Invalid dimensions for A or b in Gaussian LU solver");

        auto [L, U] = LUDecomposition(A);

        Matrix y = ForwardSubstitution(L, b);
        Matrix x = BackwardSubstitution(U, y);

        return x;
    }

}
