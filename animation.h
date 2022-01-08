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

#include "animation.h"

int menu(RenderWindow window, int mouseX, int mouseY, SDL_Event event, int clicks);

void animationIn(RenderWindow window,
	SDL_Texture* blackTexture,
	SDL_Texture* brainTexture,
	SDL_Texture* LogoTexture,
	SDL_Texture* BGTexture,
	SDL_Texture* titleTexture,
	SDL_Texture* bordeTexture,
	SDL_Texture* extraTexture,
	std::string text, int textX, int textY, int textSize,
	int BGr, int BGg, int BGb);