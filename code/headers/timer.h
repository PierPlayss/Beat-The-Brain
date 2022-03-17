#pragma once
//SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//C++
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cmath>
#include <chrono>
//Headers
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "SDL2SoundEffects.h"

using namespace std;



void timerClock(clock_t time, SDL_Texture* timerTexture, RenderWindow window, bool start, int timer, int angle);
