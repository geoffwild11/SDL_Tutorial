#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include <iostream>

using namespace std;

//Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const char* MAIN_FONT = "TechnoHideo.ttf";

//Function Prototypes
bool Init(SDL_Surface* &screen);
SDL_Surface* loadImage(string filename);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip );
bool loadFile(SDL_Surface* &image, string fileName);
bool loadFont(TTF_Font* &font);

bool update(SDL_Surface* screen);
void cleanUp();

int main( int argc, char* args[] )
{

	SDL_Surface* screen = NULL;
	SDL_Surface* dots = NULL;
	SDL_Surface* message = NULL;
	bool quit = false;
	SDL_Event event;

	//map to be blitted
	SDL_Rect clip[4];

	TTF_Font* font = NULL;

	SDL_Color textColor = { 255, 0, 255 };

	//Set environment
    if(!Init(screen))
        return 1;

    //Load the files
    if (!loadFile(dots, "sprite.png"))
    	return 1;

    if ( !loadFont( font ) )
    	return 1;

    //Clip range for the top left
       clip[ 0 ].x = 0;
       clip[ 0 ].y = 0;
       clip[ 0 ].w = 100;
       clip[ 0 ].h = 100;

       //Clip range for the top right
       clip[ 1 ].x = 100;
       clip[ 1 ].y = 0;
       clip[ 1 ].w = 100;
       clip[ 1 ].h = 100;

       //Clip range for the bottom left
       clip[ 2 ].x = 0;
       clip[ 2 ].y = 100;
       clip[ 2 ].w = 100;
       clip[ 2 ].h = 100;

       //Clip range for the bottom right
       clip[ 3 ].x = 100;
       clip[ 3 ].y = 100;
       clip[ 3 ].w = 100;
       clip[ 3 ].h = 100;

       //Fill the screen white
       SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );

       //Set some text
       message = TTF_RenderText_Solid( font, "This is my text", textColor);


    //Apply the message to the screen
     apply_surface( 0, 0, dots, screen, &clip[2] );
     apply_surface( 0, 380, dots, screen, &clip[1] );
     apply_surface( 540, 380, dots, screen, &clip[0] );
     apply_surface( 540, 0, dots, screen, &clip[3] );
     apply_surface( 300, 240, message, screen, NULL);
     //apply_surface( 180, 300, image2, screen);

    //Update Screen
     if (!update(screen))
    	 return 1;

     while (!quit)
     {
    	 //While there's an event to handle
    	 while( SDL_PollEvent( &event ) )
    	 {
    		 //If the user has Xed out the window
    		 if( event.type == SDL_QUIT )
             {
    			 //Quit the program
                quit = true;
             }
    	 }
     }

    //Free the surfaces
    SDL_FreeSurface( dots );
    TTF_CloseFont( font );
    //SDL_FreeSurface( background );

    cleanUp();

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

	if ( TTF_Init() == -1)
	{
		cout << "TTF failed to initialize" << endl;
		return false;
	}

	//Set the window caption
	SDL_WM_SetCaption( "TTF Test", NULL );

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

    //If the image was optimized just fine
    if( optimizedImage != NULL )
    {
    	//Map the color key
    	Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
    	SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
    }

    //Return the optimized image
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
	//Holds offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

    //Blit
	SDL_BlitSurface( source, clip, destination, &offset );
}
/* old apply_surface()
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
*/

bool loadFile(SDL_Surface* &image, string fileName)
{
	image = loadImage(fileName);

	if (image == NULL)
		return false;
	else
		return true;
}

bool loadFont( TTF_Font* &font )
{
	font = TTF_OpenFont( MAIN_FONT, 20 );

	if ( font == NULL )
	{
		cout << "Font failed to load" << endl;
		return false;
	}

	return true;
}

bool update(SDL_Surface* screen)
{
	//Update the screen
	if( SDL_Flip( screen ) == -1 )
	{
		return false;
	}

	else
		return true;
}

void cleanUp()
{
	TTF_Quit();
	SDL_Quit();
}
