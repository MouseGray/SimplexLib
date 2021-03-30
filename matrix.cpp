#include "matrix.h"

Matrix::Matrix()
{

}

Matrix::Matrix(short rows, short columns) :
    m_rows(rows),
    m_columns(columns)
{
    init();
    Matrix::MatrixNull(*this);
}

Matrix::Matrix(const Matrix &matrix) :
    m_rows(matrix.m_rows),
    m_columns(matrix.m_columns)
{
    init();
    Matrix::MatrixCopy(*this, matrix);
}

Matrix::~Matrix()
{
    free();
}

Matrix &Matrix::initialize(short rows, short columns)
{
    free();
    m_rows    = rows;
    m_columns = columns;
    init();
    Matrix::MatrixNull(*this);
    return *this;
}

Matrix &Matrix::operator=(const Matrix &matrix)
{
    free();
    m_rows    = matrix.m_rows;
    m_columns = matrix.m_columns;
    init();
    Matrix::MatrixCopy(*this, matrix);
    return *this;
}

num &Matrix::cell(const short row, const short column)
{
    if(row < 0 || row >= m_rows) throw 0;
    if(column < 0 || column >= m_columns) throw 0;
    return m_body[row][column];
}

num &Matrix::cell(const short row, const short column) const
{
    if(row < 0 || row >= m_rows) throw 0;
    if(column < 0 || column >= m_columns) throw 0;
    return m_body[row][column];
}

void Matrix::swapRows(const short first, const short second)
{
    num temp;
    byColumns {
        temp = m_body[first][c];
        m_body[first][c] = m_body[second][c];
        m_body[second][c] = temp;
    }
}

void Matrix::swapColumns(const short first, const short second)
{
    num temp;
    byRows {
        temp = m_body[r][first];
        m_body[r][first] = m_body[r][second];
        m_body[r][second] = temp;
    }
}

void Matrix::multiplyRowBy(const short row, const num value)
{
    byColumns {
        m_body[row][c] *= value;
    }
}

void Matrix::multiplyRowByWithout(const short row, const short column, const num value)
{
    byColumns {
        if(c == column) continue;
        m_body[row][c] *= value;
    }
}

void Matrix::multiplyColumnByWithout(const short column, const short row, const num value)
{
    byRows {
        if(r == row) continue;
        m_body[r][column] *= value;
    }
}

void Matrix::divideRowBy(const short row, const num value)
{
    byColumns {
        m_body[row][c] /= value;
    }
}

void Matrix::rowDifference(const short dist, const short src, const num coef)
{
    byColumns {
        m_body[dist][c] -= m_body[src][c]*coef;
    }
}

void Matrix::rowDifferenceWithout(const short dist, const short src, const short column, const num coef)
{
    byColumns {
        if(c == column) continue;
        m_body[dist][c] -= m_body[src][c]*coef;
    }
}

int Matrix::absMaxPosColumn(const short start, const short column)
{
    int maxRow = start;
    num maxVal = m_body[start][column].abs();
    for(int r = start; r < m_rows; r++) {
        if(maxVal < m_body[r][column].abs()){
            maxVal = m_body[r][column].abs();
            maxRow = r;
        }
    }
    return maxRow;
}

num Matrix::sumColumn(const short column)
{
    num result = 0;
    byRows {
        result += m_body[r][column];
    }
    return result;
}

void Matrix::removeRow(const short row)
{
    m_rows--;
    byColumns{
        for(int r = row; r < m_rows; r++){
            m_body[r][c] = m_body[r + 1][c];
        }
    }
}

void Matrix::removeColumn(const short column)
{
    m_columns--;
    byRows{
        for(int c = column; c < m_columns; c++){
            m_body[r][c] = m_body[r][c + 1];
        }
    }
}

bool Matrix::isNotPositiveColumn(const short column)
{
    byRows{
        if(cell(r, column) > 0) return false;
    }
    return true;
}


void Matrix::MatrixCopy(Matrix &dist, const Matrix &src)
{
    byRows_(src)
        byColumns_(src)
            dist.m_body[r][c] = src.m_body[r][c];
}

void Matrix::MatrixNull(Matrix &dist)
{
    byRows_(dist)
        byColumns_(dist)
            dist.m_body[r][c] = 0;
}

void Matrix::init()
{
    m_body = new num*[m_rows];
    byRows m_body[r] = new num[m_columns];
}

void Matrix::free()
{
    byRows delete [] m_body[r];
    delete [] m_body;
}
