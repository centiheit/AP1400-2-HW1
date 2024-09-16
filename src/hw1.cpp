
//#include "../include/hw1.h"
#include "hw1.h"

// 检查矩阵是否为空
static inline bool is_empty(const Matrix& matrix) { return matrix.empty() || matrix[0].empty(); }

Matrix algebra::input(size_t n, size_t m) {
    Matrix matrix(n, std::vector<double>(m));
    std::cout << "Please input the elements of the matrix: " << std::endl;
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            std::cin >> matrix[i][j];
        }
    }
    std::cout << "Matrix elements have been entered! " << std::endl;
    return matrix;
}

Matrix algebra::zeros(size_t n, size_t m) {
    return Matrix(n, std::vector<double>(m, 0.0));
}

Matrix algebra::ones(size_t n, size_t m) {
    return Matrix(n, std::vector<double>(m, 1.0));
}

Matrix algebra::random(size_t n, size_t m, double min, double max) {
    if (min > max) {
        throw std::logic_error("The minimum value must be less than the maximum value!");
    }
    Matrix matrix(n, std::vector<double>(m));
    // 标准伪随机数生成器
    std::default_random_engine e;
    // 实数均匀分布
    std::uniform_real_distribution<double> u(min, max);
    // 为伪随机数生成器设置种子
    e.seed(time(0));
    // 遍历矩阵，为每个元素赋值
    for (auto &i : matrix) {
        for (auto &j : i) {
            j = u(e);
        }
    }
    return matrix;
}

void algebra::show(const Matrix& matrix) {
    // 以固定小数位数输出
    std::cout << std::fixed << std::setprecision(3);
    for (auto &i : matrix) {
        for (auto &j : i) {
            // 左对齐，宽度为10
            std::cout << std::setw(10) << std::left << j;
        }
        std::cout << std::endl;
    }
}

Matrix algebra::multiply(const Matrix& matrix, double c) {
    // 拷贝函数生成矩阵
    Matrix result(matrix);
    for (auto &i : result) {
        for (auto &j : i) {
            j *= c;
        }
    }
    return result;
}

// 检查矩阵相乘是否合法
static inline void check_multiply_legality(const Matrix& matrix1, const Matrix& matrix2) {
    if (matrix1[0].size() != matrix2.size()) {
        throw std::logic_error("The number of columns of the first matrix must be equal to the number of rows of the second matrix!");
    }
}

