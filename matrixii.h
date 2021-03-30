#ifndef MATRIXII_H
#define MATRIXII_H

#include "matrix.h"
#include <vector>

//  ------------------------
//  | a11   ...   a1m | b1 |
//  | ...   ...   ... | .. |
//  | an1   ...   anm | bn |
//  ------------------------
class SIMPLEXLIB_EXPORT MatrixII : public Matrix
{
public:
    MatrixII();
    MatrixII(short rows, short columns);
    MatrixII(const MatrixII &matrix);
    virtual ~MatrixII();

    MatrixII &initialize(short rows, short columns) override;
    MatrixII &operator=(const MatrixII &matrix);

    num& b(const short row);
    num& b(const short row) const;

    void swapRows(const short first, const short second) override;

    void multiplyRowBy(const short row, const num value) override;

    void multiplyRowByWithout(const short row, const short column, const num value) override;

    void divideRowBy(const short row, const num value) override;

    void rowDifference(const short dist, const short src, const num coef) override;

    void rowDifferenceWithout(const short dist, const short src, const short column, const num coef) override;

    void removeRow(const short row) override;

    bool isNegativB();

    void toNormalForm();

    num sumB();

    num Quotient(const short row, const short column);
    int minQuotient(const short column);

    bool Gauss(const Basis& params);

    MatrixII* Gauss_2();

    int null(const short row);

    static void BCopy(MatrixII &dist, const MatrixII &src);
    static void BNull(MatrixII &dist);
private:
    void init();
    void free();

    num* m_bColumn = nullptr;
};

#endif // MATRIXII_H
