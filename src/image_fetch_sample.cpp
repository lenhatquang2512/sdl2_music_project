#include <image_fetch_sample.h>

template<typename T>
APP::Imagefetch<T>::Imagefetch(T width, T height)
    :APP::FirstGraphics<T>::FirstGraphics(width, height), 
    pngSurface{nullptr}
{
    std::cout << "Image fetch argc constructor called" << std::endl;
}

template<typename T>
APP::Imagefetch<T>::Imagefetch()
    :APP::FirstGraphics<T>::FirstGraphics(), 
    pngSurface{nullptr}
{
    std::cout << "Image fetch no-argc constructor called" << std::endl;
}

template <typename T>
void APP::Imagefetch<T>::process(void){
    APP::FirstGraphics<T>::process();
}

template <typename T>
APP::Imagefetch<T>::~Imagefetch(void) noexcept{
    std::cout << "Imagefetch destructor called" << std::endl;
    //Destroy window
	// SDL_DestroyWindow( window.get() ); //Core dump if try to run because we use share pointer
}

int main(int argc, char  **argv) {
    APP::Imagefetch<int> myObj;

    myObj.process();

    return 0;
}
