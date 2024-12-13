#include <iostream>
#include "matrix.h"

int main(){
    Matrix<int> m(2, 2, 3);
    Matrix<int> n(2, 2, 7);
    Matrix<int> result;
    m.add(n);
    m.print();

    Matrix<double> w(3, 3, 1.69);
    Matrix<double> x(3, 3, 1.30);
    Matrix<double> r;
    w.add(x);
    w.print();

    m.dot(n);
    m.print();

    m.hadamard(n);
    m.print();

    Matrix<double> A(3, 3, 0.0);
    double cnt = 0.0;
    for(int i = 0; i<A.rows; i++){
        for(int j = 0; j<A.cols; j++){
            A(i, j) = cnt;
            cnt = cnt + 0.1;
        }
    }
    A.print();
    A.transpose();
    Matrix<double> B = A;
    B.print();
}
