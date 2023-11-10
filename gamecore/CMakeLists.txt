cmake_minimum_required(VERSION 3.0.0)
project(CarrotIsYou VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(CarrotIsYou sdl_main.cpp CarrotOS.cpp CIYBoard.cpp CIYCore.cpp ./lib/MiniMalloc.cpp ./lib/LevelManager.cpp ./lib/keyInput.cpp ./lib/Interfaces.cpp)
target_link_libraries(CarrotIsYou SDL2main)
target_link_libraries(CarrotIsYou SDL2)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_FLAGS "-static-libstdc++ ${CMAKE_CXX_FLAGS}")
include(CPack)