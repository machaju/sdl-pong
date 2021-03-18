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

class GameScene
{
    public:

        GameScene();
        ~GameScene();

        void renderer(float delat);

        void initScene();

        void loadImages(); 

        void mouseMoved(int mousy);

        void event_loop();

        Ball* ball;
        PlayingField* playingField;
        Score score;
        std::vector<Paddle*> paddles; 

        SDL_Window *window = nullptr;
        SDL_Renderer *gRenderer = nullptr; 

        SDL_Surface* screenSurface = nullptr;
        


};