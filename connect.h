
#include "Board.h"

template <typename T>
class connect_Board:public Board<T> {
public:
    connect_Board ();
    bool update_board (int x, int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class connect_Player : public Player<T> {
public:
    connect_Player (string name, T symbol);
    void getmove( int& x,int& y) ;

};

template <typename T>
class connect_Random_Player : public RandomPlayer<T>{
public:
    connect_Random_Player (T symbol);
    void getmove( int& x,int &y) ;
};
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;
template <typename T>
connect_Board<T>::connect_Board() {
    this->rows = 6,this->columns = 7;
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
bool connect_Board<T>::update_board( int x, int y, T mark) {
    if (!( y < 0 || y >= this->columns)) {
        for(int k3=this->rows-1;k3>=0;k3--){
            if(this->board[k3][y]==0){
                this->board[k3][y]=toupper(mark);
                this->n_moves++;
                return true;
            }
        }
    }
    return false;
}
template <typename T>
void connect_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-------------------------------------------------------------";
    }
    cout << endl;
}
template <typename T>
bool connect_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns - 3; j++) {
            if (this->board[i][j] == this->board[i][j+1] &&
                this->board[i][j+1] == this->board[i][j+2] &&
                this->board[i][j+2] == this->board[i][j+3] &&
                this->board[i][j] != 0) {
                return true;
            }
        }
    }
    for (int i = 0; i < this->rows - 3; i++) {
        for (int j = 0; j < this->columns; j++) {
            if (this->board[i][j] == this->board[i+1][j] &&
                this->board[i+1][j] == this->board[i+2][j] &&
                this->board[i+2][j] == this->board[i+3][j] &&
                this->board[i][j] != 0) {
                return true;
            }
        }
    }

    for (int i = 0; i < this->rows - 3; i++) {
        for (int j = 0; j < this->columns - 3; j++) {
            if (this->board[i][j] == this->board[i+1][j+1] &&
                this->board[i+1][j+1] == this->board[i+2][j+2] &&
                this->board[i+2][j+2] == this->board[i+3][j+3] &&
                this->board[i][j] != 0) {
                return true;
            }

            if (this->board[i][j+3] == this->board[i+1][j+2] &&
                this->board[i+1][j+2] == this->board[i+2][j+1] &&
                this->board[i+2][j+1] == this->board[i+3][j] &&
                this->board[i][j+3] != 0) {
                return true;
            }
        }
    }

    return false;
}

template <typename T>
bool connect_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool connect_Board<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
connect_Player<T>::connect_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void connect_Player<T>::getmove( int& x,int& y) {
    cout << "\nPlease enter your move y (0 to 6): ";
    cin >> y;
}
template <typename T>
connect_Random_Player<T>::connect_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 7;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void connect_Random_Player<T>::getmove( int& x,int& y) {
    y = rand() % this->dimension;
}
