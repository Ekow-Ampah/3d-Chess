/*
	Name: Ekow Ampah
	File: Othello.cc
	Description: Implementation for Othello.cc


*/
#include"othello.h"
#include"piece.h"
#include<iostream>
#define underline "\033[4m"

using namespace std;

using namespace main_savitch_14;
Othello::Othello(){
for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j].make_empty();
        }
    }
    board[3][3].make_white();
    board[4][4].make_white();
    board[3][4].make_black();
    board[4][3].make_black();

w_score = 0;
b_score = 0;
skip = 0;
}


void Othello::display_status()const{
	int i,j;
	
	if(game::next_mover() == HUMAN){
	cout<< underline << BOLD <<   B_GREEN << BLACK <<"Player 1 (Black Piece) TURN" << RESET << endl;
	}
	else{
	cout<< underline << BOLD << B_GREEN << WHITE <<"Player 2 (White Piece) TURN" << RESET << endl;
	}
	cout   <<"    "<<BOLD << BLINK << B_GREEN << underline<< YELLOW<<"MOVE WISELY!!!" << RESET << endl;
	cout << BOLD << RED  << "   A   B   C   D   E   F   G   H "<< endl;
      for(i = 0; i < 8; ++i)
      {
	int tracker=0;
         cout << BOLD << RED << i + 1;
         for(j = 0; j < 8; ++j)
         {
            cout << B_YELLOW << " ";
            if(board[i][j].is_black())
            {
               cout<< BLACK << "[0]" << RESET;
            }
            else if(board[i][j].is_white())
            {
               cout<< WHITE <<"[X]" << RESET;
            }                         
            else
            {
               cout<< RESET << RED << "[-]";
            }
         }
         cout << RESET<< endl; 
          
      }

   }   
bool Othello::is_legal(const std::string& move) const{
	int column = int(toupper(move[0] - 'A'));
    	int row = int(move[1] - '1');
	
	if (row > 7 || row < 0){ return false; }
	if (column > 7|| column < 0) { return false; }
	if (board[row][column].is_empty() == false ){ return false; }
	


	if(game::next_mover() == HUMAN){
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 2 ; i < 8; i++){
	if(board[row][column-1].is_white() && board[row][column-i].is_black()) {
		return true;		
			
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 2 ; i < 8; i++){
	if(board[row][column+1].is_white() && board[row][column+i].is_black()) {
		return true;		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
	
	
	for(int i = 2 ; i < 8; i++){
	if(board[row+1][column].is_white() && board[row+i][column].is_black()) {
		
		return true;		
			
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 2 ; i < 8; i++){
	
	if(board[row-1][column].is_white() && board[row-i][column].is_black()) {
		return true;		
			
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row+1][column+1].is_white() && board[row+i][column+i].is_black()) {
		
		return true;		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 7; i++){
	if(board[row-1][column-1].is_white() && board[row-i][column-i].is_black()) {
		
		return true;		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row-1][column+1].is_white() && board[row-i][column+i].is_black()) {
		return true;	
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row+1][column-1].is_white() && board[row+i][column-i].is_black()) {
		
		return true;	
			
	}
}
}	
     
	
	else if(game::next_mover() == COMPUTER){
	
//////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 0 ; i < 8; i++){
	if(board[row][column+1].is_black() && board[row][column+i].is_white()) {
		
		return true;			
	}		
}
//////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 0 ; i < 8; i++){
	if(board[row][column-1].is_black() && board[row][column-i].is_white()) {
		return true;	
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
	
	
	for(int i = 2 ; i < 8; i++){
	if(board[row+1][column].is_black() && board[row+i][column].is_white()) {
		return true;		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 2 ; i < 8; i++){
	if(board[row-1][column].is_black() && board[row-i][column].is_white()) {
		return true;	
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row+1][column+1].is_black() && board[row+i][column+i].is_white()) {
		
		return true;	
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row-1][column-1].is_black() && board[row-i][column-i].is_white()) {
		
		return true;	
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row-1][column+1].is_black() && board[row-i][column+i].is_white()) {
		
		return true;	
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row+1][column-1].is_black() && board[row+i][column-i].is_white()) {
		
		return true;	
			
	}
}

	
}
else {return false;}

}

