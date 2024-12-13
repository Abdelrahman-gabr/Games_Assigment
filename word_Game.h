//
// Created by gabra on 11/28/2024.
//

#ifndef ASSIGMENT_2_WORD_GAME_H
#define ASSIGMENT_2_WORD_GAME_H
#include "Board.h"

char chh;   //
template <typename T>
class word_Board:public Board<T> {
public:
    word_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win();
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class word_Player : public Player<T> {
public:
    word_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class word_Random_Player : public RandomPlayer<T>{
public:
    word_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <bits/stdc++.h>
using namespace std;

vector<string> words;




// Constructor for X_O_Board
template <typename T>
word_Board<T>::word_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;

    ifstream filename("dic.txt");
    if (!filename) {
        cout << "Error: Could not open dictionary file (dic.txt).\n";
        exit(EXIT_FAILURE);
    }
    string emp;
    while (getline(filename, emp)) {

            words.push_back(emp);
    }

}


template <typename T>
bool word_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
//        if (mark == 0){
//            this->n_moves--;
//            this->board[x][y] = 0;
//        }
//        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
//        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void word_Board<T>::display_board() {
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

// Returns true if there is any winner
template <typename T>
bool word_Board<T>::is_win() {
    // Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        string row, col;
        for (int j = 0; j < this->columns; j++) {
            row += this->board[i][j];
            col += this->board[j][i];
        }
        if (find(words.begin(), words.end(), row) != words.end() ||
            find(words.begin(), words.end(), col) != words.end()) {
            return true;
        }
    }

    // Check diagonals
    string check1;
    check1 += this->board[0][0] ;
    check1 += this->board[1][1] ;
    check1 += this->board[2][2];

    string rcheck1;
    rcheck1 += this->board[2][2];
    rcheck1 += this->board[1][1];
    rcheck1 += this->board[0][0];

    string check2;
    check2 += this->board[0][2];
    check2 += this->board[1][1];
    check2 += this->board[2][0];

    string rcheck2;
    check2 += this->board[2][0];
    check2 += this->board[1][1];
    check2 += this->board[0][2];

    if (std::find(words.begin(), words.end(),check1) != words.end() || std::find(words.begin(), words.end(),rcheck1) != words.end() ||std::find(words.begin(), words.end(),rcheck2) != words.end() ||
        std::find(words.begin(), words.end(),check2) != words.end())  {
        return true;
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool word_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool word_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
word_Player<T>::word_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void word_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces and your char you want: ";
    cin >> x >> y >> chh;
    this->symbol = chh;   // 2
}

// Constructor for X_O_Random_Player
template <typename T>
word_Random_Player<T>::word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void word_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    chh = 'a' + (rand() % 26);
    this->symbol = chh;
}








#endif //ASSIGMENT_2_WORD_GAME_H
