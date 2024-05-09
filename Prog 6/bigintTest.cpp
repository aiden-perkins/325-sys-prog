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

        BigInt fiboHelper(BigInt n, BigInt a = 0, const BigInt &b = 1) {
            if (n == 0) {
                return a;
            } else if (n == 1) {
                return b;
            } else {
                return fiboHelper(--n, b, a + b);
            }
        }

    public:
        // Constructors
        BigInt() = default;

        BigInt(int num) {
            if (num == 0) {
                digits.push_back(0);
            } else {
                while (num > 0) {
                    digits.push_back(num % 10);
                    num /= 10;
                }
            }
        }

        BigInt(string str) {
            for (int i = str.size() - 1; i > -1; --i) {
                digits.push_back(str[i] - '0');
            }
        }

        // Comparison operators
        bool operator==(const BigInt &b) {
            return digits == b.digits;
        }

        bool operator>(const BigInt &b) const {
            int i = size();
            int j = b.size();
            if (i != j) {
                return i > j;
            } else {
                while (i--) {
                    if (digits[i] != b[i]) {
                        return digits[i] > b[i];
                    }
                }
                return false;
            }
        }

        // Operation operators
        BigInt &operator+=(const BigInt &b) {
            int aSize = size();
            int bSize = b.size();
            char carry = 0;
            for (int i = 0; i < max(aSize, bSize); ++i) {
                if (i >= aSize) {
                    digits.push_back(0);
                }
                digits[i] += carry;
                carry = 0;
                if (i < bSize) {
                    digits[i] += b[i];
                }
                if (digits[i] > 9) {
                    digits[i] -= 10;
                    carry = 1;
                }
            }
            if (carry) {
                digits.push_back(1);
            }
            return *this;
        }

        BigInt operator+(const BigInt &b) {
            BigInt result = *this;
            result += b;
            return result;
        }

        friend BigInt operator+(const int a, const BigInt &b) {
            BigInt result(a);
            result += b;
            return result;
        }

        BigInt &operator-=(const BigInt &b) {
            int aSize = size();
            int bSize = b.size();
            char carry = 0;
            for (int i = 0; i < aSize; ++i) {
                digits[i] -= carry;
                carry = 0;
                if (i < bSize) {
                    digits[i] -= b[i];
                }
                if (digits[i] < 0) {
                    digits[i] += 10;
                    carry = 1;
                }
            }
            while (digits.back() == 0 && size() > 1) {  // Remove leading zeros.
                digits.pop_back();
            }
            return *this;
        }

        BigInt operator-(const BigInt &b) {
            BigInt result = *this;
            result -= b;
            return result;
        }

        friend BigInt operator-(const int a, const BigInt &b) {
            BigInt result(a);
            result -= b;
            return result;
        }

        BigInt &operator*=(const BigInt &b) {
            BigInt loopIdx = *this;
            BigInt result = b;
            BigInt toAdd = b;
            if ((*this) > b) {
                loopIdx = b;
                result = *this;
                toAdd = *this;
            }
            while (loopIdx > 1) {
                result += toAdd;
                loopIdx--;
            }
            *this = result;
            return *this;
        }

        BigInt operator*(const BigInt &b) {
            BigInt result = *this;
            result *= b;
            return result;
        }

        BigInt operator/(const BigInt &b) {
            BigInt remainder = *this;
            BigInt result(0);
            while (remainder > b) {
                remainder -= b;
                result++;
            }
            return result;
        }

        BigInt operator%(const BigInt &b) {
            BigInt remainder = *this;
            while (remainder > b) {
                remainder -= b;
            }
            return remainder;
        }

        // Crement operators
        BigInt operator++() {
            *this += 1;
            return *this;
        }

        BigInt operator++(int) {
            BigInt old = *this;
            ++(*this);
            return old;
        }

        BigInt operator--() {
            *this -= 1;
            return *this;
        }

        BigInt operator--(int) {
            BigInt old = *this;
            --(*this);
            return old;
        }

        // Other overloads
        BigInt &operator=(const BigInt &a) = default;

        char operator[](const int i) const {
            return digits[i];
        }

        friend ostream& operator<<(ostream &out, const BigInt &b) {
            int size = b.digits.size();
            if (size > 12) {
                out << int(b.digits[size - 1]) << '.';
                for (int i = size - 2; i > size - 8; --i) {
                    out << int(b.digits[i]);
                }
                out << 'e' << size - 1;
            } else {
                for (int i = size - 1; i > -1; --i) {
                    out << int(b.digits[i]);
                }
            }
            return out;
        }

        // Non overloading functions
        int size() const {
            return digits.size();
        }

        void print() {
            for (int i = digits.size() - 1; i > -1; --i) {
                cout << int(digits[i]);
            }
        }

        BigInt fibo() {
            return fiboHelper(*this);
        }

        BigInt fact() const {
            BigInt result(1);
            for (BigInt i(0); *this > i; ++i) {
                result *= i + 1;
            }
            return result;
        }
};

void testUnit() {
    int space = 10;
    cout << "\a\nTestUnit:\n" << flush;
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
