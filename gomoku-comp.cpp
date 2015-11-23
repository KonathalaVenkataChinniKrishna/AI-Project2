/* Artificial Intelligence - PROJECT 2
 * Team Name : 	* Black Knights!!
 * Authors : 	* Konathala Venkata Chinni Krishna(130050042)
				* Bodda Gowri Shankar(130050080)
				* Prasadula Amar Sekhar(130050082)
--------------------------------------------------------------------------------
 * Board: The game board uses 0 based indices from top to bottom, left to right.
 *        E.g. 5x5 board
 *          0 1 2 3 4
 *        0 . . . . .
 *        1 . . . . .
 *        2 . . . . .
 *        3 . . . . .
 *        4 . . . . .
 *
 ------------------------------------------------------------------------------
 */
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_JPEG_Image.H>

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <set>
#include <ctime>
#include <cstdlib>
#include <string>
#include <sstream>
using namespace std;

#define MIN_BOARD_LIMIT 3
#define MAX_BOARD_LIMIT 19
//Numbers choosen at semi-random, some are powers of 2s
#define ALPHA_INF -1032768
#define BETA_INF 1032768
//win/lose occurs when exactly M pieces are in a line on the board
#define SCORE_WIN 418192
#define SCORE_LOSE -418192
//over occurs when a line pattern has over M pieces in a row
#define SCORE_OVER -16
#define SCORE_OPP_OVER 16
//deadend occurs when a move is wasted ex: a single line between opposite pieces
#define SCORE_DEADEND -128
#define SCORE_OPP_DEADEND 128
//M = M-1 in a line, with opponent piece in one of the tiles before or after it
//if two of theses threats occur, then game is won for the threat creator
#define SCORE_M 2048
#define SCORE_OPP_M -2048
//M minus = M-2 in a line with nothing on tiles before or after it
#define SCORE_M_MINUS 256
#define SCORE_OPP_M_MINUS -256
//Straight M = M-1 in a line with no pieces on tiles before and after the line
#define SCORE_STRAIGHT_M 4096
#define SCORE_OPP_STRAIGHT_M -4096
//default score for any line pattern over 1 is the size of the line pattern
//Struct used to keep track of game state and information regarding state
#define BOX_SIZE 30

/*struct GameState;

class Board : public Fl_Widget{
	
	int occup[xmaxtiles][ymaxtiles]; 
	//ActivePiece * p;
	int score;
	int color;
	bool gameend,display;
	char* scoreLabel; 
	Fl_Box *scoreBox;
	Fl_Window *current;
	Player *human;//=new Player("MARCO", 25);
	Player *computer;//=new Player("KASIA",50);
	
	public:
	Player *currentPlayer;
    char **board;
    int size;
    static const int nWin=5; //number of piecies to win (2,3,4..ecc)

	Board(int n, Fl_Window *window):Fl_Widget (0,0,xmaxtiles*tilesize,
			ymaxtiles*tilesize,"timer")
	{
	    gameend = 0 ;display=0;
		//p = new ActivePiece (this);	
		for (int i = 0 ; i < xmaxtiles ; i ++ )
		for (int j = 0 ;  j < ymaxtiles ; j ++ )
		occup[i][j] = bgcolor;
		size=n;
        board=new char *[size];
        for( int i = 0 ; i < size ; i++ )
            board[i]= new char[size];
        for(int i=0;i<size;i++)
            for(int k=0;k<size;k++)
                board[i][k]='_';
        human=new Player("CHINNI", 112);
		computer=new Player("ROBO",67);
		currentPlayer=human;
		current = window;	
	}
	void draw()
	{
		for (int i=0; i<xmaxtiles;i++)
		for (int j=0; j<ymaxtiles;j++)
			fl_draw_box(FL_BORDER_BOX,i*tilesize,j*tilesize,
				tilesize,tilesize,occup[i][j]);
	}
	bool updateBoard(GameState game)
    {
        	//cout<<"hello "<<r<<" "<<c<<endl;
        	/*int p=r, q=c;
        	r = r/50;
        	c = c/50;
        	int x, y;
        	/*if(p-50*r > 25 && q-50*c <= 25)
        	{
        		r++;
        	}
        	if(p-50*r > 25 && q-50*c > 25)
        	{
        		r++;
        		c++;
        	}
        	if(p-50*r <= 25 && q-50*c > 25)
        	{
        		c++;
        	}
        	112, 67*/
	    /*unsigned int size = cur_state.n;
		unsigned int total_size = size * size;
		//cout << " GOMOKU GAMEBOARD: " << endl;
		for (int i = 1; i < (total_size); i++) {
			for(int j=1; j< total_size; j++)
			{
				char c = cur_state.board[(i-1)*size+j];
				if(c == X)
				{
					fl_draw_box(FL_OVAL_BOX, i*BOX_SIZE, j*BOX_SIZE,
								20,20,67);
				}
				if(c == O)
				{
					fl_draw_box(FL_OVAL_BOX, i*BOX_SIZE, j*BOX_SIZE,
								20,20,112);
				}	
			}
			//if (i == 0)
				//cout << "  ";
			//if (i%size == 0 && i != 0)
				//cout << endl << "  ";
			//cout << cur_state.board[i];
		}
	//cout << endl;
            /*if((this->checkPosition(r,c)))
            {
                board[r][c]=currentPlayer->getMark();
                //cout<<currentPlayer->getMark()<<endl;
                fl_draw_box(FL_OVAL_BOX, ((r)*tilesize)-10, ((c)*tilesize)-10,
							20,20,currentPlayer->getMark());
            }*/
   /* }
};*/

struct GameState{
	bool game_end;
	int hscore;
	unsigned int n;
	unsigned int tiles_left;
	unsigned int last_row;
	unsigned int last_column;
	vector<bool> column_count;
	vector<char> board;

	GameState(unsigned int size=0): game_end(false), n(size), tiles_left(size*size), last_row(0), last_column(0)
		{column_count.assign(size, false); board.assign(size*size, '.');};

	char at(unsigned int row, unsigned int column) {
		unsigned pos = (row*n)+column;
		return board[pos];
	}

	void set(unsigned int row, unsigned int column, char player) {
		unsigned pos = (row*n)+column;
		board[pos] = player;
		column_count[column] = true;
		last_column = column;
		last_row = row;
		tiles_left--;
	}

	void draw()
	{
		for(int i=0; i<n; i++)
			for(int j=0; j<n; j++)
				fl_draw_box(FL_BORDER_BOX,i*BOX_SIZE,j*BOX_SIZE,
				BOX_SIZE,BOX_SIZE,56);
	}

	void updateBoard(GameState cur_state)
	{
		unsigned int size = cur_state.n;
		unsigned int total_size = size * size;
		//cout << " GOMOKU GAMEBOARD: " << endl;
		for (int i = 1; i < (total_size); i++) {
			for(int j=1; j< total_size; j++)
			{
				char c = cur_state.board[(i-1)*size+j];
				if(c == 'X')
				{
					fl_draw_box(FL_OVAL_BOX, i*BOX_SIZE, j*BOX_SIZE,
								20,20,67);
				}
				if(c == 'O')
				{
					fl_draw_box(FL_OVAL_BOX, i*BOX_SIZE, j*BOX_SIZE,
								20,20,112);
				}	
			}
			//if (i == 0)
				//cout << "  ";
			//if (i%size == 0 && i != 0)
				//cout << endl << "  ";
			//cout << cur_state.board[i];
		}
	}
};

void print_board(GameState cur_state) {
	unsigned int size = cur_state.n;
	unsigned int total_size = size * size;
	cout << " GOMOKU GAMEBOARD: " << endl;
	for (int i = 0; i < (total_size); i++) {
		if (i == 0)
			cout << "  ";
		if (i%size == 0 && i != 0)
			cout << endl << "  ";
		cout << cur_state.board[i];
	}
	cout << endl;
}

