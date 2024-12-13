

#include <iostream>
#include "Board.h"
#include "Numerical.h"
#include "four_by_four.h"
#include"ultimate.h"
#include"connect.h"
#include "Pyramic_Game.h"
#include "word_Game.h"
#include "game_3.h"
#include "game_6.h"
#include "MinMaxPlayer.h"


using namespace std;

template <typename T>
GameManager<T>* createGameManager(Numerical_Board<T>* board, Player<T>* players[2]) {
    return new GameManager<T>(board, players);
}
// DEBUG IT WHEN USING !
void Game1()
{
    /// Debug when using this game as there is lag on regular run
    int choice;
    Player<char>* players[2];
    Pyramid_Board<char>* B = new Pyramid_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to Gabr's Pyramid Tic-Tac-Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Pyramid_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new Pyramid_Random_Player<char>('X');
            break;
        case 3:
            players[0] = new X_O_MinMax_Player<char>('X');
            players[0]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return ;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new Pyramid_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new Pyramid_Random_Player<char>('O');
            break;
        case 3:
            players[1] = new X_O_MinMax_Player<char>('O');
            players[1]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return ;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void Game2(){
    int choice;
    Player<char>* players[2];
    connect_Board<char>* B = new connect_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to Connectfour Game. :)\n";

    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new connect_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new connect_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new connect_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new connect_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
    }

    GameManager<char> x_o_game(B, players);
    x_o_game.run();
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    int d4;
    cout<<"Do you want to 1-play again or 2-exit ,, Enter a number"<<endl;
    cin>>d4;
    while(d4!=2) {
        Game2();
        cout<<"Do you want to 1-play again or 2-exit ,, Enter a number"<<endl;
        cin>>d4;
    }
}

void Game3(){
    Game_3<char>* game = new Game_3<char>();
    string playerXName, playerOName;

    cout << "Enter Player X Name: ";
    cin >> playerXName;
    cout << "Enter Player O Name: ";
    cin >> playerOName;

    char currentSymbol = 'X';
    string currentPlayer = playerXName;

    while (!game->is_full()) {
        game->display_board();
        int x, y;
        cout << currentPlayer << " (" << currentSymbol << "), enter your move (row and column): ";
        cin >> x >> y;

        if (game->update_board(x, y, currentSymbol)) {
            auto scores = game->count_scores();
            cout << "Score - X: " << scores.first << ", O: " << scores.second << endl;

            // تبديل الدور
            currentSymbol = (currentSymbol == 'X') ? 'O' : 'X';
            currentPlayer = (currentPlayer == playerXName) ? playerOName : playerXName;
        } else {
            cout << "Invalid move, try again!" << endl;
        }
    }

    auto finalScores = game->count_scores();
    cout << "Game Over! Final Score - X: " << finalScores.first << ", O: " << finalScores.second << endl;

    if (finalScores.first > finalScores.second) {
        cout << playerXName << " wins!" << endl;
    } else if (finalScores.second > finalScores.first) {
        cout << playerOName << " wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }

    delete game;

}

void Game4()
{
    int choice;
    Player<char>* players[2];
    word_Board<char>* B = new word_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to Gabr's Word Tic Tac Toe Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:

            players[0] = new word_Player<char>(playerXName, ' ');
            break;
        case 2:
            players[0] = new word_Random_Player<char>(' ');
            break;
        case 3:
            players[0] = new X_O_MinMax_Player<char>(' ');
            players[0]->setBoard(B);
            break;

        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return ;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cout << "3. Smart Computer (AI)\n";
    cin >> choice;

    switch(choice) {
        case 1:

            players[1] = new word_Player<char>(player2Name, ' ');
            break;
        case 2:
            players[1] = new word_Random_Player<char>(' ');
            break;
        case 3:
            players[1] = new X_O_MinMax_Player<char>(' ');
            players[1]->setBoard(B);
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return ;
    }

    // Create the game manager and run the game
    GameManager<char> word_game(B, players);
    word_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

void Game8(){
    int choice;
    Player<char>* players[2];
    Ultimate<char>* B = new Ultimate<char>();
    string playerXName, player2Name;

    cout << "Welcome to Ultimate tic-toe Game. :)\n";

    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new ultimate_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new ultimate_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new ultimate_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new ultimate_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
    }

    GameManager<char> x_o_game(B, players);
    x_o_game.run();
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    int d4;
    cout<<"Do you want to 1-play again or 2-exit ,, Enter a number"<<endl;
    cin>>d4;
    while(d4!=2) {
        Game8();
        cout<<"Do you want to 1-play again or 2-exit ,, Enter a number"<<endl;
        cin>>d4;
    }
}

void Game7(){
    int choice;
    Player<char>* players[2];
    four_by_four_Board<char>* B = new four_by_four_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI 4*4 Tic-Tac-Toe Game. :)\n";
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new four_by_four_player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new four_by_four_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new four_by_four_player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new four_by_four_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
    }
    GameManager<char> x_o_game(B, players);
    x_o_game.run();
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    int d4;
    cout<<"Do you want to 1-play again or 2-exit ,, Enter a number"<<endl;
    cin>>d4;
    while(d4!=2) {
        Game7();
        cout<<"Do you want to 1-play again or 2-exit ,, Enter a number"<<endl;
        cin>>d4;
    }
}

