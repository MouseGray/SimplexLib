#include "storage.h"

Storage::Storage()
{
}

Storage::~Storage()
{
    clear();
}

bool Storage::setMatrix(MatrixX *matrix)
{
    if(matrix == nullptr) return false;
    m_container[m_cursor] = matrix;
    m_cursor++;
    return true;
}

MatrixX *Storage::getMatrix(const int &pos)
{
    return pos < m_cursor ? m_container[pos] : nullptr;
}

MatrixX *Storage::matrix()
{
    return m_container[m_cursor - 1];
}

void Storage::setCursor(const int &cursor)
{
    if(cursor < m_cursor - 1){
        for(int i = cursor + 1; i < m_cursor; i++) delete m_container[i];
    }
    m_cursor = cursor + 1;
}

int Storage::size() const
{
    return m_cursor;
}

void Storage::clear()
{
    for(int i = 0; i < m_cursor; i++) delete m_container[i];
    m_cursor = 0;
}
