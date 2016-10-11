#include <iostream>
#include "board.h"
#include "player.h"

// To be frank this function is quite redundant, but I didn't want code duplication so I implemented it anyway even if it was minimal.
bool Board::validRange(int index, int start, int end){
    return index >= start && index <= end;
}
// Here you see why I now have second thoughts on implementing it. It's just a simple condition in one line.
bool Board::isValidIndex(int index){
    return validRange(index, 0, 8);
}

// Gets the amount of players. This will always be two, but, you know, I figured I wanted a constant for it.
int Board::getPlayers(){
    return PLAYERS;
}

// The amount of tiles on the board. (Always 9, I know...)
int Board::getTiles(){
    return TILES;
}

// Checks if a game mode type is valid.
int Board::getValidType(int type){
    if(validRange(type, 0, 2))
        return type;
    return 0;
}

int Board::getType(){
    return type;
}

// Returns a pointer to the player object at index 0 or 1.
Player* Board::returnPlayer(int playerIndex){
    if(Board::isValidPlayerIndex(playerIndex)){
        if(playerIndex == 0)
            return players[0];
        else
            return players[1];
    }
    return nullptr;
}

// Sets a tile at a certain index. The playerIndex parameter is for determining which player is marking it.
void Board::setTile(int tileIndex, int playerIndex){
    if(Board::isValidIndex(tileIndex) && Board::isValidPlayerIndex(playerIndex)){
        if(playerIndex == 0)
            Board::board[tileIndex].setValue(Board::players[0]->getMark());
        else
            Board::board[tileIndex].setValue(Board::players[1]->getMark());
    }
}

// Clear a certain tile.
void Board::clearTile(int tileIndex){
    if(Board::isValidIndex(tileIndex))
        if(!emptyTile(tileIndex)){
            board[tileIndex].clearTile();
        }
}

// Self-explanatory. I use it later in the Computer class for the easy difficulty.
int Board::findFirstEmptyTile(){
    for(int x = 0; x < Board::getTiles(); x++)
        if(emptyTile(x))
            return x;
    return -1;
}

// Return a vector with indexes to all empty tiles.
std::vector<int> Board::returnTiles(){
    std::vector<int> tiles;
    for(int x = 0; x < Board::getTiles(); x++)
        if(emptyTile(x))
            tiles.push_back(x);
    return tiles;
}

/*
    Returns 0 if no one has won (yet).
    Return 10 if the 1st player won.
    Return -10 if the 2nd player won.
    Returns -1 if it's a tie.
    This is used later in the minimax algorithm in the Computer class.
*/
int Board::returnWinner(){
    Player *p = returnPlayer(0);
    int playerMark = p->getMark();

    // Check the diagonals for a winner.
    if(Tile::isValidMark(Board::getTile(4))){
        if(Board::getTile(0) == Board::getTile(4) && Board::getTile(4) == Board::getTile(8)){
            if(Board::getTile(4) == playerMark)
                return 10;
            else
                return -10;
        }if(Board::getTile(2) == Board::getTile(4) && Board::getTile(4) == Board::getTile(6)){
            if(Board::getTile(4) == playerMark)
                return 10;
            else
                return -10;
        }
    }

    // Check the rows.
    for(int x = 0; x < 9; x+=3)
        if(Tile::isValidMark(Board::getTile(x)))
            if(Board::getTile(x) == Board::getTile(x+1) && Board::getTile(x+1) == Board::getTile(x+2)){
                if(Board::getTile(x) == playerMark)
                    return 10;
                else
                    return -10;
            }

    // Check the columns.
    for(int x = 0; x < 3; x++)
        if(Tile::isValidMark(Board::getTile(x)))
            if(Board::getTile(x) == Board::getTile(x+3) && Board::getTile(x+3) == Board::getTile(x+6)){
                if(Board::getTile(x) == playerMark)
                    return 10;
                else
                    return -10;
            }

    // The remaining options are either a tie or that the game is not finished. This part checks for a tie.
    for(int x = 0; x < 9; x++){
        if(emptyTile(x))
            break;
        else if(x == 8 && !emptyTile(x))
            return -1;
    }
    // The game is not finished. Return zero.
    return 0;
}

// Is the game over yet?
bool Board::hasEnded(){
    return Board::returnWinner() != 0;
}

// Clear the whole board.
void Board::clearBoard(){
    for(int i = 0; i < TILES; i++)
        board[i].clearTile();
}

// Function to set the name of a certain player.
void Board::setName(std::string name, int playerIndex){
    Player *p = returnPlayer(playerIndex);
    if(p != nullptr)
        p->setName(name);
}

std::string Board::getName(int playerIndex){
    Player *p = returnPlayer(playerIndex);
    if(p != nullptr)
        return p->getName();
    return "";
}

bool Board::emptyTile(int index){
    if(isValidIndex(index))
        return board[index].isEmpty();
    return false;
}

char Board::getTile(int index){
    if(isValidIndex(index))
        return board[index].getValue();
    return '-';
}

/*
    Constructor for different types of gamemodes. Initializes the player objects to its subclasses accordingly.
    0 = Human vs. Human.
    1 = Human vs. A.I.
    2 = A.I. vs. A.I.
 */
Board::Board(int playerMode) : type(getValidType(playerMode)){
    if(getType() == 0){
        players[0] = new Human(Tile::CROSS);
        players[1] = new Human(Tile::NOUGHT);
    }else if(getType() == 1){
        players[0] = new Human(Tile::CROSS);
        players[1] = new Computer(players[0]->getMark());
    }else{
        players[0] = new Computer(Tile::NOUGHT);
        players[1] = new Computer(players[0]->getMark());
    }
}

bool Board::isValidPlayerIndex(int index){
    return validRange(index, 0, 1);
}
