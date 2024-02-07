#include "mainClassSample.h"

// template<typename T>
APP::FirstGraphics::FirstGraphics(void):
    APP::FirstGraphics::FirstGraphics(640,480)
{
        std::cout << "Constructor called" << std::endl;
}


// template<typename T>
APP::FirstGraphics::FirstGraphics(int width,int height):
    screen_width(width),
    screen_height(height),
    delay(2000),
    window(nullptr),
    screenSurface(nullptr),
    PNGSurface(nullptr),
    path("../img/khong_the_voi_toi.png"),
    mTexture(nullptr),
    mWidth(0),
    mHeight(0),gMusic(nullptr),
    gRenderer(nullptr),gScratch(nullptr),gHigh(nullptr),
    gMedium(nullptr),gLow(nullptr){
        std::cout << "Constructor args called" << std::endl;
}

bool APP::FirstGraphics::loadFromFile(std::string pathFile){
    std::shared_ptr<SDL_Texture> newTexture;

    std::shared_ptr<SDL_Surface> loadedSurface{ IMG_Load( pathFile.c_str()) };
    if (loadedSurface == nullptr){
        std::cout << "Unable to load image " << path  << "! SDL_image Error:" << IMG_GetError() << std::endl; 
    }
    else{
        //Color key image
		SDL_SetColorKey( loadedSurface.get() , SDL_TRUE, 
        SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

        //Create texture from surface pixels
        newTexture = std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface( gRenderer.get(), loadedSurface.get()),SDL_DestroyTexture);
		if( newTexture == nullptr )
		{
			std::cout << "Unable to create texture from" << pathFile << "! SDL Error:" << SDL_GetError() << std::endl;
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface.get() );
    }
    mTexture = newTexture;
    return mTexture != nullptr;

}

void  APP::FirstGraphics::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture.get(), red, green, blue );
}

void  APP::FirstGraphics::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture.get(), blending );
}
		
void  APP::FirstGraphics::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture.get(), alpha );
}

void  APP::FirstGraphics::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer.get(), mTexture.get(), clip, &renderQuad, angle, center, flip );
}

int APP::FirstGraphics::getWidth() const 
{
	return mWidth;
}

int APP::FirstGraphics::getHeight() const 
{
	return mHeight;
}




// template<typename T>
bool APP::FirstGraphics::init(void){
    isInitSuccess = true;
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ){
        std::cout << "SDL could not initialize! SDL_Error: "
        << SDL_GetError() << std::endl;
        isInitSuccess = false;
    }else{

        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			PRINT_CMD( "Warning: Linear texture filtering not enabled!" );
		}

        window  = std::shared_ptr<SDL_Window>(SDL_CreateWindow( "Music app FSO", SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN ), SDL_DestroyWindow); //use custom deleter

        if(window == nullptr){
            std::cout << "Window could not be created! SDL_Error: "
                 << SDL_GetError() << std::endl;
            isInitSuccess = false;
        }else{
        
            // // screenSurface =std::shared_ptr<SDL_Surface>(SDL_GetWindowSurface( window.get()), SDL_FreeSurface);
            // int imgFlags = IMG_INIT_PNG;
            // if( !( IMG_Init(imgFlags) & imgFlags) )
            // {
            //     std::cout << "SDL_image could not initialize! SDL_image Error: "
            //     << IMG_GetError() << std::endl;
            // }
            // else
            // {
            //     screenSurface = std::shared_ptr<SDL_Surface>(SDL_GetWindowSurface( window.get()),SDL_FreeSurface);
            // }

            //Create vsynced renderer for window
            gRenderer = std::shared_ptr<SDL_Renderer>(SDL_CreateRenderer( window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ),SDL_DestroyRenderer);
			if( gRenderer == nullptr ){
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				isInitSuccess = false;
			}
			else
			{
            //Initialize renderer color
            SDL_SetRenderDrawColor( gRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF );

            //Initialize PNG loading
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) )
            {
                std::cout << "SDL_image could not initialize! SDL_image Error: "
                << IMG_GetError() << std::endl;
                isInitSuccess = false;
            }

                //Initialize SDL_mixer
            if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
            {
                std::cout << "SDL_mixer could not initialize! SDL_mixer Error:" << Mix_GetError() << std::endl;
                isInitSuccess = false;
            }
		}
    }
    return isInitSuccess;
}
}

// // template<typename T>
// std::shared_ptr<SDL_Surface> APP::FirstGraphics::loadSurface(void){
//     // The final optimized image
//     std::shared_ptr<SDL_Surface> optimizedSurface = nullptr;

