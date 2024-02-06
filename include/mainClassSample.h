#pragma once

#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <memory>

#define PRINT_CMD(x) (std::cout << x << std::endl)

namespace APP{
template<typename T>
class FirstGraphics{
public:
    explicit FirstGraphics(void);
    explicit FirstGraphics(T width, T height);
    ~FirstGraphics(void) noexcept;
    void process(void);
    bool loadMedia(void);
    bool init(void);
    //Load individual images
    std::shared_ptr<SDL_Surface> loadSurface(void);


protected:
    //screen dimension constant
    T screen_width;
    T screen_height;
    T delay;

    //The window we'll be rendering to
    std::shared_ptr<SDL_Window> window; 

     //The surface contained by the window
    std::shared_ptr<SDL_Surface> screenSurface; 
    
    //Event happens
    SDL_Event  event;

    //The image we will load and show on the screen
    std::shared_ptr<SDL_Surface> PNGSurface;

    //Init, loading flags
    bool isInitSuccess;
    bool isLoadSuccess;

    std::string path;


};

// Custom deleter for SDL_Surface
struct SDLSurfaceDeleter {
    void operator()(SDL_Surface* surface) const {
        SDL_FreeSurface(surface);
    }
};
}
