#ifndef MATRIXX_H
#define MATRIXX_H

#include <vector>
#include "num.h"
#include <matrixv.h>

enum MatrixType {
    SourceMatrix,
    AfterClear,
    AfterGauss,
    InArtificialBasis,
    AfterArtificialBasis,
    InSimplexMethod,
    AfterSimplexMethod
};

class SIMPLEXLIB_EXPORT MatrixX : public MatrixV
{
public:
    // General
    MatrixX();
    MatrixX(const short rows, const short columns);
    MatrixX(const MatrixX& matrix);
    ~MatrixX();

    // Special
    // |  MatrixX*  |  OK                |
    // |  nullptr   |  Нет решений       |
    MatrixX* toClearGauss();
    // |  MatrixX*  |  OK                |
    // |  nullptr   |  Матрица вырождена |
    MatrixX* toGauss(const Basis& basis);
    // |  MatrixX*  |  Всегда            |
    MatrixX* toArtificialBasis();
    // |  MatrixX*  |  Всегда            |
    MatrixX* toSimplexFromGauss(const Basis& basis);
    // |  MatrixX*  |  OK                                |
    // |  nullptr   |  Искусственные переменные в базисе |
    MatrixX* toSimplexFromArtificialBasis(const MatrixX& abstractMatrix);
    // |  MatrixX*  |  Всегда            |
    MatrixX* toSimplexFromInequalities();


    MatrixX* nextStep(const short row, const short column);

    std::vector<num> getResult();

    //Other
    MatrixType getState();
    // Print
    std::string toString();
private:
    MatrixType m_state = MatrixType::SourceMatrix;
};

#endif // MATRIXX_H
