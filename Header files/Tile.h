#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED
// This object are used for tiles on the board.
class Tile{
public:
    // The allowed states of a tile.
    static const char CROSS = 'X', NOUGHT = 'O', EMPTY = '-';

    static bool isValidMark(char mark);
    static char getOppositeMark(char mark);

    Tile();

    bool isEmpty();
    void setValue(char mark);
    void clearTile();
    char getValue(){return value;}
private:
    char value;
};
#endif // TILE_H_INCLUDED
