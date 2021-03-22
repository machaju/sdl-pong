#include "Ball.h"

Ball::Ball() { }
Ball::~Ball() { }

void Ball::initImage(SDL_Renderer* renderer_) {
    m_renderer = renderer_;
    loadImage("glow-ball.png");
}

void Ball::setStartingPos(int startx, int starty) {
    x = startx;
    y = starty;
}

// move the ball X amount of pixels per second
void Ball::move(float seconds) {
    x += dirx * seconds;
    y += diry * seconds;   
}

PQUAD Ball::detectPaddleQuad(int paddel_loc, int paddle_height) {
    // get location on paddle
    float   paddle_collision_loc =  this->mid() - paddel_loc;
    float   paddle_quad =           paddle_collision_loc/float(paddle_height); 

    PQUAD quad = Q3;
    // angle up 
    if(paddle_quad < .2) {
        quad = Q1;
    
    // up mid
    } else if(paddle_quad < .4) {
        quad = Q2;

    // center
    } else if(paddle_quad < .6) {
        quad = Q3;

    // down mid
    } else if(paddle_quad < .8) {
        quad = Q4;

    // down
    } else {
        quad = Q5;
    }

    return quad; 
    //dirx = dirx * -1; 
}

void Ball::moveLeft(PQUAD quad) {
    dirx = -1;
    moveAngle(quad);
}

void Ball::moveRight(PQUAD quad) {
    dirx = 1;
    moveAngle(quad);
}

// TODO: make this more elegant 
void Ball::moveAngle(PQUAD quad) {
    float min   = -0.2f;
    float max   = 0.2f;

    float random    = ((float) rand()) / (float) RAND_MAX;
    float diff      = max - min;
    float r         = random * diff;
    float noise     =  min + r;   

    float newy = 0.0f;  

    switch(quad) {
        case Q1:     newy = -0.4f;       break;
        case Q2:     newy = -0.2f;       break;
        case Q3:     newy = 0.0f;        break;
        case Q4:     newy = 0.4f;        break;
        case Q5:     newy = 0.2f;        break;
    }

    diry = newy + noise; 
}
