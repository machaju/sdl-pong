#include <stdio.h>
#include <SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int delta = 16;   // 16 miliseconds

const SDL_Color HOT_PINK = {255,39,210};

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>

#include "Components/Ball.h"
#include "Components/PlayingField.h"
#include "Components/Score.h"
#include "Components/Paddle.h"

enum PLAYERS{PLAYER, AI, PLAYERS_SIZE};

enum DIFFICULTY {EASY, MEDIUM, HARD};


//  Main Functions
// -------------------
//  - handelPlayerInput
//  - updateBall
//  - checkCollisions
//  - updateAI 
//  - Render
class GameScene
{
public:
    GameScene();
    ~GameScene();

    Ball*                   ball            { nullptr };
    PlayingField*           playingField    { nullptr };
    std::vector<Paddle*>    paddles         { }; 
    std::vector<Score*>     scores          { }; 

    SDL_Window*             window          { nullptr };
    SDL_Renderer*           m_renderer      { nullptr }; 
    SDL_Surface*            screenSurface   { nullptr };

    int m_ai_paddle_speed = 6;
    int m_ball_speed = 6;


    void renderer();
    void drawDottedLine(SDL_Renderer* renderer, int x0, int y0, int x1, int y1); 
    void initScene();
    void loadImages(); 
    void mouseMoved(int mousy);

    void handlePlayerInput(SDL_Event event); 
    void updateBall(float time_passed);
    void updateAI(float time_passed); 
    void checkCollisions();
    
    void frame();
    void event_loop();

private:
    bool    m_quit = false;

    int     m_loopTimer = SDL_GetTicks();
    Uint64  m_start = SDL_GetPerformanceCounter();
    Uint64  m_end =   0;
    
    int     m_frame_timer = SDL_GetTicks();
    int     m_frame_count = 0; 

};