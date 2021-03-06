#include <SDL/SDL.h>
#include <iostream>
#include <stdlib.h> 
#include <cmath>
#include <fstream>
#include <ctime>

int map[102][102];
int click[102][102];
int  h , w , bomb , n , m ;
int h1 = 20 , w1 = 20;
bool won = false ;
bool lost = false ;
bool flag = false ;
bool mflag = false ;
SDL_Event e ;

using namespace std;

SDL_Surface *screen ;
SDL_Surface *bmp ;
SDL_Rect rect ;

void dor ( int w , int h )
{
	for ( int i = 0 ; i <= w+1 ; i++ )
	{
		for ( int j = 0 ; j <= h+1 ; j++ )
		{
			if ( i == 0 ) 	map[i][j] = 99 ;
			if ( i == w+2 ) map[i][j] = 99 ;
			if ( i == 0 ) 	map[i][j] = 99 ;
			if ( i == h+2 ) map[i][j] = 99 ;
		}
	}	
}

void clearall( int w , int h )
{
	for ( int i = 0 ; i <= w+1 ; i++ )
	{
		for ( int j = 0 ; j <= h+1 ; j++ )
		{
			map [i][j] = 0 ;
			click [i][j] = 0 ;
		}
	}
	return ;	
}

void inputmap ( int w , int h )
{
	for ( int k = 1 ; k <= bomb ; k++ )
	{
		int x ;
		int y ;
		do
		{
			x = rand() % w + 1 ;
			y = rand() % h + 1 ;
		}
		while ( map[x][y] == 9 );
		map[x][y] = 9 ;
		//////////
		for ( int i = x-1 ; i <= x+1 ; i++ )
		{
			for ( int j = y-1 ; j <= y+1 ; j++ )
			{
				if ( map[i][j] != 99 ) 
				{
					if ( map[i][j] != 9 ) map[i][j]++ ; 
				}
			}
		}
	}
}

void draw( int w , int h )
{
	SDL_Rect rect ;
	char s[100];
	for ( int j= 1 ; j <= h+1 ; j++ )
	{
		for ( int i = 1 ; i <= w+1  ; i++ )
		{
			rect.x = (i-1) * 20 ;
			rect.y = (j-1) * 20 ;
			rect.w = 20 ;
			rect.h = 20 ;
			if ( click[i][j] == 0 ) sprintf ( s , "%d.bmp" , 10 );
			if ( click[i][j] == 1 ) sprintf ( s , "%d.bmp" , map[i][j] );
			if ( click[i][j] == 2 ) sprintf ( s , "%d.bmp" , 11 );
			bmp = SDL_LoadBMP(s);
			SDL_BlitSurface( bmp , NULL , screen , &rect );	
		}
	}
}

void Finish ( int w , int h )
{
	for ( int j = 1 ; j <= h+1 ; j++ )
	{
		for ( int i = 1 ; i <= w+1; i++ )
	        {
			if ( click[i][j] == 0 ) click[i][j] = 1 ;
			if ( won == true )
			{
				if ( map[i][j] == 9 ) map[i][j] = 20 ;
			}
			if ( lost == true )
			{
				if ( click[i][j] == 2 )
				{
					if ( map[i][j] == 9 ) map[i][j] = 11 ;
					if ( map[i][j] < 9 ) 
					{
						map[i][j] = 40 ;
						click[i][j] = 1 ;
					}					
				}
				
			}	
		}
	}	
}

void Winner ( int w , int h , int bomb )
{
	int n ;
	for ( int i = 1 ; i <= w+1 ; i++ )
	{
		for ( int j = 1 ; j <= h+1 ; j++ )
		{
			if ( click[i][j] == 1 ) n++ ;
		}
	}
	if ( (w*h)-n == bomb ) 
	{
		won = true ;
	}
	n = 0 ;		
}

void OIO ( int x , int y )
{
	click[x][y] = 1 ;
     	for ( int i = x-1 ; i <= x+1 ; i++ )
	{
		for ( int j = y-1 ; j <= y+1 ; j++ )
		{
			if ( i > 0 && i < w+1 && j > 0 && j < h+1 ) 
			{
				if (click[i][j] == 0 && map[i][j] != 9 )
				{
					click[i][j] = 1 ;
					draw ( i , j );
					if ( map[i][j] == 0 ) OIO ( i , j );
				}
				if ( click[i][j] == 2 && mflag == true )
				{
					click[i][j] = 2 ;
					draw ( i , j );
					if ( map[i][j] == 0 ) OIO ( i , j );
				}	
			}
		}
	}   
}


