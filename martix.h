//
// Created by deside_adin on 9/18/21.
//

#ifndef UNTITLED5_MARTIX_H
#define UNTITLED5_MARTIX_H


#include <vector>
#include <iostream>
#include <ctime>

class Matrix {
private:
    std::vector<std::vector<float>> temp;
    int rows_;
    int columns_;
public:
    Matrix(int rows, int columns, int treangle_cof=1) : rows_(rows), columns_(columns) {
        std::vector<std::vector<float>> temp_;
        for (int i = 0; i < rows; ++i) {
            std::vector<float> buf(columns, 0.0);
            temp_.push_back(buf);
        }
        if (rows != columns) {
            temp = temp_;
        } else {
            for (int i = 0; i < rows; ++i) {
                temp_[i][i] = treangle_cof;
            }
            temp = temp_;
        }
    }

    ~Matrix() = default;

    Matrix &operator=(const Matrix &rhs) = default;

    std::vector<float> &operator[](int i) {
        return temp[i];
    }

    std::vector<float> operator*(const std::vector<float> &rhs_vector) const {
        if (columns_ == rhs_vector.size()) {
            std::vector<float> result(columns_, 0);
            for (int i = 0; i < rows_; ++i) {
                for (int j = 0; j < columns_; ++j) {
                    result[i] += temp[i][j] * rhs_vector[j];
                }
            }
            return result;
        } else {
            std::cout << "Multiplication error";
            std::exit(0);
        }
    }
    int Poryadok(){
        if (rows_==columns_){
            return rows_;
        }
        else{
            return -1;
        }
    }
    Matrix operator+(const std::vector<float> &rhs) const {
        if (rows_ == rhs.size()) {
            Matrix result = *this;
            for (int i = 0; i < rows_; ++i) {
                result[i].push_back(rhs[i]);
            }
            result.columns_ += 1;
            return result;
        } else {
            std::cout << "Plus error";
        }
    }

    Matrix operator*(const Matrix &rhs) const {
        if (columns_ == rhs.rows_) {
            Matrix result(rows_, rhs.columns_, 0);
            for (int i = 0; i < rows_; i++) {
                for (int k = 0; k < rhs.columns_; ++k) {
                    for (int j = 0; j < columns_; ++j) {
                        result[i][k] += temp[i][j] * rhs.temp[j][k];
                    }
                }
            }
            return result;
        } else {
            std::cout << "Multiplication error";
            std::exit(1);
        }
    }

    Matrix InverseMatrix() {
        if (rows_ == columns_) {
            Matrix buffer = *this;
            Matrix result(rows_, columns_);
            bool counter=1;
            for (int i = 0; i < rows_ - 1; ++i) {
                float kof = buffer[i][i];
                for (int k=0;k<columns_;++k){
                    buffer[i][k]/=kof;
                    result[i][k]/=kof;
                }
                for (int k = i + 1; k < rows_; ++k) {
                    if (buffer[i][i]==0){
                        std::cout << "Inverse matrix error";
                        std::exit(1);
                    }
                    float cof = buffer[k][i] / buffer[i][i];
                    for (int j = 0; j < columns_; j++) {
                        buffer[k][j] -= buffer[i][j] * cof;
                        result[k][j] -= result[i][j] * cof;
                    }
                }
            }
            float kof = buffer[rows_-1][rows_-1];
            for (int k=0;k<columns_;++k){
                buffer[rows_-1][k]/=kof;
                result[rows_-1][k]/=kof;
            }
            for (int i = rows_ - 1; i > 0; --i) {
                for (int k = i - 1; k >= 0; --k) {
                    if (buffer[i][i]==0){
                        std::cout << "Inverse matrix error";
                        std::exit(1);
                    }
                    float cof = buffer[k][i] / buffer[i][i];
                    for (int j = columns_-1; j >= 0; --j) {
                        buffer[k][j] -= buffer[i][j] * cof;
                        result[k][j] -= result[i][j] * cof;
                    }
                }
            }
            return result;
        } else {
            std::cout << "Inverse Matrix error";
            std::exit(1);
        }
    }
    void RandomInputing(){
        std::srand(time(NULL));
        for (int i=0;i<rows_;++i){
            for (int j=0;j<columns_;++j){
                temp[i][j]=(float)(rand()%201-100);
            }
        }
    }
    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);

    friend std::istream &operator>>(std::istream &is, Matrix &matrix);
};

std::ostream &operator<<(std::ostream &os, const Matrix &matrix) {
    for (int i = 0; i < matrix.rows_; ++i) {
        for (int j = 0; j < matrix.columns_; ++j) {
            os << matrix.temp[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}

std::istream &operator>>(std::istream &is, Matrix &matrix) {
    for (int i = 0; i < matrix.rows_; ++i) {
        for (int j = 0; j < matrix.columns_; ++j) {
            is >> matrix.temp[i][j];
        }
    }
    return is;
}

#endif //UNTITLED5_MARTIX_H
