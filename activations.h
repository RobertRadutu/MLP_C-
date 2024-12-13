#pragma once
#include <iostream>

template<typename T>
T sigmoid(T x){
   return 1 / (1 + exp(-x)); 
}

template<typename T>
T ReLU(T x){
    return x > 0 ? x : 0; 
}

template<typename T>
T TanH(T x){
    return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

template<typename T>
T ReLU_derivative(T x){
    return x > 0 ? 1 : 0;
}

template<typename T>
T sigmoid_derivative(T x){
    return sigmoid(x) * (1 - sigmoid(x));
}

template<typename T>
T TanH_derivative(T x){
    return 1 - pow(TanH(x), 2);
}

