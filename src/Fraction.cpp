#include "../core/Fraction.h"

BigInteger Fraction::gcd(BigInteger a, BigInteger b) {
    BigInteger null = a - a;
    while (a != null && b != null) {
        if (a > b) {
            a %= b;
        } else {
            b %= a;
        }
    }
    return a + b;
}

Fraction& Fraction::operator=(const Fraction &other) {
    num_ = other.num_;
    den_ = other.den_;
    return *this;
}

Fraction Fraction::operator+(const Fraction& other) {
    BigInteger i = other.num_, j = other.den_;
    BigInteger new_num = num_ * j + i * den_,  new_den = den_ * j;
    return Fraction(new_num, new_den);
}

Fraction Fraction::operator+=(const Fraction& other) {
    *this = *this + other;
    return *this;
}

void Fraction::set_gcd() {
    BigInteger n = gcd(num_, den_);
    num_ /= n;
    den_ /= n;
}

Fraction::Fraction(BigInteger &num, BigInteger &den) {
    num_ = num;
    den_ = den;
    set_gcd();
}

Fraction::Fraction(const Fraction &other) {
    num_ = other.num_;
    den_ = other.den_;
    set_gcd();
}

BigInteger Fraction::get_num() const {
    return num_;
}

BigInteger Fraction::get_den() const {
    return den_;
}

void Fraction::translation(int q) {
    this->den_.translation(10);
    this->num_.translation(10);
    std::map<Fraction, int> mp;
    std::string str = "0";
    BigInteger null(str, num_.get_p());
    str = std::to_string(q);
    BigInteger pow(str, 10, false);
    pow.translation(this->den_.get_p());
    int i = 0;
    if (num_ == den_) {
        carry = true;
    } else {
        carry = false;
    }
    while (num_ != null) {
        if (mp.find(*this) != mp.end()) {
            start = mp[*this];
            finish = i;
            break;
        }
        mp[*this] = i;
        if (den_ > num_) {
            num_ *= pow;
        }
        BigInteger res = (num_ / den_);
        res.translation(q);
        decimal.push_back(res);
        num_ %= den_;
        ++i;
    }
}

std::vector<BigInteger>& Fraction::get_decimal() {
    return decimal;
}

bool operator<(const Fraction& a, const Fraction& b) {
    BigInteger i = a.get_den(), j = b.get_den(), k = a.get_num(), l = b.get_num();
    return k * j < i * l;
}

bool operator>(const Fraction& a, const Fraction& b) {
    BigInteger i = a.get_den(), j = b.get_den(), k = a.get_num(), l = b.get_num();
    return k * j > i * l;
}
