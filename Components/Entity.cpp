#include "Entity.h"

Entity::Entity()
{

}


Entity::~Entity() {

   //  SDL_FreeSurface( m_surface );
    
}

void Entity::load_image(std::string path, SDL_Renderer* gRenderer) {

    this->gRenderer = gRenderer; 


    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        m_texture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if( m_texture == NULL )
        {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        }

        width = loadedSurface->w;
        height = loadedSurface->h;

        scaled_width = width * m_scale; 
        scaled_height = height * m_scale; 

        //Get rid of old loaded surface
        // SDL_FreeSurface( loadedSurface );
    }

    
}

void Entity::render(SDL_Surface* srcSurface) {
        
        SDL_Rect rect_dst;
            rect_dst.x = static_cast<int>(x); 
            rect_dst.y = static_cast<int>(y); 
            rect_dst.w = static_cast<int>((float)width *m_scale);
            rect_dst.h = static_cast<int>((float)height * m_scale);


        SDL_Rect (rect_src) { 
            .x = 0, 
            .y = 0, 
            .w = width,
            .h = height
     
        };
       // SDL_BlitSurface( m_surface, &rect_src, srcSurface, &rect_dst );


        // //Clear screen
        // SDL_RenderClear( gRenderer );
       

        //Render texture to screen
        SDL_RenderCopy( gRenderer, m_texture, &rect_src, &rect_dst );

      
    
}