//     // Load image at specified path
//     PRINT_CMD(path);
//     std::shared_ptr<SDL_Surface> loadedSurface{ IMG_Load( path.c_str()) };
//     if (loadedSurface == nullptr)
//     {
//         std::cout << "Unable to load image " << path  << "! SDL_image Error:" << IMG_GetError() << std::endl; 
//     }
//     else{
//         // Convert surface to screen format
//         optimizedSurface = std::shared_ptr<SDL_Surface>{SDL_ConvertSurface( loadedSurface.get(), screenSurface->format, 0)};
//         if (optimizedSurface == nullptr)
//         {
//             std::cout << "Unable to optimized image" << path << "SDL Error: " << SDL_GetError() << std::endl;
//         }
//     }
//     return optimizedSurface;
// }

// template<typename T>
bool APP::FirstGraphics::loadMedia(void){
    isLoadSuccess = true;
    // PNGSurface = loadSurface();
    // if(PNGSurface == nullptr){
    //     std::cout << "Failed to load PNG image!" << std::endl;
    //     isLoadSuccess = false;
    // }

    if(!loadFromFile("../music_files/prompt.png")){
        std::cout << "Failed to load prompt texture!" << std::endl;
        isLoadSuccess = false;
    }

    //Load music
    gMusic =std::shared_ptr<Mix_Music>(Mix_LoadMUS( "../music_files/2h-RPTMCK-9608193.mp3"),Mix_FreeMusic);
    if(gMusic == nullptr){
        printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		isLoadSuccess = false;
    }

    	//Load sound effects
	gScratch = std::shared_ptr<Mix_Chunk> (Mix_LoadWAV( "../music_files/scratch.wav" ), Mix_FreeChunk);
	if( gScratch == nullptr)
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		isLoadSuccess = false;
	}
	
	gHigh = std::shared_ptr<Mix_Chunk> (Mix_LoadWAV( "../music_files/high.wav" ),Mix_FreeChunk);
	if( gHigh == nullptr)
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		isLoadSuccess = false;
	}

	gMedium = std::shared_ptr<Mix_Chunk> (Mix_LoadWAV( "../music_files/medium.wav" ),Mix_FreeChunk);
	if( gMedium == nullptr)
	{
		printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		isLoadSuccess = false;
	}

	gLow = std::shared_ptr<Mix_Chunk> (Mix_LoadWAV( "../music_files/low.wav" ),Mix_FreeChunk);
	if( gLow == nullptr )
	{
		printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		isLoadSuccess = false;
	}
 //CLOSE ?
    return isLoadSuccess;
}

// template <typename T>
void APP::FirstGraphics::process(void){
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
                    else if(event.type == SDL_KEYDOWN){

                        switch( event.key.keysym.sym )
						{
							//Play high sound effect
							case SDLK_1:
							Mix_PlayChannel( -1, gHigh.get(), 0 );
							break;
							
							//Play medium sound effect
							case SDLK_2:
							Mix_PlayChannel( -1, gMedium.get(), 0 );
							break;
							
							//Play low sound effect
							case SDLK_3:
							Mix_PlayChannel( -1, gLow.get(), 0 );
							break;
							
							//Play scratch sound effect
							case SDLK_4:
							Mix_PlayChannel( -1, gScratch.get(), 0 );
							break;
							
							case SDLK_9:
							//If there is no music playing
							if( Mix_PlayingMusic() == 0 )
							{
								//Play the music
								Mix_PlayMusic( gMusic.get(), -1 );
							}
							//If music is being played
							else
							{
								//If the music is paused
								if( Mix_PausedMusic() == 1 )
								{
									//Resume the music
									Mix_ResumeMusic();
								}
								//If the music is playing
								else
								{
									//Pause the music
									Mix_PauseMusic();
								}
							}
							break;
							
							case SDLK_0:
							//Stop the music
							Mix_HaltMusic();
							break;
                    }
                }

            // SDL_BlitSurface( PNGSurface.get(), nullptr, screenSurface.get(), nullptr);
            // SDL_UpdateWindowSurface( window.get() );

            	//Clear screen
				SDL_SetRenderDrawColor( gRenderer.get(), 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer.get() );

				//Render prompt
				render( 0, 0 );

				//Update screen
				SDL_RenderPresent( gRenderer.get() );

            // //Add delay
            // SDL_Delay(delay);
            }
        }
    }
            
}
}


// template <typename T>
APP::FirstGraphics::~FirstGraphics(void) noexcept{
    std::cout << "Destructor called" << std::endl;
    //Destroy window
	// SDL_DestroyWindow( window.get() ); //Core dump if try to run because we use share pointer

	// //Quit SDL subsystems
	// SDL_Quit();
}

// template APP::FirstGraphics<int>::FirstGraphics();
// template void APP::FirstGraphics<int>::process(void);
// template APP::FirstGraphics<int>::~FirstGraphics();
// template bool APP::FirstGraphics<int>::loadMedia(void);
// template bool APP::FirstGraphics<int>::init(void);
// template std::shared_ptr<SDL_Surface> APP::FirstGraphics<int>::loadSurface(void);