// Aiden Perkins
// CECS 325-02
// Prog 6 – BigInt class
// Due 5-9-2024
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <vector>
#include <string>
#include <iostream>
#include <climits>
#include <iomanip>

using namespace std;

class BigInt {
    private:
        vector<char> digits;
        BigInt fiboHelper(const BigInt&, const BigInt&, const BigInt&);
        BigInt factHelper(const BigInt&, const BigInt&);
    public:
        BigInt();
        BigInt(int);
        BigInt(string);

        BigInt &operator=(const BigInt&);

        BigInt operator++();
        BigInt operator++(int);

        friend BigInt &operator+=(BigInt&, const BigInt&);
        friend BigInt operator+(const BigInt&, const BigInt&);
        friend BigInt operator+(const int&, const BigInt&);
        friend BigInt operator-(const BigInt&, const BigInt&);
        friend BigInt operator-(const BigInt&, const int&);
        friend BigInt operator*(const BigInt&, const BigInt&);
        friend BigInt operator/(const BigInt&, const BigInt&);
        friend BigInt operator%(const BigInt&, const BigInt&);

        friend bool operator==(const BigInt&, const BigInt&);
        friend bool operator>(const BigInt&, const BigInt&);
        char operator[](int) const; // index function
        void print();
        int size() const;

        BigInt fibo(); // calls fiboHelper
        BigInt fact();

        friend ostream& operator<<(ostream&, const BigInt&);
};

BigInt BigInt::fiboHelper(const BigInt &n, const BigInt &a = 0, const BigInt &b = 1) {
    if (n == 0) {
        return a;
    } else if (n == 1) {
        return b;
    } else {
        return fiboHelper(n - 1, b, a + b);
    }
}

BigInt BigInt::factHelper(const BigInt &n, const BigInt &a = 1) {
    if (2 > n) {
        return a;
    }
    return factHelper(n - 1, n * a);
}

BigInt::BigInt() = default;

BigInt::BigInt(int num) {
    if (num == 0) {
        digits.push_back(0);
    } else {
        while (num > 0) {
            digits.push_back(num % 10);
            num /= 10;
        }
    }
}

BigInt::BigInt(string str) {
    for (int i = int(str.size()) - 1; i > -1; --i) {
        digits.push_back(str[i] - '0');
    }
}

BigInt &BigInt::operator=(const BigInt &a) = default;

BigInt operator+(const BigInt &a, const BigInt &b) {
    if (a > b) {
        BigInt result = a;
        result += b;
        return result;
    } else {
        BigInt result = b;
        result += a;
        return result;
    }
}

BigInt operator+(const int &a, const BigInt &b) {
    return b + BigInt(a);
}

BigInt operator-(const BigInt &a, const BigInt &b) {
    // This function assumes a >= b.
    BigInt result = a;
    int aSize = int(result.size());
    int bSize = int(b.size());
    for (int i = 0; i < aSize; ++i) {
        if (i < bSize) {
            if (result[i] >= b[i]) {
                result.digits[i] = result[i] - b[i];
            } else {
                result.digits[i] = (result[i] + 10) - b[i];
                int j = 1;
                while (result[i + j] == 0) {
                    result.digits[i + j] = 9;
                    j++;
                }
                result.digits[i + j] -= 1;
            }
        }
    }
    while (result.digits.back() == 0) {  // Remove leading zeros.
        result.digits.pop_back();
    }
    return result;
}

BigInt operator-(const BigInt &a, const int &num) {
    return a - BigInt(num);
}

BigInt operator*(const BigInt &a, const BigInt &b) {
    BigInt loopIdx;
    BigInt result;
    BigInt toAdd;
    if (b > a) {
        loopIdx = a;
        result = b;
        toAdd = b;
    } else {
        loopIdx = b;
        result = a;
        toAdd = a;
    }
    while (loopIdx > BigInt(1)) {
        result = result + toAdd;
        loopIdx = loopIdx - 1;
    }
    return result;
}

BigInt operator/(const BigInt &a, const BigInt &b) {
    BigInt remainder = a;
    BigInt result(0);
    while (remainder > b) {
        remainder = remainder - b;
        result++;
    }
    return result;
}

BigInt operator%(const BigInt &a, const BigInt &b) {
    BigInt remainder = a;
    while (remainder > b) {
        remainder = remainder - b;
    }
    return remainder;
}

