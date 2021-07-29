//
//  Main Components
// -------------------
//  - Ball
//  - Paddel
//  - Playing Field
//  - Scores

#if defined (__EMSCRIPTEN__)
    #include <emscripten/emscripten.h>
    #include <emscripten/html5.h>
#endif
#include <functional>
#include "GameScene.h"

// variable to hold GameScene's frame function for emscripten
std::function<void()> frame_function;

// c style callback function for emscripten_set_main_loop()
// emscripten_set_main_loop() requires  a c style function, 
// since c has no sense of objects, we need a creat a 
// wrapper function to hold the member function
extern "C" void frame_wrapper() { frame_function(); }

int main(int argc, char* args[]) {

    auto scene = new GameScene(); 
    
    // attach the frame function from the scene object to frame_function
    frame_function = std::bind(&GameScene::frame, scene);

    #if defined (__EMSCRIPTEN__)
        emscripten_set_main_loop(frame_wrapper, 0, 0);
    #else
        scene->event_loop(); 
    #endif

    return 0;
}

