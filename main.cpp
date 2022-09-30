#include "matrix.hpp"
#include <iostream>

// Test matrix class' split method
int main() {
    int rows = 16;
    int cols = 16;
    int rowsSplit = 4;
    int colsSplit = 4;
    MatrixI m(rows, cols, 0);
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            m.set(i, j, rand() % 100);
        }
    }
    std::cout << m.toString() << std::endl;
    std::vector<MatrixI> v = m.split(rowsSplit, colsSplit);
    for(int i = 0; i < v.size(); i++) {
        std::cout << v[i].toString() << std::endl;
    }
}
