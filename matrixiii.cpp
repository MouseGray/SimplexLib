#include "matrixiii.h"

MatrixIII::MatrixIII()
{

}

MatrixIII::MatrixIII(short rows, short columns) :
    MatrixII(rows, columns)
{
    init();
    MatrixIII::cHeaderNull(*this);
}

MatrixIII::MatrixIII(const MatrixIII &matrix) :
    MatrixII(matrix)
{
    init();
    MatrixIII::cHeaderCopy(*this, matrix);
}

MatrixIII::~MatrixIII()
{
    free();
}

MatrixIII &MatrixIII::initialize(short rows, short columns)
{
    free();
    MatrixII::initialize(rows, columns);
    init();
    MatrixIII::cHeaderNull(*this);
    return *this;
}

MatrixIII &MatrixIII::operator=(const MatrixIII &matrix)
{
    free();
    MatrixII::operator=(matrix);
    init();
    MatrixIII::cHeaderCopy(*this, matrix);
    return *this;
}

header &MatrixIII::cHeader(const short column)
{
    return m_cHeaders[column];
}

header &MatrixIII::cHeader(const short column) const
{
    return m_cHeaders[column];
}

void MatrixIII::swapColumns(const short first, const short second)
{
    Matrix::swapColumns(first, second);
    header temp = m_cHeaders[first];
    m_cHeaders[first] = m_cHeaders[second];
    m_cHeaders[second] = temp;
}


void MatrixIII::removeColumn(const short column)
{
    Matrix::removeColumn(column);
    for(int c = column; c < m_columns; c++){
        m_cHeaders[c] = m_cHeaders[c + 1];
    }
}

void MatrixIII::cHeaderCopy(MatrixIII &dist, const MatrixIII &src)
{
    byColumns_(src){
        dist.m_cHeaders[c] = src.m_cHeaders[c];
    }
}

void MatrixIII::cHeaderNull(MatrixIII &dist)
{
    byColumns_(dist){
        dist.m_cHeaders[c] = header{ 'x', short(c) };
    }
}

void MatrixIII::init()
{
    m_cHeaders = new header[m_columns];
}

void MatrixIII::free()
{
    delete [] m_cHeaders;
}