Matrix algebra::multiply(const Matrix& matrix1, const Matrix& matrix2) {
    // 首先检测两个矩阵是否为空，只要一个矩阵为空，则结果为空矩阵
    if (is_empty(matrix1) || is_empty(matrix2)) {
        return Matrix();
    }
    // 检查矩阵相乘是否合法
    check_multiply_legality(matrix1, matrix2);
    Matrix result = zeros(matrix1.size(), matrix2[0].size());
    for (size_t i = 0; i < matrix1.size(); i++) {
        for (size_t j = 0; j < matrix2[0].size(); j++) {
            for (size_t k = 0; k < matrix1[0].size(); k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

Matrix algebra::sum(const Matrix& matrix, double c) {
    // 拷贝函数生成矩阵
    Matrix result(matrix);
    for (auto &i : result) {
        for (auto &j : i) {
            j += c;
        }
    }
    return result;
}

// 检查矩阵相加是否合法
static inline void check_sum_legality(const Matrix& matrix1, const Matrix& matrix2) {
    if ((matrix1.size() != matrix2.size()) || (matrix1[0].size() != matrix2[0].size())) {
        throw std::logic_error("The number of rows and columns of the two matrices must be equal!");
    }
}

Matrix algebra::sum(const Matrix& matrix1, const Matrix& matrix2) {
    // 首先检测两个矩阵是否为空，两个矩阵均为空，则结果为空矩阵
    if (is_empty(matrix1) && is_empty(matrix2)) {
        return Matrix();
    }
    // 检查矩阵相加是否合法
    check_sum_legality(matrix1, matrix2);
    Matrix result = zeros(matrix1.size(), matrix1[0].size());
    for (size_t i = 0; i < matrix1.size(); i++) {
        for (size_t j = 0; j < matrix1[0].size(); j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;
}

Matrix algebra::transpose(const Matrix& matrix) {
    // 首先检测矩阵是否为空，为空则结果为空矩阵
    if (is_empty(matrix)) {
        return Matrix();
    }
    Matrix result(matrix[0].size(), std::vector<double>(matrix.size()));
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

// 余子式：将矩阵的第n行第m列删除后得到的矩阵的行列式
Matrix algebra::minor(const Matrix& matrix, size_t n, size_t m) {
    if (n > matrix.size() || m > matrix[0].size()) {
        throw std::logic_error("The matrix is too small to calculate the minor!");
    }
    Matrix result(matrix.size() - 1, std::vector<double>(matrix[0].size() - 1));
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            if (i < n && j < m) {
                result[i][j] = matrix[i][j];
            }
            else if (i < n && j > m) {
                result[i][j - 1] = matrix[i][j];
            }
            else if (i > n && j < m) {
                result[i - 1][j] = matrix[i][j];
            }
            else if (i > n && j > m) {
                result[i - 1][j - 1] = matrix[i][j];
            }
        }
    }
    return result;
}

// 检查矩阵是否为方阵
static inline void check_matrix_square(const Matrix& matrix) {
    if (matrix.size() != matrix[0].size()) {
        throw std::logic_error("The matrix must be a square matrix!");
    }
}

// 二阶行列式
static inline double det2(const Matrix& matrix) {
    return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

// 三阶行列式
static inline double det3(const Matrix& matrix) {
    return matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1]
        - matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[0][1] * matrix[1][0] * matrix[2][2] - matrix[0][0] * matrix[1][2] * matrix[2][1];
}

// 计算矩阵行列式
double algebra::determinant(const Matrix& matrix) {
    // 首先检测矩阵是否为空，为空则行列式为1
    if (is_empty(matrix)) {
        return 1;
    }
    check_matrix_square(matrix);
    if (matrix.size() == 2) {
        return det2(matrix);
    }
    else if (matrix.size() == 3) {
        return det3(matrix);
    }
    // 当矩阵为4阶及以上时，使用拉普拉斯展开法计算行列式
    else {
        double result = 0.0;
        for (size_t i = 0; i < matrix.size(); i++) {
            result += matrix[i][0] * determinant(minor(matrix, i, 0)) * ((i % 2 == 0) ? 1 : -1);
        }
        return result;
    }
}

// 计算矩阵的伴随矩阵：对应元素的代数余子式组成的矩阵的转置矩阵
static Matrix adjoint(const Matrix &matrix) {
    check_matrix_square(matrix);
    Matrix result(matrix.size(), std::vector<double>(matrix.size()));
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix.size(); j++) {
            // 代数余子式：计算剩余矩阵的行列式，然后乘以相应的符号(-1)^(i+j)
            result[i][j] = algebra::determinant(algebra::minor(matrix, i, j)) * ((i + j) % 2 == 0 ? 1 : -1);
        }
    }
    return algebra::transpose(result);
}

// 计算矩阵的逆矩阵：伴随矩阵除以行列式
Matrix algebra::inverse(const Matrix& matrix) {
    // 首先检测矩阵是否为空，为空则结果为空矩阵
    if (is_empty(matrix)) {
        return Matrix();
    }
    check_matrix_square(matrix);
    double det = determinant(matrix);
    if (det == 0) {
        throw std::logic_error("The matrix is singular and cannot be inverted!");
    }
    Matrix result = adjoint(matrix);
    return multiply(result, 1.0 / det);
}

Matrix algebra::concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis=0) {
    if (axis == 0) {
        if (matrix1[0].size() != matrix2[0].size()) {
            throw std::logic_error("The col of matrix1 must be equal to the col of matrix2!");
        }
        Matrix result((matrix1.size() + matrix2.size()), std::vector<double>(matrix1[0].size()));
        for (size_t i = 0; i < matrix1.size() + matrix2.size(); i++) {
            for (size_t j = 0; j < matrix1[0].size(); j++) {
                if (i < matrix1.size()) {
                    result[i][j] = matrix1[i][j];
                }
                else {
                    result[i][j] = matrix2[i - matrix1.size()][j];
                }
            }
        }
        return result;
    }
    else if (axis == 1) {
        if (matrix1.size() != matrix2.size()) {
            throw std::logic_error("The row of matrix1 must be equal to the row of matrix2!");
        }
        Matrix result(matrix1.size(), std::vector<double>(matrix1[0].size() + matrix2[0].size()));
        for (size_t i = 0; i < matrix1.size(); i++) {
            for (size_t j = 0; j < matrix1[0].size() + matrix2[0].size(); j++) {
                if (j < matrix1[0].size()) {
                    result[i][j] = matrix1[i][j];
                }
                else {
                    result[i][j] = matrix2[i][j - matrix1[0].size()];
                }
            }
        }
        return result;
    }
    else {
        throw std::logic_error("The axis must be 0 or 1!");
    }
}

Matrix algebra::ero_swap(const Matrix& matrix, size_t r1, size_t r2) {
    if (r1 >= matrix.size() || r2 >= matrix.size()) {
        throw std::logic_error("r1 or r2 is out of range!");
    }
    Matrix result(matrix);
    std::swap(result[r1], result[r2]);
    return result;
}

Matrix algebra::ero_multiply(const Matrix& matrix, size_t r, double c) {
    if (r >= matrix.size()) {
        throw std::logic_error("r is out of range!");
    }
    Matrix result(matrix);
    for (auto &e : result[r]) {
        e *= c;
    }
    return result;
}

Matrix algebra::ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2) {
    if (r1 >= matrix.size() || r2 >= matrix.size()) {
        throw std::logic_error("r1 or r2 is out of range!");
    }
    Matrix result(matrix);
    for (size_t j = 0; j < matrix[0].size(); j++) {
        result[r2][j] += result[r1][j] * c;
    }
    return result;
}

Matrix algebra::upper_triangular(const Matrix& matrix) {
    // 首先检测矩阵是否为空，为空则结果为空矩阵
    if (matrix.empty()) {
        return Matrix();
    }
    check_matrix_square(matrix);
    Matrix result = matrix;
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = i + 1; j < matrix[0].size(); j++) {
            // 如果对角线元素为0，则交换行
            while (result[i][i] == 0) {
                size_t k = 1;
                result = ero_swap(result, i, i + k);
                k++;
            }
            double c = -result[j][i] / result[i][i];
            result = ero_sum(result, i, c, j);
        }
    }
    return result;
}