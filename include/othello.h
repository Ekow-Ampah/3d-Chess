/*
	Name: Ekow Ampah
	File: Othello.h
	Description: Creates a 8 by 8. that has the score of the game and other funtions to make the game run smoother.


*/
#ifndef OTHELLO_H
#define OTHELLO_H
#include"game.h"
#include"piece.h"
#include"colors.h"
#include<iostream>

namespace main_savitch_14
{
    class Othello:public game {
	public:        
	Othello();
        void display_status()const;
        void make_move(const std::string & move);
        bool is_legal(const std::string& move) const;
	game* clone() const{return new Othello(*this);}
	void compute_moves(std::queue<std::string>& moves)const;
	bool is_game_over()const;
	int evaluate()const{return b_score- w_score;}
	who winning() const;
	void restart();
	private:
	piece board[8][8];
	int w_score;
	int b_score;
	int skip;
    };
}
#endif

