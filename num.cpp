#include "num.h"

num::num() {}

num::num(int value) :
    numerator(value),
    denominator(1) {}

num::num(int numerator, int denominator) :
    numerator(numerator),
    denominator(denominator)
{
    this->toNormalForm();
}

num::num(float value)
{
    this->numerator = int(value*this->accuracy);
    this->numerator = accuracy;
    this->toNormalForm();
}

num::num(const num &number)
{
    this->numerator = number.numerator;
    this->denominator = number.denominator;
}

num num::operator-()
{
    return num(*this) *= -1;
}

num num::operator-(const num &rvalue)
{
    return num(*this) -= rvalue;
}

num num::operator+(const num& value)
{
    return num(*this) += value;
}

num num::operator*(const num& value)
{
    return num(*this) *= value;
}

num num::operator/(const num& value)
{
    return num(*this) /= value;
}

num& num::operator=(const num& value)
{
    this->numerator = value.numerator;
    this->denominator = value.denominator;
    return *this;
}

num& num::operator-=(const num& value)
{
    if(_is_undefined((*this))) return *this;
    if(_is_undefined(value)) return *this = value;

    if(_is_infinity((*this))) return *this;
    if(_is_infinity(value)) return *this = value;

    this->numerator = this->numerator*value.denominator - value.numerator*this->denominator;
    this->denominator = this->denominator*value.denominator;

    this->toNormalForm();

    return *this;
}

num& num::operator+=(const num& value)
{
    if(_is_undefined((*this))) return *this;
    if(_is_undefined(value)) return *this = value;

    if(_is_infinity((*this))) return *this;
    if(_is_infinity(value)) return *this = value;

    this->numerator = this->numerator*value.denominator + value.numerator*this->denominator;
    this->denominator = this->denominator*value.denominator;

    this->toNormalForm();

    return *this;
}

num& num::operator*=(const num& value)
{
    if(_is_undefined((*this))) return *this;
    if(_is_undefined(value)) return *this = value;

    if(_is_infinity((*this))) return *this;
    if(_is_infinity(value)) return *this = value;

    this->numerator = this->numerator*value.numerator;
    this->denominator = this->denominator*value.denominator;

    this->toNormalForm();

    return *this;
}

num& num::operator/=(const num& value)
{
    if(_is_undefined((*this))) return *this;
    if(_is_undefined(value)) return *this = value;

    if(_is_infinity((*this))) return *this;
    if(_is_infinity(value)) return *this = value;

    this->numerator = this->numerator*value.denominator;
    this->denominator = this->denominator*value.numerator;

    this->toNormalForm();

    return *this;
}

bool num::operator>(const num& value) const
{
    if(_is_undefined((*this))) return false;
    if(_is_undefined(value)) return false;

    if(_is_infinity((*this))) return true;
    if(_is_infinity(value)) return false;

    return this->numerator*value.denominator > value.numerator*this->denominator;
}

bool num::operator<(const num& value) const
{
    if(_is_undefined((*this))) return false;
    if(_is_undefined(value)) return false;

    if(_is_infinity((*this))) return false;
    if(_is_infinity(value)) return true;

    return this->numerator*value.denominator < value.numerator*this->denominator;
}

bool num::operator==(const num& value) const
{
    if(_is_undefined((*this))) return false;
    if(_is_undefined(value)) return false;

    if(_is_infinity((*this))) return false;
    if(_is_infinity(value)) return false;

    return this->numerator*value.denominator == value.numerator*this->denominator;
}

bool num::operator!=(const num& value) const
{
    if(_is_undefined((*this))) return false;
    if(_is_undefined(value)) return false;

    if(_is_infinity((*this))) return false;
    if(_is_infinity(value)) return false;

    return this->numerator*value.denominator != value.numerator*this->denominator;
}

bool num::operator>=(const num& value) const
{
    if(_is_undefined((*this))) return false;
    if(_is_undefined(value)) return false;

    if(_is_infinity((*this))) return true;
    if(_is_infinity(value)) return false;

    return this->numerator*value.denominator >= value.numerator*this->denominator;
}

bool num::operator<=(const num& value) const
{
    if(_is_undefined((*this))) return false;
    if(_is_undefined(value)) return false;

    if(_is_infinity((*this))) return false;
    if(_is_infinity(value)) return true;

    return this->numerator*value.denominator <= value.numerator*this->denominator;
}

num num::abs()
{
    num result;
    result.numerator = ::abs(this->numerator);
    result.denominator = ::abs(this->denominator);
    return result;
}

double num::toDouble()
{
    if(_is_undefined((*this))) return 0.0;
    if(_is_infinity((*this))) return 0.0;

    return (double)numerator/denominator;
}

std::string num::toString() const
{
    if(!denominator){
        if(!numerator) return "undefined";
        return "inf";
    }
    if(denominator == 1) return std::to_string(numerator);
    return std::to_string(numerator) + "/" + std::to_string(denominator);
}

num num::fromString(const char *text)
{
    std::string str(text);
    size_t sepPos = 0;
    if((sepPos = str.find_first_of('.')) != std::string::npos) {
        return num(std::stof(str));
    }
    if((sepPos = str.find_first_of('/')) != std::string::npos) {
        return num(std::stoi(str.substr(0, sepPos)), std::stoi(str.substr(sepPos + 1)));
    }
    return num(std::stoi(str));
}

num num::wholePart()
{
    return num(int(numerator/(double)denominator));
}

num num::fractionalPart()
{
    return num(numerator - wholePart().numerator*denominator, denominator);
}

long long num::gcd(long long a, long long b)
{
    for (long long c; b;) {
        c = a % b;
        a = b;
        b = c;
    }
    return ::abs(a);
}

void num::toNormalForm()
{
    if(_is_infinity((*this))) {
        numerator = 1;
    }
    if(numerator == 0){
        denominator = 1;
        return;
    }
    if(numerator < 0 && denominator < 0){
        numerator = -numerator;
        denominator = -denominator;
    }
    if(denominator < 0){
        numerator = -numerator;
        denominator = -denominator;
    }

    long long _gcd = gcd(numerator, denominator);
    this->numerator = numerator/_gcd;
    this->denominator = denominator/_gcd;

//    for(int i = ::abs(numerator) > ::abs(denominator) ? ::abs(denominator) : ::abs(numerator); i >= 2; i--){
//        if((numerator % i == 0) && (denominator % i == 0)){
//            this->numerator = numerator/i;
//            this->denominator = denominator/i;
//            i = (::abs(numerator) > ::abs(denominator) ? ::abs(denominator) : ::abs(numerator)) + 1;
//        }
//    }
}
