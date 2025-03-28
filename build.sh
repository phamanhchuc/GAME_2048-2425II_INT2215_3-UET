#!/bin/bash

g++ src/*.cpp -o game \
    `sdl2-config --cflags --libs` \
    -lSDL2_image -lSDL2_mixer
