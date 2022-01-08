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

int languageGame(SDL_Texture* brainTexture, SDL_Texture* LogoTexture, RenderWindow window);

void sorteador(int array[],int cantidad);
	
void Usado(int usado[], int& random, int lineas);