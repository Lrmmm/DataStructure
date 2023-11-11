#ifndef __Matrix__
#define __Matrix__
#include <iostream>
#include "../exception/myException.h"
using namespace std;
template<class T>
class Matrix{
public:
    Matrix(int rows = 0, int columns = 0);
    Matrix(const Matrix<T>&);
    ~Matrix(){delete[] elements;}
    int getRows() const {return rows;}
    int getColumns() const {return columns;}
    T& operator() (int i, int j) const;
    Matrix<T>& operator=(const Matrix<T>&);
    Matrix<T> operator+() const;
    Matrix<T> operator+(const Matrix<T>&) const;
    Matrix<T> operator-() const;
    Matrix<T> operator-(const Matrix<T>&) const;
    Matrix<T> operator*(const Matrix<T>&) const;
    Matrix<T>& operator+=(const T&);
    void output(ostream& out) const;
    friend ostream& operator<<(ostream& out, const Matrix<T>& x)
    {
        x.output(out);
        return out;
    }

private:
    int rows;
    int columns;
    T* elements;
};

template<class T>
Matrix<T>::Matrix(int nRows, int nColumns)
{
    if (nRows < 0 || nColumns < 0)
        throw illegalIndex("illegalIndex");
    
    if((nRows == 0 || nColumns == 0) && (nRows != 0 || nColumns != 0))
        throw illegalParameterValue("illegalParameterValue");
    
    this->rows = nRows;
    this->columns = nColumns;
    elements = new T[nRows * nColumns];
}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& other)
{
    rows = other.rows;
    columns = other.columns;
    elements = new T[rows * columns];

    for (int i = 0; i < rows * columns; i++)
    {
       elements[i] = other.elements[i];
    }
    
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
    if (this != &other) {
        delete [] elements;
        rows = other.rows;
        columns = other.columns;
        elements = new T[rows * columns];
        for (int i = 0; i < rows * columns; i++)
        {
            elements[i] = other.elements[i];
        }

    }
    return *this;
}

template<class T>
T& Matrix<T>::operator()(int i, int j) const
{
    if (i < 1 || i > rows || j < 1 || j > columns)
        throw MatrixIndexOutOfBounds("MatrixIndexOutOfBounds");

    return elements[(i - 1) * columns + j - 1];
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
    if (rows != other.rows || columns != other.columns)
        throw MatrixSizeMisMatch("MatrixSizeMisMatch");

    Matrix<T> res(rows , columns);
    for (int i = 0; i < rows * columns; i++)
    {
        res.elements[i] = elements[i] + other.elements[i];
    }
    
    return res;
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const{
    if (columns != other.rows)
        throw MatrixSizeMisMatch("MatrixSizeMisMatch");
    
    Matrix<T> res(rows, other.columns);

    int ct = 0;
    int cm = 0;
    int cw = 0;

    for (int i = 1; i <= rows; i++)
    {
        for (int j = 1; j < other.columns; j++)
        {
            T sum = elements[ct] * other.elements[cm];

            for (int k = 2; k <= columns; k++) {
                ct++;
                cm += other.columns;
                sum += elements[ct] * other.elements[cm];
            }
            res.elements[cw++] = sum;
        }
        ct += columns;
        cm = 0;
    }

    return res;
    
}

template<class T>
void Matrix<T>::output(ostream& out) const
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            out << elements[i*columns + j] <<"\t";
        out << endl;
    }
    
}


#endif 