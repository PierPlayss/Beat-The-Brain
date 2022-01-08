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

#include "Orientation.h"
#include "animation.h"
using namespace std;

int relojesGame(SDL_Texture* brainTexture, SDL_Texture* LogoTexture, SDL_Texture* background,RenderWindow window) {
	SDL_Texture* relojTexture = window.loadTexture("res/gfx/Orientation/watch.png");
	SDL_Texture* bordeTexture = window.loadTexture("res/gfx/bordeReloj.png");
	SDL_Texture* aguja2Texture = window.loadTexture("res/gfx/Orientation/arrow.png");
	SDL_SetTextureAlphaMod(aguja2Texture,150);
	SDL_Texture* aguja1Texture = window.loadTexture("res/gfx/Orientation/shortarrow.png");
	SDL_SetTextureAlphaMod(aguja1Texture,150);
	SDL_Texture* titleTexture = window.loadTexture("res/gfx/OrientationTitle.png");
	SDL_Texture* blackTexture = window.loadTexture("res/gfx/black.png");

	animationIn(window,
		blackTexture, brainTexture, LogoTexture, background, titleTexture, bordeTexture, bordeTexture,
		" ", 0, 0, 0, 
		161, 113, 16);
	

	bool toggleMenu = false;
	int intmenu = 0;
	int mouseX, mouseY;



	window.backgroundColor(161, 113, 16, 255);
	Entity BGEntity(0, 0, 1280, 720, background);
	window.render(BGEntity, 1);
	window.display();
	stringstream tm;
	string tiempo;
	int aux2 = 0;
	SDL_Event event;
	srand(time(NULL));
	for (int i = 0; i < 3; i++) {
		int horaAngulo = 0, minAngulo = 0;
		bool orientation = true;
		bool canShow = false;
		int clicks = -1;
		horaAngulo = rand() % 360;
		aux2 = horaAngulo / 30;
		horaAngulo = aux2 * 30;
		minAngulo = rand() % 360;
		aux2 = minAngulo / 30;
		minAngulo = aux2 * 30;
		int horaAngEspejo = 0;
		int minAngEspejo = 0;
		int aux;
		int opacidad = 0;
		int horaInt = 0;
		int minutoInt = 0;
		int centrador = 0;
		if (horaAngulo < 180) {
			aux = 180 - horaAngulo;
			horaAngEspejo = 180 + aux;
		}
		else {
			aux = horaAngulo - 180;
			horaAngEspejo = 180 - aux;
		}
		horaInt = horaAngEspejo / 30;
		if (minAngulo < 180) {
			aux = 180 - minAngulo;
			minAngEspejo = 180 + aux;
		}
		else {
			aux = minAngulo - 180;
			minAngEspejo = 180 - aux;
		}
		minutoInt = minAngEspejo / 6;
		if (minutoInt == 60) {
			minutoInt = 0;
			tm.clear();
			tm << horaInt << ":" << minutoInt << "0";
			tm >> tiempo;
		}
		else if (minutoInt < 10) {
			tm.clear();
			tm << horaInt << ":" << "0" << minutoInt;
			tm >> tiempo;
		}
		else {
			tm.clear();
			tm << horaInt << ":" << minutoInt;
			tm >> tiempo;
		}
		

		if (horaInt >= 10) {
			centrador += 100;
		}
		else centrador += 50;
		
		while (orientation) {
			window.RenderWindow::clear();
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
							if (canShow == true) {

								orientation = false;

							}
							if (canShow == false) {
								opacidad = 255;
								SDL_SetTextureAlphaMod(relojTexture, opacidad);
								SDL_SetTextureAlphaMod(aguja1Texture, opacidad);
								SDL_SetTextureAlphaMod(aguja2Texture, opacidad);
								canShow = true;
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
			
			
			window.backgroundColor(161, 113, 16, 255);
			Entity BGEntity(0, 0, 1280, 720, background);
			window.render(BGEntity, 1);

			Entity borde(135, 110, 1030, 530, bordeTexture);
			window.render(borde, 1);
			if (canShow == false) {
				if (opacidad < 255)
				{
					opacidad += 10;
				}
				if (opacidad > 255) {
					opacidad = 255;
				}
				SDL_SetTextureAlphaMod(relojTexture, opacidad);
				SDL_SetTextureAlphaMod(aguja1Texture, opacidad);
				SDL_SetTextureAlphaMod(aguja2Texture, opacidad);
				Sleep(40);
			}
			for (int i = 0; i < 2; i++) {

				Entity relojes(225 + (475 * i), 185, 383, 383, relojTexture);
				window.render(relojes, 1);

			}
			Entity minutos(226, 185, 384, 383, aguja2Texture);
			window.render(minutos, minAngulo, 1);
			Entity hora(227, 185, 383, 383, aguja1Texture);
			window.render(hora, horaAngulo, 1);

			if (canShow == true) {

				Entity minutos(701, 185, 384, 383, aguja2Texture);
				window.render(minutos, minAngEspejo, 1);
				Entity hora(701, 185, 383, 383, aguja1Texture);
				window.render(hora, horaAngEspejo, 1);
				
				
				window.drawText(tiempo.c_str(), 515 - centrador, 280, 70, 70, 70, 160, 150);
				window.drawText(tiempo.c_str(), 510 - centrador, 275, 230, 230, 230, 255, 150);
			}

		

			Entity title(0, 0, 1280, 109, titleTexture);
			window.render(title, 1);


			if (toggleMenu == true) {
				intmenu = menu(window, mouseX, mouseY, event, clicks);

				if (intmenu == 1) {
					toggleMenu = false;
					SDL_Delay(40);
				}
				if (intmenu == 2) {
					window.backgroundColor(0, 0, 0, 255);
					window.display();
					SDL_DestroyTexture(relojTexture);
					SDL_DestroyTexture(bordeTexture);
					SDL_DestroyTexture(titleTexture);
					SDL_DestroyTexture(blackTexture);
					return 1;

				}
			}

			window.display();

		}
	}
	
	
	window.backgroundColor(0, 0, 0, 255);
	window.display();
	SDL_DestroyTexture(relojTexture);
	SDL_DestroyTexture(bordeTexture);
	SDL_DestroyTexture(titleTexture);
	SDL_DestroyTexture(blackTexture);
	return 0;
}