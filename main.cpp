#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include "martix.h"
#include "SourceFunction.h"

/*class real {
private:
    int numerator;
    int denominator;
public:
    real(int numerator_=0, int denominator_=1): numerator(numerator_), denominator(denominator_) {
        this->norm();
    }
    real(int numerator_):numerator(numerator_), denominator(1) {

    }
    real operator+(const real& b) const {
        return real(this->numerator * b.denominator + b.numerator * this->denominator,
                    this->denominator * b.denominator);
    }

    real operator-(const real& b) const {
        return real(this->numerator * b.denominator - b.numerator * this->denominator,
                    this->denominator * b.denominator);
    }

    real operator*(const real& b) const {
        return real(this->numerator * b.numerator, this->denominator * b.denominator);
    }
    real& operator += (real c2)
    {
        numerator = numerator * c2.denominator + denominator * c2.numerator;
        denominator = denominator * c2.denominator;
        this->norm();
        return *this;
    }
    real& operator -= (real c2)
    {
        numerator = numerator * c2.denominator - denominator * c2.numerator;
        denominator = denominator * c2.denominator;
        this->norm();
        return *this;
    }
    real& operator*=(real c2) {
        numerator = numerator * c2.numerator;
        denominator = denominator * c2.denominator;
        this->norm();
        return *this;
    }
    real& operator=(int c2) {
        numerator = c2;
        denominator = 1;
        return *this;
    }
    real& operator=(real c2) {
        numerator = c2.numerator;
        denominator = c2.denominator;
        return *this;
    }
    real operator++() {
        this->numerator = this->numerator + this->denominator;
        return real(this->numerator, this->denominator);
    }

    real operator++(int b) {
        this->numerator = this->numerator + this->denominator;
        return real(this->numerator - this->denominator, this->denominator);
    }

    real operator/(const real& b) const {
        return real(this->numerator * b.denominator, this->denominator * b.numerator);
    }
    friend std::ostream& operator<<(std::ostream& os, const real& b);

    friend std::istream& operator>>(std::istream& is, real& b);

    inline int gcd(int a, int b);

    real norm() {
        int sign = 1;
        if (this->numerator < 0 or this->denominator < 0)
            sign = -1;
        int numerator = fabs(this->numerator);
        int denominator = fabs(this->denominator);
        int gsd = gcd(numerator, denominator);
        this->numerator /= gsd * sign;
        this->denominator /= gsd * sign;
        return *this;
    }
    bool operator ==(int c2) {
        norm();
        if (denominator != 1) {
            return false;
        }
        if (numerator == c2) {
            return true;
        }
        return false;
    }
    bool operator!=(int c2) {
        return !(*this == c2);
    }
    friend bool operator ==(int c2, real c1) {
        return c1 == c2;
    }
    friend bool operator !=(int c2, real c1) {
        return c1 != c2;
    }
    friend bool operator == (real c1, real c2)
    {
        return c1.numerator*c2.denominator == c2.numerator*c1.denominator;
    }
    friend bool operator != (real c1, real c2)
    {
        return c1.numerator * c2.denominator != c2.numerator * c1.denominator;
    }
    friend bool operator > (real c1, real c2)
    {
        return c1.numerator * c2.denominator > c2.numerator * c1.denominator;
    }
    friend bool operator < (real c1, real c2)
    {
        return c1.numerator * c2.denominator < c2.numerator * c1.denominator;
    }
    //friend real norm(real &b);
};

std::ostream& operator<<(std::ostream& os, const real& b) {
    os << b.numerator << "/" << b.denominator;
    return os;
}

std::istream& operator>>(std::istream& is, real& b) {
    std::string tod;
    is >> tod;
    std::string buf;
    for (size_t i = 0; i < tod.length(); ++i) {
        if (tod[i] == '/') {
            buf.clear();
            for (int j = i + 1; j < tod.length(); ++j) {
                buf.push_back(tod[j]);
            }
            b.denominator = std::stoi(buf);
            break;
        }
        buf.push_back(tod[i]);
        if (i == tod.length() - 1) {
            b.numerator = std::stoi(buf);
        }
    }
    b.norm();
    return is;
}

int real::gcd(int a, int b) {
    while (a > 0 && b > 0)

        if (a > b)
            a %= b;

        else
            b %= a;

    return a + b;
}*/


int main() {
    setlocale(LC_ALL, "Russian");
    std::ofstream fileout;
    fileout.open("VmaLaba.txt");
    fileout << std::setprecision(0) << std::fixed;
    int n = 10;
    float buff;
    Matrix A(n, n);
    A.RandomInputing();
    fileout << "Matrix A: " << '\n';
    fileout << A << '\n';
    std::vector<float> correct_solution(n);
    fileout << "Vector x: " << '\n';
    for (int i = 0; i < n; ++i) {
        correct_solution[i] = i + 1;
        fileout << correct_solution[i] << " ";
    }
    fileout << '\n';
    std::vector<float> f = A * correct_solution;

    fileout << "Vector f: " << '\n';
    for (int i = 0; i < f.size(); ++i) {
        fileout << f[i] << " ";
    }
    fileout << '\n';
    std::vector<float> solutions = Solve(A, f);
    fileout << "Vector x with wave: " << '\n';
    fileout << std::setprecision(6) << std::fixed;
    for (size_t i = 0; i < solutions.size(); ++i) {
        fileout << solutions[i] << " ";
    }
    fileout << '\n';
    fileout << "Relative error: " << VectorNorm(correct_solution - solutions) / VectorNorm(correct_solution) <<
              '\n';
    fileout << "Inverse Matrix: " << '\n';
    fileout << A.InverseMatrix();
    fileout << "A^(-1) * A: \n";
    fileout << A.InverseMatrix() * A;
    fileout << "Table of the dependence of the relative error on the order: \n";
    for (int i = 10; i <= 110; i += 10) {
        Matrix B(i, i);
        B.RandomInputing();
        std::vector<float> correct_solution3(i);
        for (int j = 0; j < i; ++j) {
            correct_solution3[j] = j + 1;
        }
        std::vector<float> f3 = B * correct_solution3;
        std::vector<float> solution3 = Solve(B, f3);
        fileout << "Order" << "\t\t" << "relative error\n";
        fileout << i << "\t\t\t" << VectorNorm(correct_solution3 - solution3) / VectorNorm(correct_solution) << '\n';
    }
    fileout << "Table of the dependence of the relative error on the order(Gilbert): \n";
    for (int i = 10; i <= 110; i += 10) {
        Matrix B(i, i);
        for (int k = 0; k < i; k++) {
            for (int j = 0; j < i; ++j) {
                B[k][j] = 1 / (((float) k + 1) + ((float) j + 1) - 1);
            }
        }
        std::vector<float> correct_solution3(i);
        for (int j = 0; j < i; ++j) {
            correct_solution3[j] = j + 1;
        }
        std::vector<float> f3 = B * correct_solution3;
        std::vector<float> solution3 = Solve(B, f3);
        fileout << "Order" << "\t\t" << "relative error\n";
        fileout << i << "\t\t\t" << VectorNorm(correct_solution3 - solution3) / VectorNorm(correct_solution) << '\n';
    }
}
