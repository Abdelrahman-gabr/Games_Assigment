#ifndef GAME_6_H
#define GAME_6_H

#include "Board.h"
#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class X_O_Board : public Board<T> {
public:
    X_O_Board();

    bool update_board(int x, int y, T symbol);
    void display_board();
    bool is_win();  // سيتم تنفيذ الدالة لاحقًا مع منطق "الخسارة".
    bool is_draw();
    bool game_is_over();
};

// --------------------------------------- IMPLEMENTATION FOR X_O_Board

template <typename T>
X_O_Board<T>::X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool X_O_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
        if (mark == 0) {
            this->n_moves--;
            this->board[x][y] = 0;
        } else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

template <typename T>
void X_O_Board<T>::display_board() {
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
bool X_O_Board<T>::is_win() {
    // عكس منطق الفوز: إذا تحقق "ثلاث علامات متشابهة" فهذا يعني أن اللاعب خسر
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true; // "خسارة"
        }
    }
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true; // "خسارة"
    }
    return false;
}

template <typename T>
bool X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool X_O_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// --------------------------------------- PLAYER CLASSES

template <typename T>
class X_O_Player : public Player<T> {
public:
    X_O_Player(string name, T symbol);

    void getmove(int &x, int &y);
};

template <typename T>
X_O_Player<T>::X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void X_O_Player<T>::getmove(int &x, int &y) {
    cout << "\nPlease enter your move (x y): ";
    cin >> x >> y;
}

template <typename T>
class X_O_Random_Player : public RandomPlayer<T> {
public:
    X_O_Random_Player(T symbol);

    void getmove(int &x, int &y);
};

template <typename T>
X_O_Random_Player<T>::X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void X_O_Random_Player<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}

#endif // GAME_6_H
