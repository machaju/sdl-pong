#include "Paddle.h"

Paddle::Paddle(int p) : player(p)
{
    loadImage(); 

}

Paddle::~Paddle()
{

    SDL_FreeSurface( m_surface );

    
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

    std::cout<< "paddle loc: " << this->x << ", " << this->y  << std::endl; 

}

// set paddel width based of the player and width of the playing field
void Paddle::setPaddlex(int pfx, int pfwidth) {

    if(player == 0)
    {
        this->x = (pfwidth* .05);
    }

    if(player == 1)
    {
        this->x = pfx + pfwidth;
    }
}

    void Paddle::loadImage() {

    if(player == 0)
    {
        m_surface = IMG_Load("paddle.png");
    }
    else{
        m_surface = IMG_Load("glasspaddle2.png");
    }

    width = m_surface->w;
    height = m_surface->h;

}


void Paddle::update(float delta) {

   // y += 10.f * delta;

}