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

#include "logicGame.h"
#include "animation.h"

using namespace std;

int logicGame(SDL_Texture* brainTexture, SDL_Texture* LogoTexture, SDL_Texture* BGTexture, RenderWindow window) {

	SDL_Texture* boardTexture = window.loadTexture("res/gfx/boardlogic.png");
	SDL_Texture* titleTexture = window.loadTexture("res/gfx/LogicTitle.png");
	SDL_Texture* x1Texture = window.loadTexture("res/gfx/dardox1.png");
	SDL_Texture* x2Texture = window.loadTexture("res/gfx/dardox2.png");
	SDL_Texture* x3Texture = window.loadTexture("res/gfx/dardox3.png");
	SDL_Texture* blackTexture = window.loadTexture("res/gfx/black.png");
	Entity board(135, 110, 1030, 530, boardTexture);
	Entity dardox1(245, 125, 505, 505, x1Texture);
	Entity dardox2(245, 125, 505, 505, x2Texture);
	Entity dardox3(245, 125, 505, 505, x3Texture);

	int total = 501;
	stringstream sc;
	
	bool toggleMenu = false;
	int intmenu = 0;
	int mouseX, mouseY;

	animationIn(window,
		blackTexture, brainTexture, LogoTexture, BGTexture, titleTexture, boardTexture, boardTexture,
		"501", 810, 205, 50,
		88, 18, 29);

	SDL_Event event;
	for (int i = 0; i < 3; i++) {
		int angulo[3];
		int resultado[3] = { 0,0,0 };
		int resultadoaux = 0;
		int random;
		int aux = 0;
		bool logic = true;
		int clicks = -1;
		int subtotal = 0;
		srand(time(NULL));
		bool start = false;
		bool stop = false;
		bool showResults = false;
		bool show1 = false, show2 = false, show3 = false;
		string scoresS;

		for (int j = 0; j < 3; j++) {
			random = rand() % 360;
			aux = random / 18;
			aux = aux * 18;
			angulo[j] = aux;
			setResultados(resultadoaux,angulo[j],j+1);
			resultado[j] = resultadoaux;
			subtotal += resultado[j];
	
		}
		
		subtotal = total - subtotal;

		while (logic) {
			window.clear();
			window.backgroundColor(88, 18, 29, 255);
			Entity BGEntity(0, 0, 1280, 720, BGTexture);
			Entity title(0, 0, 1280, 107, titleTexture);
			SDL_SetTextureAlphaMod(boardTexture, 240);
			window.render(BGEntity, 1);
			window.render(board, 1);
			window.render(title, 1);
			
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					window.backgroundColor(0, 0, 0, 255);
					window.display();
					return 0;
				}
				if (event.button.button == SDL_BUTTON_LEFT) {
					clicks++;
					if (clicks == 1) {
						if (toggleMenu == false) {
							if (showResults == true) {
								logic = false;
							}
							if (start == true) {
								showResults = true;
							}
							start = true;
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
			if (start == true) {
				window.render(dardox1, angulo[0], 1);
				window.render(dardox2, angulo[1], 1);
				window.render(dardox3, angulo[2], 1);
			}
			
			
			sc.clear();
			sc << total;
			sc >> scoresS;
			window.drawText(scoresS.c_str(), 810, 205, 240, 240, 240, 255, 50);
			if (showResults == true) {
				for (int i = 0; i < 3; i++) {
					sc.clear();
					sc << resultado[i];
					sc >> scoresS;
					if (resultado[i] < 10) {
						window.drawText(scoresS.c_str(), 820+25, 290 + (65 * i), 240, 240, 240, 255, 50);
					}
					else window.drawText(scoresS.c_str(), 820, 290+(65*i), 240, 240, 240, 255, 50);
					
				}
				sc.clear();
				sc << subtotal;
				sc >> scoresS;
				window.drawText(scoresS.c_str(), 800, 485, 241, 212, 20, 255, 50);
			}

			if (toggleMenu == true) {
				intmenu = menu(window, mouseX, mouseY, event, clicks);

				if (intmenu == 1) {
					toggleMenu = false;
					SDL_Delay(40);
				}
				if (intmenu == 2) {
					window.backgroundColor(0, 0, 0, 255);
					window.display();
					SDL_DestroyTexture(boardTexture);
					SDL_DestroyTexture(blackTexture);
					SDL_DestroyTexture(x1Texture);
					SDL_DestroyTexture(x2Texture);
					SDL_DestroyTexture(x3Texture);
					return 1;

				}
			}

			window.display();
		}
		total = subtotal;
	}
	window.backgroundColor(0, 0, 0, 255);
	window.display();
	SDL_DestroyTexture(boardTexture);
	SDL_DestroyTexture(blackTexture);
	SDL_DestroyTexture(x1Texture);
	SDL_DestroyTexture(x2Texture);
	SDL_DestroyTexture(x3Texture);
	return 0;

}
void setResultados(int &resultado, int angulo, int multiplicador) {
	if (angulo == 0 or angulo==360) {
		resultado = 20 * multiplicador;
		
	}
	if (angulo == 18) {
		resultado = 1 * multiplicador;
	}
	if (angulo == 36) {
		resultado = 18 * multiplicador;
	}
	if (angulo == 54) {
		resultado = 4 * multiplicador;
	}
	if (angulo == 72) {
		resultado = 13 * multiplicador;
	}
	if (angulo == 90) {
		resultado = 6 * multiplicador;
	}
	if (angulo== 108) {
		resultado = 10 * multiplicador;
	}
	if (angulo == 126) {
		resultado = 15 * multiplicador;
	}
	if (angulo ==144) {
		resultado = 12 * multiplicador;
	}
	if (angulo == 162) {
		resultado = 17 * multiplicador;
	}
	if (angulo ==180) {
		resultado = 3 * multiplicador;
	}
	if (angulo == 198) {
		resultado = 19 * multiplicador;
	}
	if (angulo ==216) {
		resultado = 7 * multiplicador;
	}
	if (angulo == 234) {
		resultado = 16 * multiplicador;
	}
	if (angulo == 252) {
		resultado = 8 * multiplicador;
	}
	if (angulo == 270) {
		resultado = 11 * multiplicador;
	}
	if (angulo ==288) {
		resultado = 14 * multiplicador;
	}
	if (angulo ==306) {
		resultado = 9 * multiplicador;
	}
	if (angulo == 324) {
		resultado = 12 * multiplicador;
	}
	if (angulo ==342) {
		resultado = 5 * multiplicador;
	}
	
}