#include "Ball.h"


Ball::Ball() {
    
}

Ball::~Ball() {
    
}

void Ball::loadImage(SDL_Renderer* gRenderer)
{

    load_image("ball.png", gRenderer);
    
}

void Ball::setStartingPos(int startx, int starty)
{
    x = startx;
    y = starty;
}

// move the ball X amount of pixels per second
void Ball::move(float seconds) {
    x += dirx * seconds;
    y += diry * seconds;   
}



void Ball::setDirection(int newdirx, int newdiry) {

    // Normalize the direction vector and multiply with BALL_SPEED
        float length = std::sqrt(newdirx * newdirx + newdiry * newdiry);
        dirx = BALL_SPEED * (newdirx / length);
        diry = BALL_SPEED * (newdiry / length);    
}
