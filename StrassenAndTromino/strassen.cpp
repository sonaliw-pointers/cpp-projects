#include <stdio.h>
using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include<ctime>
#include <math.h>
using namespace chrono;

size_t roundToPowerOf2(size_t number);
class Matrix
{
public:
    Matrix(size_t iOrder);
    Matrix(){
        _mOrder =0;
        _mpMatrix = NULL;
    }
    Matrix(Matrix const &iMatrix);
    
    ~Matrix();
    
    void PrintMatrix();
    Matrix operator +(Matrix iMatrix);
    Matrix operator -(Matrix iMatrix);
    Matrix operator *(Matrix iMatrix);
    void operator =(Matrix iMatrix);
    
    Matrix* standardMultiplication(Matrix* iMatrix);
    
    Matrix* unitMultiply(Matrix& iMatrix);
    
    void RandomInitilization();
    
    void DivideMatrixIn4(Matrix *& oMatrix11, Matrix *& oMatrix12, Matrix *& oMatrix21, Matrix *& oMatrix22);
    void conquerMatrix(Matrix & oMatrix11, Matrix & oMatrix12, Matrix & oMatrix21, Matrix & oMatrix22);
    
private:
    size_t _mOrder;
    float **_mpMatrix;
};


//Constructor for the Matrix and creates a 2D array and sets all the valeues to 0
Matrix::Matrix(size_t iOrder) :_mpMatrix(NULL), _mOrder(iOrder)
{
    
    
    _mpMatrix = new float*[iOrder];
    for (size_t row = 0; row < iOrder; row++)
    {
        _mpMatrix[row] = new float[iOrder];
        for (size_t col = 0; col < iOrder; col++)
        {
            _mpMatrix[row][col] = 0;
        }
    }
}

//Copy Constructor
//copies the same parameters from iMatrix to this Matrix
Matrix::Matrix(Matrix  const &iMatrix)
{
    _mOrder = iMatrix._mOrder;
    _mpMatrix = new float*[_mOrder];
    for (size_t row = 0; row < _mOrder; row++)
    {
        _mpMatrix[row] = new float[_mOrder];
        for (size_t col = 0; col < _mOrder; col++)
        {
            _mpMatrix[row][col] = iMatrix._mpMatrix[row][col];
        }
    }
}

//Destructor
Matrix::~Matrix()
{
    if (_mpMatrix)
    {
        for (size_t row = 0; row < _mOrder; row++)
        {
            delete[] _mpMatrix[row];
            _mpMatrix[row] = NULL;
        }
        
        delete[] _mpMatrix;
        _mpMatrix = NULL;
    }
}


//A function to prit this matrix
void Matrix::PrintMatrix()
{
    cout<< endl<<"--------------------------------------------------------------";
    
    if (_mpMatrix)
    {
        cout << endl;
        cout << endl;
        for (size_t row = 0; row < _mOrder; row++)
        {
            for (size_t col = 0; col < _mOrder; col++)
            {
                cout << "\t " << roundf(_mpMatrix[row][col] * 100) / 100;
            }
            cout << endl<< endl;
        }
    }
}


//Overlodaed + operator for addition of two Matrices
Matrix Matrix::operator+(Matrix iMatrix)
{
    Matrix pResult(_mOrder);
    for (size_t row = 0; row < _mOrder; row++)
    {
        for (size_t col = 0; col < _mOrder; col++)
        {
            pResult._mpMatrix[row][col] = _mpMatrix[row][col] + iMatrix._mpMatrix[row][col];
        }
    }
    return pResult;
}


//Overlodaed - operator for substraction of two Matrices
Matrix  Matrix::operator-(Matrix iMatrix)
{
    Matrix pResult(_mOrder);
    for (size_t row = 0; row < _mOrder; row++)
    {
        for (size_t col = 0; col < _mOrder; col++)
        {
            pResult._mpMatrix[row][col] = _mpMatrix[row][col] - iMatrix._mpMatrix[row][col];
        }
    }
    return pResult;
}

//Overlodaed * operator for multipication of two Matrices
Matrix Matrix::operator*(Matrix iMatrix)
{
    Matrix  result(_mOrder);
    for (size_t row = 0; row < _mOrder; row++)
    {
        for (size_t col = 0; col < _mOrder; col++)
        {
            result._mpMatrix[row][col] = 0;
            for (size_t val = 0; val < _mOrder; val++)
            {
                result._mpMatrix[row][col] += _mpMatrix[row][val] * iMatrix._mpMatrix[val][col];
            }
        }
    }
    return result;
}