GameState heuristics_func(GameState node, const int m, const char cur_player) {
	int board_size = node.column_count.size();
	node.hscore = 0;
	//checked_coords_columns used to handle right to left pattern checking
	//checked cords diags used to handle both diagonl directions
	set< pair<int, int> > checked_coords_columns;
	set< pair<int, int> > checked_coords_diag_botR;
	set< pair<int, int> > checked_coords_diag_topR;

	//checks for matching game patterns, column first with i as column
	for (int i = 0 ; i < board_size; i++) {
		//if there is a piece on a column, check the column for a pattern
		if (node.column_count[i]) {
			//checked_coords used to handle top to bottom pattern checking
			set< pair<int, int> > checked_coords;
			//checks row by each in each column, with j as row
			//starts by checking each piece from top to bottom of a column
			for (int j = 0;  j < board_size; j++) {
				//CHECKING LINE PATTERNS FROM TOP TO BOTTOM STARTING AT TILE
				int cur_row = j;
				char cur_piece = node.at(cur_row, i);
				if (cur_piece != '.') {
					pair<int, int> cur_pos;
					cur_pos.first = cur_row;
					cur_pos.second = i;
					//checks if this position has already been looked at by the function
					if (checked_coords.find(cur_pos) == checked_coords.end()) {
						//if this piece is the player's
						if (cur_piece == cur_player) {
							unsigned int cur_pattern_size = 1;
							//start_pattern and end_pattern tracks current row
							int start_pattern = cur_pos.first;
							int end_pattern = cur_pos.first;
							checked_coords.insert(cur_pos);
							if (cur_row+1 < board_size) {
								cur_row++;
								cur_piece = node.at(cur_row, i);
								//while next piece down is also player's piece, add
								//to counter of pattern length
								while (cur_piece == cur_player) {
									cur_pos.first = cur_row;
									cur_pos.second = i;
									end_pattern = cur_pos.first;
									checked_coords.insert(cur_pos);
									cur_pattern_size++;
									if (cur_row+1 < board_size) {
										cur_row++;
										cur_piece = node.at(cur_row, i);
									}
									else
										break;
								}
							}
							//if exactly matching m pieces in a row, from top
							//to bottom in a column, then win state and return
							if (cur_pattern_size == m) {
								node.hscore = SCORE_WIN;
								node.game_end = true;
								return node;
							}
							else if (cur_pattern_size >m)
								node.hscore += SCORE_OVER;
							//if pattern is 1 less than m, then we check for
							//either a "M" threat, or a "straight M" threat
							//two M threats = win, while straight M = win
							else if (cur_pattern_size == (m-1)) {
								//check above and below tiles of pattern
								int empty_count = 0;
								if ((start_pattern-1) >=0) {
									cur_piece = node.at(start_pattern-1, i);
									if (cur_piece == '.')
										empty_count++;
								}
								if ((end_pattern+1) < board_size) {
									cur_piece = node.at(end_pattern+1, i);
									if (cur_piece == '.')
										empty_count++;
								}
								//check if it is a straight M or normal M threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces
								if (empty_count == 1)
									node.hscore += SCORE_M;
								else if (empty_count == 2){
									node.hscore += SCORE_STRAIGHT_M;
								}
								else
									node.hscore += SCORE_DEADEND;
							}
							//if length of pattern is m-2, then use
							//m_minus. this gives priortity to plays
							//that will created an straight_m threat
							else if (cur_pattern_size == (m-2)) {
								//check above and below tiles of pattern
								int empty_count = 0;
								if ((start_pattern-1) >=0) {
									cur_piece = node.at(start_pattern-1, i);
									if (cur_piece == '.')
										empty_count++;
								}
								if ((end_pattern+1) < board_size) {
									cur_piece = node.at(end_pattern+1, i);
									if (cur_piece == '.') {
										empty_count++;
									}
								}
								//check if it is a straight M or normal M threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces
								if (empty_count == 1) {
									node.hscore += cur_pattern_size;
								}
								else if (empty_count == 2){
									bool M_tiles = false;
									//checks if there is enough room for M tiles
									if ((start_pattern-2) >=0) {
										cur_piece = node.at(start_pattern-2, i);
										if (cur_piece == '.')
											M_tiles = true;
									}
									if ((end_pattern+2) < board_size) {
										cur_piece = node.at(end_pattern+2, i);
										if (cur_piece == '.') {
											M_tiles = true;
										}
									}
									//if there is not enough room, same as a
									//deadend
									if (M_tiles)
										node.hscore += SCORE_M_MINUS;
									else
										node.hscore += SCORE_DEADEND;
								}
								else
									node.hscore += SCORE_DEADEND;
							}
							//default case to higher scores to increasing lines
							else
								node.hscore += cur_pattern_size;
						}
						//else if this piece is the opponent's
						else {
							char opp_player = cur_piece;
							unsigned int cur_pattern_size = 1;
							int start_pattern = cur_pos.first;
							int end_pattern = cur_pos.first;
							checked_coords.insert(cur_pos);
							if (cur_row+1 < board_size) {
								cur_row++;
								cur_piece = node.at(cur_row, i);
								//while next piece down is also player's piece, add
								//to counter of pattern length
								while (cur_piece == opp_player) {
									cur_pos.first = cur_row;
									cur_pos.second = i;
									end_pattern = cur_pos.first;
									checked_coords.insert(cur_pos);
									cur_pattern_size++;
									if (cur_row+1 < board_size) {
										cur_row++;
										cur_piece = node.at(cur_row, i);
									}
									else
										break;
								}
							}
							//if exactly matching m pieces in a row, from top
							//to bottom in a column, then lose state and return
							if (cur_pattern_size == m) {
								node.hscore = SCORE_LOSE;
								node.game_end = true;
								return node;
							}
							//if the pattern is over size 5, then adding onto it
							//will never help the opp win, which is a good thing
							else if (cur_pattern_size >m)
								node.hscore += SCORE_OPP_OVER;
							//if pattern is 1 less than m, then we check for
							//either a "M" threat, or a "straight M" threat from
							//the opponent
							//two M threats = lose, while straight M = lose
							else if (cur_pattern_size == (m-1)) {
								//check above and below tiles of pattern
								int empty_count = 0;
								if ((start_pattern-1) >=0) {
									cur_piece = node.at(start_pattern-1, i);
									if (cur_piece == '.') {
										empty_count++;
									}
								}
								if ((end_pattern+1) < board_size) {
									cur_piece = node.at(end_pattern+1, i);
									if (cur_piece == '.')
										empty_count++;
								}
								//check if normal line or M_minus threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces and deadend
								if (empty_count == 1) {
									node.hscore += SCORE_OPP_M;
								}
								else if (empty_count == 2){
									node.hscore += SCORE_OPP_STRAIGHT_M;
								}
								else
									node.hscore += SCORE_OPP_DEADEND;
							}
							//if length of pattern is m-2, then use
							//opp_m_minus. this gives opp priortity to plays
							//that will created an straight_m threat
							else if (cur_pattern_size == (m-2)) {
								//check above and below tiles of pattern
								int empty_count = 0;
								if ((start_pattern-1) >=0) {
									cur_piece = node.at(start_pattern-1, i);
									if (cur_piece == '.')
										empty_count++;
								}
								if ((end_pattern+1) < board_size) {
									cur_piece = node.at(end_pattern+1, i);
									if (cur_piece == '.')
										empty_count++;
								}
								//check normal line or M_minus threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces and deadend
								if (empty_count == 1)
									node.hscore -= cur_pattern_size;
								else if (empty_count == 2){
									bool M_tiles = false;
									//checks if there is enough room for M tiles
									if ((start_pattern-2) >=0) {
										cur_piece = node.at(start_pattern-2, i);
										if (cur_piece == '.')
											M_tiles = true;
									}
									if ((end_pattern+2) < board_size) {
										cur_piece = node.at(end_pattern+2, i);
										if (cur_piece == '.')
											M_tiles = true;
									}
									//if there is not enough room, same as a
									//deadend
									if (M_tiles)
										node.hscore += SCORE_OPP_M_MINUS;
									else
										node.hscore += SCORE_OPP_DEADEND;
								}
								else
									node.hscore += SCORE_OPP_DEADEND;

							}
							//default to decrement score for each opp's tile pat
							else
								node.hscore -= cur_pattern_size;
						}
					}
				}
				//CHECKING FROM PATTERNS FROM RIGHT TO LEFT STARTING AT TILE
				cur_row = j;
				int cur_column = i;
				cur_piece = node.at(cur_row, cur_column);
				if (cur_piece != '.') {
					pair<int, int> cur_pos;
					cur_pos.first = cur_row;
					cur_pos.second = cur_column;
					//checks if this position has already been looked at by the function
					if (checked_coords_columns.find(cur_pos) == checked_coords_columns.end()) {
						//if this piece is the player's
						if (cur_piece == cur_player) {
							unsigned int cur_pattern_size = 1;
							//start_pattern and end_pattern tracks columns
							int start_pattern = cur_pos.second;
							int end_pattern = cur_pos.second;
							checked_coords_columns.insert(cur_pos);
							if (cur_column+1 < board_size) {
								cur_column++;
								cur_piece = node.at(cur_row, cur_column);
								//while next piece right is also player's piece, add
								//to counter of pattern length
								while (cur_piece == cur_player) {
									cur_pos.first = cur_row;
									cur_pos.second = cur_column;
									end_pattern = cur_pos.second;
									checked_coords_columns.insert(cur_pos);
									cur_pattern_size++;
									if (cur_column+1 < board_size) {
										cur_column++;
										cur_piece = node.at(cur_row, cur_column);
									}
									else
										break;
								}
							}
							//if exactly matching m pieces in a row, from top
							//to bottom in a column, then win state and return
							if (cur_pattern_size == m) {
								node.hscore = SCORE_WIN;
								node.game_end = true;
								return node;
							}
							else if (cur_pattern_size >m)
								node.hscore += SCORE_OVER;
							//if pattern is 1 less than m, then we check for
							//either a "M" threat, or a "straight M" threat
							//two M threats = win, while straight M = win
							else if (cur_pattern_size == (m-1)) {
								//check right and left tiles of pattern
								int empty_count = 0;
								if ((start_pattern-1) >=0) {
									cur_piece = node.at(cur_row, start_pattern-1);
									if (cur_piece == '.')
										empty_count++;
								}
								if ((end_pattern+1) < board_size) {
									cur_piece = node.at(cur_row, end_pattern+1);
									if (cur_piece == '.')
										empty_count++;
								}
								//check if it is a straight M or normal M threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces
								if (empty_count == 1)
									node.hscore += SCORE_M;
								else if (empty_count == 2){
									node.hscore += SCORE_STRAIGHT_M;
								}
								else
									node.hscore += SCORE_DEADEND;
							}
							//if length of pattern is m-2, then use
							//m_minus. this gives priortity to plays
							//that will created an straight_m threat
							else if (cur_pattern_size == (m-2)) {
								//check above and below tiles of pattern
								int empty_count = 0;
								if ((start_pattern-1) >=0) {
									cur_piece = node.at(cur_row, start_pattern-1);
									if (cur_piece == '.')
										empty_count++;
								}
								if ((end_pattern+1) < board_size) {
									cur_piece = node.at(cur_row, end_pattern+1);
									if (cur_piece == '.') {
										empty_count++;
									}
								}
								//check if it is a straight M or normal M threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces
								if (empty_count == 1) {
									node.hscore += cur_pattern_size;
								}
								else if (empty_count == 2){
									bool M_tiles = false;
									//checks if there is enough room for M tiles
									if ((start_pattern-2) >=0) {
										cur_piece = node.at(cur_row, start_pattern-2);
										if (cur_piece == '.')
											M_tiles = true;
									}
									if ((end_pattern+2) < board_size) {
										cur_piece = node.at(cur_row, end_pattern+2);
										if (cur_piece == '.') {
											M_tiles = true;
										}
									}
									//if there is not enough room, same as a
									//deadend
									if (M_tiles)
										node.hscore += SCORE_M_MINUS;
									else
										node.hscore += SCORE_DEADEND;
								}
								else
									node.hscore += SCORE_DEADEND;
							}
							//default case to higher scores to increasing lines
							else
								node.hscore += cur_pattern_size;
						}
						//else if this piece is the opponent's
						else {
							char opp_player = cur_piece;
							unsigned int cur_pattern_size = 1;
							int start_pattern = cur_pos.second;
							int end_pattern = cur_pos.second;
							checked_coords_columns.insert(cur_pos);
							if (cur_column+1 < board_size) {
								cur_column++;
								cur_piece = node.at(cur_row, cur_column);
								//while next piece down is also player's piece, add
								//to counter of pattern length
								while (cur_piece == opp_player) {
									cur_pos.first = cur_row;
									cur_pos.second = cur_column;
									end_pattern = cur_pos.second;
									checked_coords_columns.insert(cur_pos);
									cur_pattern_size++;
									if (cur_column+1 < board_size) {
										cur_column++;
										cur_piece = node.at(cur_row, cur_column);
									}
									else
										break;
								}
							}
							//if exactly matching m pieces in a row, from top
							//to bottom in a column, then lose state and return
							if (cur_pattern_size == m) {
								node.hscore = SCORE_LOSE;
								node.game_end = true;
								return node;
							}
							//if the pattern is over size 5, then adding onto it
							//will never help the opp win, which is a good thing
							else if (cur_pattern_size >m)
								node.hscore += SCORE_OPP_OVER;
							//if pattern is 1 less than m, then we check for
							//either a "M" threat, or a "straight M" threat from
							//the opponent
							//two M threats = lose, while straight M = lose
							else if (cur_pattern_size == (m-1)) {
								//check above and below tiles of pattern
								int empty_count = 0;
								if ((start_pattern-1) >=0) {
									cur_piece = node.at(cur_row, start_pattern-1);
									if (cur_piece == '.') {
										empty_count++;
									}
								}
								if ((end_pattern+1) < board_size) {
									cur_piece = node.at(cur_row, end_pattern+1);
									if (cur_piece == '.')
										empty_count++;
								}
								//check if normal line or M_minus threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces and deadend
								if (empty_count == 1) {
									node.hscore += SCORE_OPP_M;
								}
								else if (empty_count == 2){
									node.hscore += SCORE_OPP_STRAIGHT_M;
								}
								else
									node.hscore += SCORE_OPP_DEADEND;
							}
							//if length of pattern is m-2, then use
							//opp_m_minus. this gives opp priortity to plays
							//that will created an straight_m threat
							else if (cur_pattern_size == (m-2)) {
								//check top left and bottom right tiles of pattern
								int empty_count = 0;
								if ((start_pattern-1) >=0) {
									cur_piece = node.at(cur_row, start_pattern-1);
									if (cur_piece == '.')
										empty_count++;
								}
								if ((end_pattern+1) < board_size) {
									cur_piece = node.at(cur_row, end_pattern+1);
									if (cur_piece == '.')
										empty_count++;
								}
								//check normal line or M_minus threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces and deadend
								if (empty_count == 1)
									node.hscore -= cur_pattern_size;
								else if (empty_count == 2){
									bool M_tiles = false;
									//checks if there is enough room for M tiles
									if ((start_pattern-2) >=0) {
										cur_piece = node.at(cur_row, start_pattern-2);
										if (cur_piece == '.')
											M_tiles = true;
									}
									if ((end_pattern+2) < board_size) {
										cur_piece = node.at(cur_row, end_pattern+2);
										if (cur_piece == '.')
											M_tiles = true;
									}
									//if there is not enough room, same as a
									//deadend
									if (M_tiles)
										node.hscore += SCORE_OPP_M_MINUS;
									else
										node.hscore += SCORE_OPP_DEADEND;
								}
								else
									node.hscore += SCORE_OPP_DEADEND;

							}
							//default to decrement score for each opp's tile pat
							else
								node.hscore -= cur_pattern_size;
						}
					}
				}
				//CHECKING FROM PATTERNS FROM BOTTOM LEFT TO TOP RIGHT STARTING AT TILE
				cur_row = j;
				cur_column = i;
				cur_piece = node.at(cur_row, cur_column);
				if (cur_piece != '.') {
					pair<int, int> cur_pos;
					cur_pos.first = cur_row;
					cur_pos.second = cur_column;
					//checks if this position has already been looked at by the function
					if (checked_coords_diag_topR.find(cur_pos) == checked_coords_diag_topR.end()) {
						//if this piece is the player's
						if (cur_piece == cur_player) {
							unsigned int cur_pattern_size = 1;
							//start_pattern and end_pattern tracks columns
							pair<int, int> start_pattern = cur_pos;
							pair<int, int> end_pattern = cur_pos;
							checked_coords_diag_topR.insert(cur_pos);
							if ((cur_column+1 < board_size) && (cur_row-1 >= 0)) {
								cur_column++;
								cur_row--;
								cur_piece = node.at(cur_row, cur_column);
								//while next piece right is also player's piece, add
								//to counter of pattern length
								while (cur_piece == cur_player) {
									cur_pos.first = cur_row;
									cur_pos.second = cur_column;
									end_pattern = cur_pos;
									checked_coords_diag_topR.insert(cur_pos);
									cur_pattern_size++;
									if ((cur_column+1 < board_size) && (cur_row-1 >= 0)) {
										cur_column++;
										cur_row--;
										cur_piece = node.at(cur_row, cur_column);
									}
									else
										break;
								}
							}
							//if exactly matching m pieces in a row, from top
							//to bottom in a column, then win state and return
							if (cur_pattern_size == m) {
								node.hscore = SCORE_WIN;
								node.game_end = true;
								return node;
							}
							else if (cur_pattern_size >m)
								node.hscore += SCORE_OVER;
							//if pattern is 1 less than m, then we check for
							//either a "M" threat, or a "straight M" threat
							//two M threats = win, while straight M = win
							else if (cur_pattern_size == (m-1)) {
								//check above and below tiles of pattern
								int empty_count = 0;
								if (((start_pattern.first+1) < board_size) && ((start_pattern.second-1) >=0)) {
									cur_piece = node.at(start_pattern.first+1, start_pattern.second-1);
									if (cur_piece == '.')
										empty_count++;
								}
								if (((end_pattern.first-1) >= 0) && ((end_pattern.second+1) < board_size)) {
									cur_piece = node.at(end_pattern.first-1, end_pattern.second+1);
									if (cur_piece == '.')
										empty_count++;
								}
								//check if it is a straight M or normal M threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces
								if (empty_count == 1)
									node.hscore += SCORE_M;
								else if (empty_count == 2){
									node.hscore += SCORE_STRAIGHT_M;
								}
								else
									node.hscore += SCORE_DEADEND;
							}
							//if length of pattern is m-2, then use
							//m_minus. this gives priortity to plays
							//that will created an straight_m threat
							else if (cur_pattern_size == (m-2)) {
								//check top right and bottom left tiles of pattern
								int empty_count = 0;
								if (((start_pattern.first+1) < board_size) && ((start_pattern.second-1) >=0)) {
									cur_piece = node.at(start_pattern.first+1, start_pattern.second-1);
									if (cur_piece == '.')
										empty_count++;
								}
								if (((end_pattern.first-1) >= 0) && ((end_pattern.second+1) < board_size)) {
									cur_piece = node.at(end_pattern.first-1, end_pattern.second+1);
									if (cur_piece == '.') {
										empty_count++;
									}
								}
								//check if it is a straight M or normal M threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces
								if (empty_count == 1) {
									node.hscore += cur_pattern_size;
								}
								else if (empty_count == 2){
									bool M_tiles = false;
									//checks if there is enough room for M tiles
									if (((start_pattern.first+2) < board_size) && ((start_pattern.second-2) >=0)) {
										cur_piece = node.at(start_pattern.first+2, start_pattern.second-2);
										if (cur_piece == '.')
											M_tiles = true;
									}
									if (((end_pattern.first-2) >= 0) && ((end_pattern.second+2) < board_size)) {
										cur_piece = node.at(end_pattern.first-2, end_pattern.second+2);
										if (cur_piece == '.') {
											M_tiles = true;
										}
									}
									//if there is not enough room, same as a
									//deadend
									if (M_tiles)
										node.hscore += SCORE_M_MINUS;
									else
										node.hscore += SCORE_DEADEND;
								}
								else
									node.hscore += SCORE_DEADEND;
							}
							//default case to higher scores to increasing lines
							else
								node.hscore += cur_pattern_size;
						}
						//else if this piece is the opponent's
						else {
							char opp_player = cur_piece;
							unsigned int cur_pattern_size = 1;
							pair<int, int> start_pattern = cur_pos;
							pair<int, int> end_pattern = cur_pos;
							checked_coords_diag_topR.insert(cur_pos);
							if ((cur_column+1 < board_size) && (cur_row-1 >= 0)) {
								cur_column++;
								cur_row--;
								cur_piece = node.at(cur_row, cur_column);
								//while next piece right is also player's piece, add
								//to counter of pattern length
								while (cur_piece == opp_player) {
									cur_pos.first = cur_row;
									cur_pos.second = cur_column;
									end_pattern = cur_pos;
									checked_coords_diag_topR.insert(cur_pos);
									cur_pattern_size++;
									if ((cur_column+1 < board_size) && (cur_row-1 >= 0)) {
										cur_column++;
										cur_row--;
										cur_piece = node.at(cur_row, cur_column);
									}
									else
										break;
								}
							}
							//if exactly matching m pieces in a row, from top
							//to bottom in a column, then win state and return
							if (cur_pattern_size == m) {
								node.hscore = SCORE_LOSE;
								node.game_end = true;
								return node;
							}
							else if (cur_pattern_size >m)
								node.hscore += SCORE_OPP_OVER;
							//if pattern is 1 less than m, then we check for
							//either a "M" threat, or a "straight M" threat
							//two M threats = win, while straight M = win
							else if (cur_pattern_size == (m-1)) {
								//check above and below tiles of pattern
								int empty_count = 0;
								if (((start_pattern.first+1) < board_size) && ((start_pattern.second-1) >=0)) {
									cur_piece = node.at(start_pattern.first+1, start_pattern.second-1);
									if (cur_piece == '.')
										empty_count++;
								}
								if (((end_pattern.first-1) >= 0) && ((end_pattern.second+1) < board_size)) {
									cur_piece = node.at(end_pattern.first-1, end_pattern.second+1);
									if (cur_piece == '.')
										empty_count++;
								}
								//check if it is a straight M or normal M threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces
								if (empty_count == 1)
									node.hscore += SCORE_OPP_M;
								else if (empty_count == 2){
									node.hscore += SCORE_OPP_STRAIGHT_M;
								}
								else
									node.hscore += SCORE_OPP_DEADEND;
							}
							//if length of pattern is m-2, then use
							//m_minus. this gives priortity to plays
							//that will created an straight_m threat
							else if (cur_pattern_size == (m-2)) {
								//check above and below tiles of pattern
								int empty_count = 0;
								if (((start_pattern.first+1) < board_size) && ((start_pattern.second-1) >=0)) {
									cur_piece = node.at(start_pattern.first+1, start_pattern.second-1);
									if (cur_piece == '.')
										empty_count++;
								}
								if (((end_pattern.first-1) >= 0) && ((end_pattern.second+1) < board_size)) {
									cur_piece = node.at(end_pattern.first-1, end_pattern.second+1);
									if (cur_piece == '.') {
										empty_count++;
									}
								}
								//check if it is a straight M or normal M threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces
								if (empty_count == 1) {
									node.hscore += cur_pattern_size;
								}
								else if (empty_count == 2){
									bool M_tiles = false;
									//checks if there is enough room for M tiles
									if (((start_pattern.first+2) < board_size) && ((start_pattern.second-2) >=0)) {
										cur_piece = node.at(start_pattern.first+2, start_pattern.second-2);
										if (cur_piece == '.')
											M_tiles = true;
									}
									if (((end_pattern.first-2) >= 0) && ((end_pattern.second+2) < board_size)) {
										cur_piece = node.at(end_pattern.first-2, end_pattern.second+2);
										if (cur_piece == '.') {
											M_tiles = true;
										}
									}
									//if there is not enough room, same as a
									//deadend
									if (M_tiles)
										node.hscore += SCORE_OPP_M_MINUS;
									else
										node.hscore += SCORE_OPP_DEADEND;
								}
								else
									node.hscore += SCORE_OPP_DEADEND;
							}
							//default case to higher scores to increasing lines
							else
								node.hscore -= cur_pattern_size;
						}
					}
				}
				//CHECKING FROM PATTERNS FROM TOP LEFT TO BOTTOM RIGHT STARTING AT TILE
				cur_row = j;
				cur_column = i;
				cur_piece = node.at(cur_row, cur_column);
				if (cur_piece != '.') {
					pair<int, int> cur_pos;
					cur_pos.first = cur_row;
					cur_pos.second = cur_column;
					//checks if this position has already been looked at by the function
					if (checked_coords_diag_botR.find(cur_pos) == checked_coords_diag_botR.end()) {
						//if this piece is the player's
						if (cur_piece == cur_player) {
							unsigned int cur_pattern_size = 1;
							//start_pattern and end_pattern tracks columns
							pair<int, int> start_pattern = cur_pos;
							pair<int, int> end_pattern = cur_pos;
							checked_coords_diag_botR.insert(cur_pos);
							if ((cur_column+1 < board_size) && (cur_row+1 < board_size)) {
								cur_column++;
								cur_row++;
								cur_piece = node.at(cur_row, cur_column);
								//while next piece right is also player's piece, add
								//to counter of pattern length
								while (cur_piece == cur_player) {
									cur_pos.first = cur_row;
									cur_pos.second = cur_column;
									end_pattern = cur_pos;
									checked_coords_diag_botR.insert(cur_pos);
									cur_pattern_size++;
									if ((cur_column+1 < board_size) && (cur_row+1 < board_size)) {
										cur_column++;
										cur_row++;
										cur_piece = node.at(cur_row, cur_column);
									}
									else
										break;
								}
							}
							//if exactly matching m pieces in a row, from top
							//to bottom in a column, then win state and return
							if (cur_pattern_size == m) {
								node.hscore = SCORE_WIN;
								node.game_end = true;
								return node;
							}
							else if (cur_pattern_size >m)
								node.hscore += SCORE_OVER;
							//if pattern is 1 less than m, then we check for
							//either a "M" threat, or a "straight M" threat
							//two M threats = win, while straight M = win
							else if (cur_pattern_size == (m-1)) {
								//check above and below tiles of pattern
								int empty_count = 0;
								if (((start_pattern.first-1) >=0) && ((start_pattern.second-1) >=0)) {
									cur_piece = node.at(start_pattern.first-1, start_pattern.second-1);
									if (cur_piece == '.')
										empty_count++;
								}
								if (((end_pattern.first+1) < board_size) && ((end_pattern.second+1) < board_size)) {
									cur_piece = node.at(end_pattern.first+1, end_pattern.second+1);
									if (cur_piece == '.')
										empty_count++;
								}
								//check if it is a straight M or normal M threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces
								if (empty_count == 1)
									node.hscore += SCORE_M;
								else if (empty_count == 2){
									node.hscore += SCORE_STRAIGHT_M;
								}
								else
									node.hscore += SCORE_DEADEND;
							}
							//if length of pattern is m-2, then use
							//m_minus. this gives priortity to plays
							//that will created an straight_m threat
							else if (cur_pattern_size == (m-2)) {
								//check above and below tiles of pattern
								int empty_count = 0;
								if (((start_pattern.first-1) >=0) && ((start_pattern.second-1) >=0)) {
									cur_piece = node.at(start_pattern.first-1, start_pattern.second-1);
									if (cur_piece == '.')
										empty_count++;
								}
								if (((end_pattern.first+1) < board_size) && ((end_pattern.second+1) < board_size)) {
									cur_piece = node.at(end_pattern.first+1, end_pattern.second+1);
									if (cur_piece == '.') {
										empty_count++;
									}
								}
								//check if it is a straight M or normal M threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces
								if (empty_count == 1) {
									node.hscore += cur_pattern_size;
								}
								else if (empty_count == 2){
									bool M_tiles = false;
									//checks if there is enough room for M tiles
									if (((start_pattern.first-2) >=0) && ((start_pattern.second-2) >=0)) {
										cur_piece = node.at(start_pattern.first-2, start_pattern.second-2);
										if (cur_piece == '.')
											M_tiles = true;
									}
									if (((end_pattern.first+2) < board_size) && ((end_pattern.second+2) < board_size)) {
										cur_piece = node.at(end_pattern.first+2, end_pattern.second+2);
										if (cur_piece == '.') {
											M_tiles = true;
										}
									}
									//if there is not enough room, same as a
									//deadend
									if (M_tiles)
										node.hscore += SCORE_M_MINUS;
									else
										node.hscore += SCORE_DEADEND;
								}
								else
									node.hscore += SCORE_DEADEND;
							}
							//default case to higher scores to increasing lines
							else
								node.hscore += cur_pattern_size;
						}
						//else if this piece is the opponent's
						else {
							char opp_player = cur_piece;
							unsigned int cur_pattern_size = 1;
							pair<int, int> start_pattern = cur_pos;
							pair<int, int> end_pattern = cur_pos;
							checked_coords_diag_botR.insert(cur_pos);
							if ((cur_column+1 < board_size) && (cur_row+1 < board_size)) {
								cur_column++;
								cur_row++;
								cur_piece = node.at(cur_row, cur_column);
								//while next piece right is also player's piece, add
								//to counter of pattern length
								while (cur_piece == opp_player) {
									cur_pos.first = cur_row;
									cur_pos.second = cur_column;
									end_pattern = cur_pos;
									checked_coords_diag_botR.insert(cur_pos);
									cur_pattern_size++;
									if ((cur_column+1 < board_size) && (cur_row+1 < board_size)) {
										cur_column++;
										cur_row++;
										cur_piece = node.at(cur_row, cur_column);
									}
									else
										break;
								}
							}
							//if exactly matching m pieces in a row, from top
							//to bottom in a column, then win state and return
							if (cur_pattern_size == m) {
								node.hscore = SCORE_LOSE;
								node.game_end = true;
								return node;
							}
							else if (cur_pattern_size >m)
								node.hscore += SCORE_OPP_OVER;
							//if pattern is 1 less than m, then we check for
							//either a "M" threat, or a "straight M" threat
							//two M threats = win, while straight M = win
							else if (cur_pattern_size == (m-1)) {
								//check above and below tiles of pattern
								int empty_count = 0;
								if (((start_pattern.first-1) >=0) && ((start_pattern.second-1) >=0)) {
									cur_piece = node.at(start_pattern.first-1, start_pattern.second-1);
									if (cur_piece == '.')
										empty_count++;
								}
								if (((end_pattern.first+1) < board_size) && ((end_pattern.second+1) < board_size)) {
									cur_piece = node.at(end_pattern.first+1, end_pattern.second+1);
									if (cur_piece == '.')
										empty_count++;
								}
								//check if it is a straight M or normal M threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces
								if (empty_count == 1)
									node.hscore += SCORE_OPP_M;
								else if (empty_count == 2){
									node.hscore += SCORE_OPP_STRAIGHT_M;
								}
								else
									node.hscore += SCORE_OPP_DEADEND;
							}
							//if length of pattern is m-2, then use
							//m_minus. this gives priortity to plays
							//that will created an straight_m threat
							else if (cur_pattern_size == (m-2)) {
								//check top left and bottom right tiles of pattern
								int empty_count = 0;
								if (((start_pattern.first-1) >=0) && ((start_pattern.second-1) >=0)) {
									cur_piece = node.at(start_pattern.first-1, start_pattern.second-1);
									if (cur_piece == '.')
										empty_count++;
								}
								if (((end_pattern.first+1) < board_size) && ((end_pattern.second+1) < board_size)) {
									cur_piece = node.at(end_pattern.first+1, end_pattern.second+1);
									if (cur_piece == '.') {
										empty_count++;
									}
								}
								//check if it is a straight M or normal M threat
								//if 0, then it means that it the pattern is
								//between 2 opponents pieces
								if (empty_count == 1) {
									node.hscore += cur_pattern_size;
								}
								else if (empty_count == 2){
									bool M_tiles = false;
									//checks if there is enough room for M tiles
									if (((start_pattern.first-2) >=0) && ((start_pattern.second-2) >=0)) {
										cur_piece = node.at(start_pattern.first-2, start_pattern.second-2);
										if (cur_piece == '.')
											M_tiles = true;
									}
									if (((end_pattern.first+2) < board_size) && ((end_pattern.second+2) < board_size)) {
										cur_piece = node.at(end_pattern.first+2, end_pattern.second+2);
										if (cur_piece == '.') {
											M_tiles = true;
										}
									}
									//if there is not enough room, same as a
									//deadend
									if (M_tiles)
										node.hscore += SCORE_OPP_M_MINUS;
									else
										node.hscore += SCORE_OPP_DEADEND;
								}
								else
									node.hscore += SCORE_OPP_DEADEND;
							}
							//default case to higher scores to increasing lines
							else
								node.hscore -= cur_pattern_size;
						}
					}
				}
			}
		}
	}
	//if there are no more tiles yet no winnning pattern detected,
	//then game ends in a draw
	if (!node.game_end && (node.tiles_left == 0)) {
		node.game_end = true;
	}
	return node;
}

