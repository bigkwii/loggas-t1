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

//! Matrix implementation, with a series of linear algebra functions
//! @tparam T The arithmetic type the matrix will store
template<
    typename T,
    typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Matrix{
    private:
        //! The number of rows in the matrix
        size_t mRows;
        //! The number of columns in the matrix
        size_t mCols;
        //! The matrix data
        std::vector<T> mData;

    //! Validates the matrix dimensions
    //! @param rows The number of rows
    //! @param cols The number of columns
    //! @throws std::invalid_argument if the dimensions are invalid
    void validate_dimensions(size_t row, size_t col) const{
        if(row < 0 || col < 0 || row >= mRows || col >= mCols){
            throw std::invalid_argument("Coords out of range");
        }
    }
};

typedef Matrix<double> MatrixD;
typedef Matrix<int> MatrixI;
typedef Matrix<float> MatrixF;
typedef Matrix<char> MatrixC;