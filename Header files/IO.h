#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED
#include <iostream>
#include <conio.h>
#include <string>
#include "board.h"
#include "player.h"

// This class is used for input and output.

class IO{
    static void flush();

    static void capitalizeChar(char *c);

public:
    static void wait();
    static void displayBoard(Board board);
    static void welcome();
    static void announceWinner(Board board);
    static std::string getString(std::string message);
    static char getAnswer(std::string message, char answers[], int len, std::string error);
};
#endif // IO_H_INCLUDED
