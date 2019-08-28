//*******************************
//*        File: othello.h
//*      Author: Matthew Ellis
//*        Date: August 04, 2019
//* Description: Declaration for othello.h
//*******************************
#include "game.h"
#include "piece.h"
#include "colors.h"

namespace main_savitch_14
{

class Othello : public game
{
public:
    enum player
    {
        HUMAN_PLAYER,
        COMPUTER_PLAYER
    };

    game *clone() const;

    void compute_moves(std::queue<std::string> &moves) const;

    int evaluate() const;

    // Constructor
    Othello();

    void restart();

    void make_move(const std::string &move);

    void display_status() const;

    bool is_legal(const std::string &move) const;

    bool is_game_over() const;

    who winning() const;

private:
    Piece board[8][8];

    bool allDirectionsLegal(player plyr, int col, int row) const;
    bool isLeftLegal(player plyr, int col, int row) const; // checks for if move to the left is legal
    bool isRightLegal(player plyr, int col, int row) const; // checks for if move to the right is legal
    bool isUpLegal(player plyr, int col, int row) const; // checks for if move up is legal
    bool isDownLegal(player plyr, int col, int row) const; // checks for if move down is legal
    bool isUpleftLegal(player plyr, int col, int row) const; // checks for if move up left is legal
    bool isUprightLegal(player plyr, int col, int row) const; // checks for if move up right is legal
    bool isDownleftLegal(player plyr, int col, int row) const; // checks for if move down left is legal
    bool isDownrightLegal(player plyr, int col, int row) const; // checks for it move down right is legal
};

} // namespace main_savitch_14
