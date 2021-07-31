#include "Score.h"
#include <iostream>

Score::Score() { 

}
Score::~Score() { }

void Score::initImage(SDL_Renderer* renderer_) {
    m_renderer = renderer_; 

    Sans = TTF_OpenFont("Aileron-SemiBold.otf", 120); //this opens a font style and sets a size
    if (Sans == NULL) {
        printf( "Unable to load font. Error: %s \n",  TTF_GetError() );
    }
    SDL_Color color = { 255,39,210 };

    // As TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
    surfaceMessage = TTF_RenderText_Blended(Sans, std::to_string(score).c_str(), color ); 
    // Now you can convert it into a texture
    m_texture = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage); 

    if (m_texture == NULL) {
        printf( "Unable to create font texture! SDL Error: %s\n", SDL_GetError() );
    }

    SDL_QueryTexture(m_texture, NULL, NULL, &width, &height);    
}

void Score::updateScore() {
    SDL_Color color = { 255,39,210 };

    if (surfaceMessage != nullptr) {
        SDL_FreeSurface(surfaceMessage);
        surfaceMessage = nullptr;
    }
    int curr_digits = check_digits(score); 

    if (curr_digits != digits)
    {
        digits = curr_digits; 
        int newwidth = digits * width;
        int newheight = height; 

        resizeRect(newwidth, newheight);
    }
    surfaceMessage = TTF_RenderText_Blended(Sans, std::to_string(score).c_str(), color);
    m_texture = SDL_CreateTextureFromSurface(m_renderer, surfaceMessage);
}

int Score::check_digits(int number)
{
    int check_digits = 0; 
    while (number != 0) { 
        number /= 10; 
        check_digits++; 
        }

    return check_digits; 
}
