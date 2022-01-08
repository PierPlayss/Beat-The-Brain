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

int ColorGame(SDL_Texture* brainTexture, SDL_Texture* LogoTexture,SDL_Texture* BGT,RenderWindow window, SDL2SoundEffects se);

void renderBG(SDL_Texture* BGTexture, SDL_Texture* bordeTexture, SDL_Texture* titleTexture, RenderWindow window);
void generadorRandom(int& anterior, int& random,int x,int y);
void setCero(int array[]);
void displayColors(int array[],RenderWindow window,
	SDL_Texture* pinkTexture,
	SDL_Texture* redTexture,
	SDL_Texture* whiteTexture,
	SDL_Texture* blueTexture,
	SDL_Texture* blackTexture,
	SDL_Texture* greenTexture,
	SDL_Texture* yellowTexture,
	SDL_Texture* purpleTexture);
void displayAnswers(int array[10][1],int contador,  RenderWindow window);

