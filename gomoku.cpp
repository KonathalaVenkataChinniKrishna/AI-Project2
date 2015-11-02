#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "stdio.h"
#include <ctime>
#include <math.h>
#include <sstream>

 
using namespace std;

static const int tilesize = 50;
static const int xmaxtiles= 19;
static const int ymaxtiles= 19;
static const int bgcolor=66;
static const double timeout=0.3;
 
class Player
{
public:
    string name;
    char mark;
    Player(string name, char mark)
    {
        this->name=name;
        this->mark=mark;
    }
 
        char getMark()
        {
            return mark;
        }
        string getName()
        {
            return name;
        }
 
};
class Board ;
void timeoutAction(void *p);

class Board : public Fl_Widget{
	
	int occup[xmaxtiles][ymaxtiles]; 
	//ActivePiece * p;
	int score;
	int color;
	bool gameend,display;
	char* scoreLabel; 
	Fl_Box *scoreBox;
	
	public:
	
	Board():Fl_Widget (0,0,xmaxtiles*tilesize,
			ymaxtiles*tilesize,"timer")
	{
	    gameend = 0 ;display=0;
		//p = new ActivePiece (this);	
		for (int i = 0 ; i < xmaxtiles ; i ++ )
		for (int j = 0 ;  j < ymaxtiles ; j ++ )
		occup[i][j] = bgcolor;
			
	}
	void setScoreBox(Fl_Box** sb)
	{
		scoreBox = *sb ;
		score=0;
		scoreLabel = (char*) malloc(sizeof(char)*10);
	}
	int timing() 
	{
		//updatescore();
		//redraw();
		Fl::repeat_timeout (timeout,timeoutAction,this);
	}
	
	void draw()
	{
		for (int i=0; i<xmaxtiles;i++)
		for (int j=0; j<ymaxtiles;j++)
			fl_draw_box(FL_BORDER_BOX,i*tilesize,j*tilesize,
				tilesize,tilesize,occup[i][j]);
				
			if(!gameend)
			{
				/*for (int i = 0 ; i < 4 ; i++)
				{
					fl_draw_box(FL_BORDER_BOX,p->tileSet[i].x*tilesize,p->tileSet[i].y*tilesize,
							tilesize,tilesize,p->color);
				}
			
				/*if(moveDown()){}
				else 
				{
					transferTiles(p->tileSet,p->color);
					deleteRow();
					//p = new ActivePiece (this);
					if (!freepiece (p->tileSet))gameend=1;
				}*/	
			
			}
			else 
			{
                  if (!display){
					cout<<"Game Ends"<<endl;
					cout<<"Score: "<<score <<endl;
					display=1;
				  }
			}
		}
		int handle(int e){
		if (e==8) // means it's a keyboard event
			switch (Fl::event_key()) { 
				case 65361 : moveLeft(); break;
				case 65362 : rotate(0);break;
				case 32 : fullDown(); break; 
				case 65363 : moveRight(); break;
				case 65364 : rotate(1); break;
			}				
	}
};
 
class Boarding
{
    
    public:
    Player *currentPlayer;
    char **board;
    int size;
    static const int nWin=5; //number of piecies to win (2,3,4..ecc)
 
        Boarding(int n, Player *beginningPlayer)
        {
            size=n;
            board=new char *[size];
            for( int i = 0 ; i < size ; i++ )
                board[i]= new char[size];
            for(int i=0;i<size;i++)
                for(int k=0;k<size;k++)
                    board[i][k]='_';
            currentPlayer=beginningPlayer;
        }
 
        void printBoard()
        {
            cout<<" \t";
            for(int i=0;i<size;i++)
               cout<<i+1<<"\t";
            cout<<"\n";
            for(int i=0;i<size;i++)
            {
                cout<<i+1<<"\t";
                for(int k=0;k<size;k++)
                    cout<<board[i][k]<<"\t";
                cout<<"\n\n";
            }
        }
 
        bool checkPosition(int row, int col)
        {
            if(row>=size || row<0 || col>=size || col <0)
               return false; 
            if(board[row][col]=='_')
                return true;
            else
                return false;
        }
 
