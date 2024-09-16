
#include <iostream>
#include <gtest/gtest.h>
//#include "../include/hw1.h"
#include "hw1.h"


int main(int argc, char **argv) {
    if (false) { // make false to run unit-tests
        // debug section
        std::cout << "test function zeros:" << std::endl;
        Matrix matrix0 = algebra::zeros(3, 2);
        for (auto &i : matrix0) {
            for (auto &j : i) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        std::cout << "test function ones:" << std::endl;
        Matrix matrix1 = algebra::ones(3, 2);
        for (auto &i : matrix1) {
            for (auto &j : i) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        std::cout << "test function random:" << std::endl;
        Matrix matrix2 = algebra::random(3, 2, 0, 1);
        for (auto &i : matrix2) {
            for (auto &j : i) {
                std::cout << j << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        std::cout << "test function show:" << std::endl;
        algebra::show(matrix2);
        std::cout << std::endl;

        std::cout << "test function multiply:" << std::endl;
        Matrix matrix3 = algebra::multiply(algebra::ones(2, 4), 2);
        std::cout << "matrix3:" << std::endl;
        algebra::show(matrix3);
        std::cout << std::endl;

        std::cout << "test function multiply:" << std::endl;
        try {
            Matrix matrix4 = algebra::multiply(matrix1, matrix3);
            std::cout << "matrix4:" << std::endl;
            algebra::show(matrix4);
            std::cout << std::endl;
        }
        catch (std::logic_error &e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << "test function input:" << std::endl;
        Matrix matrix5 = algebra::input(3, 3);
        algebra::show(matrix5);
        std::cout << std::endl;

        std::cout << "test function sum:" << std::endl;
        Matrix matrix6 = algebra::sum(matrix5, 2);
        std::cout << "matrix6:" << std::endl;
        algebra::show(matrix6);
        std::cout << std::endl;

        std::cout << "test function sum:" << std::endl;
        try {
            Matrix matrix7 = algebra::sum(matrix1, matrix6);
            std::cout << "matrix7:" << std::endl;
            algebra::show(matrix7);
            std::cout << std::endl;
        }
        catch (std::logic_error &e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << "test function transpose:" << std::endl;
        Matrix matrix8 = algebra::transpose(matrix5);
        std::cout << "matrix8:" << std::endl;
        algebra::show(matrix8);
        std::cout << std::endl;

        std::cout << "test function minor:" << std::endl;
        Matrix matrix9 = algebra::minor(matrix5, 1, 1);
        std::cout << "matrix9:" << std::endl;
        algebra::show(matrix9);
        std::cout << std::endl;

        std::cout << "test function determinant:" << std::endl;
        double det = algebra::determinant(matrix5);
        std::cout << "determinant:" << det << std::endl;

        std::cout << "test function inverse:" << std::endl;
        try {
            Matrix matrix10 = algebra::inverse(matrix5);
            std::cout << "matrix10:" << std::endl;
            algebra::show(matrix10);
            std::cout << std::endl;
        }
        catch (std::logic_error &e) {
            std::cout << e.what() << std::endl;
        }

        std::cout << "test function concatenate:" << std::endl;
        Matrix matrix11 = algebra::concatenate(matrix5, matrix5, 0);
        std::cout << "matrix11:" << std::endl;
        algebra::show(matrix11);
        std::cout << std::endl;

        std::cout << "test function concatenate:" << std::endl;
        Matrix matrix12 = algebra::concatenate(matrix5, matrix5, 1);
        std::cout << "matrix12:" << std::endl;
        algebra::show(matrix12);
        std::cout << std::endl;

        std::cout << "test function ero_swap:" << std::endl;
        Matrix matrix13 = algebra::ero_swap(matrix5, 0, 1);
        std::cout << "matrix13:" << std::endl;
        algebra::show(matrix13);
        std::cout << std::endl;

        std::cout << "test function ero_multiply:" << std::endl;
        Matrix matrix14 = algebra::ero_multiply(matrix5, 1, 2);
        std::cout << "matrix14:" << std::endl;
        algebra::show(matrix14);
        std::cout << std::endl;

        std::cout << "test function ero_sum:" << std::endl;
        Matrix matrix15 = algebra::ero_sum(matrix5, 0, 2, 1);
        std::cout << "matrix15:" << std::endl;
        algebra::show(matrix15);
        std::cout << std::endl;

        std::cout << "test function upper_triangular:" << std::endl;
        Matrix matrix16 = algebra::upper_triangular(matrix5);
        std::cout << "matrix16:" << std::endl;
        algebra::show(matrix16);
        std::cout << std::endl;

        Matrix matrix17;
        std::cout << "row is: " << matrix17.size() << std::endl;
    }
    else {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}