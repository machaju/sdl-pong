#include <stdio.h>
#include <SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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

    int m_ai_paddle_speed = 2;
    int m_ball_speed = 2;


    void renderer(float delat);
    void drawDottedLine(SDL_Renderer* renderer, int x0, int y0, int x1, int y1); 
    void initScene();
    void loadImages(); 
    void mouseMoved(int mousy);

    void handlePlayerInput(SDL_Event event); 
    void updateBall();
    void checkCollisions();
    void updateAI(); 

    void event_loop();

};