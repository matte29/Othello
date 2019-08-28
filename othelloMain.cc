//*******************************
//*        File: othelloMain.cc
//*      Author: Matthew Ellis
//*        Date: August 04, 2019
//* Description: Main for Othello game
//*******************************

#include <iostream>
#include <cstdlib>
#include <string>
#include "game.h"
#include "othello.h"

using namespace main_savitch_14;

int main()
{
    game::who Winner;
    Othello myg;

    Winner = myg.play();

    if (Winner == Othello::HUMAN)
    {
        cout << "Player 1 wins! " << endl;
    }
    else if (Winner == Othello::COMPUTER)
    {
        cout << "Computer wins! " << endl;
    }
    else if (Winner == Othello::NEUTRAL)
    {
        cout << "TIE GAME " << endl;
    }

    return 0;
}
