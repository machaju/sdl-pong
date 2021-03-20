#include <cmath>
#include <random>

#include "Entity.h"


const float BALL_SPEED = 8;

enum PQUAD{Q1, Q2, Q3, Q4, Q5};

class Ball : public Entity 
{
public: 
    Ball();
    ~Ball();

    void initImage(SDL_Renderer* renderer_) override; 

    // move the ball x amount of pixels per second
    void move(float seconds);
    void setDirection(int newdirx, int newdiry);
    void setStartingPos(int startx, int starty);

    PQUAD detectPaddleQuad(int paddle_loc, int paddle_height);

    void moveLeft(PQUAD quad);
    void moveRight(PQUAD quad);
    void moveAngle(PQUAD quad);


    // int x,y;            // the position of the ball
    // int width, height;  // the size of the ball
    int dirx=1;
    float diry = 0.0f;     // the direction of the ball 

    bool initState = true; 
};