        bool updateBoard(int r, int c)
        {
            if(checkPosition(r,c))
                board[r][c]=currentPlayer->getMark();
            else
                return false;
            return true;
        }
        
        
        bool checkWinner()
        {
           int playerCount, r, c, x,y;
            // Check Orizontal --OK
                for (r = 0; r < size; r++)
                {
                   playerCount = 0;
                   for (c = 0; c < size; c++)
                   {
                       if (board[r][c] != currentPlayer->getMark()) 
                          playerCount = 0;
                       if (board[r][c] == currentPlayer->getMark())
                          playerCount += 1;
                       if(playerCount>=nWin)
                         return true;
                   }
                }
                
                //Check Vertical --OK
                for(c=0;c<size;c++)
                {
                   playerCount = 0;
                   for (r = 0; r < size; r++)
                   {
                       if (board[r][c] == '_')
                          playerCount = 0;
                       if (board[r][c] == currentPlayer->getMark())
                          playerCount += 1;
                       if(playerCount>=nWin)
                         return true;
                   }
                   
                }
                
                //check oblique 1
                for(x=size,y=0;x>0;x--,y++)
                {
                   playerCount=0;
                   for(r=y,c=0;c<x;r++,c++)
                   {
                       if (board[r][c] == '_')
                          playerCount = 0;
                       if (board[r][c] == currentPlayer->getMark())
                          playerCount += 1;
                       if(playerCount>=nWin)
                         return true;
                   }
                }
                // check oblique 2
                for(x=size,y=0;x>0;x--,y++)
                {
                   playerCount=0;
                   for(r=0,c=y;c<x;r++,c++)
                   {
                       if (board[r][c] == '_')
                          playerCount = 0;
                       if (board[r][c] == currentPlayer->getMark())
                          playerCount += 1;
                       if(playerCount>=nWin)
                         return true;
                   }
                }
                // If nobody won
                return false;
                           
        }
 


};

void timeoutAction(void *p)
{
	((Board *)p)->timing();
}

int main(int argc, char *argv[])
{
    int row, column;
    bool control=true;
    bool winner;
    Player *human=new Player("MARCO", 'H');
    Player *computer=new Player("KASIA",'C');
    Boarding *board=new Boarding(9,human);
    
    /*WELCOME PAGE
    cout<<"*****************************************\n";
    cout<<"*****************************************\n";
    cout<<"****  GOMOKU BETA - MARCO MANZALINI  ****\n";
    cout<<"*                                       *\n";
    cout<<"--NUMBERS OF PIECIES TO WIN:"<<"  "<<board->nWin<<"  \n";
    cout<<"*                                       *\n";
    cout<<"PRESS A BUTTON TO CONTINUE\n";
    getchar();
    system("CLS");
    END WELCOME PAGE*/
    
    Fl_Window *window = new Fl_Window (950,950,"GOMOKU");
	window->color(56);
	Board *b = new Board();
	  /*   Fl_Box *scorebox = new Fl_Box(tilesize*xmaxtiles+10,50,180,200,"Score: 0\0");
	scorebox->box(FL_UP_BOX);
        scorebox->labelfont(FL_BOLD+FL_ITALIC);
        scorebox->labelsize(34);
	b->setScoreBox(&scorebox);*/ 
	window->end(); 
   	window->show();
	Fl::add_timeout(0.1, timeoutAction,b);
	int a=event_x();
	int c=event_y();
	cout<<a<<" "<<b<<endl
    return(Fl::run());
    
    do
    {
        do
        {
          board->printBoard();
          cout<<"Player:  " << board->currentPlayer->getName() <<"\n";
          cout<<"Insert row:     ";
          cin>> row;
          cout<<"Insert column:  ";
          cin>>column;
          system("CLS");
          control=board->updateBoard(row-1, column-1);
        }
        while(!control);  
        winner=board->checkWinner();
        if(!winner)
        {
          if(board->currentPlayer==human)
            board->currentPlayer=computer;
          else
            board->currentPlayer=human;
        }
    }
    while(!winner);
    board->printBoard();
    cout<<"\n\nThe winner is: "<<board->currentPlayer->getName()<<endl;
    return 1;
    
    //problems with devcpp
    cin>>row;
}
