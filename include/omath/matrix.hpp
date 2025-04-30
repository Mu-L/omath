#pragma once
#include <initializer_list>
#include <memory>
#include <string>
#include "omath/vector3.hpp"

namespace omath
{

    class Matrix final
    {
    public:
        OMATH_SE_COMPATIBLE Matrix();
        OMATH_SE_COMPATIBLE Matrix(size_t rows, size_t columns);

        OMATH_SE_COMPATIBLE Matrix(const std::initializer_list<std::initializer_list<float>>& rows);

        [[nodiscard]]
        OMATH_SE_COMPATIBLE static Matrix ToScreenMatrix(float screenWidth, float screenHeight);

        [[nodiscard]]
        OMATH_SE_COMPATIBLE static Matrix TranslationMatrix(const Vector3<float>& diff);

        [[nodiscard]]
        OMATH_SE_COMPATIBLE static Matrix OrientationMatrix(const Vector3<float>& forward, const Vector3<float>& right, const Vector3<float>& up);

        [[nodiscard]]
        OMATH_SE_COMPATIBLE static Matrix ProjectionMatrix(float fieldOfView, float aspectRatio, float near, float far);

        OMATH_SE_COMPATIBLE Matrix(const Matrix& other);

        OMATH_SE_COMPATIBLE Matrix(size_t rows, size_t columns, const float* pRaw);

        OMATH_SE_COMPATIBLE Matrix(Matrix&& other) noexcept;

        [[nodiscard]]
        OMATH_SE_COMPATIBLE size_t RowCount() const noexcept;


        [[nodiscard]]
        OMATH_SE_COMPATIBLE float& operator[](size_t row, size_t column);

        [[nodiscard]]
        OMATH_SE_COMPATIBLE size_t ColumnsCount() const noexcept;

        [[nodiscard]]
        OMATH_SE_COMPATIBLE std::pair<size_t, size_t> Size() const noexcept;

        [[nodiscard]]
        OMATH_SE_COMPATIBLE float& At(size_t iRow, size_t iCol);

        [[nodiscard]]
        OMATH_SE_COMPATIBLE float Sum();

        OMATH_SE_COMPATIBLE void SetDataFromRaw(const float* pRawMatrix);

        [[nodiscard]]
        OMATH_SE_COMPATIBLE Matrix Transpose() const;

        OMATH_SE_COMPATIBLE void Set(float val);

        [[nodiscard]]
        OMATH_SE_COMPATIBLE const float& At(size_t iRow, size_t iCol) const;

        OMATH_SE_COMPATIBLE Matrix operator*(const Matrix& other) const;

        OMATH_SE_COMPATIBLE Matrix& operator*=(const Matrix& other);

        OMATH_SE_COMPATIBLE Matrix operator*(float f) const;

        OMATH_SE_COMPATIBLE Matrix& operator*=(float f);

        OMATH_SE_COMPATIBLE Matrix& operator/=(float f);

        OMATH_SE_COMPATIBLE void Clear();

        [[nodiscard]]
        OMATH_SE_COMPATIBLE Matrix Strip(size_t row, size_t column) const;

        [[nodiscard]]
        OMATH_SE_COMPATIBLE float Minor(size_t i, size_t j) const;

        [[nodiscard]]
        OMATH_SE_COMPATIBLE float AlgComplement(size_t i, size_t j) const;

        [[nodiscard]]
        OMATH_SE_COMPATIBLE float Determinant() const;

        [[nodiscard]]
        OMATH_SE_COMPATIBLE const float* Raw() const;

        OMATH_SE_COMPATIBLE Matrix& operator=(const Matrix& other);

        OMATH_SE_COMPATIBLE Matrix& operator=(Matrix&& other) noexcept;

        OMATH_SE_COMPATIBLE Matrix operator/(float f) const;

        [[nodiscard]]
        OMATH_SE_COMPATIBLE std::string ToString() const;

        OMATH_SE_COMPATIBLE ~Matrix();

    private:
        size_t m_rows;
        size_t m_columns;
        std::unique_ptr<float[]> m_data;
    };
} // namespace omath
