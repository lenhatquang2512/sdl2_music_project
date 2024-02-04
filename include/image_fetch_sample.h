#ifndef _IMAGE_FETCH_
#define _IMAGE_FETCH_

#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>
#include <memory>

namespace ImageApp{
template <typename T>
class FirstGraphics{
public:
    FirstGraphics();
    FirstGraphics(T width, T height);
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

template<typename T>
class Imagefetch : public ImageApp::FirstGraphics<T>
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