/* Generates all game boards with pieces added next to each existing piece on the
 * board. The 8 tiles around each tile on the board is generated if possible
 * Preconditions: cur_board = node, m =  # of tiles in a row to match,
 *                score_player = player's perspective when using heuristics,
 *                player = current player to generate new moves with
 * Postconditions: Returns a deque of GameStates representing all valid generated
 *                 nodes
 */
deque<GameState> gen_all_moves(GameState cur_board, const unsigned int m, const char score_player, const char player) {
	deque<GameState> move_list;
	set< pair<int, int> > gen_coords_list;
	bool empty_board = true;
	int board_column_size = cur_board.column_count.size();
	//loops through the board and add to a list of new states to generate
	//i = column, j = column
	for (int i = 0; i < board_column_size; i++) {
		//check if there are any pieces in the column
		if (cur_board.column_count[i]) {
			empty_board = false;
			for (int j = 0; j < board_column_size; j++) {
				if (cur_board.at(j, i) != '.') {
					//add top tile to gen list
					if (j-1 >= 0) {
						if (cur_board.at(j-1, i) == '.') {
							pair<int, int> temp(j-1, i);
							gen_coords_list.insert(temp);
						}
					}
					//add bottom tile to gen list
					if (j+1 < board_column_size) {
						if (cur_board.at(j+1, i) == '.') {
							pair<int, int> temp(j+1, i);
							gen_coords_list.insert(temp);
						}
					}
					//add right tile to gen list
					if (i+1 < board_column_size) {
						if (cur_board.at(j, i+1) == '.') {
							pair<int, int> temp(j, i+1);
							gen_coords_list.insert(temp);
						}
					}
					//add left tile to gen list
					if (i-1 >= 0) {
						if (cur_board.at(j, i-1) == '.') {
							pair<int, int> temp(j, i-1);
							gen_coords_list.insert(temp);
						}
					}
					//add top left tile
					if ((j-1 >= 0) && (i-1 >= 0)) {
						if (cur_board.at(j-1, i-1) == '.') {
							pair<int, int> temp(j-1, i-1);
							gen_coords_list.insert(temp);
						}
					}
					//add top right tile
					if ((j-1 >= 0) && (i+1 < board_column_size)) {
						if (cur_board.at(j-1, i+1) == '.') {
							pair<int, int> temp(j-1, i+1);
							gen_coords_list.insert(temp);
						}
					}
					//add bottom left tile
					if ((j+1 < board_column_size) && (i-1 >= 0)) {
						if (cur_board.at(j+1, i-1) == '.') {
							pair<int, int> temp(j+1, i-1);
							gen_coords_list.insert(temp);
						}
					}
					//add bottom right tile
					if ((j+1 < board_column_size) && (i+1 < board_column_size)) {
						if (cur_board.at(j+1, i+1) == '.') {
							pair<int, int> temp(j+1, i+1);
							gen_coords_list.insert(temp);
						}
					}
				}
			}
		}
	}
	//if the board is empty, pick the middle tile to generate new state
	if (empty_board) {
		int middle_board = board_column_size/2;
		pair<int, int> temp(middle_board, middle_board);
		gen_coords_list.insert(temp);
	}
	//for each tile coordinates, generate and append to the deque a new state
	for (set< pair<int, int> >::iterator it = gen_coords_list.begin(); it != gen_coords_list.end(); it++) {
		GameState temp_board = cur_board;
		temp_board.set(it->first, it->second, player);
		temp_board = heuristics_func(temp_board, m, score_player);
		move_list.push_back(temp_board);
	}
	return move_list;
}

