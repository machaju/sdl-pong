#ifndef SDL4PONG_ENTITY_H
#define SDL4PONG_ENTITY_H


#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Entity{

    public:
    Entity();
    ~ Entity();

    void load_image(std::string path, SDL_Renderer* gRenderer); 

    void render(SDL_Surface* srcSurface);


    float x, y = 0;
    int width, height = 0;
    int scaled_width, scaled_height = 0;

    //SDL_Surface* m_surface = nullptr;

    SDL_Texture* m_texture = nullptr; 

    SDL_Renderer* gRenderer;

    float m_scale = 0.5f;


};

#endif // SDL4PONG_ENTITY_H