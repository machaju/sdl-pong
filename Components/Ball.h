#include <cmath>



const float BALL_SPEED = 550;


class Ball
{
    public: 

        Ball();
        ~Ball();

        // move the ball x amount of pixels per second
        void move(float seconds);

        void setDirection(int newdirx, int newdiry);


        int x,y;            // the position of the ball
        int width, height;  // the size of the ball
        int dirx, diry;     // the direction of the ball 

        
};