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

//Games
#include "Observation.h"
#include "Orientation.h"
#include "Memory.h"
#include "logicGame.h"
#include "discos.h"


using namespace std;

RenderWindow window("Beat the brain", 1280, 720);
//RenderWindow gamesWindow("Games Window", 1000, 500);




int main(int argc, char* argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		cout << "IMG_init has failed. Error: " << SDL_GetError() << endl;
	
	if (TTF_Init() == -1) {
		cout << "TTF_init has failed. Error: " << SDL_GetError() << endl;
	}
	int mouseX, mouseY;
	int clicks = 0;
	const int FPS = 60;
	int framerate = 0;
	//Sounds
	SDL2SoundEffects se;
	se.addSoundEffect("res/sound/memory/pink.mp3");//0
	se.addSoundEffect("res/sound/memory/red.mp3");//1
	se.addSoundEffect("res/sound/memory/white.mp3");//2
	se.addSoundEffect("res/sound/memory/blue.mp3");//3
	se.addSoundEffect("res/sound/memory/black.mp3");//4
	se.addSoundEffect("res/sound/memory/green.mp3");//5
	se.addSoundEffect("res/sound/memory/yellow.mp3");//6
	se.addSoundEffect("res/sound/memory/purple.mp3");//7
	//se.addSoundEffect("res/sound/strike.mp3"); //0

	SDL_Texture* brickTexture =window.loadTexture("res/gfx/brick.png");
	SDL_Texture* brickAfterTexture = window.loadTexture("res/gfx/brickAfter.png");
	//Menu
	SDL_Texture* brainLogic = window.loadTexture("res/gfx/logic.png");
	SDL_Texture* brainMemory = window.loadTexture("res/gfx/memory.png");
	SDL_Texture* brainObservation = window.loadTexture("res/gfx/observation.png");
	SDL_Texture* brainOrientation = window.loadTexture("res/gfx/orientation.png");
	SDL_Texture* brainLanguage = window.loadTexture("res/gfx/language.png");
	SDL_Texture* brainMT = window.loadTexture("res/gfx/multitasking.png");
	SDL_Texture* BGTexture = window.loadTexture("res/gfx/background.png");
	SDL_Texture* LogoTexture = window.loadTexture("res/gfx/logo.png");
	Entity LogicE(0, 50,1280, 720, brainLogic);
	Entity MemoryE(0, 50, 1280, 720, brainMemory);
	Entity ObservationE(0, 50, 1280, 720, brainObservation);
	Entity OrientationE(0, 50, 1280, 720, brainOrientation);
	Entity LanguageE(0, 50, 1280, 720, brainLanguage);
	Entity MTE(0, 50, 1280, 720, brainMT);
	Entity BackgroundE(0, 0, 1280, 720, BGTexture);
	Entity Logo(0, 0, 1280, 720, LogoTexture);
	//bricks[2][1] = 1;
	SDL_Event event;
	SDL_Event mouseEvent{ SDL_MOUSEMOTION };

	




	bool gameRunning = true;
	int contador = 0;
	bool played[6] = { 0,0,0,0,0,0 };
	bool start = false;
	bool stop = false;
	srand(time(NULL));
	while (gameRunning)
	{	
		window.RenderWindow::clear();
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
			if (event.type == SDL_MOUSEMOTION) {

				mouseX = event.motion.x -25;
				mouseY = event.motion.y -25;
				//cout << mouseX << "," << mouseY << endl;
				
			}
			if (event.button.button == SDL_BUTTON_LEFT) {
				clicks++;
				if (clicks == 1) {
					if (start == true) {
						stop = true;
					}
					else start = true;
				}
				else clicks = 0;
			}
		}
		
	
		if (stop == false) {
			
			window.backgroundColor(0, 0, 0);
			window.render(BackgroundE, 1);
			window.render(Logo, 1);
			
		}

		if (start == false) {
			contador++;
			Sleep(1000);
			
			window.drawText("Press click to start", 385, 650, 240, 240, 240, 255, 40);
			

		}
		else {
			/*if (stop == false) {
				contador++;
				Sleep(1000);
			}*/
			if (stop == false) {
				//contador++;
				contador = rand() % 5;
				//cout << contador << endl;
				Sleep(400);
			}

		}

		if (contador == 0) {
			if (played[contador] == false) {
				window.render(LogicE, 1);
			}
			else contador++;
			
		}
		if (contador == 1) {
			if (played[contador] == false) {
				window.render(MemoryE, 1);
			}
			else contador++;
		}
		if (contador == 2) {
			if (played[contador] == false) {
				window.render(OrientationE, 1);
			}
			else contador++;
		}
		if (contador == 3) {
			if (played[contador] == false) {
				window.render(ObservationE, 1);
			}
			else contador++;
		}
		///*if (contador == 4) {
		//	window.render(LanguageE, 1);
		//}
		if (contador == 4) {
			if (played[contador] == false) {
				window.render(MTE, 1);
			}
			else contador++;
			
			//contador = -1;
		}
	
		
		if (stop == true) {
			Sleep(600);
			//cout << contador << endl;
			if (contador == 0) {
				logicGame(BGTexture, window);
				played[contador] = true;
			}
			if (contador == 1) {
				ColorGame(BGTexture, window,se);
				played[contador] = true;
			}
			if (contador == 2) {
				relojesGame(BGTexture, window);
				played[contador] = true;
			}
			if (contador == 3) {
				brickGame(brickTexture, brickAfterTexture, BGTexture, window);
				played[contador] = true;
			}
			if (contador == -1) {
				discosGame(BGTexture, window);
				played[contador] = true;
			}
			
			stop = false;
			start = false;
			contador == 0;
			window.clear();
		}
		
		if (contador >= 4) {
			//window.render(MTE, 1);
			contador = -1;
		}

		



		window.display();
		
		
	
	
	}

	window.cleanUp();
	SDL_Quit();
	TTF_Quit();

	return 0;
}

