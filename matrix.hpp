#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <limits>
#include <numeric>

using namespace std;

//! Matrix class
template <typename T>
class Matrix {
    private:
        std::vector<std::vector<T> > matrix;
        int rows;
        int cols;
    
    public:

    //! Constructor for a matrix of size rows x cols with all elements set to value
    //! @param rows number of rows
    //! @param cols number of columns
    //! @param value value to set all elements to
    Matrix(int rows, int cols, T value) {
        this->rows = rows;
        this->cols = cols;
        matrix.resize(rows);
        for (int i = 0; i < rows; i++) {
            matrix[i].resize(cols, value);
        }
    }

    //! Constructor for a square matrix with all elements set to a value
    //! @param size number of rows and columns
    //! @param value value to set all elements to
    Matrix(int size, T value){
        Matrix(size, size, value);
    }

    //! method to convert matrix to string
    //! @return string representation of matrix
    std::string toString() {
        std::stringstream ss;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                ss << matrix[i][j] << " ";
            }
            ss << std::endl;
        }
        return ss.str();
    }

    //! method to set the element at row i and column j to value
    //! @param i row index
    //! @param j column index
    //! @param value value to set element to
    void set(int i, int j, T value) {
        matrix[i][j] = value;
    }

    //! method to validate if an element at row i and column j is within the matrix
    //! @param i row index
    //! @param j column index
    //! @return true if element is within matrix, false otherwise
    bool inBounds(int i, int j) {
        return (i >= 0 && i < rows && j >= 0 && j < cols);
    }

    //! method to get the element at row i and column j
    //! @param i row index
    //! @param j column index
    //! @return element at row i and column j
    T get(int i, int j) {
        if(!inBounds(i, j)) {
            throw std::out_of_range("Index out of bounds");
        }
        return matrix[i][j];
    }

};

typedef Matrix<double> MatrixD;
typedef Matrix<int> MatrixI;
typedef Matrix<float> MatrixF;
typedef Matrix<char> MatrixC;

