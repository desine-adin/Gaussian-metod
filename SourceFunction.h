//
// Created by deside_adin on 9/23/21.
//

#ifndef UNTITLED5_SOURCEFUNCTION_H
#define UNTITLED5_SOURCEFUNCTION_H
std::vector<float> Solve(Matrix A, std::vector<float> f) {
    int n = A.Poryadok();
    Matrix matr = A + f;
    float kof;
    int counter{0};
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t k = i + 1; k < n; ++k) {
            if (matr[i][i] == 0) {
                counter++;
                for (size_t z = i + 1; z < n; ++z) {
                    if (matr[z][i] != 0) {
                        for (int m = 0; m < n + 1; ++m) {
                            matr[i][m] += matr[z][m];
                        }
                        counter++;
                        break;
                    }
                }
            }
            if (counter != 1) {
                if (matr[i][i] == 0) {
                    std::cout << "Бесконечно много решений ";
                    exit(0);
                }
                kof = matr[k][i] / matr[i][i];
                for (size_t j = i; j < n + 1; ++j) {
                    matr[k][j] -= matr[i][j] * kof;
                }
                kof = 0;
            }
            if (counter == 1) {
                std::vector<float> buf;
                buf = matr[i];
                matr[i] = matr[k];
                matr[k] = buf;
            }
        }
    }
    int counter2{0};
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n + 1; ++j) {
            if (matr[i][j] != 0) {
                counter2++;
                if (j == n) {
                    counter2++;
                }
                break;
            }
        }
        if (counter2 == 0) {
            std::cout << "Бесконечно много решений " << std::endl;
            exit(0);
            break;
        }
        if (counter2 == 2) {
            std::cout << "Нет решений " << std::endl;
            exit(0);
            break;
        }
        counter2 = 0;
    }
    std::vector<float> solutions(n);
    float sum = 0;
    for (int i = n - 1; i >= 0; --i) {
        for (size_t j = i + 1; j < n; ++j) {
            sum += solutions[j] * matr[i][j];
        }
        solutions[i] = (matr[i][n] - sum) / matr[i][i];
        sum = 0;
    }
    return solutions;
}

float VectorNorm(const std::vector<float> &vect) {
    float max = fabs(vect[0]);
    for (int i = 1; i < vect.size(); ++i) {
        if (fabs(vect[i]) > max) {
            max = fabs(vect[i]);
        }
    }
    return max;
}

std::vector<float> operator-(const std::vector<float> &rhs, const std::vector<float> &lhs) {
    if (rhs.size() == lhs.size()) {
        std::vector<float> result(rhs.size());
        for (int i = 0; i < rhs.size(); ++i) {
            result[i] = rhs[i] - lhs[i];
        }
        return result;
    } else {
        std::cout << "Vector error";
        std::exit(1);
    }
}
#endif //UNTITLED5_SOURCEFUNCTION_H
