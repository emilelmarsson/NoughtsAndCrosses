#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED
#include <string>
#include <vector>
#include "tile.h"
class Player;

// The game board class.

class Board{
private:
    static const int TILES = 9;
    Tile board[TILES];
    static const int PLAYERS = 2;
    Player *players[PLAYERS];
    int type;

    static bool validRange(int index, int start, int end);

    static bool isValidIndex(int index);
public:
    static int getPlayers();
    static int getTiles();

    int getValidType(int type);
    void setType(int type);
    int getType();

    void clearBoard();

    int findFirstEmptyTile();

    std::vector<int> returnTiles();

    int returnWinner();
    bool hasEnded();

    Player* returnPlayer(int playerIndex);

    void setName(std::string name, int playerIndex);

    std::string getName(int playerIndex);

    bool emptyTile(int index);

    char getTile(int index);

    Board(){}
    Board(int playerMode);

    void setTile(int tileIndex, int playerIndex);
    void clearTile(int tileIndex);

    static bool isValidPlayerIndex(int index);
};
#endif // BOARD_H_INCLUDED
