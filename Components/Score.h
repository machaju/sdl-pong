#include <SDL_ttf.h>
#include "Entity.h"

class Score : public Entity 
{
public:
    Score();
    ~Score();
    
    TTF_Font*       Sans            { nullptr }; 
    SDL_Surface*    surfaceMessage  { nullptr };
    int             score           { 0 };              // the score 

    
    void initImage(SDL_Renderer* renderer_) override; 
    void updateScore();        
};