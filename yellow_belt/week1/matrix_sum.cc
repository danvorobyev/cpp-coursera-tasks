#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
public:
    Matrix() {}

    Matrix(int num_rows, int num_cols) {
        Reset(num_rows, num_cols);
    }

    void Reset(int num_rows, int num_cols) {
        if (num_rows < 0 || num_cols < 0) {
            throw out_of_range("");
        }
        if (num_rows == 0 || num_cols == 0) {
            num_rows = 0;
            num_cols = 0;
        }
        rows= num_rows;
        cols = num_cols;
        values.assign(num_rows, vector<int>(num_cols));
    }

    int GetNumRows() const {
        return rows;
    }

    int GetNumColumns() const {
        return cols;
    }

    int At(int row_num, int col_num) const {
        if (row_num < 0 || row_num >= rows
            || col_num < 0 || col_num >= cols)
            throw out_of_range("");
        return values[row_num][col_num];
    }

    int& At(int row_num, int col_num) {
        if (row_num < 0 || row_num >= rows
            || col_num < 0 || col_num >= cols)
            throw out_of_range("");
        return values[row_num][col_num];
    }
private:
    int rows = 0;
    int cols = 0;
    vector<vector<int> > values;
};

istream& operator>>(istream& input, Matrix& matrix) {
    int num_rows, num_cols;
    input >> num_rows >> num_cols;
    matrix = Matrix(num_rows, num_cols);
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_cols; col++) {
            input >> matrix.At(row, col);
        }
    }
    return input;
}

ostream& operator<<(ostream& output, const Matrix& matrix) {
    output << matrix.GetNumRows() << " "  << matrix.GetNumColumns() << endl;
    for (int row = 0; row < matrix.GetNumRows(); row++) {
        for (int col = 0; col < matrix.GetNumColumns(); col++) {
            output << matrix.At(row, col) << " ";
        }
        output << endl;
    }
    return output;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.GetNumColumns() != rhs.GetNumColumns() 
        || lhs.GetNumRows() != rhs.GetNumRows())
        return false;
    for (int row = 0; row < lhs.GetNumRows(); row++) {
        for (int col = 0; col < lhs.GetNumColumns(); col++) {
            if (lhs.At(row, col) != rhs.At(row, col)) {
                return false;
            }
        }
    }
    return true;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs) {
    if (lhs.GetNumColumns() != rhs.GetNumColumns() 
        || lhs.GetNumRows() != rhs.GetNumRows())
        throw invalid_argument("");
    Matrix matrix(lhs.GetNumRows(), lhs.GetNumColumns());
    for (int row = 0; row < matrix.GetNumRows(); row++) {
        for (int col = 0; col < matrix.GetNumColumns(); col++) {
            matrix.At(row, col) = lhs.At(row, col) + rhs.At(row, col);
        }
    }
    return matrix;
}