#pragma once
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

int logicGame(SDL_Texture* brainTexture, SDL_Texture* LogoTexture,SDL_Texture* BGTexture, RenderWindow window);
void setResultados(int &resultado, int angulo, int multiplicador);