#ifndef MATRIXV_H
#define MATRIXV_H

#include "matrixiv.h"

class SIMPLEXLIB_EXPORT MatrixV : public MatrixIV
{
public:
    MatrixV();
    MatrixV(short rows, short columns);
    MatrixV(const MatrixV &matrix);
    virtual ~MatrixV();

    MatrixV &initialize(short rows, short columns) override;
    MatrixV &operator=(const MatrixV &matrix);

    header& vHeader(const short row);
    header& vHeader(const short row) const;

    void swapHeaders(const short row, const short column);

    void removeRow(const short row) override;

    void calculateBasis(const MatrixV &matrix);

    void simplex(const short row, const short column);

    bool clearGauss();

    bool clearMatrix();

    static void vHeaderCopy(MatrixV &dist, const MatrixV &src);
    static void vHeaderNull(MatrixV &dist);
private:
    void init();
    void free();

    header* m_vHeaders = nullptr;
};

#endif // MATRIXV_H
