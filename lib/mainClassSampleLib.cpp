#include "mainClassSample.h"

template<typename T>
APP::FirstGraphics<T>::FirstGraphics(void):
    APP::FirstGraphics<T>::FirstGraphics(640,480)
{
        std::cout << "Constructor called" << std::endl;
}


template<typename T>
APP::FirstGraphics<T>::FirstGraphics(T width, T height):
    screen_width(width),
    screen_height(height),
    delay(2000),
    window(nullptr),
    screenSurface(nullptr),
    PNGSurface(nullptr),
    path("../img/khong_the_voi_toi.png"){
        std::cout << "Constructor args called" << std::endl;
}

template<typename T>
bool APP::FirstGraphics<T>::init(void){
    isInitSuccess = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0 ){
        std::cout << "SDL could not initialize! SDL_Error: "
        << SDL_GetError() << std::endl;
        isInitSuccess = false;
    }else{
            window  = std::shared_ptr<SDL_Window>(SDL_CreateWindow( "FSO ", SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN ), SDL_DestroyWindow); //use custom deleter

        if(window == nullptr){
            std::cout << "Window could not be created! SDL_Error: "
                 << SDL_GetError() << std::endl;
            isInitSuccess = false;
        }else{
        
            // screenSurface =std::shared_ptr<SDL_Surface>(SDL_GetWindowSurface( window.get()), SDL_FreeSurface);
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init(imgFlags) & imgFlags) )
            {
                std::cout << "SDL_image could not initialize! SDL_image Error: "
                << IMG_GetError() << std::endl;
            }
            else
            {
                screenSurface = std::shared_ptr<SDL_Surface>(SDL_GetWindowSurface( window.get()),SDL_FreeSurface);
            }
		}
    }
    return isInitSuccess;
}

template<typename T>
std::shared_ptr<SDL_Surface> APP::FirstGraphics<T>::loadSurface(void){
    // The final optimized image
    std::shared_ptr<SDL_Surface> optimizedSurface = nullptr;

    // Load image at specified path
    PRINT_CMD(path);
    std::shared_ptr<SDL_Surface> loadedSurface{ IMG_Load( path.c_str()) };
    if (loadedSurface == nullptr)
    {
        std::cout << "Unable to load image " << path  << "! SDL_image Error:" << IMG_GetError() << std::endl; 
    }
    else{
        // Convert surface to screen format
        optimizedSurface = std::shared_ptr<SDL_Surface>{SDL_ConvertSurface( loadedSurface.get(), screenSurface->format, 0)};
        if (optimizedSurface == nullptr)
        {
            std::cout << "Unable to optimized image" << path << "SDL Error: " << SDL_GetError() << std::endl;
        }
    }
    return optimizedSurface;
}

template<typename T>
bool APP::FirstGraphics<T>::loadMedia(void){
    isLoadSuccess = true;
    PNGSurface = loadSurface();
    if(PNGSurface == nullptr){
        std::cout << "Failed to load PNG image!" << std::endl;
        isLoadSuccess = false;
    }
    return isLoadSuccess;

}

template <typename T>
void APP::FirstGraphics<T>::process(void){
    if(!init()){
        PRINT_CMD("Failed to initialize!");
    }else{
        if(!loadMedia()){
            PRINT_CMD("Failed to load media");
        }else{
            bool quit = false;
            while(!quit){
                while(SDL_PollEvent(&event) != 0){
                    if(event.type == SDL_QUIT){
                        quit = true;
                    }
                }

            SDL_BlitSurface( PNGSurface.get(), nullptr, screenSurface.get(), nullptr);
            SDL_UpdateWindowSurface( window.get() );

            // //Add delay
            // SDL_Delay(delay);
            }
        }
    }
            
}


template <typename T>
APP::FirstGraphics<T>::~FirstGraphics(void) noexcept{
    std::cout << "Destructor called" << std::endl;
    //Destroy window
	// SDL_DestroyWindow( window.get() ); //Core dump if try to run because we use share pointer

	// //Quit SDL subsystems
	// SDL_Quit();
}

template APP::FirstGraphics<int>::FirstGraphics();
template void APP::FirstGraphics<int>::process(void);
template APP::FirstGraphics<int>::~FirstGraphics();
template bool APP::FirstGraphics<int>::loadMedia(void);
template bool APP::FirstGraphics<int>::init(void);
template std::shared_ptr<SDL_Surface> APP::FirstGraphics<int>::loadSurface(void);