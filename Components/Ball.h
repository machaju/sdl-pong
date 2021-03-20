#include <cmath>

#include "Entity.h"



const float BALL_SPEED = 550;


class Ball : public Entity
{
    public: 

        Ball();
        ~Ball();

        void loadImage(SDL_Renderer* gRenderer); 

        // move the ball x amount of pixels per second
        void move(float seconds);

        void setDirection(int newdirx, int newdiry);

        void setStartingPos(int startx, int starty);

        int detect_paddle_quad(int paddle_loc, int paddle_height);

        void moveLeft(int quad);

        void moveRight(int quad);

        void moveAngle(int quad);


        // int x,y;            // the position of the ball
        // int width, height;  // the size of the ball
        int dirx=1;
        float diry = 0.0f;     // the direction of the ball 

        bool initState = true; 

        
};