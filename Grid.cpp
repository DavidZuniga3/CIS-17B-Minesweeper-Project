#include <iostream>
#include <iomanip>

#include "Grid.hpp"

using namespace std;

Grid::Grid()
{
    this->rows = 0;
    this->cols = 0;
    this->board = nullptr;
}

Grid::Grid(int r, int c)
{
    this->rows = r;
    this->cols = c;

    this->board = new Cell*[this->rows];
    for (int i = 0; i < this->rows; i++)
    {
        this->board[i] = new Cell[this->cols];
    }
}

void Grid::putMines(int n)
{
    this->nMines = n;
    int r, c;
    
    //this is essentially brian's function modded to work with objects
    for(int i = 0; i < this->nMines; i++){
        r = rand() % this->rows;
        c = rand() % this->cols;
        if(this->board[r][c].isMine() == true) i--;
            else 
            {
                this->board[r][c].setMine(true);
                
                //todo: increment minesNearby for surrounding mines
                countMines(r,c);
            }
    }
}
void Grid::countMines(int row, int col)
{
    //Locations around tile
    int rowOffset;
    int colOffset;

    /* Assuming bomb is in location [i][j]

        [i-1][j-1]   [i-1][j]   [i-1][j+1]
        [i][j-1]     [i][j]     [i][j+1]
        [i+1][j-1]   [i+1][j]   [i+1][j+1]
    */
   //loops through tile offsets
    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            //tiles surrounding bomb
            rowOffset = row + i;
            colOffset = col + j;

            //Checks if bomb is at the edges or in corners, within range
            if(rowOffset > -1 && rowOffset < this->rows && colOffset > -1 && colOffset < this->cols)
            {
                this->board[rowOffset][colOffset].incMine();
            }
        }
    }
}

void Grid::print()
{
    //header
    this->header();

    //grid
    for (int i = 0; i < this->rows; i++)
    {
        cout << setw(2) << i << "| ";
        for (int j = 0; j < this->cols; j++)
        {
            cout << setw(2) << this->board[i][j].display();
        }
        cout << " |" << endl;
    }

    //footer?
    cout << "  ";
    for (int i = 0; i < this->cols; i++)
        cout << "--";
    cout << "----" << endl;
}

void Grid::header()
{
    cout << endl << "    ";
    for (int i = 0; i < this->cols; i++)
        cout << setw(2) << static_cast<char>(i + 65);
    cout<<endl<<"  ";
    for (int i = 0; i < this->cols; i++)
        cout << "--";
    cout << "---- " << endl;
}

Grid::~Grid()
{
    //delete all the rows
    for (int i = 0; i < this->rows; i++)
    {
        delete []this->board[i];
    }

    //delete the board
    delete [] this->board;
}
