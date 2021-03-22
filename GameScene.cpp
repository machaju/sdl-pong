#include "GameScene.h"

GameScene::GameScene() {

    // set difficulty
    DIFFICULTY diff = DIFFICULTY::HARD;

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

    //set AI paddle speed & ball speed
    switch(diff)
    {
        case DIFFICULTY::EASY:
            m_ai_paddle_speed = 10;
            m_ball_speed = 12;
            break;
        case DIFFICULTY::MEDIUM:
            m_ai_paddle_speed = 16;
            m_ball_speed = 21;
            break;
        case DIFFICULTY::HARD:
            m_ai_paddle_speed = 20;
            m_ball_speed = 24;
            break;
    }

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

// main event loop 
void GameScene::event_loop() {
    SDL_Event e;
    bool quit = false;
    
    int loopTimer = SDL_GetTicks();
    Uint64 start = SDL_GetPerformanceCounter();
    Uint64 end =   0;
    
    int frame_timer = SDL_GetTicks();
    int frame_count = 0;

    while (!quit) {
        // Poll Events
        while(SDL_PollEvent(&e)!= 0) {
            if (e.type == SDL_QUIT) quit = true;
        }
        
        // Handle player input 
        handlePlayerInput(e); 

        // Move Ball
        if (SDL_GetTicks() - loopTimer > 5) {
            end = SDL_GetPerformanceCounter();
            float secondsElapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
            updateBall(secondsElapsed * 100.f);
            updateAI(secondsElapsed * 100.f);
            start = SDL_GetPerformanceCounter();
            loopTimer = SDL_GetTicks();
        }
        
        // Check for collisions
        checkCollisions();
        
        // render objects 
        renderer();

        // SDL_Delay(5);
        
        // Frames per second
        ++frame_count;
        if (SDL_GetTicks() - frame_timer > 1000) {
	        std::cout << "Current FPS: " << frame_count << std::endl;
            frame_timer = SDL_GetTicks();
            frame_count = 0;
        }
    } 
}


void GameScene::handlePlayerInput(SDL_Event e) {

        // get mouse movements
        if (e.type == SDL_MOUSEMOTION) {
            //Get mouse position
            int x = 0, y = 0;
            SDL_GetMouseState( &x, &y );

            mouseMoved(y);
        }

        // get mouse clicks 
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            //ball->move(float(m_ball_speed) / float(delta));
            ball->initState = false; 
        }
}


// move the player paddle to be centered with the mouse height 
void GameScene::mouseMoved(int mousy) {
    for(auto p : paddles) {
        if (p->player == PLAYER) {
            // remember to use the scaled position here 
            p->movePaddle(mousy - (p->scaled_height / 2), playingField->y, playingField->height);

            // if the player hasn't clicked yet, center the ball with the players paddle   
            if (ball->initState && ((int)ball->x == (int)paddles[PLAYER]->scaled_width + (int)paddles[PLAYER]->x)) {
                ball->setStartingPos(ball->x, mousy - (ball->scaled_height / 2.f));
            }

        // update AI paddle to track mouse/ball movements in init state 
        } else {
            if (ball->initState && (ball->x + ball->scaled_width == paddles[AI]->x)) {
                ball->setStartingPos(ball->x, paddles[AI]->mid() - (ball->scaled_height / 2.f));
            }
        }
    }
}


// if the ball is not on a player's 
//paddle, move the ball 
void GameScene::updateBall(float time_passed) { 
    if (ball->initState == false) {
        ball->move(float(m_ball_speed) / time_passed); 
    }
}

void GameScene::updateAI(float time_passed) {
    float paddle_speed = (float)m_ai_paddle_speed / time_passed;
    float tolerance = paddles[AI]->scaled_height / 8.f;

    // move the AI paddle in the direction of the ball 
    if (ball->mid() < (paddles[AI]->mid() - tolerance)) {
        paddles[AI]->y -= paddle_speed;

    } else if (ball->mid() > (paddles[AI]->mid() + tolerance)) {
        paddles[AI]->y += paddle_speed;
    
    // Slow down movement when ball is in the middle of paddle
    } else {
        float diff = paddles[AI]->mid() - ball->mid();
        float adjust = diff / tolerance;
        paddles[AI]->y -= (paddle_speed * adjust);
    }
}

// check for collisions with both paddles and check to see if the ball goes off screen
// if the ball goes off screen, it updates scores and resets the ball on the winner's paddle 
void GameScene::checkCollisions() {
    // hits players paddle
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
    if(ball->top() <= playingField->y) {
        ball->diry = abs(ball->diry);
    } else if (ball->bottom() >= playingField->height) {
        ball->diry = abs(ball->diry) * -1;
    }

    // goes off screen 
    // point for player
    if(ball->x > playingField->width) {
        scores[PLAYER]->score ++;
        scores[PLAYER]->updateScore();
        std::cout << "point for player! -- score: P1: "  << scores[PLAYER]->score << " P2: "<<  scores[AI]->score << std::endl; 
        // set starting ball position on PLAYER's paddle
        ball->setStartingPos(paddles[PLAYER]->x + paddles[PLAYER]->scaled_width , paddles[PLAYER]->mid() - ball->scaled_height/2); 
        ball->initState=true; 
        
    // point for ai
    } else if(ball->x + ball->scaled_width < playingField->x) {
        scores[AI]->score ++; 
        scores[AI]->updateScore();
        std::cout << "point for AI! -- score: P1: "  << scores[PLAYER]->score << " P2: "<<  scores[AI]->score << std::endl; 
        // Start ball on AI's paddle 
        ball->setStartingPos(paddles[AI]->x - ball->scaled_width, paddles[AI]->mid() - ball->scaled_height/2); 
        ball->initState=true; 
    }
}

void GameScene::renderer() {
    // darw black background 
    SDL_SetRenderDrawColor(m_renderer, 0,0,0,255);

    // Clear screen
    SDL_RenderClear(m_renderer);
       
    // Render paddles
    for (auto it : paddles) {
        it->setPaddlex(playingField->x, playingField->width);
        it->render(screenSurface);  
    }

    for (auto it : scores) {
        it->render(screenSurface);
    }

    // draw dotted line
    drawDottedLine(m_renderer, playingField->width/2, playingField->y, playingField->width/2, playingField->height);

    // Render ball last so it appears over the dotted line and the scores 
    ball->render(screenSurface); 

    //Update screen
    SDL_RenderPresent(m_renderer);
    SDL_UpdateWindowSurface(window);
}


// load all the images & font for the game 
void GameScene::loadImages() {
    // load paddles 
    for(int i = 0 ; i < PLAYERS_SIZE; i++) {
        paddles[i]->initImage(m_renderer); 
        scores[i] ->initImage(m_renderer); // actually a font 
    }

    ball->initImage(m_renderer); 
}

// draws the dotted line to represent half-field 
// horrible performance since it is calling render for every point 
void GameScene::drawDottedLine(SDL_Renderer* renderer, int x0, int y0, int x1, int y1) {
        
    // Lets make the dotted line pink :) 
    SDL_SetRenderDrawColor( renderer, HOT_PINK.r, HOT_PINK.g, HOT_PINK.b, 255 );

    int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = dx+dy, e2;
    int count = 0;
    while (1) {
        if (count < 10) {SDL_RenderDrawPoint(renderer,x0,y0);}
        if (x0==x1 && y0==y1) break;
        e2 = 2*err;
        if (e2 > dy) { err += dy; x0 += sx; }
        if (e2 < dx) { err += dx; y0 += sy; }
        count = (count + 1) % 20;
    }
}


