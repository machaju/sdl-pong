#include "GameScene.h"


GameScene::GameScene() {

     playingField = new PlayingField(SCREEN_WIDTH * .9, SCREEN_HEIGHT * .9);

     ball = new Ball(); 

    Paddle *p1 = new Paddle(0);
    Paddle *p2 = new Paddle(1);

    paddles.push_back(p1);
    paddles.push_back(p2);


    //  SDL_Texture* texture1 = SDL_CreateTextureFromSurface(render, paddles[0]->m_surface);
    //  SDL_Texture* texture2 = SDL_CreateTextureFromSurface(render, paddles[1]->m_surface);

    
        // create game window 
        initScene();

}

GameScene::~GameScene() {

    SDL_FreeSurface(screenSurface);
}

void GameScene::initScene()
{
// Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO < 0))
    {
        std::cout << "SDL cound not initialize! SDL error: " << SDL_GetError() << std::endl;
    }

    else{
        // create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if(window == nullptr)
        {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl; 
        }

        else{
            std::cout << "Window created successfully!" << std::endl; 

            //             // get window surface
            // screenSurface = SDL_GetWindowSurface(window); 

            // // fill the surface white
            // SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

            // SDL_UpdateWindowSurface(window);


            //Create renderer for window
            gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                }

                else{
                    std::cout << "Initialized Image loading!" << std::endl; 


                    loadImages();

                    ball->setStartingPos((  paddles[0]->width + paddles[0]->x), 
                                    (paddles[0]->height - (paddles[0]->height /2)) );

                
                }
            }
        
      
        }

    }
}

void GameScene::renderer(float delta)
{
    //SDL_SetRenderDrawColor(render, 0,0,0,255);

    //Clear screen
    SDL_RenderClear( gRenderer );

   // SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

    // render ball & board
    if(ball->initState)
    { 
        ball->render(screenSurface);
    }
    

    // render paddels
    for (auto it : paddles)
    {
        it->setPaddlex(playingField->x, playingField->width);
        it->render(screenSurface);  
    }

    //Update screen
    SDL_RenderPresent( gRenderer );

    SDL_UpdateWindowSurface( window );
}


// move the player paddle to be centered with the mouse height 
void GameScene::mouseMoved(int mousy) {
    
    for(auto p : paddles)
    {
        if (p->player == 0)
        {
            p->movePaddle(mousy - (p->scaled_height / 2), playingField->y, playingField->height);

            // ball->setStartingPos((  paddles[0]->width + paddles[0]->x), 
            //                          (mousy - (ball->height/2) ));

            ball->setStartingPos((  paddles[0]->scaled_width + paddles[0]->x), 
                                     (mousy - (ball->scaled_height/2) ));
        }
    }
}

void GameScene::event_loop()
{
    // had to to add an event loop here, this diverges from the tutorial on 
    // Lazy Foo the long DELAY seemd to be locking up the processor 
    SDL_Event e;
    bool quit = false;
    while (!quit) {

        while(SDL_PollEvent(&e)!= 0) {
            if (e.type == SDL_QUIT) quit = true;
        }

        float delta = 0.01;

        renderer(delta);

        if( e.type == SDL_MOUSEMOTION )
        {
            //Get mouse position
            int x, y;
            SDL_GetMouseState( &x, &y );

            std::cout << x << ", " << y << std::endl; 

            mouseMoved(y);

        }

        
        //paddles[0]->update(delta);

        SDL_Delay(16);
    } 
}

void GameScene::loadImages() {
    
    // load paddles 
    for(auto it : paddles)
    {
        it->loadImage(gRenderer); 
    }

    ball->loadImage(gRenderer); 
}