BigInt BigInt::operator++() {
    *this += BigInt(1);
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt old = *this;
    ++(*this);
    return old;
}

BigInt &operator+=(BigInt &a, const BigInt &b) {
    int aSize = int(a.size());
    int bSize = int(b.size());
    for (int i = 0; i < aSize; ++i) {
        if (i < bSize) {
            char sum = a[i] + b[i];
            if (int(sum) > 9) {
                if (i + 1 == aSize) {
                    a.digits.push_back(1);
                } else {
                    a.digits[i + 1]++;
                }
                sum -= 10;
            }
            a.digits[i] = sum;
        } else {
            if (int(a.digits[i]) > 9) {
                if (i + 1 == aSize) {
                    a.digits.push_back(1);
                } else {
                    a.digits[i + 1]++;
                }
                a.digits[i] -= 10;
            }
        }
    }
    return a;
}

bool operator==(const BigInt &a, const BigInt &b) {
    return a.digits == b.digits;
}

bool operator>(const BigInt &a, const BigInt &b) {
    int i = a.size();
    int j = b.size();
    if (i != j) {
        return i > j;
    } else {
        while (i--) {
            if (a[i] != b[i]) {
                return a[i] > b[i];
            }
        }
        return false;
    }
}

char BigInt::operator[](const int i) const {  // index function
    return digits[i];
}

void BigInt::print() {
    for (int i = int(digits.size()) - 1; i > -1; --i) {
        cout << int(digits[i]);
    }
}

int BigInt::size() const {
    return int(digits.size());
}

BigInt BigInt::fibo() {  // calls fiboHelper
    return fiboHelper(*this);
}

BigInt BigInt::fact() {
    return factHelper(*this);
}

ostream &operator<<(ostream &out, const BigInt &bigInt) {
    int size = int(bigInt.digits.size());
    if (size > 12) {
        out << int(bigInt.digits[size - 1]) << '.';
        for (int i = size - 2; i > size - 8; --i) {
            out << int(bigInt.digits[i]);
        }
        out << 'e' << size - 1;
    } else {
        for (int i = size - 1; i > -1; --i) {
            out << int(bigInt.digits[i]);
        }
    }
    return out;
}

void testUnit() {
    int space = 10;
    cout << "\nTestUnit:\n" << flush;
    system("whoami");
    system("date");
    // initialize variables
    BigInt n1(25);
    BigInt s1("25");
    BigInt n2(1234);
    BigInt s2("1234");
    BigInt n3(n2);
    BigInt fibo(12345);
    BigInt fact(50);
    BigInt imax = INT_MAX;
    BigInt big("9223372036854775807");
    // display variables
    cout << "n1(int) :" << setw(space) << n1 << endl;
    cout << "s1(str) :" << setw(space) << s1 <<endl;
    cout << "n2(int) :" << setw(space) << n2 <<endl;
    cout << "s2(str) :" << setw(space) << s2 <<endl;
    cout << "n3(n2) :" << setw(space) << n3 <<endl;
    cout << "fibo(12345):" << setw(space) << fibo << endl;
    cout << "fact(50) :" << setw(space) << fact <<endl;
    cout << "imax :" << setw(space) << imax << endl;
    cout << "big :" << setw(space) << big << endl;
    cout << "big.print(): ";
    big.print();
    cout << endl;
    cout << n2 << "/" << n1 << " = " << n2 / n1 << " rem " << n2 % n1 << endl;
    cout << "fibo(" << fibo << ") = " << fibo.fibo() << endl;
    cout << "fact(" << fact << ") = " << fact.fact() << endl;
    cout << "10 + n1 = " << 10 + n1 << endl;
    cout << "n1 + 10 = " << n1 + 10 << endl;
    cout << "(n1 == s1)? --> " << ((n1 == s1)?"true":"false") <<endl;
    cout << "n1++ = ? --> before:" << n1++ << " after:" << n1 << endl;
    cout << "++s1 = ? --> before:" << ++s1 << " after:" << s1 << endl;
    cout << "s2 * big = ? --> " << s2 * big << endl;
    cout << "big * s2 = ? --> " << big * s2 << endl;
}

int main() {
    testUnit();
    return 0;
}
