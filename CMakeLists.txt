##################################################################
#
#   To compile, set target manually below:
#
#       "auto"      Attempt to autodetect
#       "osx"       MacOS
#       "web"       Emscripten
#       "windows"   Windows
#       "linux"     Linux
#
##################################################################
##################################################################

# change this line to change compile target 
set(EXPORT_TARGET "web")


##################################################################
##################################################################
# set cmake version
cmake_minimum_required(VERSION 3.7)

project(SDL4Pong)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

# determine target
if (EXPORT_TARGET MATCHES "auto")
    if     (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        set(EXPORT_TARGET "osx")
    elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        set(EXPORT_TARGET "windows")
    elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        set(EXPORT_TARGET "linux")
    endif()
endif()
if     (EXPORT_TARGET MATCHES "osx") 
    add_compile_definitions(TARGET_MAC)
elseif (EXPORT_TARGET MATCHES "web") 
    add_compile_definitions(TARGET_WEB)
elseif (EXPORT_TARGET MATCHES "windows") 
    add_compile_definitions(TARGET_WIN)
elseif (EXPORT_TARGET MATCHES "linux") 
    add_compile_definitions(TARGET_LIN)
endif()


# add the sub directories for the project 
add_subdirectory("Components")

# pull up the child sources and add the main 
set(SDL_PONG_SRC ${SDL_PONG_SRC} 
    GameScene.cpp
    main.cpp
    )

# add exe and link the libraries 
add_executable(SDL4Pong ${SDL_PONG_SRC})

# copy 'assets' directory to 'build' directory
add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/*.*
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)

if (EXPORT_TARGET MATCHES "osx")


  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/local/include")

  # Find the sdl libs and include the headers 
  find_package(SDL2 REQUIRED)
  find_package(SDL2_image REQUIRED)
  find_package(SDL2_ttf REQUIRED)

  include_directories(SDL4Pong 
                      ${SDL2_INCLUDE_DIRS}
                      ${SDL2_IMAGE_INCLUDE_DIRS}
                      ${SDL2_TTF_INCLUDE_DIRS})




  target_link_libraries(SDL4Pong 
                      ${SDL2_LIBRARIES}
                      ${SDL2_IMAGE_LIBRARIES}
                      ${SDL2_TTF_LIBRARIES})

elseif (EXPORT_TARGET MATCHES "web")
    # To optimze file size in order: -O1, -O2, -O3, -Os, -Oz
    set(CMAKE_C_LINK_FLAGS "")                  # Clear the linker flags that clang tries to use
    set(CMAKE_CXX_LINK_FLAGS "")                # Clear the linker flags that clang tries to use
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=[png] -s USE_SDL_TTF=2 -Oz -std=c++11 --shell-file ../shell.html") 
    set(CMAKE_C_COMPILER "emcc")
    set(CMAKE_CXX_COMPILER "emcc")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    #   --preload-file assets/shapes.png        # To allow access to local filesystem
    #   --embed-file assets/shapes.png          # To embed in js file, not compatible yet with sokol_app
    #   -s ALLOW_MEMORY_GROWTH=1                # To allow for dynamic memory access
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-s TOTAL_MEMORY=33554432 -s DEMANGLE_SUPPORT=1 -s WASM=0 -std=c++11 --bind --preload-file glow-ball.png --preload-file glow-paddle.png --preload-file Aileron-SemiBold.otf")

    # -s TOTAL_MEMORY=X  with X higher than the current value 16777216

    # -s WASM=0                         force javascript or
    # -s WASM=1                         use webassembly
    # --shell-file <path>               create a html file without emscripten logo and debug shell

elseif (EXPORT_TARGET MATCHES "windows")

    ### TODO ###

elseif (EXPORT_TARGET MATCHES "linux")

    ### TODO ###

endif()
                  