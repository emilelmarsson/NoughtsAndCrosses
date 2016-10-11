#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "player.h"

using namespace std;

char Player::getMark(){
    return mark;
}

Player::Player(char mark){
    setMark(mark);
}

void Player::setName(string name){
    this->name = name;
}

// Virtual functions
void Player::makeMove(Board *board, int playerIndex){}

void Player::setName(int playerIndex){}

string Player::getName(){
    return name;
}

// Sets the mark of the player.
void Player::setMark(char mark){
    if(Tile::isValidMark(mark))
        this->mark = mark;
    else
        this->mark = Tile::CROSS;
}

// Utilizes the superclass.
void Human::setName(string name){
    Player::setName(name);
}

// Prompts the user for a name.
void Human::setName(int playerIndex){
    if(!Board::isValidPlayerIndex(playerIndex))
        return;
    // Integer to character conversion.
    char cx = static_cast<char>(48 + playerIndex + 1);
    string answer = IO::getString(string("Enter the name of player ") + cx + string(": "));
    Human::setName(answer);
}

// Prompt the user for a tile number. If that tile is not empty, ask again.
void Human::makeMove(Board *board, int playerIndex){
    bool condition = false;
    do{
        char newAnswers[] = "123456789";
        string name = this->getName();
        char answer = IO::getAnswer("What tile does " + name + " want to mark? (1-9): ", newAnswers, 9, "Choose a number from 1 to 9, please. ");

        int tileIndex = answer - '1';

        condition = board->emptyTile(tileIndex);
        if(condition)
            board->setTile(tileIndex, playerIndex);
        else{
            cout << "That tile is already marked. Try again.";
            // Press any key to continue.
            IO::wait();
        }
    }while(!condition);
}

Human* Human::convertType(Player *p){
    return static_cast <Human*>(p);
}
// All of the available computer names. Equally many male and female names. #genderequality.
const string Computer::names[] = {"John", "Marcus", "Jacob", "George", "Henrietta", "Marie", "Charlotte", "Zoe"};

// Randomly get a name from the list.
void Computer::setName(string name){
    int index = rand() % (int)(Computer::namesLength());

    Player::setName("A.I. " + names[index]);
}

// Sets the computers name and asks for the difficulty of the A.I.
void Computer::setName(int playerIndex){
    if(!Board::isValidPlayerIndex(playerIndex))
        return;
    Computer::setName("");

    char answers[Computer::DIFFICULTY_RANGE];
    for(int x = 0; x < Computer::DIFFICULTY_RANGE; x++)
        answers[x] = (char)(x + 49);
    char answer = IO::getAnswer("What difficulty should " + this->getName() + " play on?\n\n1: Easy.\n2: Normal.\n3: Perfect play.\n4: Random play.\n", answers, Computer::DIFFICULTY_RANGE, "Choose a difficulty from 1 to 4, please.");

    int difficulty = answer - '1';
    Computer::setDifficulty(difficulty);
}

// The minimax algorithm for determining the best move for the computer.
Move Computer::getMove(Board board, int playerIndex, int depth){
    int winner = board.returnWinner();
    /*  If the game is over, return the score.
        0 = Tie.
        10 = Player 1 won.
        -10 = Player 2 won.
        (A depth is also added (or subtracted) so the computer favors equally good moves lower in the tree. This
         is more beneficial, since this algorithm assumes its opponent plays perfectly. So if the computer
         knows it's going to lose, it might choose a tile which ends the game more quickly. We don't want it to
         do that, because if its opponent doesn't play perfectly and we end the game later rather than earlier
         we leave the opponent with more opportunities to make mistakes.
    */
    if(winner != 0){
        int difficulty = getDifficulty(), offset = 0;
        /*
            If the computer difficulty is set to 1, "normal difficulty", the computer shouldn't play perfectly so
            we add a random offset for every move so that it might prioritize worse moves before better ones.
            We intentionally make it stupider.
        */
        if(difficulty == 1){
            offset = ((rand() % 60) - 30);
        }
        if(winner == 10)
            return Move(10 + depth + offset);
        else if(winner == -10)
            return Move(-10 - depth + offset);
        else if(winner == -1)
            return Move(0 + offset);
    }

    vector<Move> moves;

    // Recursively go through all of the available moves and calculate their score.
    for(int n = 0; n < Board::getTiles(); n++)
        if(board.emptyTile(n)){
            board.setTile(n, playerIndex);

            int newPlayerIndex = playerIndex == 0 ? 1 : 0;

            Move move = getMove(board, newPlayerIndex, depth + 1);
            move.setIndex(n);
            moves.push_back(move);

            board.clearTile(n);
        }

    int bestMove = 0;
    int bestScore = playerIndex == 0 ? -100000 : 100000;

    /*
        Get the the best move.
        The 1st player wants to maximize its score. Because the higher score means the first player has won.
        The 2nd player wants to minimize its score, because lower score means victory for the second player.
    */
    for(int i = 0; i < moves.size(); i++){
        bool condition = playerIndex == 0 ? moves[i].getScore() > bestScore : moves[i].getScore() < bestScore;

        // If there is a better score than the current one, replace it.
        if(condition){
            bestScore = moves[i].getScore();
            bestMove = i;
        }
    }

    /*
        If there are more than one best move, we want to create a little bit of randomness, so that the games
        aren't the same every time.
     */
    vector<Move> possibleMoves;
    for(int i = 0; i < moves.size(); i++)
        if(bestScore == moves[i].getScore())
            possibleMoves.push_back(moves[i]);

    bestMove = rand() % (possibleMoves.size());

    return possibleMoves[bestMove];
}

// Making the moves for different A.I. difficulties.
void Computer::makeMove(Board *board, int playerIndex){
    int difficulty = this->getDifficulty();

    int tileIndex = 0;

    if(difficulty == 0){
        tileIndex = board->findFirstEmptyTile();
    }else if(difficulty == 1){
        Move move = getMove(*board, playerIndex, 0);
        tileIndex = move.getIndex();
    }else if(difficulty == 2){
        Move move = getMove(*board, playerIndex, 0);
        tileIndex = move.getIndex();
    }else if(difficulty == 3){
        vector<int> tiles = board->returnTiles();
        tileIndex = rand() % (int)(tiles.size());
        tileIndex = tiles.at(tileIndex);
    }

    board->setTile(tileIndex, playerIndex);

    // Simulate waiting time.

    char cx = (char)(tileIndex + 49);
    cout << this->getName() + " marked tile " + cx + ".";
}

void Computer::setDifficulty(int difficulty){
    if(difficulty >= 0 && difficulty <= 3)
        this->difficulty = difficulty;
    else
        difficulty = 1;
}

Computer* Computer::convertType(Player *p){
    return static_cast <Computer*>(p);
}

int Computer::namesLength(){
    return sizeof(Computer::names)/sizeof(string);
}