/* Function used to generate a new move by placing new game piece on the board
 * Preconditions: cur_board = GameState object representing the game board,
 *                player = char either X or O to place tile piece,
 *                row = row in the gameboard, starting from top to bottom
 *                column = column in gameboard, starting from left to right
 * Postconditions: Returns a GameState object with new piece placed on board if
 *                 no errors
 */
GameState player_gen_move(GameState cur_board, char player, unsigned int row, unsigned int column) {
	unsigned int pos = (row*cur_board.n)+column;
	unsigned int n = cur_board.n;

	//if there are no free tiles left on gameboard
	if ( cur_board.game_end || cur_board.tiles_left == 0) {
		cout << "Game has ended or board is filled" << endl;
		return cur_board;
	}
	//checks if input row, column is accurate and if tile at pos is free
	if (((row < 0 || row >= n) || (column < 0 || column >= n)) || cur_board.board[pos] != '.') {
		cout << "Illegal move by player " << player << " at " << row << " " << column << endl;
	}
	else {
		cur_board.board[pos] = player;
		cur_board.column_count[column] = true;
		cur_board.tiles_left--;
		cur_board.last_column = column;
		cur_board.last_row = row;
	}
	return cur_board;
}

/* Function used to generate a new random move on the game board
 * Preconditions: cur_board = GameState object representing the game board,
 *                player = char either X or O to place tile piece,
 * Postconditions: Returns a GameState object with new piece placed on board if
 *                 no errors
 */
