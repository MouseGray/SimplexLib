#ifndef MATRIXIII_H
#define MATRIXIII_H

#include "matrixii.h"

struct header {
    char symbol = 'x';
    short index = 0;
};
//  -------------------
//  | x1    ...   xm  |
//  ------------------------
//  | a11   ...   a1m | b1 |
//  | ...   ...   ... | .. |
//  | an1   ...   anm | bn |
//  ------------------------
class SIMPLEXLIB_EXPORT MatrixIII : public MatrixII
{
public:
    MatrixIII();
    MatrixIII(short rows, short columns);
    MatrixIII(const MatrixIII &matrix);
    virtual ~MatrixIII();

    MatrixIII &initialize(short rows, short columns) override;
    MatrixIII &operator=(const MatrixIII &matrix);

    header& cHeader(const short column);
    header& cHeader(const short column) const;

    void swapColumns(const short first, const short second) override;

    void removeColumn(const short column) override;

    static void cHeaderCopy(MatrixIII &dist, const MatrixIII &src);
    static void cHeaderNull(MatrixIII &dist);
private:
    void init();
    void free();

    header* m_cHeaders = nullptr;
};

#endif // MATRIXIII_H
