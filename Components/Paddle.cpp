#include "Paddle.h"

Paddle::Paddle(int p) : player(p)
{
  

}

Paddle::~Paddle()
{
    
}

void Paddle::loadImage(SDL_Renderer* gRenderer)
{
  if(player == 0)
    {
        load_image("paddle.png", gRenderer);
    }
    else{
        load_image("glasspaddle2.png", gRenderer);
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

//    std::cout<< "paddle loc: " << this->x << ", " << this->y  << std::endl; 

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

        // std::cout << "PFX: " << pfx << std::endl; 
        // std::cout << "PFW: " << pfwidth << std::endl; 

        // this->x = 300; 
    }
}

void Paddle::update(float delta) {

   // y += 10.f * delta;

}