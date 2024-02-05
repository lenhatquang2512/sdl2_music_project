#pragma once

#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <memory>

namespace APP{
template<typename T>
class FirstGraphics{
public:
    explicit FirstGraphics(void);
    FirstGraphics(T, T);
    ~FirstGraphics(void) noexcept;
    void process(void);


protected:
    //screen dimension constant
    T screen_width;
    T screen_height;
    T delay;

    //The window we'll be rendering to
    std::shared_ptr<SDL_Window> window; 

     //The surface contained by the window
    std::shared_ptr<SDL_Surface> screenSurface; 

};

// Custom deleter for SDL_Surface
struct SDLSurfaceDeleter {
    void operator()(SDL_Surface* surface) const {
        SDL_FreeSurface(surface);
    }
};
}
