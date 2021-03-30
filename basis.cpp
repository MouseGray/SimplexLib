#include "basis.h"

Basis::Basis()
{

}

Basis::~Basis()
{
    free();
}

void Basis::create(int size)
{
    free();
    m_size = size;
    m_body = new num[m_size];
    for(int i = 0; i < m_size; i++) m_body[i] = 0;
}

num &Basis::operator[](int i)
{
    return m_body[i];
}

num &Basis::operator[](int i) const
{
    return m_body[i];
}

void Basis::fill(const num &value)
{
    for(int i = 0; i < m_size; i++) m_body[i] = value;
}

void Basis::free()
{
    delete [] m_body;
}
