cmake_minimum_required(VERSION 3.7)
project(SDL4Pong)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

message(${CMAKE_MODULE_PATH})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/local/include")

# Find the sdl libs and include the headers 
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(SDL4Pong 
                    ${SDL2_INCLUDE_DIRS}
                    ${SDL2_IMAGE_INCLUDE_DIRS}
                    ${SDL2_TTF_INCLUDE_DIRS})

message( ${SDL2_IMAGE_INCLUDE_DIRS})


# add the sub directories for the project 
add_subdirectory("Components")

# pull up the child sources and add the main 
set(SDL_PONG_SRC ${SDL_PONG_SRC} 
    GameScene.cpp
    main.cpp
    )

# add exe and link the libraries 
add_executable(SDL4Pong ${SDL_PONG_SRC})
target_link_libraries(SDL4Pong 
                    ${SDL2_LIBRARIES}
                    ${SDL2_IMAGE_LIBRARIES}
                    ${SDL2_TTF_LIBRARIES})

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_CURRENT_SOURCE_DIR}/assets/*.*
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)