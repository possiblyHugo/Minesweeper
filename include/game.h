#ifndef GAME_H
#define GAME_H

#include <iostream>
#include<cstdlib>



class Game {
public:
    void CreateBoard() {
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                board[i][j] = 'u';
                visibleBoard[i][j] = '#';
            }
        }

        GenerateMines();
        GenerateTiles();
    }

    void DrawBoard() {
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                std::cout << board[i][j];
            }
            std::cout << RESET << "\n";
        }
    }

    void Print_Visible_board() {
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {
                Print_Colored_Char(board[i][j]);
                std::cout << " ";
            }
            std::cout << "\n";
        }
    }

private:
    char board [30][30]; // This is the actual board 
    char visibleBoard[30][30]; // This is the board that the player sees

    // Generate mines
    void GenerateMines() {
        srand((unsigned) time(NULL));

        int Mines = 100;
        int x = 0, y = 0;
        while (Mines > 0) {
            x = rand() % 30;
            y = rand() % 30;

            if (board[x][y] == 'u') {
                board[x][y] = 'm'; // Place mine
                Mines--;
            }
        }
    }

    void GenerateTiles() {
        for (int i = 0; i < 30; i++) {
            for (int j = 0; j < 30; j++) {

                // Check if tile is a mine
                if (board[i][j] == 'm') {
                    continue;
                }

                int mines = 0;

                if (j - 1 >= 0 && board[i][j - 1] == 'm') { // Left
                    mines++;
                }

                if (j + 1 < 30 && board[i][j + 1] == 'm') { // Right
                    mines++;
                }

                if (i - 1 >= 0 && board[i - 1][j] == 'm') { // Up
                    mines++;
                }                

                if (i + 1 < 30 && board[i + 1][j] == 'm') { // Down
                    mines++;
                }

                if (i - 1 >= 0 && j - 1 >= 0 && board[i - 1][j - 1] == 'm') { // Top Left
                    mines++;
                }   

                if (i - 1 >= 0 && j + 1 < 30 && board[i - 1][j + 1] == 'm') { // Top right
                    mines++;
                }

                if (i + 1 < 30 && j - 1 >= 0 && board[i + 1][j - 1] == 'm') { // Bottom left
                    mines++;
                }

                if (i + 1 < 30 && j + 1 >= 0 && board[i + 1][j + 1] == 'm') { // Bottom right
                    mines++;
                }
                

                char charValue = '0' + mines;

                board[i][j] = charValue;
            }
        }
    }

    void Print_Colored_Char(char character) {

        /*
            1 = CYAN
            2 = GREEN
            3 = YELLOW
            4 = BLUE
            5 = MAGENTA
            6 = BOLDCYAN
            7 = BOLDGREEN
            8 = BOLDYELLOW

            MINE = RED

        */

        switch (character) {
            
            case '0':
                std::cout << WHITE << character;
                break;
            case '1':
                std::cout << CYAN << character;
                break;
            case '2':
                std::cout << GREEN << character;
                break;
            case '3':
                std::cout << YELLOW << character;
                break;
            case '4':
                std::cout << BLUE << character;
                break;
            case '5':
                std::cout << MAGENTA << character;
                break;
            case '6':
                std::cout << CYAN << character;
                break;
            case '7':
                std::cout << BOLDGREEN << character;
                break;
            case '8':
                std::cout << BOLDYELLOW << character;
                break;
            case 'm':
                std::cout << RED << 'm';
                break;
            case 'f': // flag
                std::cout << RED << 'F';
                resetcolor();
                break;
            default:
                std::cout << "Error:" << character;
        }
    }

};



#endif