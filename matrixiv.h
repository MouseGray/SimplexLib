#ifndef MATRIXIV_H
#define MATRIXIV_H

#include <algorithm>
#include <map>

#include "rgb.h"

#include "matrixiii.h"

//  -------------------
//  | x1    ...   xm  |
//  ------------------------
//  | a11   ...   a1m | b1 |
//  | ...   ...   ... | .. |
//  | an1   ...   anm | bn |
//  ------------------------
//  | k1    ...   km  | f  |
class SIMPLEXLIB_EXPORT MatrixIV : public MatrixIII
{
public:
    MatrixIV();
    MatrixIV(short rows, short columns);
    MatrixIV(const MatrixIV &matrix);
    virtual ~MatrixIV();

    MatrixIV &initialize(short rows, short columns) override;
    MatrixIV &operator=(const MatrixIV &matrix);

    num& fRow(const short column);
    num& fRow(const short column) const;

    num& f();

    inline short& solveRow() { return m_solveRow; }
    inline short& solveColumn() { return m_solveColumn; }

    void swapColumns(const short first, const short second) override;
    void removeColumn(const short column) override;

    void minusSumColumnsInF();

    void multiplyColumnByWithout(const short column, const short row, const num value) override;

    void fRowDifferenceWithout(const short row, const short column, const num coef);

    bool nextSolveCell(short* row, short* column);

    int maxNegativeCoefficient();
    int maxNegativeCoefficient(int index);

    Matrix* priorityMatrix();

    rgb** colorMatrix(int* row = nullptr, int* column = nullptr);

    void toMin();

    bool hasNegativeColumn();

    static void fCopy(MatrixIV &dist, const MatrixIV &src);
    static void fNull(MatrixIV &dist);
private:
    void init();
    void free();

    num* m_fRow = nullptr;
    num  m_f = 0;

    short m_solveRow = -1;
    short m_solveColumn = -1;
};

#endif // MATRIXIV_H