//Overlodaed = operator for assignment of two Matrices
void Matrix::operator=(Matrix iMatrix)
{
    _mOrder = iMatrix._mOrder;
    for (size_t row = 0; row < _mOrder; row++)
    {
        for (size_t col = 0; col < _mOrder; col++)
        {
            _mpMatrix[row][col] = iMatrix._mpMatrix[row][col];
        }
    }
}



//Multiply function for multiplication of base case of Starssen's Multiplication
Matrix * Matrix::unitMultiply(Matrix&  iMatrix)
{
    Matrix*  pResult = NULL;
    if (1 == _mOrder)
    {
        pResult = new Matrix(_mOrder);
        pResult->_mpMatrix[0][0] = _mpMatrix[0][0] * iMatrix._mpMatrix[0][0];
    }
    
    return pResult;
}

//A function for the initialization of the Matrix with the random float values
void Matrix::RandomInitilization()
{
    for (size_t row = 0; row < _mOrder; row++)
    {
        for (size_t col = 0; col < _mOrder; col++)
        {
            _mpMatrix[row][col] = -5.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (5.0f - (-5.0f))));
            _mpMatrix[row][col] = roundf(_mpMatrix[row][col] * 100) / 100;
        }
    }
}

//A function to divide this Matrix in four equal Matrices
void Matrix::DivideMatrixIn4(Matrix *& oMatrix11, Matrix *& oMatrix12, Matrix *& oMatrix21, Matrix *& oMatrix22)
{
    size_t roundedHalf = roundToPowerOf2(_mOrder) / 2;
    oMatrix11 = new Matrix(roundedHalf);
    oMatrix12 = new Matrix(roundedHalf);
    oMatrix21 = new Matrix(roundedHalf);
    oMatrix22 = new Matrix(roundedHalf);
    
    for (size_t row = 0; row < roundedHalf; row++)
    {
        for (size_t col = 0; col < roundedHalf; col++)
        {
            oMatrix11->_mpMatrix[row][col] = _mpMatrix[row][col];
        }
        for (size_t col = roundedHalf; col < _mOrder; col++)
        {
            oMatrix12->_mpMatrix[row][col - roundedHalf] = _mpMatrix[row][col];
        }
    }
    
    for (size_t row = roundedHalf; row < _mOrder; row++)
    {
        for (size_t col = 0; col < roundedHalf; col++)
        {
            oMatrix21->_mpMatrix[row - roundedHalf][col] = _mpMatrix[row][col];
        }
        for (size_t col = roundedHalf; col < _mOrder; col++)
        {
            oMatrix22->_mpMatrix[row - roundedHalf][col - roundedHalf] = _mpMatrix[row][col];
        }
    }
    
}

//A function to combile 4 Matrices into a single Matrix
void Matrix::conquerMatrix(Matrix & oMatrix11, Matrix & oMatrix12, Matrix & oMatrix21, Matrix & oMatrix22)
{
    size_t half = roundToPowerOf2(_mOrder) / 2;
    for (size_t row = 0; row < half; row++)
    {
        for (size_t col = 0; col < half; col++)
        {
            _mpMatrix[row][col] = oMatrix11._mpMatrix[row][col];
        }
        for (size_t col = half; col < _mOrder; col++)
        {
            _mpMatrix[row][col] = oMatrix12._mpMatrix[row][col - half];
        }
    }
    
    for (size_t row = half; row < _mOrder; row++)
    {
        for (size_t col = 0; col < half; col++)
        {
            _mpMatrix[row][col] = oMatrix21._mpMatrix[row - half][col];
        }
        for (size_t col = half; col < _mOrder; col++)
        {
            _mpMatrix[row][col] = oMatrix22._mpMatrix[row - half][col - half];
        }
    }
}

//Function to Convert Number to the nearest power of two
size_t roundToPowerOf2(size_t number)
{
    int count = 0;
    
    if (number && !(number&(number - 1)))
        return number;
    
    while (number != 0)
    {
        number >>= 1;
        count += 1;
    }
    
    return 1 << count;
}

//Multiplication function for multiplication of two Matrices
void standardMultiplication(Matrix&  iMatrixA, Matrix&  iMatrixB)
{
    cout<<endl<<"Standard Multiplication Output:";
    Matrix oMatrixC = iMatrixA*iMatrixB;
    oMatrixC.PrintMatrix();
    
}

