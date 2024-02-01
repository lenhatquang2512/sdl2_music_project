#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <iostream>

int main( int argc, char* args[] )
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG);
    
    SDL_Window* window = SDL_CreateWindow( "Health bar", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );
        
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface* healthbar_sur = IMG_Load("/home/quang_le/quang_prog/test/test_code_cpp_tut/sdl_tut/sdl_demo/img/healthbar.png");
    SDL_Texture* healthbar_tex = SDL_CreateTextureFromSurface(renderer, healthbar_sur);

    SDL_Rect rect{100, 100, 200, 22};
    
    int x = 0; // x position of the mouse
    
    while (true) {
        SDL_Event e;
        if (SDL_WaitEvent(&e)) {
            if (e.type == SDL_QUIT) {
                break;
            }
            if(e.type == SDL_MOUSEMOTION) {
                x = e.motion.x;
                
                if(x < 196)
                    x = 196;
                
                if(x > 392)
                    x = 392;
            }
        }
        SDL_Rect rect2{102, 102, (x-196), 18};
        
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        
        SDL_RenderCopy(renderer, healthbar_tex, NULL, &rect);
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect2);
        
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(healthbar_tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}