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
#include "language.h"
#include "carplates.h"

#include "animation.h"

using namespace std;

RenderWindow window("Beat the brain", 1280, 720);
//RenderWindow gamesWindow("Games Window", 1000, 500);

const int FPS = 60;
int refreshRate = 1000 / FPS;
int frame = 0;

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
	se.addSoundEffect("res/sound/observation/car.mp3");//8
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
	bool toggleMenu = false;
	int intmenu = 0;
	int ended = 0;
	
	srand(time(NULL));
	while (gameRunning)
	{	
		
		int aux = 0;
		bool rendered = true;
		window.RenderWindow::clear();
		// Get our controls and events
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				gameRunning = false;
			if (event.type == SDL_MOUSEMOTION) {

				mouseX = event.motion.x;
				mouseY = event.motion.y;
				//cout << mouseX << "," << mouseY << endl;
				
			}
			if (event.button.button == SDL_BUTTON_LEFT) {
				SDL_Delay(20);
				clicks++;
				if (clicks == 1) {
					if (toggleMenu == false) {
						if (start == true) {
							stop = true;
						}
						else start = true;
					}
				}
				else clicks = 0;
			}
			if (event.type == SDL_KEYDOWN) {
				if ((event.key.keysym.sym == SDLK_RETURN) &&
					(event.key.keysym.mod & KMOD_ALT))
				{
					window.ToggleFullscreen(); 
				}
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					if (toggleMenu == false) {
						toggleMenu = true;
					}
					else toggleMenu = false;
				}
				
			}
		}
		
		
		
		if (stop == false) {
			
			window.backgroundColor(0, 0, 0, 255);
			window.render(BackgroundE, 1);
			window.render(Logo, 1);
			
		}
		if (toggleMenu == false) {
			if (start == false) {
				if (frame == FPS) {
					contador++;
					frame = 0;
					if (contador == 6) {
						contador = 0;
					}
				}

				window.drawText("Press click to start", 385, 650, 240, 240, 240, 255, 40);

			}
			else {

				if (stop == false) {
					if (frame * 2 == FPS) {
						contador++;
						//contador = rand() % 6;
						frame = 0;
						if (contador == 6) {
							contador = 0;
						}
					}
				}
			}


		}


		if (contador == 0 and played[0] == true) {
			contador++;
		}
		if (contador == 1 and played[1] == true) {
			contador++;
		}
		if (contador == 2 and played[2] == true) {
			contador++;
		}
		if (contador == 3 and played[3] == true) {
			contador++;
		}
		if (contador == 4 and played[4] == true) {
			contador++;
		}
		if (contador == 5 and played[5] == true) {
			while (rendered) {
				if (played[aux] == false) {
					contador = aux;
					rendered = false;
				}
				else aux++;
			}
		}
		ended = 0;
		for (int i = 0; i < 6; i++) {
			if (played[i] == true) {
				ended++;
			}
			if (ended == 6) {
				gameRunning = false;
			}
		}


		if (contador == 0) {
			window.render(LogicE, 1);
		}
		if (contador == 1) {
			window.render(MemoryE, 1);
		}
		if (contador == 2) {
			window.render(OrientationE, 1);
		}
		if (contador == 3) {
			window.render(ObservationE, 1);
		}
		if (contador == 4) {
			window.render(LanguageE, 1);
		}
		if (contador == 5) {
			window.render(MTE, 1);
			//contador = -1;
		}


		//cout << contador << endl;

		if (stop == true) {
			Sleep(600);
			//cout << contador << endl;
			if (contador == 0) {
				if (logicGame(brainLogic, LogoTexture, BGTexture, window) == 0) {
					played[contador] = true;
				}
			}
			if (contador == 1) {
				if (ColorGame(brainMemory, LogoTexture, BGTexture, window, se) == 0) {
					played[contador] = true;
				}
			}
			if (contador == 2) {
				if (relojesGame(brainOrientation, LogoTexture, BGTexture, window) == 1) {
					played[contador] = true;
				}				
			}
			if (contador == 3) {
				CarPlates(window, BGTexture, brainObservation, LogoTexture, se);
				if (brickGame(brainObservation, LogoTexture, brickTexture, brickAfterTexture, BGTexture, window) == 0) {
					played[contador] = true;
				}
			
			}
			if (contador == 4) {
				if (languageGame(brainLanguage, LogoTexture, window) == 0) {
					played[4] = true;
				}				
			}
			if (contador == 5) {
				if (discosGame(brainMT, LogoTexture, BGTexture, window) == 0) {
					played[5] = true;
				}				
			}

			stop = false;
			start = false;
			contador == 0;

		}
		
		
		if (toggleMenu == true) {
			intmenu = menu(window, mouseX, mouseY, event, clicks);
				if (intmenu == 1) {
					toggleMenu = false;
				}
				if (intmenu == 2) {
					gameRunning = false;
					
				}
		}


		window.display();

		Sleep(refreshRate);
		if (frame == FPS) {
			frame = 0;
		}
		else frame++;
	}

	window.cleanUp();
	SDL_Quit();
	TTF_Quit();

	return 0;
}

