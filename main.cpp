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

std::function<void()> frame_function;

extern "C" void frame_wrapper() { frame_function(); }

int main(int argc, char* args[]) {

    auto scene = new GameScene(); 
    frame_function = std::bind(&GameScene::frame, scene);

    #if defined (__EMSCRIPTEN__)
        emscripten_set_main_loop(frame_wrapper, 0, 0);
    #else
        scene->event_loop(); 
    #endif

    return 0;
}

