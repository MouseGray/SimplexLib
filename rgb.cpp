#include "rgb.h"

rgb::rgb()
{

}

rgb::rgb(int r, int g, int b) :
    m_r(r),
    m_g(g),
    m_b(b)
{

}

void rgb::set(int r, int g, int b)
{
    m_r = r;
    m_g = g;
    m_b = b;
}
