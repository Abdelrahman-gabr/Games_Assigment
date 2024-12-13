#ifndef GAME3_H
#define GAME3_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class Game_3 {
public:
    Game_3();
    bool update_board(int x, int y, T symbol);
    void display_board();
    pair<int, int> count_scores();
    bool is_full();
    bool is_valid_move(int x, int y);

private:
    int rows, columns;
    vector<vector<T>> board;
    int n_moves;
};

template <typename T>
Game_3<T>::Game_3() {
    rows = columns = 5;
    board = vector<vector<T>>(rows, vector<T>(columns, 0));
    n_moves = 0;
}

template <typename T>
bool Game_3<T>::update_board(int x, int y, T symbol) {
    if (is_valid_move(x, y)) {
        board[x][y] = toupper(symbol);
        n_moves++;
        return true;
    }
    return false;
}

template <typename T>
bool Game_3<T>::is_valid_move(int x, int y) {
    return (x >= 0 && x < rows && y >= 0 && y < columns && board[x][y] == 0);
}

template <typename T>
void Game_3<T>::display_board() {
    for (int i = 0; i < rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < columns; j++) {
            cout << setw(3) << board[i][j] << " |";
        }
        cout << "\n---------------------------------";
    }
    cout << endl;
}

template <typename T>
pair<int, int> Game_3<T>::count_scores() {
    int scoreX = 0, scoreO = 0;


    auto count_line = [&](vector<T> line) {
        int countX = 0, countO = 0;
        for (T cell : line) {
            if (cell == 'X') {
                countX++;
                if (countX == 3) {
                    scoreX++;
                    countX = 0;
                }
            } else {
                countX = 0;
            }
            if (cell == 'O') {
                countO++;
                if (countO == 3) {
                    scoreO++;
                    countO = 0;
                }
            } else {
                countO = 0;
            }
        }
    };

    for (int i = 0; i < rows; i++) count_line(board[i]);

    for (int j = 0; j < columns; j++) {
        vector<T> column(rows);
        for (int i = 0; i < rows; i++) column[i] = board[i][j];
        count_line(column);
    }

    for (int start = 0; start <= columns - 3; start++) {
        vector<T> diag1, diag2;
        for (int i = 0; i < rows - start; i++) {
            if (start + i < columns) {
                diag1.push_back(board[i][start + i]);
                diag2.push_back(board[start + i][i]);
            }
        }
        count_line(diag1);
        count_line(diag2);
    }

    return {scoreX, scoreO};
}

template <typename T>
bool Game_3<T>::is_full() {
    return n_moves == rows * columns;
}

#endif // GAME3_H