//Multiplication function for multiplication of two Matrices Using recursive Strassen's Multiplication algorithm
void recStrassensMultiplication(size_t order, Matrix &iMatrixA, Matrix &iMatrixB, Matrix *& ioMatrixC)
{
    size_t half = roundToPowerOf2(order) / 2;
    
    if (1 <= half)
    {
        Matrix *A11 = NULL, *A12 = NULL, *A21 = NULL, *A22 = NULL;
        Matrix *B11 = NULL, *B12 = NULL, *B21 = NULL, *B22 = NULL;
        
        Matrix *M1 = NULL, *M2 = NULL, *M3 = NULL, *M4 = NULL;
        Matrix *M5 = NULL, *M6 = NULL, *M7 = NULL;
        
        
        iMatrixA.DivideMatrixIn4(A11, A12, A21, A22);
        iMatrixB.DivideMatrixIn4(B11, B12, B21, B22);
        
        Matrix sumA11_A22 = (*A11) + (*A22);
        Matrix sumA11_A12 = (*A11) + (*A12);
        Matrix sumA21_A22 = (*A21) + (*A22);
        Matrix sustractA21_A11 = ((*A21) - (*A11));
        Matrix sustractA12_A22 = ((*A12) - (*A22));
        
        Matrix sumB11_B22 = (*B11) + (*B22);
        Matrix sumB11_B12 = ((*B11) + (*B12));
        Matrix sumB21_B22 = ((*B21) + (*B22));
        Matrix sustractB12_B22 = (*B12) - (*B22);
        Matrix sustractB21_B11 = (*B21) - (*B11);
        
        recStrassensMultiplication(half, sumA11_A22, sumB11_B22, M1);
        recStrassensMultiplication(half, sumA21_A22, (*B11), M2);
        recStrassensMultiplication(half, (*A11), sustractB12_B22, M3);
        recStrassensMultiplication(half, (*A22), sustractB21_B11, M4);
        recStrassensMultiplication(half, sumA11_A12, (*B22), M5);
        recStrassensMultiplication(half, sustractA21_A11, sumB11_B12, M6);
        recStrassensMultiplication(half, sustractA12_A22, sumB21_B22, M7);
        
        
        if (M1 && M2 && M4 && M5 && M6 && M7)
        {
            Matrix C11(half), C12(half), C21(half), C22(half);
            C11 = ((*M1) + (*M4) - (*M5) + (*M7));
            C12 = (*M3) + (*M5);
            C21 = (*M2) + (*M4);
            C22 = ((*M1) + (*M3) - (*M2) + (*M6));
            
            ioMatrixC = new Matrix(order);
            ioMatrixC->conquerMatrix(C11, C12, C21, C22);
        }
        
        delete A11; A11 = NULL;
        delete A12; A12 = NULL;
        delete A21; A21 = NULL;
        delete A22; A22 = NULL;
        delete B11; B11 = NULL;
        delete B12; B12 = NULL;
        delete B21; B21 = NULL;
        delete B22; B22 = NULL;
        delete M1; M1 = NULL;
        delete M2; M2 = NULL;
        delete M3; M3 = NULL;
        delete M4; M4 = NULL;
        delete M5; M5 = NULL;
        delete M6; M6 = NULL;
        delete M7; M7 = NULL;
        
    }
    else if (1 == order)
    {
        ioMatrixC = iMatrixA.unitMultiply(iMatrixB);
    }
}

//Multiplication function for multiplication of two Matrices Using Strassen's Multiplication algorithm using Strassen's recursive Multiplication Algorithm
void strassensMultiplication(size_t order, Matrix &iMatrixA, Matrix &iMatrixB){
    cout<<endl<<"Strassen's Multiplication Output:";
    Matrix *pD = NULL;
    recStrassensMultiplication(order, iMatrixA, iMatrixB, pD);
    if (pD)
    {
        pD->PrintMatrix();
    }
    delete pD; pD = NULL;
    
    
}



int main(int argc, char *argv[])
{
    srand(static_cast <unsigned> (time(0)));
    if (argc != 2)
        cout << "usage: " << argv[0] << " Order \n";
    else
    {
        cout <<endl << "Matrix A:";
        int order = stoi(argv[1]);
        Matrix A(order);
        A.RandomInitilization();
        A.PrintMatrix();
        
        cout<<endl<<"Matxix B:";
        Matrix B(order);
        B.RandomInitilization();
        B.PrintMatrix();
        
        strassensMultiplication(order,A,B);
        
        standardMultiplication(A,B);
        
        
    }
    return 0;
}
