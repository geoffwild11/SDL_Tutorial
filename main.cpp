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
SDL_Surface* loadImage(string filename);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );

int main( int argc, char* args[] )
{
	//Set environment
    if(!Init())
        return 1;

	SDL_Surface* screen = setScreen();
	SDL_Surface* message = NULL;
	SDL_Surface* background = NULL;


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
        return false;

	else
		return true;
}

SDL_Surface* loadImage(string filename)
{
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = SDL_LoadBMP( filename.c_str() );

    //If nothing went wrong in loading the image
    if( loadedImage != NULL )
    {
    	//Create an optimized image
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old image
        SDL_FreeSurface( loadedImage );
    }

    //Return the optimized image
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect offset;

    //Give the offsets to the rectangle
    offset.x = x;
    offset.y = y;

    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}
