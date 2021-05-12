# sdl-pong
Here is a simple pong implementation with SDL2. 

## Exexute c++ on the web :) 
asm.js/wasm live demo: https://machaju.github.io/sdl4pong/
Take a look at the top-level CMake for instructions on compiling for the web. Also take note of  `emscripten_set_main_loop(frame_wrapper, 0, 0);` in `main.cpp`. 

## REQUIREMENTS
- SDL2
- SDL_IMAGE
- SDL_TTF

