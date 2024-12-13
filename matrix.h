//template programming, including all the implementation in the header file

#pragma once
#include <cstddef>
#include <sys/types.h>
#include <vector>
#include <cmath>
#include <cassert>
#include <iostream>
#include <tuple>
#include <functional>
#include <random>

const float PI = 3.14159;

template<typename T>
class Matrix{
    std::vector<T> data;
    std::tuple<size_t, size_t> tshape;
    T random_normal(T mean=0, T std=1){
        static std::random_device __randomDevice;
        static std::mt19937 __randomGen(__randomDevice());
        static std::normal_distribution<T> __normalDistribution(mean, std);
        return __normalDistribution(__randomGen);
    }

public:
    size_t rows, cols;
    
    //standard constructor
    Matrix(){}
    Matrix(size_t rows, size_t cols, T v = 0){
        this->rows = rows;
        this->cols = cols;
        this->tshape = std::make_tuple(rows, cols);
        this->data = std::vector<T>(rows * cols, v);
    }
    ~Matrix(){}

    /////////////// OVERLOADING OPERATORS  ///////////////
    
    // used for access and modification of the element
    T& operator()(size_t row, size_t column){
        return this->data[row*this->cols+column];    
    }
    
    Matrix operator=(const std::vector<T>& v){
        assert(v.size() == this->rows * this->cols);
        this->data = v;
        return *this;
    }

    //////////////// UTILITY FUNCTIONS  ///////////////

    // Function to print the shape of the matrix
    void shape(){
        std::cout << "Shape (r, c) : " << std::get<0>(this->tshape)  << " " << std::get<1>(this->tshape) << std::endl;
    }

    // Function to print the matrix
    void print(){
        for(size_t i = 0; i<this->rows; i++){
            for(size_t j = 0; j<this->cols; j++){
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << std::endl;
        }
    }
    
    // Function to reset the matrix to zeros
    void zeros(){
        for(size_t i = 0; i<this->rows; i++){
            for(size_t j = 0; j<this->cols; j++)
                (*this)(i, j) = 0;
        }
    }

    // Function to retrieve the data vector
    std::vector<T> rawdata(){
        return this->data;
    }
    
    // Function to apply a function to all elements of a matrix | IN PLACE |
    /*
    void apply(std::function<T(T)> f){
        for(int i = 0; i<this->rows; i++){
            for(int j = 0; j<this->cols; j++){
                (*this)(i, j) = f((*this)(i, j));
            }
        }
    }
    */
    Matrix apply(std::function<T(T)> f){
        Matrix result(this->rows, this->cols);
        for(int i = 0; i<this->rows; i++){
            for(int j = 0; j<this->cols; j++){
                result(i, j) = f((*this)(i, j));
            }
        }
       return result; 
    }

   //////////////// LINEAR ALGEBRA OPERATIONS  /////////////// 
   
   /*
    Made use of RVO (return value optimized) / MOVE semantics which is way faster compared to COPY semantics [this makes 2 copies once at return and once when assings the value to the line that calls the function]
   */
   void add(Matrix m) {
        assert(this->tshape == m.tshape);
        Matrix result(this->rows, this->cols);
        for(size_t i = 0; i<this->rows; i++){
            for(size_t j = 0; j<this->cols; j++)
               result(i, j) = (*this)(i, j) + m(i, j); 
        }
       (*this) = std::move(result); 
   }

   void subtract(Matrix m){
        assert(this->tshape == m.tshape);
        Matrix result(this->rows, this->cols);
        for(size_t i = 0; i<this->rows; i++){
            for(size_t j = 0; j<this->cols; j++)
               result(i, j) = (*this)(i, j) - m(i, j); 
        }
       (*this) = std::move(result); 
   }
   
   void hadamard(Matrix m){
        assert(this->tshape == m.tshape);
        Matrix result(this->rows, this->cols);
        for(size_t i = 0; i<this->rows; i++){
            for(size_t j = 0; j<this->cols; j++)
               result(i, j) = (*this)(i, j) * m(i, j); 
        }
       (*this) = std::move(result); 
   }

   void dot(Matrix m){
        assert(this->tshape == m.tshape);
        Matrix result(this->rows, this->cols);
        for(size_t k = 0; k<this->rows; k++){
            for(size_t c = 0; c<this->cols; c++){
                for(size_t r = 0; r<this->rows; r++){
                    result(k, c)+= (*this)(k, r) * m(r, c);
                }
            }
        }
       (*this) = std::move(result); 
   }

   void transpose(){
       Matrix result(this->rows, this->cols);
       for(int i = 0; i<this->rows; i++){
        for(int j = 0; j<this->cols; j++){
            result(j, i) = (*this)(i, j);
        }
       }
        (*this) = std::move(result);   
   }

   Matrix<T> const_mul(double x){
       Matrix<T> result(this->rows, this->cols);
       for(int i = 0; i<this->rows; i++){
        for(int j = 0; j<this->cols; j++){
            result(i, j) = (*this)(i, j) * x;
        }
       }
       return result;
   }
};
