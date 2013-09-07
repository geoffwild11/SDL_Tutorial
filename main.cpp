#include "SDL/SDL.h"
#include <string>

using namespace std;

//Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//Function Prototypes
SDL_Surface* setScreen();
bool Init();

int main( int argc, char* args[] )
{
	/*
	//The images
	    SDL_Surface* hello = NULL;
	    SDL_Surface* screen = NULL;
	*/

	//Set environment
	//Initialize all SDL subsystems
    if(!Init())
    {
        return 1;
    }
	SDL_Surface* screen = setScreen();
	SDL_Surface* message = NULL;
	SDL_Surface* background = NULL;


	//Init(screen);

    //Load image
    message = SDL_LoadBMP( "hello.bmp" );

    //Apply image to screen
    SDL_BlitSurface( message, NULL, screen, NULL );

    //Update Screen
    SDL_Flip( screen );

    //Pause
    SDL_Delay( 4000 );

    //Free the loaded image
    SDL_FreeSurface( message );

    //Quit SDL
    SDL_Quit();

    return 0;
}

SDL_Surface* setScreen()
{
	return SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
}

bool Init()
{
	 //Initialize all SDL subsystems
	    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
	    {
	        return false;
	    }

	    else
	    	return true;
}
