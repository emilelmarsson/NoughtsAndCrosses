#include "IO.h"
class Board;
class Player;

// Flush...
void IO::flush(){
    std::cin.ignore(1000,'\n');
}

// Capitalize a char.
 void IO::capitalizeChar(char *c){
    if(*c >= 97 && *c <= 122)
        *c -= 32;
}

// Press any key to continue.
void IO::wait(){
    getch();
    std::cout << std::endl;
}

// Display the current state of the board.
void IO::displayBoard(Board board){
    std::cout << std::endl;
    for(int i = 0; i < 3; i++){
        std::cout << "| ";
        for(int j = 0; j < 3; j++){
            std::cout << board.getTile(i * 3 + j) << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


// Welcome the users.
void IO::welcome(){
    std::cout << " - = Welcome to Tic-Tac-Toe = -\n\n";
}

// Announce the winner.
void IO::announceWinner(Board board){
    int winner = board.returnWinner();

    if(winner != -1){
        int playerIndex = winner == 10 ? 0 : 1;
        std::string name = board.returnPlayer(playerIndex)->getName();
        std::cout << "The winner is " << name << "!";
    }else
        std::cout << "It's a tie!";

    wait();
}

// Get a string from a user.
std::string IO::getString(std::string message){
    std::string answer;
    std::cout << message;
    std::cin >> answer;
    flush();
    return answer;
}

/*
    Get the answer to a question on the form. "Which tile do you want to mark? (1-9): ".
    Very persistent function, doesn't exit until the question has been answered.
*/
char IO::getAnswer(std::string message, char answers[], int len, std::string error){
    bool condition;
    char answer;
    do{
        std::cout << message;
        std::cin.get(answer);
        flush();
        capitalizeChar(&answer);

        for(int i=0;i < len;i++)
            if(answer == answers[i]){
                condition = true;
                break;
            }
        if(!condition){
            std::cout << error;
            wait();
        }
    }while(!condition);
    return answer;
}
