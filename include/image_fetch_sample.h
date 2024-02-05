#ifndef _IMAGE_FETCH_
#define _IMAGE_FETCH_

#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <memory>
#include "mainClassSample.h"

namespace ImageApp{

template<typename T>
class Imagefetch : public APP::FirstGraphics<T>
{
public:
    Imagefetch();
    Imagefetch(T width, T height);
    ~Imagefetch() noexcept;

    // Load media from the path
    void loadMedia(std::string &path);
    std::shared_ptr<SDL_Surface> loadSurface(const std::string &path);
    void process(void);
    void updateSurface();


private:
    //Current displayed PNG image
    std::shared_ptr<SDL_Surface> pngSurface;    

};

}

#endif
