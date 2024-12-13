
#ifndef ASSIGMENT_2_PROB7_H
#define ASSIGMENT_2_PROB7_H

#include "Board.h"
extern int c,c2;
extern int c6;
template <typename T>
class four_by_four_Board:public Board<T> {
public:
    four_by_four_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class four_by_four_player : public Player<T> {
public:
    four_by_four_player (string name, T symbol);
    void getmove(int& x, int& y) ;
    void getindedx(int& x, int& y);

};

template <typename T>
class four_by_four_Random_Player : public RandomPlayer<T>{
public:
    four_by_four_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};

//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>
#include<cmath>
using namespace std;

int c3,c4;
int c6;
template <typename T>
four_by_four_Board<T>::four_by_four_Board() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            if (i == 0) {
                if (j % 2 == 0)
                    this->board[i][j] = 'O';
                else
                    this->board[i][j] = 'X';
            }
            else if (i == 3)
            {
                if (j % 2 == 0)
                    this->board[i][j] = 'X';
                else
                    this->board[i][j] = 'O';
            }
            else
                this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool four_by_four_Board<T>::update_board(int x, int y, T mark) {
    while(this->board[c3][c4] != toupper(mark)) {
        if (c6==1) {
            c3 = rand() % 4;
            c4 = rand() % 4;
        }
        else {
            cout << endl;
            cout << "Sorry the present index you entered is not valid, please enter index again: ";
            cin >> c3 >> c4;
        }
    }

    while(this->board[x][y] != 0) {
        if (c6==1) {
            x = rand() % 4;
            y = rand() % 4;
        }
        else {
            cout << endl;
            cout << "Sorry the new place is not empty please enter index again ";
            cin >> x >> y;
        }
    }

    while(!((abs(c3 - x) == 1 && c4 == y) || (abs(c4 - y) == 1 && c3 == x))) {
        if (c6==1) {
            x = rand() % 4;
            y = rand() % 4;
        }
        else {
            cout << endl;
            cout << "sorry the symbol should move one open place and not diagonally , try again ";
            cin >> x >> y;
        }
    }


    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        this->n_moves++;
        this->board[x][y] = toupper(mark);
        this->board[c3][c4] = 0;

        return true;
    }

    return false;
}


template <typename T>
void four_by_four_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {

            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}


template <typename T>
bool four_by_four_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns - 2; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i][j + 1] &&
                this->board[i][j] == this->board[i][j + 2]) {
                return true;
            }
        }
    }
    for (int j = 0; j < this->columns; j++) {
        for (int i = 0; i < this->rows - 2; i++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j] &&
                this->board[i][j] == this->board[i + 2][j]) {
                return true;
            }
        }
    }
    for (int i = 0; i < this->rows - 2; i++) {
        for (int j = 0; j < this->columns - 2; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i][j] == this->board[i + 2][j + 2]) {
                return true;
            }
        }
    }
    for (int i = 0; i < this->rows - 2; i++) {
        for (int j = 2; j < this->columns; j++) {
            if (this->board[i][j] != 0 &&
                this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i][j] == this->board[i + 2][j - 2]) {
                return true;
            }
        }
    }
    return false;
}
template <typename T>
bool four_by_four_Board<T>::is_draw() {
    return (this->n_moves==900&&!is_win());
}

template <typename T>
bool four_by_four_Board<T>::game_is_over() {
    return is_win();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
four_by_four_player<T>::four_by_four_player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void four_by_four_player<T>::getmove(int& x, int& y) {
    c6=0;
    if(this->getsymbol()=='X') {
        cout << "Enter the index of X you want to move";
        cin>>c3>>c4;
    }
    else if(this->getsymbol()=='O') {
        cout << "Enter the index of O you want to move";
        cin>>c3>>c4;
    }

    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
four_by_four_Random_Player<T>::four_by_four_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));

}

template <typename T>
void four_by_four_Random_Player<T>::getmove(int& x, int& y) {
    c6=1;
    if(this->getsymbol()=='X') {
        c= rand() % this->dimension;
        c2=rand() % this->dimension;
    }
    else if(this->getsymbol()=='O') {
        c= rand() % this->dimension;
        c2=rand() % this->dimension;
    }
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif //ASSIGMENT_2_PROB7_H
