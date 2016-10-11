#include "tile.h"

// If a mark is valid for a tile. Valid ones are crosses and noughts.
bool Tile::isValidMark(char mark){
    return mark == Tile::CROSS || mark == Tile::NOUGHT;
}

// Given a cross or a nought, get the opposite.
char Tile::getOppositeMark(char mark){
    return mark == Tile::CROSS ? Tile::NOUGHT : Tile::CROSS;
}

// By default a tile is empty.
Tile::Tile(){
    value = Tile::EMPTY;
}

// Is the tile empty?
bool Tile::isEmpty(){
    return value == Tile::EMPTY;
}

// Clear the tile.
void Tile::clearTile(){
    value = Tile::EMPTY;
}

// Set the tile. (You can't set it to the empty state, you've got to use clearTile() for that.)
void Tile::setValue(char mark){
    if(Tile::isEmpty() && Tile::isValidMark(mark))
        value = mark;
}
