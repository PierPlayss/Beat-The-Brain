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

int CarPlates(RenderWindow window, SDL_Texture* BGTexture,SDL_Texture* brainTexture, SDL_Texture* LogoTexture,SDL2SoundEffects se, Mix_Music* bgm);
