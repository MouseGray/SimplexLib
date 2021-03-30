#include "matrixii.h"

MatrixII::MatrixII()
{

}

MatrixII::MatrixII(short rows, short columns) :
    Matrix(rows, columns)
{
    init();
    MatrixII::BNull(*this);
}

MatrixII::MatrixII(const MatrixII &matrix) :
    Matrix(matrix)
{
    init();
    MatrixII::BCopy(*this, matrix);
}

MatrixII::~MatrixII()
{
    free();
}

MatrixII &MatrixII::initialize(short rows, short columns)
{
    free();
    Matrix::initialize(rows, columns);
    init();
    MatrixII::BNull(*this);
    return *this;
}

MatrixII &MatrixII::operator=(const MatrixII &matrix)
{
    free();
    Matrix::operator=(matrix);
    init();
    MatrixII::BCopy(*this, matrix);
    return *this;
}

num &MatrixII::b(const short row)
{
    return m_bColumn[row];
}

num &MatrixII::b(const short row) const
{
    return m_bColumn[row];
}

void MatrixII::swapRows(const short first, const short second)
{
    Matrix::swapRows(first, second);
    num temp = m_bColumn[first];
    m_bColumn[first] = m_bColumn[second];
    m_bColumn[second] = temp;
}

void MatrixII::multiplyRowBy(const short row, const num value)
{
    Matrix::multiplyRowBy(row, value);
    m_bColumn[row] *= value;
}

void MatrixII::multiplyRowByWithout(const short row, const short column, const num value)
{
    Matrix::multiplyRowByWithout(row, column, value);
    m_bColumn[row] *= value;
}

void MatrixII::divideRowBy(const short row, const num value)
{
    Matrix::divideRowBy(row, value);
    m_bColumn[row] /= value;
}

void MatrixII::rowDifference(const short dist, const short src, const num coef)
{
    Matrix::rowDifference(dist, src, coef);
    m_bColumn[dist] -= m_bColumn[src]*coef;
}

void MatrixII::rowDifferenceWithout(const short dist, const short src, const short column, const num coef)
{
    Matrix::rowDifferenceWithout(dist, src, column, coef);
    m_bColumn[dist] -= m_bColumn[src]*coef;
}

num MatrixII::sumB()
{
    num value = 0;
    byRows{
        value += m_bColumn[r];
    }
    return value;
}

num MatrixII::Quotient(const short row, const short column)
{
    return m_bColumn[row] / cell(row, column);
}

int MatrixII::minQuotient(const short column)
{
    int minPos = -1;
    num curVal = 0;
    num minVal = INFINITY;
    byRows{
        if(cell(r, column) <= 0) continue;
        curVal = m_bColumn[r] / cell(r, column);
        if(curVal < minVal){
            minVal = curVal;
            minPos = r;
        }
    }
    return minPos;
}

bool MatrixII::Gauss(const Basis& params)
{
    int index;
    // Прямой ход
    for (int c = 0, step = 0; c < params.size(); c++)
    {
        if(params[c] == 0) continue;
        index = absMaxPosColumn(step, c);
        // Если максимум по абсолютному значению равен нулю, значит весь столбец равен нулю
        // следовательно матрица вырождена
        if (cell(index, c) == 0) return false;
        // Меняем строки местами (ставим строку с наибольшим коэффициентов в самый верх)
        swapRows(step, index);
        // Делим строку на головной элемент (приводим его к 1)
        divideRowBy(step, cell(step, c));

        for (int i = step + 1; i < m_rows; i++)
            rowDifference(i, step, cell(i, c));

        step++;
    }
    // Обратный ход
    for (int c = params.size() - 1, step = rows() - 1; c >= 0; c--)
    {
        if(params[c] == 0) continue;
        for (int r = 0; r < step; r++)
        {
            rowDifference(r, step, cell(r, c));
        }
        step--;
    }
    return true;
}

MatrixII *MatrixII::Gauss_2()
{
    int index;
    MatrixII *matrix = new MatrixII(*this);

    // Прямой ход
    for (int c = 0, step = 0; c < matrix->columns(); c++)
    {
        index = matrix->absMaxPosColumn(step, c);
        // Если максимум по абсолютному значению равен нулю, значит весь столбец равен нулю
        // следовательно матрица вырождена
        if (matrix->cell(index, c) == 0) continue;
        // Делим строку на головной элемент (приводим его к 1)
        matrix->divideRowBy(step, matrix->cell(step, c));

        for (int i = step + 1; i < matrix->rows(); i++)
            matrix->rowDifference(i, step, matrix->cell(i, c));

        step++;
    }

    return matrix;
}

int MatrixII::null(const short row)
{
    byColumns{
        if(cell(row, c) != 0) return 0;
    }
    if(b(row) != 0) return -1;
    return 1;
}

void MatrixII::BCopy(MatrixII &dist, const MatrixII &src)
{
    byRows_(src){
        dist.m_bColumn[r] = src.m_bColumn[r];
    }
}

void MatrixII::BNull(MatrixII &dist)
{
    byRows_(dist){
        dist.m_bColumn[r] = 0;
    }
}

void MatrixII::init()
{
    m_bColumn = new num[m_rows];
}

void MatrixII::free()
{
    delete [] m_bColumn;
}


void MatrixII::removeRow(const short row)
{
    Matrix::removeRow(row);
    for(int r = row; r < m_rows; r++){
        m_bColumn[r] = m_bColumn[r + 1];
    }
}

bool MatrixII::isNegativB()
{
    byRows{
        if(m_bColumn[r] < 0) return true;
    }
    return false;
}

void MatrixII::toNormalForm()
{
    byRows{
        if(m_bColumn[r] < 0){
            multiplyRowBy(r, -1);
        }
    }
}
