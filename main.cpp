#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>

using namespace std;

//Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

//Function Prototypes
bool Init(SDL_Surface* &screen);
SDL_Surface* loadImage(string filename);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );

int main( int argc, char* args[] )
{
	SDL_Surface* screen = NULL;
	SDL_Surface* message = NULL;
	SDL_Surface* background = NULL;

	//Set environment
    if(!Init(screen))
        return 1;

    message = loadImage("hello.bmp");
    background = loadImage("background.bmp");

    apply_surface( 0, 0, background, screen );
    apply_surface( 320, 0, background, screen );
    apply_surface( 0, 240, background, screen );
    apply_surface( 320, 240, background, screen );

    //Apply the message to the screen
     apply_surface( 180, 140, message, screen );

    /*//Load image
    message = SDL_LoadBMP( "hello.bmp" );*/

    //Apply image to screen
    //SDL_BlitSurface( message, NULL, screen, NULL );

     //Update the screen
     if( SDL_Flip( screen ) == -1 )
     {
    	 return 1;
     }

    //Update Screen
    //SDL_Flip( screen );

    //Pause
    SDL_Delay( 2000 );

    //Free the surfaces
    SDL_FreeSurface( message );
    SDL_FreeSurface( background );

    //Quit SDL
    SDL_Quit();

    return 0;
}

bool Init(SDL_Surface* &screen)
{
	//Initialize all SDL subsystems
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
        return false;

	screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

		if (screen == NULL)
			return false;
	//Set the window caption
	SDL_WM_SetCaption( "Hello World", NULL );

	return true;
}

SDL_Surface* loadImage(string filename)
{
	//Temporary storage for the image that's loaded
	SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

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