GameState random_gen_move(GameState cur_board, char player) {
	unsigned int n = cur_board.n;

	//if there are no free tiles left on gameboard
	if ( cur_board.game_end || cur_board.tiles_left == 0) {
		cout << "Game has ended or board is filled" << endl;
		return cur_board;
	}
	//if there exists an empty spot
	//NOTE: As the # of free tiles becomes closer to 0,
	//the more likely there will be collisions with occupied tiles
	else {
		//generates random positions for tile piece until it finds an empty one
		int row = rand() % n;
		int column = rand() % n;
		char piece = cur_board.at(row, column);
		while (piece != '.') {
			row = rand() % n;
			column = rand() % n;
			piece = cur_board.at(row, column);
		}
		unsigned int pos = (row*cur_board.n)+column;
		cur_board.board[pos] = player;
		cur_board.column_count[column] = true;
		cur_board.tiles_left--;
		cur_board.last_column = column;
		cur_board.last_row = row;
	}
	return cur_board;
}
/*
 * Preconditions: root = GameState object representing the game board,
 * Postconditions: Returns a GameState object with new piece placed on board if
 */
pair<int, pair<int, int> > alphabeta(GameState root,
	unsigned int depth, pair<int, pair<int, int> > alpha,
	pair<int, pair<int, int> > beta, char player, bool maxPlayer,
	timespec &start_time, const unsigned int &time_limit, bool &cutoff,
	unsigned int m) {

	timespec time_now;
	clock_gettime(CLOCK_REALTIME, &time_now);
	double time_taken = (time_now.tv_sec - start_time.tv_sec)+(time_now.tv_nsec - start_time.tv_nsec)/1000000000.0;
	//cout << "TIME AT DEPTH: " << depth <<" " << time_taken << endl;
	if (time_taken > time_limit) {
		cutoff = true;
		return alpha;
	}

	//if cutoff, terminal node, or depth at zero
	if ((time_taken >= time_limit) || depth == 0 || root.game_end || root.tiles_left == 0) {
		pair<int, pair<int, int> > hscore;
		//hscore.first = heuristics score function
		hscore.first = root.hscore;

		//if (root.game_end)
			//(root.hscore == 5376 && root.last_row == 5&& root.last_column == 6)
			//print_board(root);

		//Given the choice between winning moves, we wish the pick the winning
		//sequence that is closer to starting node in the alphabeta search
		//higher priority is given to winning quicker. likewise, if a node is
		//a losing one, the quicker we lose, the worst off we are
		if (hscore.first == SCORE_WIN)
			hscore.first += depth;
		if (hscore.first == SCORE_LOSE)
			hscore.first -= depth;
		//
		//if (root.game_end)
		//cout <<"  debug: root.last_row: " << root.last_row << "root.last_column: " << root.last_column << " hscore: "<< hscore.first <<endl;
		hscore.second.first = root.last_row;
		hscore.second.second = root.last_column;
		//if(hscore.first == SCORE_WIN){
		//print_board(root);
		//cout<<" BOARD SCORE: "<< hscore.first<<endl;

			//cout <<"  debug: root.last_row: " << root.last_row << "root.last_column: " << root.last_column << " hscore: "<< hscore.first <<endl;
		//}
		return hscore;
	}

	//used to flip the players for generating new moves
	char current_player;
	if (player == 'X') {
		if (maxPlayer)
			current_player = 'X';
		else
			current_player = 'O';
	}
	else if (player == 'O') {
		if (maxPlayer)
			current_player = 'O';
		else
			current_player = 'X';
	}
	else {
		cout << "alphabeta error: unrecognized player" << endl;
	}
	//cout<<"START BOARD" << endl;
	//print_board(root);
	deque<GameState> moves = gen_all_moves(root, m, player, current_player);
	//if (time_taken > time_limit) {
	//}
	/*
	cout<< "ALPHABETA DEPTH: " << depth << " GEN PLAYER " << current_player << endl;
	for (deque<GameState>::iterator itr = moves.begin(); itr != moves.end(); itr++) {
		print_board(*itr);
		cout << "LAST MOVE: " << itr->last_row << ", " << itr->last_column << " SCORE: " << itr->hscore <<endl;
	}*/

	if (maxPlayer) {
		for (deque<GameState>::iterator itr = moves.begin(); itr != moves.end(); itr++) {
			pair<int, pair<int, int> > temp_score;
			//
			//if (depth == 1){
				//print_board(*itr);
				//cout<<" BOARD SCORE: "<< *itr.first<<endl;
				//}
			//
			temp_score = alphabeta(*itr, depth-1, alpha, beta, player, false, start_time, time_limit, cutoff, m);
			if (cutoff) {
				return alpha;
			}
			if (temp_score.first > alpha.first) {
				alpha.first = temp_score.first;
				alpha.second.first = itr->last_row;
				alpha.second.second = itr->last_column;
				//if (depth == 3)
					//cout <<"  changing alpha: last_row: " << alpha.second.first << "last_column: " << alpha.second.second << " hscore: "<< alpha.first <<endl;

			}
			//if (depth == 5)
				//cout <<"  debug: root.last_row: " << alpha.second.first << "root.last_column: " << alpha.second.second << " hscore: "<< alpha.first <<endl;

			if (alpha.first >= beta.first)
				break;
		}/*
		if (depth == 3) {
			cout <<"  debug: root.last_row: " << alpha.second.first << "root.last_column: " << alpha.second.second << " hscore: "<< alpha.first <<endl;
		}*/

		return alpha;
	}
	else {
		for (deque<GameState>::iterator itr = moves.begin(); itr != moves.end(); itr++) {
			pair<int, pair<int, int> > temp_score;
			temp_score = alphabeta(*itr, depth-1, alpha, beta, player, true, start_time, time_limit, cutoff, m);
			if (cutoff) {
				return beta;
			}
			if (temp_score.first < beta.first) {
				beta.first = temp_score.first;
				beta.second.first = itr->last_row;
				beta.second.second = itr->last_column;
				if (depth == 3)
					cout <<"  changing beta: last_row: " << alpha.second.first << "last_column: " << alpha.second.second << " hscore: "<< alpha.first <<endl;

			}
			if (alpha.first >= beta.first)
				break;
		}
		return beta;
	}
}
pair<int, int> itr_deep_minimax(GameState root, char player, const unsigned int time_limit, unsigned int m) {
	timespec start;
	//timespec prog_start, prog_end;
	pair<int, pair<int, int> > alpha, beta;
	pair<int, int> r_move;
	alpha.first = ALPHA_INF;
	beta.first = BETA_INF;
	unsigned int depth = 1;
	bool cutoff = false;
	pair<int, pair<int, int> > best_move;
	best_move.first = 0;
	best_move.second.first = -1;
	best_move.second.second = -1;

	//starts alphabeta algorithm with player's turn
	//alphabeta generates every move starting with player
	//clock_gettime(CLOCK_REALTIME, &prog_start);
	clock_gettime(CLOCK_REALTIME, &start);
	while (!cutoff) {
		best_move = alphabeta(root, depth, alpha, beta, player, true, start, time_limit, cutoff, m);
		if (!cutoff) {
			r_move = best_move.second;
			//
			//cout << "BEST MOVE:" << r_move.first <<", " <<r_move.second <<" SCORE: " << best_move.first << endl;
			//
			depth+=2;
		}
	}
	//clock_gettime(CLOCK_REALTIME, &prog_end);
	//double time_taken = (prog_end.tv_sec - prog_start.tv_sec)+(prog_end.tv_nsec - prog_start.tv_nsec)/1000000000.0;
	//cout << "TIME AT DEPTH: " << depth <<" " << time_taken << endl;
	//cout << " start.tv_sec " << start.tv_sec << " end " << end.tv_sec << endl;
	//cout << " start.tv_nsec " << start.tv_nsec << " end " << end.tv_nsec << endl;
	//cout <<"  debug: best_move.first.first" << best_move.second.first <<endl;
	return r_move;
}
void mode_one(unsigned int size, const char starting_player, const unsigned int time_limit, const unsigned int m) {
	GameState game_board(size);
	bool player_x = true;
	cin.ignore();
	while (!game_board.game_end) {
		char cur_player;
		if (player_x) {
			cur_player = 'X';
		}
		else{
			cur_player = 'O';
		}
		if (cur_player == starting_player) {
			bool inputs_ok = false;
			int row;
			int column;
			string position;
			cout << "Enter row and column(Ex: 4 5): ";
			getline(cin, position);
			stringstream ss(position);
			string token;
			vector<string> num_store;
			while (getline(ss, token, ' ')) {
				//cout << "TOKEN: "<<token << endl;
				num_store.push_back(token);
			}
			if (num_store.size() == 2) {
				istringstream (num_store[0]) >> row;
				istringstream (num_store[1]) >> column;
				inputs_ok = true;
				//cout << "ROW COLOUMN: "<< row << ", " << column << endl;
			}
			while (num_store.size() != 2 || !inputs_ok) {
				num_store.clear();
				cout << "Enter row and column(Ex: 4 5): ";
				getline(cin, position);
				stringstream ss(position);
				string token;
				while (getline(ss, token, ' ')) {
					num_store.push_back(token);
				}
				if (num_store.size() == 2) {
					istringstream (num_store[0]) >> row;
					istringstream (num_store[1]) >> column;
					//cout << "ROW COLOUMN: "<< row << ", " << column << endl;
					inputs_ok = true;
				}
			}
			game_board = player_gen_move(game_board, cur_player, row, column);
		}
		else {
			pair<int, int> results = itr_deep_minimax(game_board, cur_player, time_limit, m);
			game_board = player_gen_move(game_board, cur_player, results.first, results.second);
		}
		game_board = heuristics_func(game_board, m, cur_player);
		print_board(game_board);
		cout << cur_player << "'s move: " << game_board.last_row << " " << game_board.last_column << endl;
		player_x = !player_x;
	}
}
void mode_two(unsigned int size, const char random_player, const unsigned int time_limit, const unsigned int m){
	GameState game_board(size);
	bool player_x = true;
	while (!game_board.game_end) {
		char cur_player;
		if (player_x) {
			cur_player = 'X';
		}
		else{
			cur_player = 'O';
		}
		//random moves require no minimax algorithm
		if (cur_player == random_player)
			game_board = random_gen_move(game_board, cur_player);
		else {
			pair<int, int> results = itr_deep_minimax(game_board, cur_player, time_limit, m);
			game_board = player_gen_move(game_board, cur_player, results.first, results.second);
		}
		game_board = heuristics_func(game_board, m, cur_player);
		print_board(game_board);
		cout << cur_player << "'s move: " << game_board.last_row << " " << game_board.last_column << endl;
		player_x = !player_x;
	}
}
void mode_three(unsigned int size, const unsigned int time_limit, const unsigned int m){
	GameState game_board(size);
	bool player_x = true;
	while (!game_board.game_end) {
		char cur_player;
		if (player_x) {
			cur_player = 'X';
		}
		else{
			cur_player = 'O';
		}
		pair<int, int> results = itr_deep_minimax(game_board, cur_player, time_limit, m);
		game_board = player_gen_move(game_board, cur_player, results.first, results.second);
		game_board = heuristics_func(game_board, m, cur_player);
		print_board(game_board);

		cout << cur_player << "'s move: " << results.first << " " << results.second << endl;
		player_x = !player_x;
	}
}

