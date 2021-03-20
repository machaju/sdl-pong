#include "GameScene.h"

GameScene::GameScene() {
    playingField = new PlayingField(SCREEN_WIDTH , SCREEN_HEIGHT);

    ball = new Ball(); 

    Paddle *p1 = new Paddle(0);
    Paddle *p2 = new Paddle(1);
    paddles.push_back(p1);
    paddles.push_back(p2);

    Score *s1 = new Score();
    Score *s2 = new Score();
    s1->x = playingField->width *.25;
    s1->y = playingField->height *.1;
    s2->x = playingField->width *.75;
    s2->y = playingField->height *.1;

    scores.push_back(s1);
    scores.push_back(s2);

    //  SDL_Texture* texture1 = SDL_CreateTextureFromSurface(render, paddles[0]->m_surface);
    //  SDL_Texture* texture2 = SDL_CreateTextureFromSurface(render, paddles[1]->m_surface);
    
    // create game window 
    initScene();
}

GameScene::~GameScene() {
    SDL_FreeSurface(screenSurface);
}

void GameScene::initScene() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO < 0)) {
        std::cout << "SDL cound not initialize! SDL error: " << SDL_GetError() << std::endl;
    }
    
    // create window
    window = SDL_CreateWindow("SDL4Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(window == nullptr) {
        std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl; 
    }
    std::cout << "Window created successfully!" << std::endl; 

    //             // get window surface
    // screenSurface = SDL_GetWindowSurface(window); 
    // // fill the surface white
    // SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
    // SDL_UpdateWindowSurface(window);

    // Initialize Font Engine
    TTF_Init();

    //Create renderer for window
    m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (m_renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    }
    //Initialize renderer color
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
    }
    std::cout << "Initialized Image loading!" << std::endl; 
    
    loadImages();

    // set starting positions
    for(auto p : paddles) {
        p->movePaddle((playingField->height/2) - (p->scaled_height/2), playingField->y, playingField->height);
        p->setPaddlex(playingField->x, playingField->width);
    }

    ball->setStartingPos((paddles[0]->scaled_width + paddles[0]->x), 
                         (paddles[0]->y) + (paddles[0]->scaled_height / 2) - (ball->height/4));
}

void GameScene::renderer(float delta) {
    //SDL_SetRenderDrawColor(render, 0,0,0,255);

    // Clear screen
    SDL_RenderClear(m_renderer);
    // SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));

    // Render ball & board
    ball->render(screenSurface);
       
    // Render paddles
    for (auto it : paddles) {
        it->setPaddlex(playingField->x, playingField->width);
        it->render(screenSurface);  
    }

    for (auto it : scores) {
        it->render(screenSurface);
    }

    //Update screen
    SDL_RenderPresent(m_renderer);
    SDL_UpdateWindowSurface( window );
}


// move the player paddle to be centered with the mouse height 
void GameScene::mouseMoved(int mousy) {
    for(auto p : paddles) {
        if (p->player == PLAYER) {
            // remember to use the scaled position here 
            p->movePaddle(mousy - (p->scaled_height / 2), playingField->y, playingField->height);

            // if the player hasn't clicked yet, center the ball with the players paddle   
            if(ball->initState && (ball->x == paddles[PLAYER]->scaled_width + paddles[PLAYER]->x)) {
                ball->setStartingPos(( ball->x), (mousy - (ball->scaled_height/2) ));
            }

        // update AI paddle
        } else {
            if(ball->initState && (ball->x + ball->scaled_width == paddles[AI]->x)) {
                ball->setStartingPos(ball->x, paddles[AI]->mid() - ball->scaled_height/2);
            }

            // TODO: add logic here -- keeping centered for now 
            //p->movePaddle((playingField->height/2) - (p->scaled_height/2), playingField->y, playingField->height);
            //p->setPaddlex(playingField->x, playingField->width);

            // p->movePaddle(100, playingField->y, playingField->height);
            // p->setPaddlex(300, playingField->width);
        }
    }
}

