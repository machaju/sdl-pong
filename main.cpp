

#include "GameScene.h"

//  Main Components
// -------------------
//  - Ball
//  - Paddel
//  - Playing Field
//  - Scores




int main(int argc, char* args[]) {

    auto scene = new GameScene(); 
    scene->event_loop(); 

    return 0;
}

