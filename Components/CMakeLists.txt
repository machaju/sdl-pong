file(GLOB_RECURSE SLD_PONG_SRC_COMP
     "*.h"
     "*.cpp"
)

set(SDL_PONG_SRC 
    ${SDL_PONG_SRC} 
    ${SLD_PONG_SRC_COMP}
    PARENT_SCOPE)



message(${SLD_PONG_SRC_COMP} )