void Othello::make_move(const std::string & move){
	
	if(move == "****"){
      cout << "You might regret that skip :( NEXT!!!" << endl;
	skip++;
      game::make_move(" ");
      return;
    }
	int column = int(toupper(move[0] - 'A'));
    	int row = int(move[1] - '1');
	int track = 0;
	
	 
	if(game::next_mover() == HUMAN){
	board[row][column].make_black();
	//board[row+1][column].make_black();
	//////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 2 ; i < 8; i++){
	if(board[row][column-1].is_white() && board[row][column-i].is_black()) {
		for(int j = column-1; j > column-i; j--){
			board[row][j].flip();
		}		
			
	}
}
	
//////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 2 ; i < 8; i++){
	if(board[row][column+1].is_white() && board[row][column+i].is_black()) {
		for(int j = column+1; j < column+i; j++){
			board[row][j].flip();
		}		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
	
	
	for(int i = 2 ; i < 8; i++){
	if(board[row+1][column].is_white() && board[row+i][column].is_black()) {
		
		for(int j = row+1; j < row+i; j++){
			board[j][column].flip();
		}		
			
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 2 ; i < 8; i++){
	
	if(board[row-1][column].is_white() && board[row-i][column].is_black()) {

		for(int j = row-1; j > row-i; j--){
			board[j][column].flip();
		}		
			
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row+1][column+1].is_white() && board[row+i][column+i].is_black()) {
		
		for(int j = row+1; j < row+i; j++){
			for(int z = column+1; z < column+i; z++){
			board[j][z].flip();
		}	
		}		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row-1][column-1].is_white() && board[row-i][column-i].is_black()) {
		
		for(int j = row-1; j > row-i; j--){
			for(int z = column-1; z > column-i; z--){
			board[j][z].flip();
		}	
		}		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row-1][column+1].is_white() && board[row-i][column+i].is_black()) {
		
		for(int j = row-1; j > row-i; j--){
			for(int z = column+1; z < column+i; z++){
			board[j][z].flip();
		}	
		}		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row+1][column-1].is_white() && board[row+i][column-i].is_black()) {
		
		for(int j = row+1; j < row+i; j++){
			
			for(int z = column-1; z > column-i; z--){
			
			board[j][z].flip();
		}	
		}		
			
	}
}

game::make_move(move);
skip = 0;

}

	

	else if(game::next_mover()==COMPUTER){
	
	board[row][column].make_white();
//////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 0 ; i < 8; i++){
	if(board[row][column+1].is_black() && board[row][column+i].is_white()) {
		for(int j = column+1; j < column+i; j++){
			board[row][j].flip();
		}		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 0 ; i < 8; i++){
	if(board[row][column-1].is_black() && board[row][column-i].is_white()) {
		for(int j = column-1; j > column-i; j--){
			board[row][j].flip();
		}		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
	
	
	for(int i = 2 ; i < 8; i++){
	if(board[row+1][column].is_black() && board[row+i][column].is_white()) {
		for(int j = row+1; j < row+i; j++){
			board[j][column].flip();
		}		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
	for(int i = 2 ; i < 8; i++){
	if(board[row-1][column].is_black() && board[row-i][column].is_white()) {
		
		for(int j = row-1; j > row-i; j--){
			board[j][column].flip();
		}		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row+1][column+1].is_black() && board[row+i][column+i].is_white()) {
		
		for(int j = row+1; j < row+i; j++){
			for(int z = column+1; j < column+i; j++){
			board[j][z].flip();
		}	
		}		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row-1][column-1].is_black() && board[row-i][column-i].is_white()) {
		
		for(int j = row-1; j > row-i; j--){
			for(int z = column-1; j > column-i; j--){
			board[j][z].flip();
		}	
		}		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row-1][column+1].is_black() && board[row-i][column+i].is_white()) {
		
		for(int j = row-1; j > row-i; j--){
			for(int z = column+1; j < column+i; j++){
			board[j][z].flip();
		}	
		}		
			
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
for(int i = 2 ; i < 8; i++){
	if(board[row+1][column-1].is_black() && board[row+i][column-i].is_white()) {
		
		for(int j = row+1; j < row+i; j++){
			for(int z = column-1; j > column-i; j--){
			board[j][z].flip();
		}	
		}		
			
	}
}
game::make_move(move);
skip = 0;
		
}
}

Othello::who Othello:: winning() const{
	for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				
				if (board[i][j].is_black()) { b_score + 1; }
				if (board[i][j].is_white()) { w_score + 1; }
			}
		}

	if (b_score> w_score){return HUMAN;}
	else if (b_score == w_score) { return NEUTRAL; }
	else{ return COMPUTER;}

}
void Othello:: restart(){
	for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            board[i][j].make_empty();
        }
    }
    board[3][3].make_white();
    board[4][4].make_white();
    board[3][4].make_black();
    board[4][3].make_black();

}
bool Othello::is_game_over()const{
	int count = 0;
for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
           if(board[i][j].is_empty() == false)
       {
         count++;
       }
        }
    }
if (count == 64){ return true;}
else{return false;}



}

void Othello:: compute_moves(std::queue<std::string>& moves)const{
   string tmp = "  ";

   for(char c = 'A'; c < 'I'; ++c){
     tmp[0] = c;
     	for(char n = '1'; n < '9'; ++n){
       tmp[1] = n;
       if(is_legal(tmp))
       {
         moves.push(tmp);
       }
     }
   }
	if (moves.empty()) { moves.push("****"); }
 }


