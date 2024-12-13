#ifndef _3X3X_O_H
#define _3X3X_O_H

#include "Board.h"
#include<map>

template <typename T>
class ultimate_Board:public Board<T> {
public:
    ultimate_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};
template <typename T>
class Ultimate:public Board<T> {
private:
    ultimate_Board<T>* small[3][3];
public:
    Ultimate ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class ultimate_Player : public Player<T> {
public:
    ultimate_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class ultimate_Random_Player : public RandomPlayer<T>{
public:
    ultimate_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION
int c,c2;
int moves=0;
int nmoves=0;
map<int,int>d;
#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

template <typename T>
Ultimate<T>::Ultimate() {
    this->rows = this->columns = 3;
    for(int v1=0;v1<this->rows;v1++) {
        for (int v2 = 0; v2 < this->columns; v2++){
            small[v1][v2]=new ultimate_Board<T>();
        }
    }
}
template <typename T>
bool Ultimate<T>::update_board(int x, int y, T symbol) {

    return small[c][c2]->update_board(x, y, symbol);
}

template <typename T>
void Ultimate<T>::display_board() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            small[i][j]->display_board();
        }
    }
}
template <typename T>
bool Ultimate<T>::is_win() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (small[i][0]->is_win() && small[i][1]->is_win() && small[i][2]->is_win()) {
                return true;
            }
            if (small[0][j]->is_win() && small[1][j]->is_win() && small[2][j]->is_win()) {
                return true;
            }
            if (small[0][0]->is_win() && small[1][1]->is_win() && small[2][2]->is_win()) {
                return true;
            }
            if (small[0][2]->is_win() && small[1][1]->is_win() && small[2][0]->is_win()) {
                return true;
            }
        }
    }
    return false;
}
template <typename T>
bool Ultimate<T>::is_draw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!small[i][j]->is_draw()) {
                return false;
            }
        }
    }
    return true;
}
template <typename T>
bool Ultimate<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
ultimate_Board<T>::ultimate_Board() {
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
bool ultimate_Board<T>::update_board(int x, int y, T mark) {
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            moves++;
            this->board[x][y] = toupper(mark);
        }
        if (this->is_win()) {
            for (int i = 0; i < this->rows; i++) {
                for (int j = 0; j < this->columns; j++) {
                    this->board[i][j] = toupper(mark);
                }
            }
            this->n_moves=0;
            moves=0;
        }
        if (this->is_draw()) {
            this->n_moves=0;
            moves=0;
            for (int i = 0; i < this->rows; i++) {
                for (int j = 0; j < this->columns; j++) {
                    this->board[i][j] = 'D';
                }
            }
        }
        return true;
    }
    return false;
}


template <typename T>
void ultimate_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout<<endl;
}

template <typename T>
bool ultimate_Board<T>::is_win() {
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0)) {
            return true;
        }
    }

    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0)) {
        return true;
    }

    return false;
}

template <typename T>
bool ultimate_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool ultimate_Board<T>::game_is_over() {
    return is_win() || is_draw();
}
template <typename T>
ultimate_Player<T>::ultimate_Player(string name, T symbol) : Player<T>(name, symbol) {}
template <typename T>
void ultimate_Player<T>::getmove(int& x, int& y) {
    if(moves==0){
        cout<<"Enter the index of small board with separate spaces to play in";
        cin>>c>>c2;
        for(auto mm:d){
            while(c==mm.first && c2==mm.second){
                cout<<"Sorry this  Board is completed, please enter the two index again"<<endl;
                cin>>c>>c2;
            }
        }
        d.insert({c,c2});

    }
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
}

template <typename T>
ultimate_Random_Player<T>::ultimate_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void ultimate_Random_Player<T>::getmove(int& x, int& y) {
    if(moves==0){
        c=rand() % this->dimension;
        c2=rand() % this->dimension;
        for(auto mm:d){
            while(c==mm.first && c2==mm.second){
                c=rand() % this->dimension;
                c2=rand() % this->dimension;
            }
        }
        d.insert({c,c2});

    }
    x = rand() % this->dimension;
    y = rand() % this->dimension;
}







#endif //_3X3X_O_H

