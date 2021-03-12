#include <SDL.h>
#include <SDL_image.h>
#include <iostream>



class Paddle
{
    public:

        Paddle(int player);
        ~Paddle();

        // move paddle based on mous y location
        void movePaddle(int y, int pfy, int pfh);

        void setPaddlex(int pfx, int pfwidth);

        void loadImage(); 
        void update(float delta);


        float x { 0 }, y { 0 };            // the position of the paddle
        int width, height;   // the size of the paddle
        int player;         // whos paddle is this 0 = player , 1 = ai 

        SDL_Surface* m_surface = nullptr;
};