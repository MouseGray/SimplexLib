#include "matrixv.h"

MatrixV::MatrixV()
{

}

MatrixV::MatrixV(short rows, short columns) :
    MatrixIV(rows, columns)
{
    init();
    MatrixV::vHeaderNull(*this);
}

MatrixV::MatrixV(const MatrixV &matrix) :
    MatrixIV(matrix)
{
    init();
    MatrixV::vHeaderCopy(*this, matrix);
}

MatrixV::~MatrixV()
{
    free();
}

MatrixV &MatrixV::initialize(short rows, short columns)
{
    free();
    MatrixIV::initialize(rows, columns);
    init();
    MatrixV::vHeaderNull(*this);
    return *this;
}

MatrixV &MatrixV::operator=(const MatrixV &matrix)
{
    free();
    MatrixIV::operator=(matrix);
    init();
    MatrixV::vHeaderCopy(*this, matrix);
    return *this;
}

header &MatrixV::vHeader(const short row)
{
    return m_vHeaders[row];
}

header &MatrixV::vHeader(const short row) const
{
    return m_vHeaders[row];
}

void MatrixV::swapHeaders(const short row, const short column)
{
    header temp = cHeader(column);
    cHeader(column) = vHeader(row);
    vHeader(row) = temp;
}

void MatrixV::calculateBasis(const MatrixV &matrix)
{
    num value = 0;
    byColumns{
        value = 0;
        byRows value += -cell(r, c)*matrix.fRow(vHeader(r).index);
        value += matrix.fRow(cHeader(c).index);
        fRow(c) = value;
    }
    value = 0;
    byRows value += b(r)*matrix.fRow(vHeader(r).index);
    f() = -value;
}

void MatrixV::simplex(const short row, const short column)
{
    swapHeaders(row, column);
    cell(row, column) = num(1)/cell(row, column);

    multiplyRowByWithout(row, column, cell(row, column));

    for(int r = 0; r < m_rows; r++){
        if(r == row) continue;
        rowDifferenceWithout(r, row, column, cell(r, column));
    }

    fRowDifferenceWithout(row, column, fRow(column));

    multiplyColumnByWithout(column, row, -cell(row, column));

    if(cHeader(column).symbol == 'z') removeColumn(column);
}

bool MatrixV::clearGauss()
{
    bool isNull;
    for(int r = m_rows - 1; r >= 0; r--){
        isNull = true;
        byColumns{
            if(cell(r, c) != 0){
                isNull = false;
                break;
            }
        }
        if(!isNull) continue;
        if(b(r) != 0) return false;
        removeRow(r);
    }
    return true;
}

bool MatrixV::clearMatrix()
{
    MatrixII* matrix = Gauss_2();
    for(int r = m_rows - 1; r >= 0; r--){
        int result = matrix->null(r);
        if(result == -1) return false; // Нет решения
        else if(result == 1) removeRow(r);
    }
    delete matrix;
    return true;
}

void MatrixV::vHeaderCopy(MatrixV &dist, const MatrixV &src)
{
    byRows_(src){
        dist.m_vHeaders[r] = src.m_vHeaders[r];
    }
}

void MatrixV::vHeaderNull(MatrixV &dist)
{
    byRows_(dist){
        dist.m_vHeaders[r] = header{ 'x', short(dist.m_columns + r) };
    }
}

void MatrixV::init()
{
    m_vHeaders = new header[m_rows];
}

void MatrixV::free()
{
    delete [] m_vHeaders;
}


void MatrixV::removeRow(const short row)
{
    MatrixIV::removeRow(row);
    for(int r = 0; r < m_rows; r++){
        m_vHeaders[r] = m_vHeaders[r + 1];
    }
}
