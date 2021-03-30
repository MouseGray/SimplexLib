#ifndef NUM_H
#define NUM_H

#include "SimplexLib_global.h"

#include <string>

#define _is_undefined(a) (a.numerator == 0 && a.denominator == 0)
#define _is_infinity(a) (a.numerator != 0 && a.denominator == 0)

#define num_undefined num(0, 0)

#define n0 num(0)
#define n1 num(1)

using byte_t = unsigned char;

class SIMPLEXLIB_EXPORT num
{
public:
    num();
    num(int value);
    num(int numerator, int denominator);
    num(float value);
    num(const num& number);

    num operator-();
    num operator-(const num& rvalue);
    num operator+(const num& value);
    num operator*(const num& value);
    num operator/(const num& value);
    num& operator=(const num& value);
    num& operator-=(const num& value);
    num& operator+=(const num& value);
    num& operator*=(const num& value);
    num& operator/=(const num& value);

    bool operator>(const num& value) const;
    bool operator<(const num& value) const;
    bool operator==(const num& value) const;
    bool operator!=(const num& value) const;
    bool operator>=(const num& value) const;
    bool operator<=(const num& value) const;

    num abs();

    double toDouble();

    std::string toString() const;

    static num fromString(const char* text);

    num wholePart();
    num fractionalPart();

    static long long gcd(long long a, long long b);
private:
    void toNormalForm();

    long long numerator = 0;
    long long denominator = 1;

    static const long accuracy = 10000;
};

#endif // NUM_H
