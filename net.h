#include "data.h"
#include "activations.h"
#include <chrono>

template<typename T>
class Net{
  private:
    size_t ID;

    std::vector<Matrix<T>> weights;
    std::vector<Matrix<T>> bias;
    std::vector<Matrix<T>> activations; 

    std::vector<int> layers;
    double lr = 0.01;
    double loss;
    double delta = 0.02;
    
    double avg_acc; 
    double avg_loss;
    int iterations;

    Matrix<T> forward(Matrix<T> X){
        this->activations.clear();
        this->activations.push_back(X);
        for(int i = 0; i<layers.size() - 1; i++){
          Matrix<T> Z = this->activations[i].dot(this->weights[i]).add(this->bias);
          Matrix<T> A = Z.apply(sigmoid<T>);
          this->activations.push_back(A);
        }
        return this->activations.back();
    }

    /* 
       Update the weights in order to decrease the loss function
       The updates of the weights/biases are done after every iteration, could be done after the whole backward function is executed
    */
    void backward(Matrix<T> y){
      Matrix<T> ypred = this->activations.back();
      Matrix<T> error = ypred.subtract(y);
      for(int i = this->activations[i]-1; i>0; i--){
        Matrix<T> ones(this->activations[i].rows, this->activations[i].cols, 1);
        Matrix<T> grad = error.hadamard(activations[i].subtract(ones - activations[i]));
        Matrix<T> weight_update = grad.dot(this->activations[i-1].transpose()).const_mul(lr); 
        this->weights[i-1] = this.weights[i-1].subtract(weight_update);
        Matrix<T> bias_update = grad.const_mul(lr); 
        this->bias[i-1] = this->bias[i-1].subtract(bias_update);
        error = grad.dot(this->weight[i-1].transpose());
      }
    }

  public:
    Net(std::vector<size_t>& layers, double lr = 0.01, int iterations = 1000, std::string activation="sigmoid"){
      this->layers = layers;
      this->lr = lr;
      this->iterations = iterations;
      this->activation_function = activation;
    }

    void train(Matrix<T> X, Matrix<T> Y, size_t print_after_iter = 1000, bool save_info = false){
      double eta;
      double time;
      std::cout << "Starting the training..." << std::endl;
      for(int i = 0; i<iterations; i++){
        auto start = std::chrono::high_resolution_clock::now();
        Matrix<T> x = Matrix(1, 1, X(0, i%X.cols));
        Matrix<T> y = Matrix(1, 1, Y(0, i%Y.cols));
        Matrix<T> ypred = forward(x);
        backward(y);
        avg_loss+=loss;
        if(std::abs(y(0, 0) - ypred(0, 0)) <= delta){
          avg_acc+=1;
        }
        auto end = std::chrono::high_resolution_clock::now();
        time += std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
        if(i % print_after_iter == 0 && i != 0){
          eta = (time / print_after_iter) * (iterations - i);
          eta /= 1000000; //microseconds to seconds
          int minutes = eta / 60;
          int seconds = (int)eta % 60;
          std::cout << "Iteration number: " << i
          << "Avg Loss: " << avg_loss
          << "Avg Acc: " << avg_acc
          << "ETA " << "minutes: " << minutes << " seconds: " << seconds << std::endl;

          avg_loss = 0.;
          avg_acc = 0.;
          time = 0.;
        }
      }
        std::cout << "Training completed!" << std::endl;
    }

    Matrix<T> predict(Matrix<T> X){
       Matrix<T> predictions(1, X.cols);
       for(int i = 0; i<X.cols; i++){
        Matrix<T> x = Matrix(1, 1, X(0, i));
        predictions(0, i) = forward(x);
       }
       return predictions;
    }
};
