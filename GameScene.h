#include <stdio.h>
#include <SDL.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

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
        void loadField(); 

        void mouseMoved(int mousy);

        void event_loop();

        Ball ball;
        PlayingField* playingField;
        Score score;
        std::vector<Paddle*> paddles; 

        SDL_Window *window = nullptr;
        SDL_Renderer *render = nullptr; 

        SDL_Surface* screenSurface = nullptr;
        


};