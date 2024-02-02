#pragma once

#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <memory>

namespace APP{
class FirstGraphics{
public:
    explicit FirstGraphics(void);
    ~FirstGraphics(void) noexcept;
    void process(void);


private:
    //screen dimension constant
    int screen_width;
    int screen_height;

    //The window we'll be rendering to
    std::shared_ptr<SDL_Window> window; 

     //The surface contained by the window
    std::shared_ptr<SDL_Surface> screenSurface; 

};
}