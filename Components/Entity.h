#ifndef SDL4PONG_ENTITY_H
#define SDL4PONG_ENTITY_H


#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Entity
{
public:
    Entity();
    ~Entity();

    SDL_Texture*    m_texture       { nullptr }; 
    SDL_Renderer*   m_renderer      { nullptr };

    float   x               { 100 };
    float   y               { 100 };
    int     width           { 100 };
    int     height          { 100 };
    int     scaled_width    { 100 };
    int     scaled_height   { 100 };
    float   m_scale         { 0.5f };       // scale the graphics

public:
    virtual void    initImage(SDL_Renderer* renderer_) { };
    virtual void    loadImage(std::string path); 
    void            render(SDL_Surface* srcSurface);

    int     top();
    int     mid(); 
    int     bottom();
};

#endif // SDL4PONG_ENTITY_H
