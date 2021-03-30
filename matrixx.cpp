#include "matrixx.h"

MatrixX::MatrixX(const short rows, const short columns) :
    MatrixV(rows, columns)
{
}

MatrixX::MatrixX(const MatrixX &matrix) :
    MatrixV(matrix),
    m_state(matrix.m_state)
{
}

MatrixX::~MatrixX()
{
}

MatrixX *MatrixX::toClearGauss()
{
    MatrixX* matrix = new MatrixX(*this);
    matrix->m_state = MatrixType::AfterClear;
    if(!matrix->clearMatrix()){
        delete matrix;
        return nullptr;
    }
    return matrix;
}

MatrixX *MatrixX::toGauss(const Basis &basis)
{
    MatrixX* matrix = new MatrixX(*this);
    matrix->m_state = MatrixType::AfterGauss;
    if(!matrix->Gauss(basis)){
        delete matrix;
        return nullptr;
    }
    if(matrix->isNegativB()){
        delete matrix;
        return nullptr;
    }
    if(!matrix->clearGauss()){
        delete matrix;
        return nullptr;
    }
    return matrix;
}

MatrixX *MatrixX::toArtificialBasis()
{
    MatrixX* matrix = new MatrixX(*this);
    byRows{
        matrix->vHeader(r) = header{'z', short(r)};
    }
    matrix->m_state = MatrixType::InArtificialBasis;
    matrix->minusSumColumnsInF();
    return matrix;
}

MatrixX *MatrixX::toSimplexFromGauss(const Basis &basis)
{
    MatrixX* matrix = new MatrixX(m_rows, m_columns - m_rows);
    matrix->m_state = MatrixType::InSimplexMethod;
    int curBasisVar = 0;
    byColumns{
        if(basis[c] != 0){
            matrix->vHeader(curBasisVar) = cHeader(c);
            curBasisVar++;
            continue;
        }
        byRows_((*matrix))
            matrix->cell(r, c - curBasisVar) = cell(r, c);
        matrix->cHeader(c - curBasisVar) = cHeader(c);
    }
    MatrixV::BCopy(*matrix, *this);
    matrix->calculateBasis(*this);
    return matrix;
}

#define exit        {return matrix;}
#define error_exit  {delete matrix; return nullptr;}
MatrixX *MatrixX::toSimplexFromArtificialBasis(const MatrixX &abstractMatrix)
{
    MatrixX* matrix = new MatrixX(*this);
    m_state = MatrixType::AfterArtificialBasis;
    matrix->m_state = MatrixType::InSimplexMethod;
    byRows if(vHeader(r).symbol == 'z') {
        if(fRow(r) == 0) {
            swapHeaders(r, 0);
            removeColumn(0);
        }
        else error_exit;
    }
    matrix->calculateBasis(abstractMatrix);
    exit;
}
#undef exit
#undef error_exit

MatrixX *MatrixX::toSimplexFromInequalities()
{
    MatrixX *matrix = new MatrixX(*this);
    matrix->m_state = MatrixType::InSimplexMethod;
    byRows{
        matrix->vHeader(r) = header{'z', short(r)};
    }
    return matrix;
}

MatrixX *MatrixX::nextStep(const short row, const short column)
{
    MatrixX* matrix = new MatrixX(*this);
    solveRow() = row;
    solveColumn() = column;
    matrix->simplex(row, column);
    return matrix;
}

std::string MatrixX::toString()
{
    std::string text;
    text += "h ";
    for(int _column_ = 0; _column_ < m_columns; _column_++){
        text += cHeader(_column_).symbol + std::to_string(cHeader(_column_).index) + " ";
    }
    text += "\n";

    for(int _row_ = 0; _row_ < m_rows; _row_++){
        text += cHeader(_row_).symbol + std::to_string(cHeader(_row_).index) + " ";
        for(int _column_ = 0; _column_ < m_columns; _column_++){
            text += cell(_row_, _column_).toString() + " ";
        }
        text += b(_row_).toString() + " ";
        text += "\n";
    }
    text += "F ";
    for(int _column_ = 0; _column_ < m_columns; _column_++){
        text += fRow(_column_).toString() + " ";
    }
    text += f().toString() + " ";
    text += "\n";
    return text;
}

std::vector<num> MatrixX::getResult()
{
    std::vector<num> result;
    int size = 0;
    byColumns if(cHeader(c).symbol == 'x') size++;
    byRows if(vHeader(r).symbol == 'x') size++;

    result.resize(size, 0);
    byRows{
        if(vHeader(r).symbol == 'x'){
            result[vHeader(r).index] = b(r);
        }
    }
    return result;
}

MatrixType MatrixX::getState()
{
    return m_state;
}
