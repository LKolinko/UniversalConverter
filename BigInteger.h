#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>
#include <map>

class BigInteger {
public:
    BigInteger() = default;
    BigInteger(std::string& a, int p, bool flag = true);
    BigInteger(int len, int p);
    BigInteger(const BigInteger& other);
    ~BigInteger() = default;
    std::vector<int> get_number();
    int& get_p();
    int get_length();
    static void normalization(BigInteger& bi);
    bool operator==(const BigInteger& other);
    bool operator!=(const BigInteger& other);
    bool operator>(const BigInteger& other);
    bool operator<(const BigInteger& other);
    static BigInteger get_rank(int a, int p);
    void BinaryExponentiation(int n);
    void translation(int q);
    BigInteger& operator=(const BigInteger& other);
    BigInteger operator+(const BigInteger& other);
    BigInteger operator-(const BigInteger& other);
    BigInteger operator*(const BigInteger& other);
    BigInteger operator/(const BigInteger& other);
    BigInteger operator/(int n);
    BigInteger operator%(const BigInteger& other);
    BigInteger& operator+=(const BigInteger& other);
    BigInteger& operator-=(const BigInteger& other);
    BigInteger& operator*=(const BigInteger& other);
    BigInteger& operator/=(const BigInteger& other);
    BigInteger& operator%=(const BigInteger& other);
    [[nodiscard]] bool GetErrors() const;

    friend std::string out(std::string out, BigInteger& Bi);
    friend std::ostream& operator<<(std::ostream& out, BigInteger Bi);

private:
    int lengthWithZeros;
    bool Errors = false;
    static void SetLenKaratsuba(BigInteger &bi, int len);
    BigInteger Karatsuba(BigInteger &a, BigInteger &b);
    static BigInteger SlowMultiplication(BigInteger &a, BigInteger &b);
    int p_{};
    std::vector<int> number_;
};
