#ifndef MATRIX_H
#define MATRIX_H

#include <basis.h>
#include <num.h>

#define byRows for(int r = 0; r < m_rows; r++)
#define byColumns for(int c = 0; c < m_columns; c++)

#define byRows_(mat) for(int r = 0; r < mat.m_rows; r++)
#define byColumns_(mat) for(int c = 0; c < mat.m_columns; c++)

//  -------------------
//  | a11   ...   a1m |
//  | ...   ...   ... |
//  | an1   ...   anm |
//  -------------------
class SIMPLEXLIB_EXPORT Matrix
{
public:
    Matrix();
    Matrix(short rows, short columns);
    Matrix(const Matrix &matrix);
    virtual ~Matrix();

    virtual Matrix &initialize(short rows, short columns);
    Matrix &operator=(const Matrix &matrix);

    num& cell(const short row, const short column);
    num& cell(const short row, const short column) const;

    inline int rows() const { return m_rows; }
    inline int columns() const { return m_columns; }

    virtual void swapRows(const short first, const short second);
    virtual void swapColumns(const short first, const short second);

    virtual void multiplyRowBy(const short row, const num value);

    virtual void multiplyRowByWithout(const short row, const short column, const num value);
    virtual void multiplyColumnByWithout(const short column, const short row, const num value);

    virtual void divideRowBy(const short row, const num value);

    virtual void rowDifference(const short dist, const short src, const num coef);

    virtual void rowDifferenceWithout(const short dist, const short src, const short column, const num coef);

    int absMaxPosColumn(const short start, const short column);
    num sumColumn(const short column);

    virtual void removeRow(const short row);
    virtual void removeColumn(const short column);

    bool isNotPositiveColumn(const short column);

    static void MatrixCopy(Matrix &dist, const Matrix &src);
    static void MatrixNull(Matrix &dist);
private:
    void init();
    void free();

    num** m_body = nullptr;
protected:
    short m_rows = 0;
    short m_columns = 0;
};

#endif // MATRIX_H
