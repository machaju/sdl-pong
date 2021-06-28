# sdl-pong 🕹
Here is a simple pong implementation with SDL2. 

SDL2 is a cross platfrom library that provides low-level access to computer hardware. It is responsible for the windowing, capturing the user input and rendering the objects to the screen.  


## Exexute c++ on the web :) 
asm.js/wasm live demo: https://machaju.github.io/sdl4pong/

Take a look at the top-level CMake for instructions on compiling for the web. Also take note of  `emscripten_set_main_loop(frame_wrapper, 0, 0);` in [main.cpp](main.cpp). 


## REQUIREMENTS

- [SDL2](https://www.libsdl.org/download-2.0.php)
- [SDL_IMAGE](https://www.libsdl.org/projects/SDL_image/)
- [SDL_TTF](https://www.libsdl.org/projects/SDL_ttf/)

The CMakeFinds in [cmake/modules](cmake/modules/) should take care of finding these libraries once they are installed.

## Building Locally 👷‍♀️🚧
### Clone the Repo
   
``` 
> git clone https://github.com/machaju/sdl-pong.git
Cloning into 'sdl-pong'...
```

### Verify Target System

By default, the target set  is set to "web", which will build .js files instead of a c++ executable.

Change this line in [CMakeLists.txt](CMakeLists.txt) from "web" to "auto". 
```
#edit this line to change compile target 
set(EXPORT_TARGET "auto")
```

### Build the project 
``` 
cd sdl-pong
mkdir build
cd build 
cmake ..
make -j4
```

### Run SDL4Pong
```./SDL4Pong```

An SDL window should appear with the game ready to play!  

![SDL4Pong running locally](/images/SDL4Pong-1.png "SDL4Pong")

### Play! 

**Left Click** to begin. 

Move your paddle using your mouse or trackpad. The paddle only moves in the Y direction, so no need to worry about horizontal movement. 

Try to get the ball past the enemy paddle. 

![Playing SDL4Pong locally](/images/SDL4Pong-2.png "SDL4PongPlaying")


## Enemy Paddle
The Enemy paddle will track the ball "imperfectly" using a buffer to slow the paddle down when it gets close to the ball. 

## Difficulty 🔥
You can change the difficulty in [GameScene.cpp](GameScene.cpp).

Possible selections include: 

- EASY
- MEDIUM
- HARD


By default the difficulty is set to HARD. 

```
GameScene::GameScene() {

    // set difficulty
    DIFFICULTY diff = DIFFICULTY::HARD;
```

## ASSETS
I drew [glow-ball.png](assets/glow-ball.png) and [glow-paddle.png](assets/glow-paddle.png) in AffinityDesigner but you can swap them out for better graphics if you'd like, just make sure the names remain the same. 

I'm using and open font called Alieron for the scores. 
