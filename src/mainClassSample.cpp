#include <stdio.h> /* printf and fprintf */
#include <iostream>
#include "mainClassSample.h"

// Custom deleter for SDL_Surface
struct SDLSurfaceDeleter {
    void operator()(SDL_Surface* surface) const {
        SDL_FreeSurface(surface);
    }
};

template <typename T>
APP::FirstGraphics<T>::FirstGraphics(void):
    screen_width(640),
    screen_height(480),
    delay(2000),
    window(nullptr),
    screenSurface(nullptr){
        std::cout << "Constructor called" << std::endl;
}

template <typename T>
void APP::FirstGraphics<T>::process(void){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "SDL could not initialize! SDL_Error: "
        << SDL_GetError() << std::endl;
    }else{

        // window = std::make_shared<SDL_Window>(tempWindow, SDL_DestroyWindow);  //ERROR

        window  = std::shared_ptr<SDL_Window>(SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN ), SDL_DestroyWindow);

        if(window == nullptr){
            std::cerr << "Window could not be created! SDL_Error: "
                 << SDL_GetError() << std::endl;
        }else{
            //Get window surface
            screenSurface =std::shared_ptr<SDL_Surface>(SDL_GetWindowSurface( window.get()), SDLSurfaceDeleter{});

            //Fill the surface white
			SDL_FillRect( screenSurface.get(), nullptr, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

            //Update the surface
			SDL_UpdateWindowSurface( window.get() );

            //Hack to get window to stay up
            // SDL_Event e; 
            // bool quit = false; 
            // while( quit == false ){ 
            //     while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }

            //Add delay
            SDL_Delay(delay);
		}
	}
            
}

template <typename T>
APP::FirstGraphics<T>::~FirstGraphics(void) noexcept{
    //Destroy window
	// SDL_DestroyWindow( window.get() );

	// //Quit SDL subsystems
	// SDL_Quit();
}


int main(int argc, char  **argv)
{
    APP::FirstGraphics<int> myObj;

    myObj.process();

    return 0;
}

