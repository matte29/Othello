
//*******************************
//*        File: piece.h
//*      Author: Matthew Ellis
//*        Date: August 07, 2019
//* Description: declartion file for piece class
//*******************************
#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>
    
class Piece {   
  public:
  
    enum color 
    { 
        BLACK, 
        WHITE, 
        EMPTY
    };    
  
    // default constructor     
    Piece(); 

    void placeBlack();

    void placeWhite();

    void flip(); 

    void setColor(const color& c);

    color getColor()const;

  private:
    
    color location;

 };
#endif