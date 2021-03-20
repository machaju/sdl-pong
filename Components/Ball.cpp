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

int Ball::detect_paddle_quad(int paddel_loc, int paddle_height)
{

    // get location on paddle
    int ball_mid = y + (scaled_height/2);
    float paddle_collision_loc = ball_mid - paddel_loc;
    float paddle_quad = paddle_collision_loc/float(paddle_height); 

    int quad = 2;
    // angle up 
    if(paddle_quad < .25)
    {
        quad = 1;
        std::cout << " 1st Quad" << std::endl; 

    }
    // up mid
    else if(paddle_quad < .5)
    {
        quad = 2;
        std::cout << " 2nd Quad" << std::endl; 

    }
    // down mid
    else if(paddle_quad < .75)
    {
        quad = 3;
        std::cout << " 3rd Quad" << std::endl; 

    }
    // down 
    else
    {
        quad = 4;
        std::cout << " 4th Quad" << std::endl; 

    }

    return quad; 


    //dirx = dirx * -1; 
}

void Ball::moveLeft(int quad)
{
    dirx = -1;
    moveAngle(quad);
}

void Ball::moveRight(int quad)
{
    dirx = 1;
    moveAngle(quad);

}

// TODO: make this more elegant 
void Ball::moveAngle(int quad)
{
       switch(quad)
    {
        case 1:
            diry = -0.2f;
            break;
        case 2:
            diry = -0.1f;
            break;
        case 3:
            diry = 0.1f;
            break;
        case 4:
            diry = 0.2f;
            break;
    }
}
