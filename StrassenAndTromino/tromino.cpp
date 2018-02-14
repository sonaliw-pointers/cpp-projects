
using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include<ctime>
#include <math.h>

//Class SquareTromino
class SquareTromino
{
public:
    
    SquareTromino(int size);
    void setHoleLocation(int x, int y, int val);
    
    void printSquareTromino();
    void trominoTile();
    static int indexSquareTromino;
    
private:
    int _size;
    int _holeRow;
    int _holeCol;
    int _order;
    int **_mpSquareTromino;
    int _holeVal;
    
    void DivideSquareTrominoIn4(SquareTromino *& oSquareTromino11, SquareTromino *& oSquareTromino12, SquareTromino *& oSquareTromino21, SquareTromino *& oSquareTromino22);
    void ConquerSquareTrominoIn4(SquareTromino & oSquareTromino11, SquareTromino & oSquareTromino12, SquareTromino & oSquareTromino21, SquareTromino & oSquareTromino22);
};

//Function to maintain the index of SquareTromino
int SquareTromino::indexSquareTromino = 0;
SquareTromino::SquareTromino(int size) :_mpSquareTromino(NULL)
{
    _size = size;
    _holeRow = -1;
    _holeCol = -1;
    _order = (int)pow(2, _size);
    _mpSquareTromino = new int *[_order];
    
    for (int row = 0; row < _order; row++)
    {
        _mpSquareTromino[row] = new int[_order];
        for (int col = 0; col < _order; col++)
        {
            _mpSquareTromino[row][col] = -1;
        }
    }
    
}

//Function for setting the value and location of hole
void SquareTromino::setHoleLocation(int x, int y, int val)
{
    _holeRow = x;
    _holeCol = y;
    _holeVal = val;
    _mpSquareTromino[_holeRow][_holeCol] = val;
}

//Function to divide the given problem in the four equal parts
void SquareTromino::DivideSquareTrominoIn4(SquareTromino *& oSquareTromino11, SquareTromino *& oSquareTromino12, SquareTromino *& oSquareTromino21, SquareTromino *& oSquareTromino22)
{
    indexSquareTromino++;

    int roundedHalf = _order / 2;
    int newRow = _holeRow - roundedHalf;
    int newCol = _holeCol - roundedHalf;
    oSquareTromino11 = new SquareTromino(_size - 1);
    oSquareTromino12 = new SquareTromino(_size - 1);
    oSquareTromino21 = new SquareTromino(_size - 1);
    oSquareTromino22 = new SquareTromino(_size - 1);
    
    
    //Checking the location of the hole and setting the values for the other quadrants
    if (-1 < newRow)
    {
        if (-1 < newCol)
        {
            //A22
            oSquareTromino11->setHoleLocation(roundedHalf - 1, roundedHalf - 1, indexSquareTromino);
            oSquareTromino12->setHoleLocation(roundedHalf - 1, 0, indexSquareTromino);
            oSquareTromino21->setHoleLocation(0, roundedHalf - 1, indexSquareTromino);
            oSquareTromino22->setHoleLocation(newRow, newCol, _holeVal);
            
        }
        else
        {
            //A21
            oSquareTromino11->setHoleLocation(roundedHalf - 1, roundedHalf - 1, indexSquareTromino);
            oSquareTromino12->setHoleLocation(roundedHalf - 1, 0, indexSquareTromino);
            oSquareTromino21->setHoleLocation(newRow, _holeCol, _holeVal);
            oSquareTromino22->setHoleLocation(0, 0, indexSquareTromino);
            
        }
    }
    else
    {
        
        if (-1 < newCol)
        {
            //A12
            oSquareTromino11->setHoleLocation(roundedHalf - 1, roundedHalf - 1, indexSquareTromino);
            oSquareTromino12->setHoleLocation(_holeRow, newCol,_holeVal);
            oSquareTromino21->setHoleLocation(0, roundedHalf - 1, indexSquareTromino);
            oSquareTromino22->setHoleLocation(0, 0, indexSquareTromino);
            
        }
        else
        {
            
            //A11
            oSquareTromino11->setHoleLocation(_holeRow,_holeCol, _holeVal);
            oSquareTromino12->setHoleLocation(roundedHalf - 1, 0, indexSquareTromino);
            oSquareTromino21->setHoleLocation(0, roundedHalf - 1, indexSquareTromino);
            oSquareTromino22->setHoleLocation(0, 0, indexSquareTromino);
            
        }
    }
    
 
}

//Combining the SquareTrominos which are divided earlier
void SquareTromino::ConquerSquareTrominoIn4(SquareTromino & oSquareTromino11, SquareTromino & oSquareTromino12, SquareTromino & oSquareTromino21, SquareTromino & oSquareTromino22)
{
    
    int half = _order / 2;
    for (int row = 0; row < half; row++)
    {
        for (int col = 0; col < half; col++)
        {
            _mpSquareTromino[row][col] = oSquareTromino11._mpSquareTromino[row][col];
        }
        for (int col = half; col < _order; col++)
        {
            _mpSquareTromino[row][col] = oSquareTromino12._mpSquareTromino[row][col - half];
        }
    }
    
    for (int row = half; row < _order; row++)
    {
        for (int col = 0; col < half; col++)
        {
            _mpSquareTromino[row][col] = oSquareTromino21._mpSquareTromino[row - half][col];
        }
        for (int col = half; col < _order; col++)
        {
            _mpSquareTromino[row][col] = oSquareTromino22._mpSquareTromino[row - half][col - half];
        }
    }
}

//Funtion to print the Square containing the trominos
void SquareTromino::printSquareTromino()
{
    if (_mpSquareTromino)
    {
        cout << endl;
        for (int row = 0; row < _order; row++)
        {
            for (int col = 0; col < _order; col++)
            {
                cout << "\t " << _mpSquareTromino[row][col];
            }
            cout << endl;
        }
    }
}

//The main function to place the Trominos in the given square
void SquareTromino::trominoTile()
{
    if (1 == _size)
    {
        indexSquareTromino++;
        for (int row = 0; row < 2; row++)
        {
            for (int col = 0; col < 2; col++)
            {
                if (_holeRow != row || _holeCol != col)
                {
                    _mpSquareTromino[row][col] = indexSquareTromino;
                }
            }
        }
    }
    else
    {
        SquareTromino *A11 = NULL, *A12 = NULL, *A21 = NULL, *A22 = NULL;
        DivideSquareTrominoIn4(A11, A12, A21, A22);

        if (A11 && A12 && A21 && A22)
        {
            A11->trominoTile();
            A12->trominoTile();
            A21->trominoTile();
            A22->trominoTile();

        }
        ConquerSquareTrominoIn4(*A11, *A12, *A21, *A22);
        delete A11; A11 = NULL;
        delete A12; A12 = NULL;
        delete A21; A21 = NULL;
        delete A22; A22 = NULL;
    }
}


int main(int argc, const char * argv[]) {
    
    if (argc != 4)
        cout << "usage: " << argv[0] << " <value of k> <hole position row number> <hole position column number> \n";
    else
    {
        int size = atoi(argv[1]);
        int holeX = stoi(argv[2]);
        int holeY = stoi(argv[3]);
        SquareTromino t(size);
        t.setHoleLocation(holeX, holeY, 0);
        t.trominoTile();
        t.printSquareTromino();
    }
    return 0;
}
