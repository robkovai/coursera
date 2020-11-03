#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Matrix {
public:
    using Size = pair<int, int>;

    Matrix() = default;

    Matrix(int rows, int columns) {
        this->Init(rows, columns);
    }

    void Reset(int rows, int columns) {
        this->Clear();
        this->Init(rows, columns);
    }

    int& At(int row, int column) {
        if (row >= 0 && column >= 0 && this->size.first > row && this->size.second > column)
            return this->data.at(row).at(column);
        throw out_of_range("");
    }

    int At(int row, int column) const {
        if (row >= 0 && column >= 0 && this->size.first > row && this->size.second > column)
            return this->data.at(row).at(column);
        throw out_of_range("");
    }

    int GetNumRows() const {
        return this->size.first;
    } 
    
    int GetNumColumns() const {
        return this->size.second;
    }

    friend istream& operator>>(istream &stream, Matrix &matrix) {
        int rows, columns;
        stream >> rows >> columns;
        matrix.Reset(rows, columns);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j) 
                stream >> matrix.At(i, j);
        return stream;
    }

    friend ostream& operator<<(ostream &stream, const Matrix &matrix) {
        stream << matrix.GetNumRows() << ' ' << matrix.GetNumColumns() << endl;
        for (int i = 0; i < matrix.GetNumRows(); ++i) {
            for (int j = 0; j < matrix.GetNumColumns(); ++j) {
                if (j > 0)
                    stream << ' ';
                stream << matrix.At(i, j);
            }
            if (i != matrix.GetNumRows() - 1)
                stream << endl;
        }
        return stream;
    }

    friend bool operator==(const Matrix &lhs, const Matrix &rhs) {
        if (lhs.size == rhs.size) {
            for (int i = 0; i < lhs.GetNumRows(); ++i) 
                for (int j = 0; j < lhs.GetNumColumns(); ++j)
                    if (lhs.At(i, j) != rhs.At(i, j))
                        return false;
            return true;
        }
        return false;
    }

    friend Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
        if (lhs.size != rhs.size)
            throw invalid_argument("Invalid matrix sizes. " + to_string(lhs.size.first) + 'x' + to_string(lhs.size.second) + " != "
                + to_string(rhs.size.first) + 'x' + to_string(rhs.size.second));
        Matrix matrix(lhs.GetNumRows(), lhs.GetNumColumns());
        for (int i = 0; i < matrix.GetNumRows(); ++i)
            for (int j = 0; j < matrix.GetNumColumns(); ++j)
                matrix.At(i, j) = lhs.At(i, j) + rhs.At(i,j);
        return matrix;
    }

private:    
    void Clear() {
        this->data.clear();
    }

    void Init(int rows, int columns) {
        if (rows < 0 || columns < 0)
            throw out_of_range("");

        if (rows == 0 || columns == 0)
            return;

        this->size = make_pair(rows, columns);
        this->data.resize(rows);
        for (int i = 0; i < rows; ++i)
            this->data.at(i).resize(columns);
    }

    Size GetSize() const {
        return this->size;
    }

    vector<vector<int>> data;
    Size size = {0, 0};
};

int main() {
  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << one + two << endl;
  return 0;
}