void Game5() {
    int choice;
    Player<char>* players[2];
    Numerical_Board<char> *B = reinterpret_cast<Numerical_Board<char> *>(new Numerical_Board<int>());
    string playerXName, player2Name;

    cout << "Welcome to Numerical Game. :)\n";

    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new Numerical_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new Numerical_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return;
    }

    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new Numerical_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new Numerical_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return;
    }

    auto x_o_game = createGameManager<char>(B, players);
    x_o_game->run();
    delete x_o_game;

    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
    int d4;
    cout<<"Do you want to 1-play again or 2-exit ,, Enter a number"<<endl;
    cin>>d4;
    cin.ignore();
    while(d4!=2) {
        Game5();
        cout<<"Do you want to 1-play again or 2-exit ,, Enter a number"<<endl;
        cin>>d4;
    }

}

void Game6() {
    int choice;
    Player<char>* players[2];
    X_O_Board<char>* B = new X_O_Board<char>();
    string playerXName, player2Name;

    cout << "Welcome to FCAI X-O Game. :)\n";

    // Set up player 1
    cout << "Enter Player X name: ";
    cin >> playerXName;
    cout << "Choose Player X type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new X_O_Player<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new X_O_Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return ;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new X_O_Player<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new X_O_Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return ;
    }

    // Create the game manager and run the game
    GameManager<char> x_o_game(B, players);
    x_o_game.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }
}

int main(){
    while(true){
        cout<<"Welcome to our World in Tic Tac Toe"<<endl;
        int a16;
        cout<<"Enter the number of game you want to play\n 1-Pyramid\n 2-connect four\n 3- 5 x 5 Tic Tac Toe\n 4-Word\n 5-Numerical tic tac toe\n 6-Misere \n 7-four by four tic tac toe\n 8-ultimate tic tac toe"<<endl;
        cin>>a16;
        if (a16 == 1)
        {
            Game1();
        }
        else if(a16==2){
            Game2();
        }

        else if (a16 == 3)
        {
            Game3();
        }
        else if (a16 == 4)
        {
            Game4();
        }
        else if(a16==5){
            Game5();
        }
        else if (a16 == 6)
        {
            Game6();
        }
        else if(a16==7){
            Game7();
        }
        else if(a16==8){
            Game8();
        }
        int hd;
        cout<<"\nDo you want to play another game? \n1-YES\n2-NO"<<endl;
        cin>>hd;
        if(hd==2){
            cout<<"Thanks for using our program ^-^"<<endl;
            break;
        }

    }

    return 0;
}

