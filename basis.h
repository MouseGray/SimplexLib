#ifndef BASIS_H
#define BASIS_H

#include "num.h"

class SIMPLEXLIB_EXPORT Basis
{
public:
    Basis();
    ~Basis();
    void create(int size);
    num& operator[](int i);
    num& operator[](int i) const;
    inline int size() const { return m_size; }
    void normalize();

    void fill(const num &value);
private:
    void free();
    num* m_body = nullptr;
    int  m_size = 0;
};

#endif // BASIS_H
