#include <SDL.h>
#include <stdio.h>
//Screens Dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
  //The Windown we'll be rendering to
  SDL_Window* window = NULL;
  //The Surface contained by the window
  SDL_Surface* screenSurface = NULL;
  //Initialize SDL
  if(SDL_Init( SDL_INIT_VIDEO) < 0)
    {
      printf("SDL could not initialize! SDL_ERROR: %s\n", SDL_GetError()); 
    }
  else
    {
      //create Window
      window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
      if(window == NULL)
	{
	  printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
	}
      else
	{
	  //Get Window Surface
	  screenSurface = SDL_GetWindowSurface(window);
	  //Fill the surface white
	  SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	  //Update the Surface
	  SDL_UpdateWindowSurface(window);
	  //Wait two seconds
	  SDL_Delay(2000);
	  //Destroy window
	}
      
    }
  //Destroy window
  SDL_DestroyWindow(window);
  //Quit SDL subsystems
  SDL_Quit();
  return 0;
  
}