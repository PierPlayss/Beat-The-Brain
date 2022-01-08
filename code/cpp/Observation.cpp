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

#include "Observation.h"
#include "animation.h"
using namespace std;



int brickGame(SDL_Texture* brainTexture, SDL_Texture* LogoTexture, SDL_Texture* brickTexture, SDL_Texture* brickAfter, SDL_Texture* background,RenderWindow gamesWindow) {
	SDL_Texture* bordeTexture = gamesWindow.loadTexture("res/gfx/borde.png");
	SDL_Texture* obTitleTexture = gamesWindow.loadTexture("res/gfx/ObservationTitle.png");
	Entity titleE(0, 0, 1280, 107, obTitleTexture);
	int bricks[10][10];
	int brockenBricks = 0;
	bool showBroken = false;
	bool observation = true;
	bool showTotal = false;
	int clicks = -1;
	stringstream tb;
	string brickString;
	int opacidad = 1;
	


	bool toggleMenu = false;
	int intmenu = 0;
	int mouseX, mouseY;

	SDL_Event event;
	
	for (int i = 0; i < 3; i++) {
		int brockenBricks = 0;
		opacidad = 1;
		setup(brockenBricks, bricks);
		observation = true;
		showBroken = false;
		showTotal = false;
		while (observation) {
			gamesWindow.RenderWindow::clear();
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					observation = false;

				if (event.button.button == SDL_BUTTON_LEFT) {
					clicks++;
					if (clicks == 1) {
						if (toggleMenu == false) {
							if (showTotal == true) {
								observation = false;
								gamesWindow.backgroundColor(0, 0, 0, 255);
							}
							if (showBroken == true) {
								showTotal = true;
							}
							else {
								opacidad = 255;
								SDL_SetTextureAlphaMod(brickTexture, opacidad);
								showBroken = true;
							}
						}
					
					}
					else clicks = 0;

				}
				if (event.type == SDL_MOUSEMOTION) {

					mouseX = event.motion.x;
					mouseY = event.motion.y;
					//cout << mouseX << "," << mouseY << endl;

				}
				if (event.type == SDL_KEYDOWN) {
					if ((event.key.keysym.sym == SDLK_RETURN) &&
						(event.key.keysym.mod & KMOD_ALT))
					{
						gamesWindow.ToggleFullscreen();
					}
					if (event.key.keysym.sym == SDLK_ESCAPE) {
						if (toggleMenu == false) {
							toggleMenu = true;
						}
						else toggleMenu = false;
					}
				}
			}
			
			gamesWindow.backgroundColor(31, 82, 33, 255);
			gamesWindow.render(titleE, 1);
			gamesWindow.drawText("Cuenta los ladrillos que faltan", 530, 38, 240, 240, 240, 255, 21);
			Entity BackgroundE(0, 0, 1280, 720, background);
			gamesWindow.render(BackgroundE, 1);

			if (GetAsyncKeyState('R')) {
				showBroken = false;
				setup(brockenBricks, bricks);
				showTotal = false;
			}

			if (showTotal == true) {
				displayBricks(brickAfter, gamesWindow, bricks, 0);
			}

			if (showBroken == true)displayBricks(brickTexture, gamesWindow, bricks, 1);
			else {
				if (opacidad < 255)
				{
					opacidad += 10;
				}
				if (opacidad > 255) {
					opacidad = 255;
				}SDL_SetTextureAlphaMod(brickTexture, opacidad);

				Sleep(40);
				displayBricks(brickTexture, gamesWindow, bricks, 0);
			}

			if (showTotal == true) {
				tb.clear();
				tb << brockenBricks;
				tb >> brickString;
				gamesWindow.drawText(brickString.c_str(), 515, 280, 70, 70, 70,125, 150);
				gamesWindow.drawText(brickString.c_str(), 510, 275, 230, 230, 230,255, 150);
			}
			Entity borde(135, 110, 1030, 530, bordeTexture);
			gamesWindow.render(borde, 1);

			if (toggleMenu == true) {
				intmenu = menu(gamesWindow, mouseX, mouseY, event, clicks);

				if (intmenu == 1) {
					toggleMenu = false;
					SDL_Delay(40);
				}
				if (intmenu == 2) {
					gamesWindow.backgroundColor(0, 0, 0, 255);
					gamesWindow.display();
					SDL_DestroyTexture(bordeTexture);
					SDL_DestroyTexture(obTitleTexture);
					return 1;

				}
			}


			gamesWindow.display();
		}
	
	}
	gamesWindow.backgroundColor(0, 0, 0, 255);
	gamesWindow.display();
	SDL_DestroyTexture(bordeTexture);
	SDL_DestroyTexture(obTitleTexture);
	return 0;
}



