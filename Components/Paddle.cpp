#include "Paddle.h"

Paddle::Paddle(int p) : player(p) { }
Paddle::~Paddle() { }

void Paddle::initImage(SDL_Renderer* renderer_) {
    m_renderer = renderer_;
    if (player == 0) {
        loadImage("paddle.png");
    } else{
        loadImage("glasspaddle2.png");
    }
}
// move paddle based on mouse y location
void Paddle::movePaddle(int y, int pfy, int pfheight) {
    // // check upper bound
    // if( this->y < (0))
    // {
    //     this->y = 0;
    //     std::cout<< "NEG! " << std::endl; 


    // }
    // // check lower bound
    // else if(y > pfheight)
    // {
    //     this->y = pfheight;
    // }
    // // set paddle to mouse location
    // else
    // {
        this->y = y;
   // }
}

// set paddel width based of the player and width of the playing field
void Paddle::setPaddlex(int pfx, int pfwidth) {
    if (player == 0) {
        this->x = (pfwidth* .05);
    }

    if(player == 1) {
        this->x = pfwidth * .9;
    }
}

void Paddle::update(float delta) {
   // y += 10.f * delta;
}

