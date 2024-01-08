#pragma once
#include "BigInteger.h"

class Fraction {
public:
    Fraction() = default;
    Fraction(BigInteger& num, BigInteger& den);
    Fraction(const Fraction& other);
    ~Fraction() = default;
    Fraction& operator=(const Fraction& other);
    Fraction operator+(const Fraction& other);
    Fraction operator+=(const Fraction& other);
    [[nodiscard]] BigInteger get_num() const;
    [[nodiscard]] BigInteger get_den() const;
    void translation(int q);
    std::vector<BigInteger>& get_decimal();

    friend bool operator<(const Fraction& a, const Fraction& b);
    friend bool operator>(const Fraction& a, const Fraction& b);

    int start = -1, finish = -1;

    bool carry = false;

private:
    std::vector<BigInteger> decimal;
    void set_gcd();
    static BigInteger gcd(BigInteger a, BigInteger b);
    BigInteger num_;
    BigInteger den_;
};
