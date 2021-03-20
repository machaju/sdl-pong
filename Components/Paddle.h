#ifndef SDL4PONG_PADDLE_H
#define SDL4PONG_PADDLE_H

#include "Entity.h"

class Paddle : public Entity
{
public:
    Paddle(int player);
    ~Paddle();


    int  player     { 0 };              // whos paddle is this 0 = player , 1 = ai    

public:
    void initImage(SDL_Renderer* renderer_) override; 
    void movePaddle(int y, int pfy, int pfh);
    void setPaddlex(int pfx, int pfwidth);
    void update(float delta);
};

#endif // SDL4PONG_PADDLE_H