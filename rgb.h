#ifndef RGB_H
#define RGB_H

#include "SimplexLib_global.h"

#define GREEN  127, 255, 0
#define RED    183, 0,   0
#define WHITE  255, 255, 255

class SIMPLEXLIB_EXPORT rgb
{
public:
    rgb();
    rgb(int r, int g, int b);

    void set(int r, int g, int b);

    inline int& r() { return m_r; };
    inline int& g() { return m_g; };
    inline int& b() { return m_b; };
private:
    int m_r = 0;
    int m_g = 0;
    int m_b = 0;
};

#endif // RGB_H
