#include "Ball.h"


Ball::Ball() {
    
}

Ball::~Ball() {
    
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
