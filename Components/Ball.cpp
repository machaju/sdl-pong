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
    if        (paddle_quad < .1) { quad = Q1;
    } else if (paddle_quad < .2) { quad = Q2;
    } else if (paddle_quad < .3) { quad = Q3;
    } else if (paddle_quad < .4) { quad = Q4;
    } else if (paddle_quad < .5) { quad = Q5;
    } else if (paddle_quad < .6) { quad = Q6;
    } else if (paddle_quad < .7) { quad = Q7;
    } else if (paddle_quad < .8) { quad = Q8;
    } else if (paddle_quad < .9) { quad = Q9;
    } else {
        quad = Q10;
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
    float min   = -0.25f;
    float max   =  0.25f;

    float random    = ((float) rand()) / (float) RAND_MAX;
    float diff      = max - min;
    float r         = random * diff;
    float noise     = min + r;   

    float newy = 0.0f;  

    switch(quad) {
        case Q1:        newy = -0.8f;       break;
        case Q2:        newy = -0.7f;       break;
        case Q3:        newy = -0.6f;        break;
        case Q4:        newy = -0.4f;        break;
        case Q5:        newy = -0.2f;        break;
        case Q6:        newy = 0.2f;       break;
        case Q7:        newy = 0.4f;       break;
        case Q8:        newy = 0.6f;        break;
        case Q9:        newy = 0.7f;        break;
        case Q10:       newy = 0.8f;        break;

    }

    diry = newy + noise; 
}
