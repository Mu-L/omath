#include "omath/matrix.hpp"
#include "omath/angles.hpp"
#include "omath/vector3.hpp"
#include "omath/compile_definitions.hpp"
#include <CodeVirtualizer/ThemidaSDK.h>
#include <complex>
#include <format>
#include <stdexcept>
#include <utility>


namespace omath
{
    Matrix::Matrix(const size_t rows, const size_t columns)
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        if (rows == 0 and columns == 0)
            throw std::runtime_error("Matrix cannot be 0x0");

        m_rows = rows;
        m_columns = columns;

        m_data = std::make_unique<float[]>(m_rows * m_columns);

        Set(0.f);
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
    }

    Matrix::Matrix(const std::initializer_list<std::initializer_list<float>>& rows)
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        m_rows = rows.size();
        m_columns = rows.begin()->size();


        for (const auto& row: rows)
            if (row.size() != m_columns)
                throw std::invalid_argument("All rows must have the same number of columns.");

        m_data = std::make_unique<float[]>(m_rows * m_columns);

        size_t i = 0;
        for (const auto& row: rows)
        {
            size_t j = 0;
            for (const auto& value: row)
                At(i, j++) = value;
            ++i;
        }
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
    }

    Matrix::Matrix(const Matrix& other)
    {
        OMATH_SE_PLACE_MACROS(VM_MUTATE_ONLY_START)

        m_rows = other.m_rows;
        m_columns = other.m_columns;

        m_data = std::make_unique<float[]>(m_rows * m_columns);

        for (size_t i = 0; i < m_rows; ++i)
            for (size_t j = 0; j < m_columns; ++j)
                At(i, j) = other.At(i, j);

        OMATH_SE_PLACE_MACROS(VM_MUTATE_ONLY_END)
    }

    Matrix::Matrix(const size_t rows, const size_t columns, const float* pRaw)
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)

        m_rows = rows;
        m_columns = columns;


        m_data = std::make_unique<float[]>(m_rows * m_columns);

        for (size_t i = 0; i < rows * columns; ++i)
            At(i / rows, i % columns) = pRaw[i];

        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
    }

    size_t Matrix::RowCount() const noexcept
    {
        return m_rows;
    }
    
    float& Matrix::operator[](const size_t row, const size_t column)
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        auto& result = At(row, column);
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        return result;
    }

    Matrix::Matrix(Matrix&& other) noexcept
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)

        m_rows = other.m_rows;
        m_columns = other.m_columns;
        m_data = std::move(other.m_data);

        other.m_rows = 0;
        other.m_columns = 0;

        other.m_data = nullptr;

        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
    }

    size_t Matrix::ColumnsCount() const noexcept
    {
        return m_columns;
    }

    std::pair<size_t, size_t> Matrix::Size() const noexcept
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        const std::pair result = {RowCount(), ColumnsCount()};
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        return result;
    }

    float& Matrix::At(const size_t iRow, const size_t iCol)
    {
        return const_cast<float&>(std::as_const(*this).At(iRow, iCol));
    }

    float Matrix::Sum()
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        float sum = 0;

        for (size_t i = 0; i < RowCount(); i++)
            for (size_t j = 0; j < ColumnsCount(); j++)
                sum += At(i, j);

        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        return sum;
    }

    const float& Matrix::At(const size_t iRow, const size_t iCol) const
    {
        return m_data[iRow * m_columns + iCol];
    }

    Matrix Matrix::operator*(const Matrix& other) const
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)

        if (m_columns != other.m_rows)
            throw std::runtime_error("n != m");

        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        auto outMat = Matrix(m_rows, other.m_columns);

        for (size_t d = 0; d < m_rows; ++d)
            for (size_t i = 0; i < other.m_columns; ++i)
                for (size_t j = 0; j < other.m_rows; ++j)
                {
                    OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
                    outMat.At(d, i) += At(d, j) * other.At(j, i);
                    OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
                }


        return outMat;

    }

    Matrix& Matrix::operator*=(const Matrix& other)
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        *this = *this * other;
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        return *this;
    }

    Matrix Matrix::operator*(const float f) const
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        auto out = *this;
        for (size_t i = 0; i < m_rows; ++i)
        {
            for (size_t j = 0; j < m_columns; ++j)
                out.At(i, j) *= f;
        }
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        return out;
    }

    Matrix& Matrix::operator*=(const float f)
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        for (size_t i = 0; i < RowCount(); i++)
            for (size_t j = 0; j < ColumnsCount(); j++)
                At(i, j) *= f;

        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        return *this;
    }

    void Matrix::Clear()
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        Set(0.f);
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
    }

    Matrix& Matrix::operator=(const Matrix& other)
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        if (this == &other)
            return *this;

        for (size_t i = 0; i < m_rows; ++i)
            for (size_t j = 0; j < m_columns; ++j)
                At(i, j) = other.At(i, j);
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        return *this;
    }

    Matrix& Matrix::operator=(Matrix&& other) noexcept
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        if (this == &other)
            return *this;

        m_rows = other.m_rows;
        m_columns = other.m_columns;
        m_data = std::move(other.m_data);

        other.m_rows = 0;
        other.m_columns = 0;

        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        return *this;
    }

    Matrix& Matrix::operator/=(const float f)
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        for (size_t i = 0; i < m_rows; ++i)
            for (size_t j = 0; j < m_columns; ++j)
                At(i, j) /= f;
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        return *this;
    }

    Matrix Matrix::operator/(const float f) const
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        auto out = *this;
        for (size_t i = 0; i < m_rows; ++i)
            for (size_t j = 0; j < m_columns; ++j)
                out.At(i, j) /= f;
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        return out;
    }

    std::string Matrix::ToString() const
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        std::string str;

        for (size_t i = 0; i < m_rows; i++)
        {
            for (size_t j = 0; j < m_columns; ++j)
            {
                str += std::format("{:.1f}", At(i, j));

                if (j == m_columns - 1)
                    str += '\n';
                else
                    str += ' ';
            }
        }
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        return str;
    }

    float Matrix::Determinant() const
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        if (m_rows + m_columns == 2)
            return At(0, 0);

        if (m_rows == 2 and m_columns == 2)
            return At(0, 0) * At(1, 1) - At(0, 1) * At(1, 0);

        float fDet = 0;
        for (size_t i = 0; i < m_columns; i++)
            fDet += AlgComplement(0, i) * At(0, i);

        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        return fDet;
    }

    float Matrix::AlgComplement(const size_t i, const size_t j) const
    {
        const auto tmp = Minor(i, j);
        return ((i + j + 2) % 2 == 0) ? tmp : -tmp;
    }

    Matrix Matrix::Transpose() const
    {
        Matrix transposed = {m_columns, m_rows};

        for (size_t i = 0; i < m_rows; ++i)
            for (size_t j = 0; j < m_columns; ++j)
                transposed.At(j, i) = At(i, j);

        return transposed;
    }

    Matrix::~Matrix() = default;

    void Matrix::Set(const float val)
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        for (size_t i = 0; i < m_rows; ++i)
            for (size_t j = 0; j < m_columns; ++j)
                At(i, j) = val;
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
    }

    Matrix Matrix::Strip(const size_t row, const size_t column) const
    {
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_START)
        Matrix stripped = {m_rows - 1, m_columns - 1};
        size_t iStripRowIndex = 0;

        for (size_t i = 0; i < m_rows; i++)
        {
            if (i == row)
                continue;

            size_t iStripColumnIndex = 0;
            for (size_t j = 0; j < m_columns; ++j)
            {
                if (j == column)
                    continue;

                stripped.At(iStripRowIndex, iStripColumnIndex) = At(i, j);
                iStripColumnIndex++;
            }

            iStripRowIndex++;
        }
        OMATH_SE_PLACE_MACROS(VIRTUALIZER_MUTATE_ONLY_END)
        return stripped;
    }

    float Matrix::Minor(const size_t i, const size_t j) const
    {
        return Strip(i, j).Determinant();
    }

    Matrix Matrix::ToScreenMatrix(const float screenWidth, const float screenHeight)
    {
        return {
                {screenWidth / 2.f, 0.f, 0.f, 0.f},
                {0.f, -screenHeight / 2.f, 0.f, 0.f},
                {0.f, 0.f, 1.f, 0.f},
                {screenWidth / 2.f, screenHeight / 2.f, 0.f, 1.f},
        };
    }

    Matrix Matrix::TranslationMatrix(const Vector3<float>& diff)
    {
        return {
                {1.f, 0.f, 0.f, 0.f},
                {0.f, 1.f, 0.f, 0.f},
                {0.f, 0.f, 1.f, 0.f},
                {diff.x, diff.y, diff.z, 1.f},
        };
    }

    Matrix Matrix::OrientationMatrix(const Vector3<float>& forward, const Vector3<float>& right, const Vector3<float>& up)
    {
        return {
                {right.x, up.x, forward.x, 0.f},
                {right.y, up.y, forward.y, 0.f},
                {right.z, up.z, forward.z, 0.f},
                {0.f, 0.f, 0.f, 1.f},
        };
    }

    Matrix Matrix::ProjectionMatrix(const float fieldOfView, const float aspectRatio, const float near, const float far)
    {
        const float fovHalfTan = std::tan(angles::DegreesToRadians(fieldOfView) / 2.f);

        return {{1.f / (aspectRatio * fovHalfTan), 0.f, 0.f, 0.f},
                {0.f, 1.f / fovHalfTan, 0.f, 0.f},
                {0.f, 0.f, (far + near) / (far - near), 2.f * near * far / (far - near)},
                {0.f, 0.f, -1.f, 0.f}};
    }

    const float* Matrix::Raw() const
    {
        return m_data.get();
    }

    void Matrix::SetDataFromRaw(const float* pRawMatrix)
    {
        for (size_t i = 0; i < m_columns * m_rows; ++i)
            At(i / m_rows, i % m_columns) = pRawMatrix[i];
    }

    Matrix::Matrix()
    {
        m_columns = 0;
        m_rows = 0;
        m_data = nullptr;
    }
} // namespace omath
