//
// Created by gabra on 12/4/2024.
//

#ifndef ASSIGMENT_2_PYRAMIC_GAME_H
#define ASSIGMENT_2_PYRAMIC_GAME_H
#include "Board.h"

template <typename T>
class Pyramid_Board:public Board<T> {
public:
    Pyramid_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Pyramid_Player : public Player<T> {
public:
    Pyramid_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Pyramid_Random_Player : public RandomPlayer<T>{
public:
    Pyramid_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
Pyramid_Board<T>::Pyramid_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Pyramid_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Pyramid_Board<T>::display_board() {
    bool ok = false;
    for (int i = 0; i < this->rows; i++) {
        if (i == 0) cout << "                ";

        for (int j = 0; j < this->columns; j++) {
            if (i == j) {
                if (i != 0 && i != 2)
                    cout << endl;
                else
                    ok = true;
            }

            if (i == 0 && j == 1)
                cout << "        ";
            //////// problem when chhose 0 0!!
            cout << "(" << i << "," << j << ")";
            cout << "  " << this->board[i][j] ;
            if (ok) {
                cout << endl;
                ok = false;
            }
        }

    }
    cout << "\n-----------------------------------------";
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool Pyramid_Board<T>::is_win() {

    // Check Diagonals
    if ((this->board[0][0] == this->board[0][1] && this->board[0][1] == this->board[1][1] && this->board[0][1]  != 0) ||
        (this->board[0][0] == this->board[1][0] && this->board[1][0] == this->board[2][2] && this->board[1][0]!= 0))
        return true;
    // Check Rows
    if ((this->board[0][1] == this->board[0][2] && this->board[0][2]  == this->board[1][0] && this->board[0][2] != 0) ||
        (this->board[1][1] == this->board[1][2] && this->board[1][2]  == this->board[2][0] && this->board[1][2] != 0)||
        (this->board[2][1] == this->board[2][0] && this->board[2][0]  == this->board[2][2] && this->board[2][0] != 0))
            return true;
    // Check Column
    if (this->board[0][0] == this->board[0][2] && this->board[0][2] == this->board[2][0] && this->board[0][2] != 0)
        return true;

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Pyramid_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Pyramid_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Pyramid_Player<T>::Pyramid_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Pyramid_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

// Constructor for X_O_Random_Player
template <typename T>
Pyramid_Random_Player<T>::Pyramid_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Pyramid_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}
#endif //ASSIGMENT_2_PYRAMIC_GAME_H
