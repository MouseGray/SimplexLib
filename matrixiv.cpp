#include "matrixiv.h"

MatrixIV::MatrixIV()
{

}

MatrixIV::MatrixIV(short rows, short columns) :
    MatrixIII(rows, columns)
{
    init();
    MatrixIV::fNull(*this);
}

MatrixIV::MatrixIV(const MatrixIV &matrix) :
    MatrixIII(matrix)
{
    init();
    MatrixIV::fCopy(*this, matrix);
}

MatrixIV::~MatrixIV()
{
    free();
}

MatrixIV &MatrixIV::initialize(short rows, short columns)
{
    free();
    MatrixIII::initialize(rows, columns);
    init();
    MatrixIV::fNull(*this);
    return *this;
}

MatrixIV &MatrixIV::operator=(const MatrixIV &matrix)
{
    free();
    MatrixIII::operator=(matrix);
    init();
    MatrixIV::fCopy(*this, matrix);
    return *this;
}

num &MatrixIV::fRow(const short column)
{
    return m_fRow[column];
}

num &MatrixIV::fRow(const short column) const
{
    return m_fRow[column];
}

num &MatrixIV::f()
{
    return m_f;
}

void MatrixIV::swapColumns(const short first, const short second)
{
    MatrixIII::swapColumns(first, second);
    num temp = m_fRow[first];
    m_fRow[first] = m_fRow[second];
    m_fRow[second] = temp;
}

void MatrixIV::removeColumn(const short column)
{
    MatrixIII::removeColumn(column);
    for(int c = column; c < m_columns; c++){
        m_fRow[c] = m_fRow[c + 1];
    }
}

void MatrixIV::minusSumColumnsInF()
{
    byColumns{
        m_fRow[c] = -sumColumn(c);
    }
    m_f = -sumB();
}

void MatrixIV::multiplyColumnByWithout(const short column, const short row, const num value)
{
    MatrixIII::multiplyColumnByWithout(column, row, value);
    m_fRow[column] *= value;
}

void MatrixIV::fRowDifferenceWithout(const short row, const short column, const num coef)
{
    byColumns {
        if(c == column) continue;
        m_fRow[c] -= cell(row, c)*coef;
    }
    m_f -= b(row)*coef;
}

bool MatrixIV::nextSolveCell(short *row, short *column)
{
    if((*column = maxNegativeCoefficient()) < 0) return false; // Все неотрицательные
    int i = 1;
    while ((*row = minQuotient(*column)) < 0) {
        if((*column = maxNegativeCoefficient(i)) < 0) return false; // Все неотрицательные
        i++;
    }
    return true;
}

int MatrixIV::maxNegativeCoefficient()
{
    num max = 0;
    int maxPos = -1;
    byColumns{
        if(m_fRow[c] < max){
            max = m_fRow[c];
            maxPos = c;
        }
    }
    return maxPos;
}

bool comp(std::pair<int, num> a, std::pair<int, num> b){
    return a.second < b.second;
}

int MatrixIV::maxNegativeCoefficient(int index)
{
    if(index >= m_columns) return -1;
    std::vector<std::pair<int, num>> array;
    byColumns array.push_back({c, m_fRow[c]});
    std::sort(array.begin(), array.end(), comp);
    if(array[index].second >= 0) return -1;
    return array[index].first;
}

Matrix *MatrixIV::priorityMatrix()
{
    // | 0 | Преобразование недопустимо
    // | 1 | Преобразование не улучшит результат
    // | 2 | Преобразование улучшит результат
    // | 3 | Преобразование автомоматическое
    Matrix* matrix = new Matrix(*this);
    byColumns{
        if(m_fRow[c] >= 0)
            byRows matrix->cell(r, c) = 0;
        else{
            int minPos = minQuotient(c);
            if(minPos == -1) byRows matrix->cell(r, c) = 0;
            else {
                num minQuotient = Quotient(minPos, c);
                byRows {
                    if(cell(r, c) <= 0) matrix->cell(r, c) = 0;
                    else if(Quotient(r, c) == minQuotient) matrix->cell(r, c) = 2;
                    else matrix->cell(r, c) = 1;
                }
            }
        }
    }
    if(m_solveRow != -1 && m_solveColumn != -1) matrix->cell(m_solveRow, m_solveColumn) = 3;
    return matrix;
}

rgb **MatrixIV::colorMatrix(int *row, int *column)
{
    rgb** result = new rgb*[rows()];
    for(int i = 0; i < rows(); i++) result[i] = new rgb[columns()];

    byColumns{
        if(m_fRow[c] >= 0)
            byRows result[r][c].set(WHITE);
        else{
            int minPos = minQuotient(c);
            if(minPos == -1) byRows result[r][c].set(WHITE);
            else {
                num minQuotient = Quotient(minPos, c);
                byRows {
                    if(cell(r, c) <= 0) result[r][c].set(WHITE);
                    else if(Quotient(r, c) == minQuotient) result[r][c].set(GREEN);
                    else result[r][c].set(WHITE);
                }
            }
        }
    }
    if(row != nullptr) *row = rows();
    if(column != nullptr) *column = columns();
    if(m_solveRow != -1 && m_solveColumn != -1) result[m_solveRow][m_solveColumn].set(RED);
    return result;
}

void MatrixIV::toMin()
{
    byColumns{
        m_fRow[c] = -m_fRow[c];
    }
}

bool MatrixIV::hasNegativeColumn()
{
    byColumns{
        if(m_fRow[c] >= 0) continue;
        if(isNotPositiveColumn(c)) return true;
    }
    return false;
}

void MatrixIV::fCopy(MatrixIV &dist, const MatrixIV &src)
{
    byColumns_(src){
        dist.m_fRow[c] = src.m_fRow[c];
    }
    dist.m_f = src.m_f;
}

void MatrixIV::fNull(MatrixIV &dist)
{
    byColumns_(dist){
        dist.m_fRow[c] = 0;
    }
    dist.m_f = 0;
}

void MatrixIV::init()
{
    m_fRow = new num[m_columns];
}

void MatrixIV::free()
{
    delete [] m_fRow;
}
