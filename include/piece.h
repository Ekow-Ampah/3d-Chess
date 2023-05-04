/*
	Name: Ekow Ampah
	File: Piece.cc
	Description: The foundation for the whole program;


*/
#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <string>

class piece {
    public:
    piece(char c = 'E') {type = c;}
    bool is_black()const{return(type == 'B');}
    bool is_white()const{return(type == 'W');}
    bool is_empty()const{return(type == 'E');}
    
    
    void flip(){
	if(is_black()){ make_white();}
	else if(is_white()){ make_black();}
	}
    void make_empty(){type = 'E';}
    void make_white(){type = 'W';}
    void make_black(){type = 'B';}

    

    private:

   char type;

};
#endif
