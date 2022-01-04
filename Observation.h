#pragma once
//SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//C++
#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <string>
//Headers
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "SDL2SoundEffects.h"

int brickGame(SDL_Texture* brickTexture, SDL_Texture* brickAfter,SDL_Texture* background, RenderWindow gamesWindow);
void setup(int &brockenBricks , int bricks[10][10]);
void displayBricks(SDL_Texture* brickTexture, RenderWindow gamesWindow, int bricks[10][10],bool show);
