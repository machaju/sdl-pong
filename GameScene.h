#include <stdio.h>
#include <SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <vector>

#include "Components/Ball.h"
#include "Components/PlayingField.h"
#include "Components/Score.h"
#include "Components/Paddle.h"

enum PLAYERS{PLAYER, AI, PLAYERS_SIZE};

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

    void renderer(float delat);
    void initScene();
    void loadImages(); 
    void mouseMoved(int mousy);

    void event_loop();

};