#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED
// A class used in conjunction with the minimax algorithm to store indexes and scores in the same variable.
class Move{
    int index, score;
public:
    Move() : index(0), score(0) {}
    Move(int score) : index(0){this->score = score;}

    void setIndex(int index){this->index = index;}

    int getIndex(){return index;}
    int getScore(){return score;}
};
#endif // MOVE_H_INCLUDED
