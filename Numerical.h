
#include "Board.h"
#include<list>
#include <cstdlib>
#include<algorithm>


template <typename T>
class Numerical_Board:public Board<T> {
public:
    Numerical_Board ();
    bool update_board (int x , int y , int symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Numerical_Player : public Player<T> {
protected:
    list<int>d1={1,3,5,7,9};
    list<int>d2={2,4,6,8};
    char m9='X' , m1='O';
public:
    Numerical_Player (string name, T symbol);
    void getmove(int& x, int& y) ;



    int dimension;
};

template <typename T>
class Numerical_Random_Player : public RandomPlayer<T>{
protected:
    list<int>d1={1,3,5,7,9};
    list<int>d2={2,4,6,8};
    char m9='X' , m1='O';
public:
    Numerical_Random_Player (T symbol);
    void getmove(int &x, int &y) ;

};





//--------------------------------------- IMPLEMENTATION


#include <iostream>
#include <iomanip>

using namespace std;
int cf;
template <typename T>
Numerical_Board<T>::Numerical_Board() {
    this->rows = this->columns = 3;
    this->board = new int*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new int[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Numerical_Board<T>::update_board(int x, int y, int mark) {
        if(cf==1) {
            while (x < 0 || x >= this->rows || y < 0 || y >= this->columns||this->board[x][y]!=0) {
                cout << "Sorry this is an invalid index,,please enter the index again";
                cin >> x >> y;
            }
        }
        else if (cf==0) {
            while (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
                x = rand() % 3;
                y = rand() % 3;
            }
        }

    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = mark;
        }

        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Numerical_Board<T>::display_board() {
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
bool Numerical_Board<T>::is_win() {
    if(this->board[0][0]+this->board[1][1]+this->board[2][2]==15||this->board[0][2]+this->board[1][1]+this->board[2][0]==15){
        return true;
    }
    for(int k3=0;k3<this->rows;k3++){
        if(this->board[k3][0]+this->board[k3][1]+this->board[k3][2]==15||this->board[0][k3]+this->board[1][k3]+this->board[2][k3]==15){
            return true;
        }
    }
    return false;
}
template <typename T>
bool Numerical_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Numerical_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Numerical_Player<T>::Numerical_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Numerical_Player<T>::getmove(int& x, int& y) {
    cf=1;
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;
    if(this->symbol==m9) {
        int m8;
        cout << "Choose number from this array\n";
        auto it = this->d1.begin();
        for (it = this->d1.begin(); it != this->d1.end(); it++) {
            cout << *it << " ";
        }
        cout << endl;
        cin >> m8;
        auto y4 = find(this->d1.begin(), this->d1.end(), m8);
        while (y4 == this->d1.end()) {
            cout << "Error, please enter a number in the list" << endl;
            cin >> m8;
            y4 = find(this->d1.begin(), this->d1.end(), m8);
        }
        auto yes = find(this->d1.begin(), this->d1.end(), m8);
        if (yes != this->d1.end()) {
            this->d1.erase(yes);
        }
        this->symbol=m8;
        m9=this->symbol;
    }

    else if(this->symbol==m1){
        cout<<"Choose number from this array\n" ;
        auto it=this->d2.begin();
        for(it=this->d2.begin();it!=this->d2.end();it++){
            cout<<*it<<" ";
        }
        int m8;
        cout<<endl;
        cin>>m8;
        auto y4 = find(this->d2.begin(), this->d2.end(), m8);
        while (y4 == this->d2.end()) {
            cout << "Error, please enter a number in the list" << endl;
            cin >> m8;
            y4 = find(this->d2.begin(), this->d2.end(), m8);
        }
        auto yes = find(this->d2.begin(), this->d2.end(), m8);
        if (yes != this->d2.end()) {
            this->d2.erase(yes);
        }
        this->symbol=m8;
        m1=this->symbol;
    }
}
template <typename T>
Numerical_Random_Player<T>::Numerical_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));
}

template <typename T>
void Numerical_Random_Player<T>::getmove(int& x, int& y) {
    cf=0;
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    if(this->symbol==m9){
        int m10;
        auto it = this->d1.begin();
        advance(it, rand() %  this->d1.size());
        m10 = *it;
        this->d1.erase(it);
        this->symbol=m10;
        m9=this->symbol;

    }
    else if(this->symbol==m1){
        auto it = this->d2.begin();
        advance(it, rand() % this->d2.size());
        int m10;
        m10=*it;
        this->d2.erase(it);
        this->symbol=m10;
        m1=this->symbol;

    }
}

