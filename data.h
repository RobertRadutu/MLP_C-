#pragma once
#include "matrix.h"
#include <cstddef>
#include <cstring>
#include <fstream>
#include <vector>

template<typename T>
class Data{
private:
    std::string targetFun;
    void vec2csv(const std::vector<T>& data, const std::string& dir, const std::string& file, char del = ','){
        system(("mkdir -p" + dir).c_str());
        std::string path = dir + "/" + file;
        std::ofstream f(path, std::ios::out);
        if(!f.is_open()){
            throw std::runtime_error("Could not open the file");
        }
        for(size_t i = 0; i<data.size(); i++){
            f << data[i];
            if(i != data.size() - 1) f << del;
        }
        
        f << std::endl;
        f.close();
    }
public:
    Data(){};
    
    // Function to generate a linspace of n points between [a, b];
    Matrix<T> linspace(T a, T b, size_t n){
        Matrix<T> result(1, n);
        T step = (b - a) / (n - 1);
        for(size_t i = 0; i<n; i++){
            result(0, i) = a + i * step;
        }
        return result;
    }

	// Function to generate a target matrix using a specific function
    Matrix<T> generate(Matrix<T> X, std::string function){
        this->targetfun = function;
        
        if(!std::strcmp(function.c_str(), "sin")){ // here "sin" is a const char*
            X.apply([](T x){return sin(x);});
        }
        
        if(!std::strcmp(function.c_str(), "cos")){
            X.apply([](T x){return cos(x);});
        }

        if (!std::strcmp(function.c_str(), "tanh"))
           return X.apply([](T x) { return tanh(x); });

        if (!std::strcmp(function.c_str(), "sin^2"))
           return X.apply([](T x) { return sin(x) * sin(x); });

        if (!std::strcmp(function.c_str(), "cos^2"))    
           return X.apply([](T x) { return cos(x) * cos(x); });        
    	
		this->targetFun = "";
		std::cout << "Function unrecognized" << std::endl;
		return Matrix<T>(0, 0);
	}
    
    // Function to generate a random matrix by making use of a seed 
	Matrix<T> sample(size_t n = 1, T a = 0, T b = 1){
	    Matrix<T> result(1, n);

        // init the random seed using the current time
        srand(time(NULL));
        for(size_t i = 0; i<n; i++) 
            result(0, i) = a + static_cast<T>(rand()) / (static_cast<T>(RAND_MAX / (b-a)));
        return result;    
    }

    void savehyper(const std::vector<size_t>& layers, T lr, size_t iterations, size_t ID, const std::string& activation, const std::string& file){
        std::string dirname = "model_" + std::to_string(ID);
        system(("mkdir -p " + dirname).c_str());
        std::string combined_path = dirname + "/" + file;
        std::ofstream f(combined_path, std::ios::out);
        if(!f.is_open()){
            throw std::runtime_error("Could not open the file");
        }
        f << "Layers: ";
        for(size_t i = 0; i<layers.size(); i++){
            f << layers[i];
            if(i != layers.size() - 1) f << ", ";
        }
        
        f << std::endl;
        f << "LR: ";
        f << lr << std::endl;
        f << "Iterations: ";
        f << iterations << std::endl;
        f << "Activation: ";
        f << activation << std::endl;
        f.close();
    }
};