void GameScene::event_loop() {
    SDL_Event e;
    bool quit = false;
    int frameStart = SDL_GetTicks();

    while (!quit) {
        while(SDL_PollEvent(&e)!= 0) {
            if (e.type == SDL_QUIT) quit = true;
        }
        
        int frameTime = SDL_GetTicks() - frameStart;        
        float delta = 0.01;

        if (e.type == SDL_MOUSEMOTION) {
            //Get mouse position
            int x = 0, y = 0;
            SDL_GetMouseState( &x, &y );

            mouseMoved(y);
        }

        // Move Ball
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            ball->move(1);
            ball->initState = false; 
        }
        if (ball->initState ==false) {
            ball->move(BALL_SPEED); 
        }

        // Check for collisions
        // hits players paddel
        if ((ball->x <= (paddles[PLAYER]->x + paddles[PLAYER]->scaled_width))
            && (ball->x > (paddles[PLAYER]->x + (paddles[PLAYER]->scaled_width * 0.5))) 
            && ((ball->y <= (paddles[PLAYER]->y +  paddles[PLAYER]->scaled_height))
            && (ball->y + ball->scaled_height >= (paddles[PLAYER]->y )))) {
            ball->moveRight(ball->detectPaddleQuad(paddles[PLAYER]->y, paddles[PLAYER]->scaled_height)); 
        }
        // hits ai paddle
        if (((ball->x + ball->scaled_width) >= paddles[AI]->x)
            && (ball->x + ball->scaled_width < (paddles[AI]->x + paddles[AI]->scaled_width * .5)) 
            && ((ball->y <= (paddles[AI]->y +  paddles[AI]->scaled_height))
            && (ball->y + ball->scaled_height >= (paddles[AI]->y )))) {
            ball->moveLeft(ball->detectPaddleQuad(paddles[AI]->y, paddles[AI]->scaled_height)); 
        }
        // hits top or bottom of playing field
        if(ball->top() <= playingField->y || ball->bottom() >= playingField->height) {
            ball->diry = ball->diry * -1;
        }

        // goes off screen 
        // point for player
        if(ball->x > playingField->width) {
            scores[PLAYER]->score ++;
            scores[PLAYER]->updateScore();
            std::cout << "point for player! -- score: P1: "  << scores[PLAYER]->score << " P2: "<<  scores[AI]->score << std::endl; 
            ball->setStartingPos(paddles[PLAYER]->x + paddles[PLAYER]->scaled_width , paddles[PLAYER]->mid() - ball->scaled_height/2); 
            ball->initState=true; 
            
        // point for ai
        } else if(ball->x + ball->scaled_width < playingField->x) {
            scores[AI]->score ++; 
            scores[AI]->updateScore();
            std::cout << "point for AI! -- score: P1: "  << scores[PLAYER]->score << " P2: "<<  scores[AI]->score << std::endl; 
            ball->setStartingPos(paddles[AI]->x - ball->scaled_width, paddles[AI]->mid() - ball->scaled_height/2); 
            ball->initState=true; 
        }

        // update AI
        if(ball->bottom() < paddles[AI]->mid()) {
            paddles[AI]->movePaddle(paddles[AI]->y -2, playingField->y, playingField->height);
        } else if(ball->top() > paddles[AI]->mid()) {
            paddles[AI]->movePaddle(paddles[AI]->y +2, playingField->y, playingField->height);
        }
        
        // render objects 
        renderer(delta);
        
        //paddles[0]->update(delta);

        SDL_Delay(16);
    } 
}

void GameScene::loadImages() {
    // load paddles 
    for(int i = 0 ; i < PLAYERS_SIZE; i++) {
        paddles[i]->initImage(m_renderer); 
        scores[i] ->initImage(m_renderer); 
    }

    ball          ->initImage(m_renderer); 
}