void setup(int &brockenBricks,int bricks[10][10]) {

	int contador = 0;
	int auxiliar = 0;
	int randomNumber[2] = { 0,0 };
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			bricks[j][i] = 0;
		}
	}
	srand(time(NULL));
	brockenBricks = 15 + rand() % 10;
	//cout << brockenBricks << endl;

	while (contador != brockenBricks) {
		auxiliar= rand() % 4;
		if (contador+3 < brockenBricks and auxiliar==1) {
			randomNumber[1] = rand() % 9;
			randomNumber[0] = rand() % 9;
			for (int i = 0; i < 3; i++) {
				if (bricks[randomNumber[0] + i][randomNumber[1]] == 0) {
					bricks[randomNumber[0] + i][randomNumber[1]] = 1;
					contador++;
				}
				
			}
			
		}
		if (contador + 3 < brockenBricks and auxiliar == 2) {
			randomNumber[1] = rand() % 9;
			randomNumber[0] = rand() % 9;
			for (int i = 0; i < 2; i++) {
				if (bricks[randomNumber[0] + i][randomNumber[1] + i] == 0) {
					bricks[randomNumber[0] + i][randomNumber[1] + i] = 1;
					contador++;
					
				}
			}
			if (bricks[randomNumber[0] + 2][randomNumber[1] + 1] == 0) {
				bricks[randomNumber[0] + 2][randomNumber[1] + 1] = 1;
				contador++;
				
			}
		
			
		}
		if (auxiliar == 3) {
			randomNumber[1] = rand() % 9;
			randomNumber[0] = rand() % 9;
			if (bricks[randomNumber[0]][randomNumber[1]] == 0) {
				bricks[randomNumber[0]][randomNumber[1]] = 1;
				contador++;
				
			}
			
		}
	}
	brockenBricks = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (bricks[j][i] == 1) {
				brockenBricks++;
			}
		}
	}
	
}

void displayBricks(SDL_Texture* brickTexture, RenderWindow gamesWindow, int bricks[10][10],bool show) {
	int bricksNotBroken[10][10];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			bricksNotBroken[j][i] = 0;
		}
	}
	
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (show == 0) {
				if (bricksNotBroken[j][i] == 0) {
					if (i % 2 == 0 and j == 0) {
						Entity brick(150+(100 * j), 125 + (50 * i), 47, 45, brickTexture);
						gamesWindow.render(brick, 1);
					}
					else if (i % 2 == 0) {
						Entity brick(150 + -45 + (100 * j), 125 + (50 * i), 95, 45, brickTexture);
						gamesWindow.render(brick, 1);
					}
					else {
						Entity brick(150 + (100 * j), 125 + (50 * i), 95, 45, brickTexture);
						gamesWindow.render(brick, 1);
					}

				}

			}
			else {
				if (bricks[j][i] == 0) {
					if (i % 2 == 0 and j == 0) {
						Entity brick(150 + (100 * j), 125 + (50 * i), 47, 45, brickTexture);
						gamesWindow.render(brick, 1);
					
					}
					else if (i % 2 == 0) {
						Entity brick(150 + -45 + (100 * j), 125 + (50 * i), 95, 45, brickTexture);
						gamesWindow.render(brick, 1);
					}
					else {
						Entity brick(150 + 0 + (100 * j), 125 + (50 * i), 95, 45, brickTexture);
						gamesWindow.render(brick, 1);
					}

				}

			}
			
		}
	}
	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0) {
			Entity brick(1105, 125 + (50 * i), 47, 45, brickTexture);
			gamesWindow.render(brick, 1);
		}

	}
}