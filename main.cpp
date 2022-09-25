#include "matrix.hpp"
#include <iostream>

int main(int argc, char** argv){
    MatrixD m = MatrixD(3, 3, 1.0);
    std::cout << m.toString() << std::endl;
    return 0;
}