int main()
{

ifstream cin ("i.txt");

	cin >> w ;
	cin >> h ;
	cin >> bomb ;
	
cin.close();
	
srand( time(NULL) );
SDL_Init(SDL_INIT_EVERYTHING);
screen = SDL_SetVideoMode(w*20,h*20,32,SDL_SWSURFACE);
unsigned char * data = (unsigned char *) screen -> pixels ;

	
	bool finish = false ;
	int x , y , a ;
	char s[100];
	int picturename ;
	
		clearall ( w , h );
		dor ( w , h );
		inputmap ( w , h );

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
		for ( int i = 0 ; i <= w ; i++ )
		{
			for ( int j = 0 ; j <= h ; j++ )
		  	{		
				rect.x = i * w1 ;
				rect.y = j * h1 ;
				rect.w = w1 ;
				rect.h = h1 ;
				sprintf( s , "%d.bmp" , 10 );
				bmp = SDL_LoadBMP(s);
				SDL_BlitSurface( bmp , NULL , screen , &rect );
			}
		}
		SDL_Flip(screen);
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////


		while ( !finish )
		{
			if (SDL_PollEvent( &e ))  if ( e.type == SDL_QUIT )  finish = true ;		
			if ( e.type == SDL_MOUSEBUTTONDOWN )
			{
				SDL_GetMouseState( &x , &y );
				x /= w1 ;
				y /= h1 ;
				rect.x = x * w1 ;
				rect.y = y * h1;
				rect.w = w1 ;
				rect.h = h1 ;
		                x++ ;
		                y++ ;
				                if ( e.button.button == SDL_BUTTON_LEFT)
				                {

				                //////////
					                if ( map[x][y] == 0 && click[x][y] == 0 ) 
					                {
						                OIO ( x , y );
						                SDL_Flip( screen );
					                }
				                //////////
					                if ( click[x][y] == 0)
					                {
						                click[x][y] = 1 ;
					                }
				                //////////
					                if ( map[x][y] == 9 && click[x][y] != 2 ) 
					                {	
						                finish = true ;
						                lost = true ;
						                map[x][y] = 30 ;
						                cout << "YOU LOST" << endl ;
					                } 
				                //////////
					                if ( map[x][y] != 9 ) Winner( w , h , bomb ); 
					                if ( won == true ) 
					                {	
						                finish = true ;			
						                cout << "YOU WON" << endl ;
					                }
				                //////////
					                if ( finish == true )
					                {       
								Finish ( w , h );
						                draw ( w , h );
		                                                SDL_Flip(screen);
					                }
				                //////////
		                                }
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\\//                                     
		                                if ( e.button.button == SDL_BUTTON_RIGHT && flag == false )
		                                {
		                                	if ( flag != true && click[x][y] == 2 ) 
		                                	{
		                               			click[x][y] = 0 ;
		                               			flag = true ;
		                              		}
		                               		if ( flag != true && click[x][y] == 0 ) 
		                               		{
		                               			click[x][y] = 2 ;
		                               			flag = true ;
		                               		}
				     		}
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\// 		             	
				     		if ( e.button.button == SDL_BUTTON_MIDDLE && click[x][y] == 1 )
				     		{
				     			for ( int i = x-1 ; i <= x+1 ; i++ )
				     			{
				     				for ( int j = y-1 ; j <= y+1 ; j++ )
				     				{
				     					if ( click[i][j] == 2 ) n++ ;
				     					if ( click[i][j] == 2 && map[i][j] < 9 ) m++ ;
				     				}
				     			}
				     			if ( map[x][y] < n )
				     			{
				     				if ( m != 0 )
					                	{
					                		lost = true ;
					                		finish = true ;
					                		cout << "YOU LOST" << endl ; 
					                		Finish ( w , h );
						                	draw ( w , h );	
					                	}
				     			}
				     			
				     			if ( map[x][y] == n ) 
				     			{	
				     				mflag = true ;
				     				if ( m != 0 )
					                	{
					                		lost = true ;
					                		finish = true ;
					                		cout << "YOU LOST" << endl ; 
					                		Finish ( w , h );
						                	draw ( w , h );	
					                	}
				     				OIO ( x , y );
				     				Winner ( w , h , bomb );
				 				if ( won == true ) 
					                	{	
						                	finish = true ;			
						                	cout << "YOU WON" << endl ;
						                	Finish ( w , h );
						                	draw ( w , h );
					                	}
					                	
				     			}
				     			n = 0 ;
				     			m = 0 ;
				     		} 
	//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\//
				     		//////////
		                                draw ( w , h );
		                                SDL_Flip( screen );
		        }
		        if ( e.button.button != SDL_BUTTON_RIGHT ) flag = false ;
		}
	SDL_Delay(2500);
	return 0 ;	
}


