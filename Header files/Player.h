#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "tile.h"
#include "IO.h"
#include "board.h"
#include "move.h"

// This is an abstract class. It can either represent a Human or a Computer.

class Player{
public:
    char getMark();

    Player(char mark);

    virtual void setName(std::string name);

    virtual void setName(int playerIndex);

    virtual void makeMove(Board *board, int playerIndex);

    virtual std::string getName();

    void setMark(char mark);
private:
    char mark;
    std::string name;
};

class Human : public Player{
public:
    Human(char mark) : Player(mark){}

    void setName(int playerIndex);
    void setName(std::string name);
    void makeMove(Board *board, int playerIndex);

    static Human* convertType(Player *p);
};

class Computer : public Player{
public:
    Computer(char mark) : Player(Tile::getOppositeMark(mark)), difficulty(1){
    }

    void setName(int playerIndex);
    void setName(std::string name);
    void makeMove(Board *board, int playerIndex);
    void setDifficulty(int difficulty);
    int getDifficulty(){return difficulty;};
    Move getMove(Board board, int playerIndex, int depth);

    static Computer* convertType(Player *p);
    static const int DIFFICULTY_RANGE = 4;
private:
    static int namesLength();
    int difficulty;

    static const std::string names[];
};
#endif // PLAYER_H_INCLUDED
