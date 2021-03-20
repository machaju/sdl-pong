#include "GameScene.h"


GameScene::GameScene() {

     playingField = new PlayingField(SCREEN_WIDTH *.9 , SCREEN_HEIGHT *.9);

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
        window = SDL_CreateWindow("SDL4Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

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

                    // set starting positions
                    for(auto p : paddles)
                    {
                        p->movePaddle((playingField->height/2) - (p->scaled_height/2), playingField->y, playingField->height);
                        p->setPaddlex(playingField->x, playingField->width);
                    }

                    ball->setStartingPos((  paddles[0]->scaled_width + paddles[0]->x), 
                                    (paddles[0]->y) + (paddles[0]->scaled_height / 2) - (ball->height/4));

                
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
 
    ball->render(screenSurface);
    
    

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
            // remember to use the scaled position here 
            p->movePaddle(mousy - (p->scaled_height / 2), playingField->y, playingField->height);

            // if the player hasn't clicked yet, center the ball with the players paddle   
            if(ball->initState)
            {
                ball->setStartingPos((  paddles[0]->scaled_width + paddles[0]->x), 
                                     (mousy - (ball->scaled_height/2) ));
            }
        }
        // update AI paddle
        else{

            // TODO: add logic here -- keeping centered for now 
            p->movePaddle((playingField->height/2) - (p->scaled_height/2), playingField->y, playingField->height);
            //p->setPaddlex(playingField->x, playingField->width);

            // p->movePaddle(100, playingField->y, playingField->height);
            // p->setPaddlex(300, playingField->width);

        }
    }
}

void GameScene::event_loop()
{
    // had to to add an event loop here, this diverges from the tutorial on 
    // Lazy Foo the long DELAY seemd to be locking up the processor 
    SDL_Event e;
    bool quit = false;
    int frameStart = SDL_GetTicks();

    while (!quit) {

        while(SDL_PollEvent(&e)!= 0) {
            if (e.type == SDL_QUIT) quit = true;
        }
        
        int frameTime = SDL_GetTicks() - frameStart;        

        float delta = 0.01;


        if( e.type == SDL_MOUSEMOTION )
        {
            //Get mouse position
            int x, y;
            SDL_GetMouseState( &x, &y );

           // std::cout << x << ", " << y << std::endl; 

            mouseMoved(y);

        }

        if(e.type == SDL_MOUSEBUTTONDOWN)
        {
            //move ball
            ball->move(1);
            ball->initState = false; 
        }

        //move ball
        if(ball->initState ==false)
        {
            ball->move(5); 
        }

        //check for collisions
      
        if((ball->x <= (paddles[0]->x + paddles[0]->scaled_width))
        && (ball->x > (paddles[0]->x + (paddles[0]->scaled_width * 0.5))) 
        && ((ball->y <= (paddles[0]->y +  paddles[0]->scaled_height))
        && (ball->y + ball->scaled_height >= (paddles[0]->y ))))
        {
            ball->moveRight(ball->detect_paddle_quad(paddles[0]->y, paddles[0]->scaled_height)); 
        }

        if((ball->x + ball->scaled_width) >= paddles[1]->x)
        {
            ball->moveLeft(ball->detect_paddle_quad(paddles[1]->y, paddles[1]->scaled_height)); 
        }
        


        // render objects 
        renderer(delta);

        
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
