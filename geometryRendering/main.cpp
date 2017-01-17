#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

//Screens Dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


//Loads individual image as a texture
SDL_Texture* loadTexture(std::string path);
//Start up SDL and create a window
bool init();
//Loads media
bool loadMedia();
//Frees media and shut down SDL
void close();


//The Window we will be rendering to
SDL_Window* gWindow = nullptr;
//The Window Renderer
SDL_Renderer* gRenderer = nullptr;
//Current display texture
SDL_Texture* gTexture = nullptr;

int main()
{
    //Start up SDL and create window
    if(!init())
    {

        printf("Failed to initialize!\n");
    }
    else
    {
        //Load media
        if(!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            //Main loop flag
            bool quit = false;
            //Event handler
            SDL_Event e;
            //While application is running
            while(!quit)
            {
                //Handle events on queue
                while(SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if(e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                }
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                //Clear Screen
                SDL_RenderClear(gRenderer);
                //Render red filled quad
                SDL_Rect fillRect = {SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(gRenderer, &fillRect);

                //Render green oulined quad
                SDL_Rect outlineRect = {SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH * 2/3, SCREEN_HEIGHT * 2/3};
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
                SDL_RenderDrawRect(gRenderer, &outlineRect);

                //Draw the blue horizontal line
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
                SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);

                //Draw Vertical line of yellow dots
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
                for (int i = 0; i < SCREEN_HEIGHT; i += 4)
                {
                  SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH/2, i);
                }
                //Render Texture to Screen
                SDL_RenderCopy(gRenderer, gTexture, nullptr, nullptr);
                //Update Screen
                SDL_RenderPresent(gRenderer);
            }
        }
    }
//Free resources and close SDL
    close();
    return 0;
}

bool init()
{
  //Initialization flag
    bool success = true;
    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == nullptr)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            //Create renderer Window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == nullptr)
            {
              printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
              success = false;
            }
            else
            {
              //Initialize renderer color
              SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

              //Initialize PNG loading
              int imgFlags = IMG_INIT_PNG;
              if(!(IMG_Init(imgFlags) & imgFlags))
              {
                printf("SDL Image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                success = false;
              }

            }

        }
    }
    return success;
}
SDL_Texture* loadTexture(std::string path)
{
  //The Final Texture
  SDL_Texture* newTexture = nullptr;
  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if(loadedSurface == nullptr)
  {
    printf("Unable to load image %s! SDL_Image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
    //create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if(newTexture == nullptr)
    {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    //Get rid of old surface
    SDL_FreeSurface(loadedSurface);

  }
  return newTexture;
}
bool loadMedia()
{
  //Loading succes flag
  bool success = true;
  //Nothing to load
  return success;
}
void close()
{
  //Free loaded image
  SDL_DestroyTexture(gTexture);
  gTexture = nullptr;
  //Destroy window
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;
  gRenderer = nullptr;

  //Quit SDL Subsystems
  IMG_Quit();
  SDL_Quit();
}
