#include "../core/BigInteger.h"


BigInteger::BigInteger(const BigInteger& other) {
    number_ = other.number_;
    p_ = other.p_;
}

BigInteger::BigInteger(std::string& a, int p, bool flag) {
    this->p_ = p;
    std::reverse(a.begin(), a.end());
    std::stringstream ss(a);
    char c;
    int i = 0;
    while (ss >> c) {
        if (i == this->number_.size()) {
            this->number_.push_back(0);
        }
        if (c >= 'A' && c <= 'Z') {
            this->number_[i] = c - 'A' + 10;
        } else if (c >= '0' && c <= '9') {
            this->number_[i] = c - '0';
        } else {
            if (c == '\n') continue;
            std::string num;
            while (ss >> c) {
                if (c != ']' && c != '[') {
                    num += c;
                } else {
                    break;
                }
            }
            std::reverse(num.begin(), num.end());
            this->number_[i] = std::stoi(num);
        }
        if (flag) {
            if (this->number_.back() >= p) {
                Errors = true;
            }
        }
        ++i;
    }
    lengthWithZeros = (int)this->number_.size();
    while (this->number_.back() == 0 && this->number_.size() > 1) {
        this->number_.pop_back();
    }
}

BigInteger::BigInteger(int len, int p) {
    this->number_.resize(len, 0);
    this->p_ = p;
}

std::vector<int> BigInteger::get_number() {
    std::vector<int> res = this->number_;
    std::reverse(res.begin(), res.end());
    return res;
}

int& BigInteger::get_p() {
    return p_;
}

bool BigInteger::GetErrors() const {
    return Errors;
}

BigInteger BigInteger::get_rank(int a, int p) {
    BigInteger res;
    res.p_ = p;
    while (a) {
        res.number_.push_back(a % p);
        a /= p;
    }
    return res;
}

void BigInteger::translation(int q) {
    if (this->p_ == q) {
        return;
    }
    if (this->number_.empty()) {
        return;
    }
    if (q > this->p_ || q == 10) {
        std::string str = "0";
        BigInteger res(str, q);
        str = "1";
        BigInteger pw(str, q);

        BigInteger pw_up;
        pw_up.p_ = q;
        if (q == 10 && this->p_ > q) {
            int n = this->p_;
            while (n) {
                pw_up.number_.push_back(n % 10);
                n /= 10;
            }
        } else {
            pw_up.number_.push_back(this->p_);
        }

        for (int i : this->number_) {
            res += get_rank(i, q) * pw;
            pw *= pw_up;
        }
        this->p_ = q;
        *this = res;
    } else {
        BigInteger res(0, q);
        BigInteger pw;
        pw.p_ = this->p_;
        int n = q;
        while (n) {
            pw.number_.push_back(n % this->p_);
            n /= this->p_;
        }
        std::string str = "0";
        BigInteger null(str, q);
        while (*this != null) {
            res.number_.push_back((*this % pw).number_[0]);
            *this /= pw;
        }
        this->p_ = q;
        if (res.number_.empty()) {
            res = BigInteger(str, q);
        }
        *this = res;
    }
}

void BigInteger::BinaryExponentiation(int n) {
    std::string one = "1";
    BigInteger res(one, this->p_);
    BigInteger number = *this;
    while (n) {
        if (n & 1) {
            res *= number;
            --n;
        } else {
            number *= number;
            n /= 2;
        }
    }
    *this = res;
}

bool BigInteger::operator==(const BigInteger& other) {
    if (other.number_.size() != this->number_.size()) {
        return false;
    }
    for (int i = 0; i < this->number_.size(); ++i) {
        if (this->number_[i] != other.number_[i]) {
            return false;
        }
    }
    return true;
}

bool BigInteger::operator>(const BigInteger& other) {
    for (int i = std::max((int)this->number_.size() - 1, (int)other.number_.size() - 1); i >= 0; --i) {
        if ((this->number_.size() > i ? this->number_[i] : 0) < (other.number_.size() > i ? other.number_[i] : 0)) {
            return false;
        } else if ((this->number_.size() > i ? this->number_[i] : 0) > (other.number_.size() > i ? other.number_[i] : 0)) {
            break;
        }
    }
    return !(*this == other);
}

bool BigInteger::operator<(const BigInteger &other) {
    for (int i = std::max((int)this->number_.size() - 1, (int)other.number_.size() - 1); i >= 0; --i) {
        if ((this->number_.size() > i ? this->number_[i] : 0) > (other.number_.size() > i ? other.number_[i] : 0)) {
            return false;
        } else if ((this->number_.size() > i ? this->number_[i] : 0) < (other.number_.size() > i ? other.number_[i] : 0)) {
            break;
        }
    }
    return !(*this == other);
}

BigInteger& BigInteger::operator=(const BigInteger& other) {
    number_ = other.number_;
    p_ = other.p_;
    return *this;
}

BigInteger BigInteger::operator+(const BigInteger& other) {
    BigInteger res = *this;
    int carry = 0;
    for (int i = 0; i < std::max(other.number_.size(), res.number_.size()) || carry; ++i) {
        if (res.number_.size() == i) {
            res.number_.push_back(0);
        }
        int num = (res.number_[i] + (other.number_.size() > i ? other.number_[i] : 0) + carry) % p_;
        carry = (res.number_[i] + (other.number_.size() > i ? other.number_[i] : 0) + carry) / p_;
        res.number_[i] = num;
    }
    return res;
}

