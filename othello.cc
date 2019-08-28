//*******************************
//*        File: othello.cc
//*      Author: Matthew Ellis
//*        Date: August 04, 2019
//* Description: immplementation file for othello.h
//*******************************
#include <iostream>
#include <string>
#include <queue>
#include "othello.h"

// Table of Contents
//
//  1. Default Constructor
//
//  2. restart
//
//  3. display_status 
//
//  4. make_move
//
//  5. is_leagal
//
//  6. allDirectionsLegal
//
//  7 - 14. all 8 directions 
//
//  15. winning
//  
//  16. is_game_over
//
//  17. clone
//
//  18. compute_moves
//
//  19. evaluate

namespace main_savitch_14
{

Othello::Othello()
{
    restart();
}

////////////////////////////////////////////////////////////////////////

void Othello::restart()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i == 3 && j == 4) // set base pieces
            {
                board[i][j].setColor(Piece::BLACK);
            }
            else if (i == 3 && j == 3)
            {
                board[i][j].setColor(Piece::WHITE);
            }
            else if (i == 4 && j == 3)
            {
                board[i][j].setColor(Piece::BLACK);
            }
            else if (i == 4 && j == 4)
            {
                board[i][j].setColor(Piece::WHITE);
            }
            else
            {
                board[i][j].setColor(Piece::EMPTY);
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////

void Othello::display_status() const
{
    const int length = 8;

    cout << " ";
    for (int j = 0; j < length; ++j)
    {
        cout << "  " << CYAN << char('A' + j) << " ";
    }
    cout << RESET;
    cout << endl;
    cout << " ";
    for (int j = 0; j < length; ++j)
    {
        cout << "+---";
    }
    cout << "+" << endl;

    for (int i = 0; i < length; ++i)
    {
        cout << CYAN << (1 + i) << RESET;
        for (int j = 0; j < length; ++j)
        {
            char f = ' ';

            if (board[i][j].getColor() == Piece::WHITE)
            {
                f = (char)176;
            }
            else if (board[i][j].getColor() == Piece::BLACK)
            {
                f = (char)219;
            }

            if (f == (char)219)
            {
                cout << "| " << RED << f << RESET << " ";
            }
            else
            {
                cout << "| " << f << " ";
            }
        }
        cout << "|" << endl;
        cout << " ";
        for (int j = 0; j < length; ++j)
        {
            cout << "+---";
        }
        cout << "+" << endl;
    }

    cout << RED << "Red = Black, " << WHITE << "and White = White. " << RESET << endl;

    if (next_mover() == HUMAN)
    {
        cout << MAGENTA << "It is player 1's turn: " << RESET << endl;
    }
    else
    {
        cout << MAGENTA << "It is player 2's turn. " << RESET << endl;
    }
}

///////////////////////////////////////////////////////////////////////

void Othello::make_move(const string &move)
{
    int row, col;
    col = int(toupper(move[0]) - 'A');
    row = int(toupper(move[1]) - '1');

    // if user == human, black piece
    if (next_mover() == game::HUMAN)
    {
        board[row][col].setColor(Piece::BLACK);

        if (isUpLegal(HUMAN_PLAYER, col, row))
        {
            for (int i = row - 1; board[i][col].getColor() != Piece::BLACK && i > -1; i--)
            {
                board[i][col].flip();
            }
        }

        if (isDownLegal(HUMAN_PLAYER, col, row))
        {
            for (int i = row + 1; board[i][col].getColor() != Piece::BLACK && i < 8; i++)
            {
                board[i][col].flip();
            }
        }

        if (isRightLegal(HUMAN_PLAYER, col, row))
        {
            for (int i = col + 1; board[row][i].getColor() != Piece::BLACK && i < 8; i++)
            {
                board[row][i].flip();
            }
        }

        if (isLeftLegal(HUMAN_PLAYER, col, row))
        {
            for (int i = col - 1; board[row][i].getColor() != Piece::BLACK && i > -1; i--)
            {
                board[row][i].flip();
            }
        }

        if (isUprightLegal(HUMAN_PLAYER, col, row))
        {
            for (int i = (row - 1), j = (col + 1); board[i][j].getColor() != Piece::BLACK && i > -1 && j < 8; i--, j++)
            {
                board[i][j].flip();
            }
        }

        if (isUpleftLegal(HUMAN_PLAYER, col, row))
        {
            for (int i = (row - 1), j = (col - 1); board[i][j].getColor() != Piece::BLACK && i > -1 && j > -1; i--, j--)
            {
                board[i][j].flip();
            }
        }

        if (isDownrightLegal(HUMAN_PLAYER, col, row))
        {
            for (int i = (row + 1), j = (col + 1); board[i][j].getColor() != Piece::BLACK && i < 8 && j < 8; i++, j++)
            {
                board[i][j].flip();
            }
        }

        if (isDownleftLegal(HUMAN_PLAYER, col, row))
        {
            for (int i = (row + 1), j = (col - 1); board[i][j].getColor() != Piece::BLACK && i < 8 && j > -1; i++, j--)
            {
                board[i][j].flip();
            }
        }
    }
    // if user == Computer or second player, white piece
    else if (next_mover() == COMPUTER)
    {
        board[row][col].setColor(Piece::WHITE);

        if (isUpLegal(COMPUTER_PLAYER, col, row))
        {
            for (int i = row - 1; board[i][col].getColor() != Piece::WHITE && i > -1; i--)
            {
                board[i][col].flip();
            }
        }

        if (isDownLegal(COMPUTER_PLAYER, col, row))
        {
            for (int i = row + 1; board[i][col].getColor() != Piece::WHITE && i < 8; i++)
            {
                board[i][col].flip();
            }
        }

        if (isRightLegal(COMPUTER_PLAYER, col, row))
        {
            for (int i = col + 1; board[row][i].getColor() != Piece::WHITE && i < 8; i++)
            {
                board[row][i].flip();
            }
        }

        if (isLeftLegal(COMPUTER_PLAYER, col, row))
        {
            for (int i = col - 1; board[row][i].getColor() != Piece::WHITE && i > -1; i--)
            {
                board[row][i].flip();
            }
        }

        if (isUprightLegal(COMPUTER_PLAYER, col, row))
        {
            for (int i = (row - 1), j = (col + 1); board[i][j].getColor() != Piece::WHITE && i > -1 && j < 8; i--, j++)
            {
                board[i][j].flip();
            }
        }

        if (isUpleftLegal(COMPUTER_PLAYER, col, row))
        {
            for (int i = (row - 1), j = (col - 1); board[i][j].getColor() != Piece::WHITE && i > -1 && j > -1; i--, j--)
            {
                board[i][j].flip();
            }
        }

        if (isDownrightLegal(COMPUTER_PLAYER, col, row))
        {
            for (int i = (row + 1), j = (col + 1); board[i][j].getColor() != Piece::WHITE && i < 8 && j < 8; i++, j++)
            {
                board[i][j].flip();
            }
        }

        if (isDownleftLegal(COMPUTER_PLAYER, col, row))
        {
            for (int i = (row + 1), j = (col - 1); board[i][j].getColor() != Piece::WHITE && i < 8 && j > -1; i++, j--)
            {
                board[i][j].flip();
            }
        }
    }

    game::make_move(move);
}

///////////////////////////////////////////////////////////////////////

bool Othello::is_legal(const string &move) const
{
    int row, col;
    col = int(toupper(move[0]) - 'A');
    row = int(toupper(move[1]) - '1');

    if (next_mover() == HUMAN)
    {
        if (board[row + 1][col].getColor() == Piece::WHITE ||
            board[row - 1][col].getColor() == Piece::WHITE ||
            board[row][col + 1].getColor() == Piece::WHITE ||
            board[row][col - 1].getColor() == Piece::WHITE ||
            board[row + 1][col + 1].getColor() == Piece::WHITE ||
            board[row + 1][col - 1].getColor() == Piece::WHITE ||
            board[row - 1][col + 1].getColor() == Piece::WHITE ||
            board[row - 1][col - 1].getColor() == Piece::WHITE)
            ;

        else
        {
            return false;
        }
    }
    else if (next_mover() == COMPUTER)
    {
        if (board[row + 1][col].getColor() == Piece::BLACK ||
            board[row - 1][col].getColor() == Piece::BLACK ||
            board[row][col + 1].getColor() == Piece::BLACK ||
            board[row][col - 1].getColor() == Piece::BLACK ||
            board[row + 1][col + 1].getColor() == Piece::BLACK ||
            board[row + 1][col - 1].getColor() == Piece::BLACK ||
            board[row - 1][col + 1].getColor() == Piece::BLACK ||
            board[row - 1][col - 1].getColor() == Piece::BLACK)
            ;

        else
        {
            return false;
        }
    }

    if (board[row][col].getColor() == Piece::EMPTY && next_mover() == HUMAN)
    {
        return (allDirectionsLegal(HUMAN_PLAYER, col, row));
    }
    else if (board[row][col].getColor() == Piece::EMPTY && next_mover() == COMPUTER)
    {
        return (allDirectionsLegal(COMPUTER_PLAYER, col, row));
    }
    else
    {
        return false;
    }

} // is_legal end

////////////////////////////////////////////////////////////////////////

bool Othello::allDirectionsLegal(player plyr, int c, int r) const
{
    if (plyr == HUMAN_PLAYER)
    {
        return (isLeftLegal(HUMAN_PLAYER, c, r) ||
                isRightLegal(HUMAN_PLAYER, c, r) ||
                isUpLegal(HUMAN_PLAYER, c, r) ||
                isDownLegal(HUMAN_PLAYER, c, r) ||
                isUpleftLegal(HUMAN_PLAYER, c, r) ||
                isUprightLegal(HUMAN_PLAYER, c, r) ||
                isDownleftLegal(HUMAN_PLAYER, c, r) ||
                isDownrightLegal(HUMAN_PLAYER, c, r));
    }
    else if (plyr == COMPUTER_PLAYER)
    {
        return (isLeftLegal(COMPUTER_PLAYER, c, r) ||
                isRightLegal(COMPUTER_PLAYER, c, r) ||
                isUpLegal(COMPUTER_PLAYER, c, r) ||
                isDownLegal(COMPUTER_PLAYER, c, r) ||
                isUpleftLegal(COMPUTER_PLAYER, c, r) ||
                isUprightLegal(COMPUTER_PLAYER, c, r) ||
                isDownleftLegal(COMPUTER_PLAYER, c, r) ||
                isDownrightLegal(COMPUTER_PLAYER, c, r));
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////

bool Othello::isDownLegal(player plyr, int col, int row) const
{
    if (row < 6 && plyr == HUMAN_PLAYER)
    {
        int i;
        if (board[row + 1][col].getColor() == Piece::WHITE)
        {

            for (i = row + 1; (board[i][col].getColor() != Piece::BLACK) && (board[i][col].getColor() != Piece::EMPTY) && i < 8; i++)
                ;

            if (board[i][col].getColor() == Piece::BLACK)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else if (row < 6 && plyr == COMPUTER_PLAYER)
    {
        int i;
        if (board[row + 1][col].getColor() == Piece::BLACK)
        {

            for (i = row + 1; (board[i][col].getColor() != Piece::WHITE) && (board[i][col].getColor() != Piece::EMPTY) && i < 8; i++)
                ;

            if (board[i][col].getColor() == Piece::WHITE)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////

bool Othello::isUpLegal(player plyr, int col, int row) const
{
    if (row > 1 && plyr == HUMAN_PLAYER)
    {
        int i;
        if (board[row - 1][col].getColor() == Piece::WHITE)
        {

            for (i = row - 1; (board[i][col].getColor() != Piece::BLACK) && (board[i][col].getColor() != Piece::EMPTY) && i > -1; i--)
                ;

            if (board[i][col].getColor() == Piece::BLACK)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else if (row > 1 && plyr == COMPUTER_PLAYER)
    {
        int i;
        if (board[row - 1][col].getColor() == Piece::BLACK)
        {

            for (i = row - 1; (board[i][col].getColor() != Piece::WHITE) && (board[i][col].getColor() != Piece::EMPTY) && i > -1; i--)
                ;

            if (board[i][col].getColor() == Piece::WHITE)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////

bool Othello::isLeftLegal(player plyr, int col, int row) const
{
    if (col > 1 && plyr == HUMAN_PLAYER)
    {
        int i;
        if (board[row][col - 1].getColor() == Piece::WHITE)
        {

            for (i = col - 1; (board[row][i].getColor() != Piece::BLACK) && (board[row][i].getColor() != Piece::EMPTY) && i > -1; i--)
                ;

            if (board[row][i].getColor() == Piece::BLACK)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else if (col > 1 && plyr == COMPUTER_PLAYER)
    {
        int i;
        if (board[row][col - 1].getColor() == Piece::BLACK)
        {

            for (i = col - 1; (board[row][i].getColor() != Piece::WHITE) && (board[row][i].getColor() != Piece::EMPTY) && i > -1; i--)
                ;

            if (board[row][i].getColor() == Piece::WHITE)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////

bool Othello::isRightLegal(player plyr, int col, int row) const
{
    if (col < 6 && plyr == HUMAN_PLAYER)
    {
        int i;
        if (board[row][col + 1].getColor() == Piece::WHITE)
        {

            for (i = col + 1; (board[row][i].getColor() != Piece::BLACK) && (board[row][i].getColor() != Piece::EMPTY) && i < 8; i++)
                ;

            if (board[row][i].getColor() == Piece::BLACK)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else if (col < 6 && plyr == COMPUTER_PLAYER)
    {
        int i;
        if (board[row][col + 1].getColor() == Piece::BLACK)
        {

            for (i = col + 1; (board[row][i].getColor() != Piece::WHITE) && (board[row][i].getColor() != Piece::EMPTY) && i < 8; i++)
                ;

            if (board[row][i].getColor() == Piece::WHITE)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////

bool Othello::isUpleftLegal(player plyr, int col, int row) const
{
    if ((row > 1 && col > 1) && plyr == HUMAN_PLAYER)
    {
        int i, j;
        if (board[row - 1][col - 1].getColor() == Piece::WHITE)
        {
            for (i = row - 1, j = col - 1; (board[i][j].getColor() != Piece::BLACK) && (board[i][j].getColor() != Piece::EMPTY) && i > -1 && j > -1; i--, j--)
                ;
            if (board[i][j].getColor() == Piece::BLACK)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else if ((row > 1 && col > 1) && plyr == COMPUTER_PLAYER)
    {
        int i, j;
        if (board[row - 1][col - 1].getColor() == Piece::BLACK)
        {
            for (i = row - 1, j = col - 1; (board[i][j].getColor() != Piece::WHITE) && (board[i][j].getColor() != Piece::EMPTY) && i > -1 && j > -1; i--, j--)
                ;
            if (board[i][j].getColor() == Piece::WHITE)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////

bool Othello::isUprightLegal(player plyr, int col, int row) const
{
    if ((row > 1 && col < 6) && plyr == HUMAN_PLAYER)
    {
        int i, j;
        if (board[row - 1][col + 1].getColor() == Piece::WHITE)
        {
            for (i = row - 1, j = col + 1; (board[i][j].getColor() != Piece::BLACK) && (board[i][j].getColor() != Piece::EMPTY) && i > -1 && j < 8; i--, j++)
                ;

            if (board[i][j].getColor() == Piece::BLACK)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else if ((row > 1 && col < 6) && plyr == COMPUTER_PLAYER)
    {
        int i, j;
        if (board[row - 1][col + 1].getColor() == Piece::BLACK)
        {
            for (i = row - 1, j = col + 1; (board[i][j].getColor() != Piece::WHITE) && (board[i][j].getColor() != Piece::EMPTY) && i > -1 && j < 8; i--, j++)
                ;

            if (board[i][j].getColor() == Piece::WHITE)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////

bool Othello::isDownleftLegal(player plyr, int col, int row) const
{
    if ((row < 6 && col > 1) && plyr == HUMAN_PLAYER)
    {
        int i, j;
        if (board[row + 1][col - 1].getColor() == Piece::WHITE)
        {
            for (i = row + 1, j = col - 1; (board[i][j].getColor() != Piece::BLACK) && (board[i][j].getColor() != Piece::EMPTY) && i < 8 && j > -1; i++, j--)
                ;

            if (board[i][j].getColor() == Piece::BLACK)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else if ((row < 6 && col > 1) && plyr == COMPUTER_PLAYER)
    {
        int i, j;
        if (board[row + 1][col - 1].getColor() == Piece::BLACK)
        {
            for (i = row + 1, j = col - 1; (board[i][j].getColor() != Piece::WHITE) && (board[i][j].getColor() != Piece::EMPTY) && i < 8 && j > -1; i++, j--)
                ;

            if (board[i][j].getColor() == Piece::WHITE)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////

bool Othello::isDownrightLegal(player plyr, int col, int row) const
{
    if ((row < 6 && col < 6) && plyr == HUMAN_PLAYER)
    {
        int i, j;
        if (board[row + 1][col + 1].getColor() == Piece::WHITE)
        {
            for (i = row + 1, j = col + 1; (board[i][j].getColor() != Piece::BLACK) && (board[i][j].getColor() != Piece::EMPTY) && i < 8 && j < 8; i++, j++)
                ;

            if (board[i][j].getColor() == Piece::BLACK)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else if ((row < 6 && col < 6) && plyr == COMPUTER_PLAYER)
    {
        int i, j;
        if (board[row + 1][col + 1].getColor() == Piece::BLACK)
        {
            for (i = row + 1, j = col + 1; (board[i][j].getColor() != Piece::WHITE) && (board[i][j].getColor() != Piece::EMPTY) && i < 8 && j < 8; i++, j++)
                ;

            if (board[i][j].getColor() == Piece::WHITE)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////

game::who Othello::winning() const
{
    size_t blackPiecesOnBoard = 0;
    size_t whitePiecesOnBoard = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].getColor() == Piece::BLACK)
            {
                blackPiecesOnBoard++;
            }
            else if (board[i][j].getColor() == Piece::WHITE)
            {
                whitePiecesOnBoard++;
            }
        }
    }

    if (blackPiecesOnBoard > whitePiecesOnBoard)
    {
        return game::HUMAN;
    }
    else if (blackPiecesOnBoard < whitePiecesOnBoard)
    {
        return game::COMPUTER;
    }
    else if (blackPiecesOnBoard == whitePiecesOnBoard)
    {
        return game::NEUTRAL;
    }

    return game::NEUTRAL;
}

////////////////////////////////////////////////////////////////////////

bool Othello::is_game_over() const
{
    queue<string> moves;

    compute_moves(moves);

    if (moves.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

////////////////////////////////////////////////////////////////////////

game *Othello::clone() const
{
    return new Othello(*this);
}

////////////////////////////////////////////////////////////////////////

void Othello::compute_moves(queue<string> &moves) const
{
    
    string nums = "12345678";

    string chars = "ABCDEFGH";

    string move = "  ";

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            move[0] = chars[i];
            move[1] = nums[j];
            if (is_legal(move))
            {
                moves.push(move);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////

int Othello::evaluate() const // simple evaluate function, computer will make choice that will give it the most pieces on the board
{
    int points = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j].getColor() == Piece::WHITE) // the more white pieces the move gets the better the move
            {
                points++;
            }
            else if (board[i][j].getColor() == Piece::BLACK)
            {
                points--;
            }
        }
    }
    return points;
}

} // namespace main_savitch_14