int main() {
	srand(time(NULL));
	bool menu_ok = false;
	unsigned int m = 3; //has to be atleast 3, problem =  if M is variable, cant use same tactics as normal gomoku, without limiting m
	unsigned int size = 15;
	//char random_player = 'X';
	const unsigned int time_l = 10;
	int game_mode;
	int board_size;
	int time_limit;
	int matching_row;

	cout << "Enter board size(min " << MIN_BOARD_LIMIT
	          << " , max " << MAX_BOARD_LIMIT << "): ";
	cin >> board_size;
	while (cin.fail() || board_size < MIN_BOARD_LIMIT || board_size > MAX_BOARD_LIMIT) {
		cin.clear();
		cin.ignore();
		cout << "Enter board size(min " << MIN_BOARD_LIMIT
		          << " , max " << MAX_BOARD_LIMIT << "): ";
		cin >> board_size;
	}

	cout << "Enter time limit(seconds): ";
	cin >> time_limit;
	while (cin.fail() || time_limit < 1) {
		cin.clear();
		cin.ignore();
		cout << "Time limit must be >= 1. Enter time limit(seconds): ";
		cin >> time_limit;
	}

	cout << "Enter # of pieces in a row to match(min " << MIN_BOARD_LIMIT << "): ";
	cin >> matching_row;
	while (cin.fail() || matching_row < MIN_BOARD_LIMIT) {
		cin.clear();
		cin.ignore();
		cout << "Enter # of pieces in a row to match(min " << MIN_BOARD_LIMIT << "): ";
		cin >> matching_row;
	}

	cout << "Game board parameters: size = " << board_size << ", time limit = "
	          << time_limit << ", m = " << matching_row << endl;
	cout << "Program mode menu:\n"
	          << " 1) Human vs Agent\n"
	          << " 2) Random moves vs Agent\n"
	          << " 3) Agent vs Agent\n"
	          << endl;
	cout << "Enter a mode: ";
	cin >> game_mode;
	if (!cin.fail()) {
		if (game_mode == 1 || game_mode == 2 || game_mode == 3)
			menu_ok = true;
	}
	while (cin.fail() || !menu_ok) {
		cin.clear();
		cin.ignore();
		cout << "Invalid menu choice. Enter a mode: ";
		cin >> game_mode;
		if (!cin.fail()) {
			if (game_mode == 1 || game_mode == 2 || game_mode == 3)
				menu_ok = true;
			}
	}
	Fl_Window *window = new Fl_Window (board_size*BOX_SIZE,board_size*BOX_SIZE,"GOMOKU");
	window->color(56);
	window->end(); 
   	window->show();
	//Board *b = new Board(board_size, window);

	//execute mode choices after a valid mode choice
	if (game_mode == 1) {
		bool m1_ok = false;
		char starting_player;
		cout << "Mode 1 choosen.  Enter choice for human player(X or O): ";
		cin >> starting_player;
		if (!cin.fail()) {
			if (starting_player == 'X' || 'O')
				m1_ok = true;
			else if (starting_player == 'x') {
				starting_player = 'X';
				m1_ok = true;
			}
			else if (starting_player == 'o') {
				starting_player = 'O';
				m1_ok = true;
			}
		}
		while (cin.fail() || !m1_ok) {
			cin.clear();
			cin.ignore();
			cout << "Mode 1 choosen.  Enter choice for human player(X or O): ";
			cin >> starting_player;
			if (!cin.fail()) {
				if (starting_player == 'X' || 'O')
					m1_ok = true;
				else if (starting_player == 'x') {
					starting_player = 'X';
					m1_ok = true;
				}
				else if (starting_player == 'o') {
					starting_player = 'O';
					m1_ok = true;
				}
			}
		}
		mode_one(board_size, starting_player, time_limit, matching_row);
	}
	else if (game_mode == 2) {
		bool m2_ok = false;
		char random_player;
		cout << "Mode 2 choosen.  Enter choice for random player(X or O): ";
		cin >> random_player;
		if (!cin.fail()) {
			if (random_player == 'X' || 'O')
				m2_ok = true;
			else if (random_player == 'x') {
				random_player = 'X';
				m2_ok = true;
			}
			else if (random_player == 'o') {
				random_player = 'O';
				m2_ok = true;
			}
		}
		while (cin.fail() || !m2_ok) {
			cin.clear();
			cin.ignore();
			cout << "Mode 2 choosen.  Enter choice for random player(X or O): ";
			cin >> random_player;
			if (!cin.fail()) {
				if (random_player == 'X' || 'O')
					m2_ok = true;
				else if (random_player == 'x') {
					random_player = 'X';
					m2_ok = true;
				}
				else if (random_player == 'o') {
					random_player = 'O';
					m2_ok = true;
				}
			}
		}
		mode_two(board_size, random_player, time_limit, matching_row);
	}
	else if (game_mode == 3) {
		cout << "Mode 3 choosen." << endl;

		Fl::run();
		Fl::unlock();
		cout<<"kjh";
		mode_three(board_size, time_limit, matching_row);
	}
	else
		cout << "ERROR" << endl;
	return 0;
}
