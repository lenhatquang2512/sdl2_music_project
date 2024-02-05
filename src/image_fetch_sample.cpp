#include "image_fetch_sample.h"

// Custom deleter for SDL_Surface
struct SDLSurfaceDeleter {
    void operator()(SDL_Surface* surface) const {
        SDL_FreeSurface(surface);
    }
};

template <typename T>
ImageApp::FirstGraphics<T>::FirstGraphics()
    :FirstGraphics<T>{640, 480}
    {
        std::cout << "Constructor called" << std::endl;
}

template <typename T>
ImageApp::FirstGraphics<T>::FirstGraphics(T width, T height):
    screen_width(width),
    screen_height(height),
    delay(2000),
    window(nullptr),
    screenSurface(nullptr){
        std::cout << "Constructor with arguments called" << std::endl;
}

template <typename T>
void ImageApp::FirstGraphics<T>::process(void){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "SDL could not initialize! SDL_Error: "
        << SDL_GetError() << std::endl;
    }else{

        // window = std::make_shared<SDL_Window>(tempWindow, SDL_DestroyWindow);  //ERROR

        window  = std::shared_ptr<SDL_Window>(SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN ), SDL_DestroyWindow); //use custom deleter

        if(window == nullptr){
            std::cerr << "Window could not be created! SDL_Error: "
                 << SDL_GetError() << std::endl;
        }
        else{
        /*
            //Get window surface
            screenSurface =std::shared_ptr<SDL_Surface>(SDL_GetWindowSurface( window.get()), SDLSurfaceDeleter{});

            //Fill the surface white
            SDL_FillRect( screenSurface.get(), nullptr, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

            //Update the surface
            SDL_UpdateWindowSurface( window.get() );

            //Add delay
            SDL_Delay(delay);
        */
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init(imgFlags) & imgFlags) )
            {
                std::cerr << "SDL_image could not initialize! SDL_image Error: "
                << IMG_GetError() << std::endl;
            }
            else
            {
                screenSurface = std::shared_ptr<SDL_Surface>(SDL_GetWindowSurface( window.get()), SDLSurfaceDeleter{});
            }
        }
    }
            
}

template <typename T>
ImageApp::FirstGraphics<T>::~FirstGraphics(void) noexcept{
    std::cout << "Destructor called" << std::endl;
    //Destroy window
    // SDL_DestroyWindow( window.get() ); //Core dump if try to run because we use share pointer
}


template<typename T>
ImageApp::Imagefetch<T>::Imagefetch(T width, T height)
    :FirstGraphics<T>(width, height), 
    pngSurface{nullptr}
{
    std::cout << "Image fetch argc constructor called" << std::endl;
}

template<typename T>
ImageApp::Imagefetch<T>::Imagefetch():
    FirstGraphics<T>(),
    pngSurface{nullptr}
{
    std::cout << "Image fetch no-argc constructor called" << std::endl;
}

template <typename T>
void ImageApp::Imagefetch<T>::process(void){
    FirstGraphics<T>::process();
}

template <typename T>
void ImageApp::Imagefetch<T>::loadMedia(std::string &path)
{
   pngSurface = loadSurface( path );
   if(pngSurface == nullptr)
   {
       std::cout << "Failed to load PNG image!" << std::endl;
   }
}
   

template <typename T>
std::shared_ptr<SDL_Surface> ImageApp::Imagefetch<T>::loadSurface(const std::string &path)
{
    // The final optimized image
    std::shared_ptr<SDL_Surface> optimizedSurface = nullptr;

    // Load image at specified path
    std::shared_ptr<SDL_Surface> loadedSurface{ IMG_Load( path.c_str()) };
    if (loadedSurface == nullptr)
    {
        std::cout << "Unable to load image " << path  << "! SDL_image Error:" << IMG_GetError() << std::endl; 
    }
    else
    {
        // Convert surface to screen format
        optimizedSurface = std::shared_ptr<SDL_Surface>{SDL_ConvertSurface( loadedSurface.get(), ImageApp::FirstGraphics<T>::screenSurface->format, 0)};
        if (optimizedSurface == nullptr)
        {
            std::cout << "Unable to optimized image" << path << "SDL Error: " << SDL_GetError() << std::endl;
        }
    }
    return optimizedSurface;
}

template <typename T>
void ImageApp::Imagefetch<T>::updateSurface()
{
    SDL_BlitSurface( pngSurface.get(), NULL, ImageApp::FirstGraphics<T>::screenSurface.get(), NULL );
    SDL_UpdateWindowSurface( ImageApp::FirstGraphics<T>::window.get() );
}

template <typename T>
ImageApp::Imagefetch<T>::~Imagefetch(void) noexcept{
    std::cout << "Imagefetch destructor called" << std::endl;
    //Destroy window
    // SDL_DestroyWindow( window.get() ); //Core dump if try to run because we use share pointer
}


int main(int argc, char  **argv) {
    ImageApp::Imagefetch<int> myObj;
    myObj.process();
    std::string path{"../img/anh_gai.png"};
    myObj.loadMedia(path);

    //Main loop flag
    bool quit = false;
    //Event handler
    SDL_Event e;

    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }

        myObj.updateSurface();
    }

    return 0;
}
