#pragma once

#include "sdl2Interface.h"
#include <string>
#include <memory>

namespace APP
{
template<typename T>
class Imagefetch : public APP::FirstGraphics<T>
{
public:
    Imagefetch();
    Imagefetch(T width, T height);
    ~Imagefetch() noexcept;

    // Load media from the path
    void loadMedia(std::string &path);
    void process(void);

private:
    //Current displayed PNG image
    std::shared_ptr<SDL_Surface> pngSurface;    

};

};