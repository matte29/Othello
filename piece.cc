//*******************************
//*        File: piece.cc
//*      Author: Matthew Ellis
//*        Date: August 07, 2019
//* Description: implementation for piece class
//*******************************

#include <iostream>
#include <cstdlib>
#include <string>
#include "piece.h"

// Default COnstructor
Piece::Piece()
{
    location = EMPTY;
}

void Piece::placeBlack()
{
    if (location == EMPTY)
    {
        location = BLACK;
    }
}

void Piece::placeWhite()
{
    if (location == EMPTY)
    {
        location = WHITE;
    }
}

void Piece::flip()
{
    if (location == BLACK)
    {
        location = WHITE;
    }
    else if (location == WHITE)
    {
        location = BLACK;
    }
}

void Piece::setColor(const color &c)
{
    location = c;
}

Piece::color Piece::getColor() const
{
    return location;
}




