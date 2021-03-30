#ifndef STORAGE_H
#define STORAGE_H

#include "matrixx.h"

#define MAXSTORAGE 100

class SIMPLEXLIB_EXPORT Storage
{
public:
    Storage();
    ~Storage();
    bool setMatrix(MatrixX* matrix);
    MatrixX* getMatrix(const int &pos);
    MatrixX* matrix();
    void setCursor(const int &cursor);
    int size() const;
    void clear();
private:
    int m_cursor = 0;

    MatrixX* m_container[MAXSTORAGE];
};

#endif // STORAGE_H