BigInteger BigInteger::operator-(const BigInteger& other) {
    BigInteger a, b;
    if (*this > other) {
        a = *this;
        b = other;
    } else {
        b = *this;
        a = other;
    }
    int carry = 0;
    for (int i = 0; i < b.number_.size() || carry; ++i) {
        a.number_[i] -= carry + (i < b.number_.size() ? b.number_[i] : 0);
        if (a.number_[i] < 0) {
            carry = 1;
            a.number_[i] += p_;
        } else {
            carry = 0;
        }
    }
    while (a.number_.size() > 1 && a.number_.back() == 0) {
        a.number_.pop_back();
    }
    return a;
}

// приведение длинны к степени двойки
void BigInteger::SetLenKaratsuba(BigInteger &bi, int len) {
    while (len & (len - 1)) {
        ++len;
    }
    bi.number_.resize(len);
}

// наивное возведение
BigInteger BigInteger::SlowMultiplication(BigInteger &a, BigInteger &b) {
    BigInteger res((int)a.number_.size() * 2, a.p_);
    for (int i = 0; i < a.number_.size(); ++i) {
        for (int j = 0; j < a.number_.size(); ++j) {
            res.number_[i + j] += a.number_[i] * b.number_[j];
        }
    }
    return res;
}

void BigInteger::normalization(BigInteger &bi) {
    for (int i = 0; i < bi.number_.size(); ++i) {
        bi.number_[i + 1] += bi.number_[i] / bi.p_;
        bi.number_[i] %= bi.p_;
    }
    while (bi.number_.back() == 0 && bi.number_.size() > 1) {
        bi.number_.pop_back();
    }
}

BigInteger BigInteger::Karatsuba(BigInteger &a, BigInteger &b) {
    BigInteger res((int)a.number_.size() * 2, a.p_);
    if (a.number_.size() <= 512) {
        return SlowMultiplication(a, b);
    }
    int midl = (int)a.number_.size() / 2;
    BigInteger X_l(midl, a.p_), X_r(midl, a.p_), Y_l(midl, a.p_), Y_r(midl, a.p_);
    for (int i = 0; i < midl; ++i) {
        X_r.number_[i] = a.number_[i];
        Y_r.number_[i] = b.number_[i];
    }
    for (int i = midl; i < a.number_.size(); ++i) {
        X_l.number_[i - midl] = a.number_[i];
        Y_l.number_[i - midl] = b.number_[i];
    }
    BigInteger P1 = Karatsuba(X_l, Y_l);
    BigInteger P2 = Karatsuba(X_r, Y_r);
    BigInteger X(midl, a.p_), Y(midl, a.p_);
    for (int i = 0; i < a.number_.size(); ++i) {
        X.number_[i] = X_l.number_[i] + X_r.number_[i];
        Y.number_[i] = Y_l.number_[i] + Y_r.number_[i];
    }
    BigInteger P3 = Karatsuba(X, Y);
    for (int i = 0; i < a.number_.size(); ++i) {
        P3.number_[i] -= P1.number_[i] + P2.number_[i];
        res.number_[i] = P2.number_[i];
        res.number_[i + a.number_.size()] = P1.number_[i];
    }
    for (int i = midl; i < a.number_.size() + midl; ++i) {
        res.number_[i] += P3.number_[i - midl];
    }
    return res;
}

BigInteger BigInteger::operator*(const BigInteger& other) {
    int len = std::max((int)this->number_.size(), (int)other.number_.size());
    BigInteger a = *this;
    BigInteger b = other;
    SetLenKaratsuba(a, len);
    SetLenKaratsuba(b, len);
    BigInteger res = Karatsuba(a, b);
    normalization(res);
    return res;
}

BigInteger BigInteger::operator/(const int n) {
    BigInteger res = *this;
    for (int i = (int)res.number_.size() - 1; i >= 0; --i) {
        if (i) {
            res.number_[i - 1] += (res.number_[i] % n) * res.p_;
        }
        res.number_[i] /= n;
    }
    while (res.number_.back() == 0) {
        res.number_.pop_back();
    }
    return res;
}

BigInteger BigInteger::operator/(const BigInteger& other) {
    std::string str = "1";
    BigInteger one(str, this->p_);
    BigInteger l = one - one, r = *this + one, c = other;
    while (r - l > one) {
        BigInteger mid = (l + r) / 2;
        BigInteger res = mid * c;
        if (res > *this) {
            r = mid;
        } else {
            l = mid;
        }
    }
    return l;
}

BigInteger BigInteger::operator%(const BigInteger& other) {
    BigInteger res = *this - ((*this / other) * other);
    return res;
}

BigInteger& BigInteger::operator+=(const BigInteger& other) {
    *this = *this + other;
    return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& other) {
    *this = *this - other;
    return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
    *this = *this * other;
    return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
    *this = *this / other;
    return *this;
}

BigInteger& BigInteger::operator%=(const BigInteger& other) {
    *this = *this % other;
    return *this;
}

std::ostream& operator<<(std::ostream& out, BigInteger Bi) {
    std::vector<int> res = Bi.get_number();
    for (int re : res) {
        if (re >= 0 && re <= 9) {
            out << re;
        } else if (re >= 10 && re <= 35) {
            out << char(re - 10 + 'A');
        } else {
            out << '[' << re << ']';
        }
    }
    return out;
}

std::string out(std::string out, BigInteger& Bi) {
    std::vector<int> res = Bi.get_number();
    for (int re : res) {
        if (re >= 0 && re <= 9) {
            out += std::to_string(re);
        } else if (re >= 10 && re <= 35) {
            out += char(re - 10 + 'A');
        } else {
            out += '[';
            out += std::to_string(re);
            out += ']';
        }
    }
    return out;
}

bool BigInteger::operator!=(const BigInteger &other) {
    return !(*this == other);
}

int BigInteger::get_length() {
    return lengthWithZeros;
}
