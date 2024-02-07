#pragma once

#include <SDL2/SDL.h> /* macOS- and GNU/Linux-specific */
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <memory>
#include <string>
#include <stdio.h>

#define PRINT_CMD(x) (std::cout << x << std::endl)

namespace APP{
// template<typename T>
class FirstGraphics{
public:
    explicit FirstGraphics(void);
    explicit FirstGraphics(int width, int height);
    ~FirstGraphics(void) noexcept;
    void process(void);
    bool loadMedia(void);
    bool init(void);
    //Load individual images
    // std::shared_ptr<SDL_Surface> loadSurface(void);

    //Music
    bool loadFromFile(std::string pathFile);
    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( Uint8 alpha );
    
    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, 
    SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
    int getWidth() const ;
    int getHeight() const;


protected:
    //screen dimension constant
    int screen_width;
    int screen_height;
    int delay;

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

    std::shared_ptr<SDL_Texture> mTexture;
    int mWidth;
    int mHeight;

    //The music that will be played
    std::shared_ptr<Mix_Music> gMusic;

    //The window renderer
    std::shared_ptr<SDL_Renderer> gRenderer;
    std::shared_ptr<Mix_Chunk> gScratch;
    std::shared_ptr<Mix_Chunk> gHigh;
    std::shared_ptr<Mix_Chunk> gMedium;
    std::shared_ptr<Mix_Chunk> gLow;

};

// Custom deleter for SDL_Surface
struct SDLSurfaceDeleter {
    void operator()(SDL_Surface* surface) const {
        SDL_FreeSurface(surface);
    }
};
}
