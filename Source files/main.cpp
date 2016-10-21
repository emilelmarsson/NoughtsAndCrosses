#include <iostream>
#include "IO.h"
#include "board.h";
#include "player.h"
#include <cstdlib>
#include <ctime>

using namespace std;

/*
    This project was created in September and October of 2016 by Emil Elmarsson.
    I did it to practice OOP in C++. It was also an interesting challenge to
    implement the minimax algorithm.
*/

int main()
{
    // This variable tells if the user wants to replay with the same settings
    bool replay;
    // The board of the game
    Board board;

    // Welcomes the user.
    IO::welcome();

    // A seed for the random number generator so that we don't get the same every time.
    srand(time(NULL));

    // This is the main loop. Continues until the user doesn't want to play anymore.
    while(true){
        // If the user doesn't want to replay, reset the board with new players.
        if(!replay){
            char answers[] = "1234";
            // Prompt the user for what gamemode they want to choose.
            char answer = IO::getAnswer("Which gamemode do you want to play?\n\n1: Human vs. Human.\n2: Human vs. A.I.\n3: A.I. vs. A.I.\n4: Exit.\n\n", answers, 4, "You have to enter a number from 1 to 4. Try again. ");
            int type = answer - '1';

            // If the user wants to exit, break.
            if(type == 3)
                break;

            /*  Setting the board to the chosen type.
                0 = Human vs. Human.
                1 = Human vs. A.I.
                2 = A.I. vs. A.I.
            */
            board = Board(type);

            /*  Iterates through the players and sets their names. Player is an abstract class with two subclasses.
                Human, and Computer. The setName function is a virtual function. In the Human class the function
                prompts the user for a name, while in the Computer one a random one is chosen from a list. It also
                asks for the A.I. difficulty.
            */
            for(int x = 0; x < Board::getPlayers(); x++){
                Player *p = board.returnPlayer(x);
                p->setName(x);
            }
        }

        // Displays the board.
        IO::displayBoard(board);

        bool firstPlayerTurn = true;
        // The game loop. Continues until the game is over.
        while(!board.hasEnded()){
            // New turn, change the player index.
            int playerIndex = firstPlayerTurn ? 0 : 1;
            // Retrieves the appropriate player for this turn.
            Player *p = board.returnPlayer(playerIndex);

            /*  Make a move. This is also a virtual function. The Human one asks the user which tile it wants to mark, while
                the Computer one computes an adequate tile according to its difficulty.
            */
            p->makeMove(&board, playerIndex);

            // Display the board again.
            IO::displayBoard(board);

            // It's the other player's turn.
            firstPlayerTurn = !firstPlayerTurn;
        }

        // The game is over so we must announce the winner. (Or if it's a tie.)
        IO::announceWinner(board);

        char answers[] = "YN";
        char answer = IO::getAnswer("Do you want to replay? (Y/N): ", answers, 2, "Please answer Y for yes or N for no. ");

        if(answer == 'Y'){
            // If the user wants to replay we maintain the player objects while clearing the board.
            board.clearBoard();
            // We swap the players so that both players get a chance to start.
            board.swapPlayers();
            replay = true;
        }else
            replay = false;
    }
}
