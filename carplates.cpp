//SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//C++
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <fstream>
//Headers
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "SDL2SoundEffects.h"

#include "carplates.h"
#include "language.h"
#include "animation.h"

using namespace std;

int CarPlates(RenderWindow window, SDL_Texture* BGTexture, SDL_Texture* brainTexture, SDL_Texture* LogoTexture,SDL2SoundEffects se) {
	SDL_Texture* plateTexture = window.loadTexture("res/gfx/plate.png");
	SDL_Texture* plateSelectedTexture = window.loadTexture("res/gfx/plateSelected.png");
	SDL_Texture* carTexture = window.loadTexture("res/gfx/car.png");
	SDL_Texture* cityTexture = window.loadTexture("res/gfx/city.png");
	SDL_Texture* bordeTexture = window.loadTexture("res/gfx/borde.png");
	SDL_Texture* obTitleTexture = window.loadTexture("res/gfx/ObservationTitle.png");
	SDL_Texture* blackTexture = window.loadTexture("res/gfx/black.png");
	Entity title(0, 0, 1280, 107, obTitleTexture);
	string plateFont = { "res/font/Licencia.ttf" };

	Entity car(0, 0, 900, 500, carTexture);
	Entity plate(0, 0, 900, 500, plateTexture);
	int clicks = -1;
	stringstream tr;
	string aux;
	std::string matriculas[4][6] = {{"C G 3 2   J X U","D G 8 2   J X U","C G 8 2   J X U","L G 8 2   J X U","C G 8 2   J D U","C G 8 2  J X B"},
							   {"R N 4 5   D H C","F N 4 5   D H R","F N 4 5   D H C","E N 4 5   D H C","F M 4 5   D H C","F N 4 5  D H P"},
							   {"P L 8 6   W R A","P L 8 6   W R F","P L 7 6   W R A","A L 8 6   W R A","P K 8 6   W R A","P L 8 6  T R A"},
							   {"D N 4 1   P R A","D N 4 1   P R S","D N 4 1   P A T","M N 4 1   P R T","D N 4 1   P R T","D W 4 1  P R T"}
	};

	bool toggleMenu = false;
	int intmenu = 0;
	int mouseX, mouseY;
	
	srand(time(NULL));
	int usado[3] = { -1,-1,-1 };
	int cant = 4;

	SDL_Event event;

	animationIn(window, blackTexture, 
		brainTexture, LogoTexture, BGTexture, obTitleTexture, bordeTexture, cityTexture,
		"Cual es la matricula?", 550, 38, 21,
		21,82,33);



	for (int i = 0; i < 3; i++) {
		int random = rand() % 4;
		Usado(usado, random, cant);
		usado[i] = random;
		int selected = rand() % 6;
		float multiplicador = 0;
		int opacidad = 255;
		bool start = false;
		bool stop = false;
		bool carplates = true;
		bool show = false;
		bool sound = true;

		while (carplates) {
			window.clear();
			window.backgroundColor(31, 82, 33,255);
			Entity borde(135, 110, 1030, 530, bordeTexture);
			Entity city(135, 110, 1030, 530, cityTexture);
			Entity BackgroundE(0, 0, 1280, 720, BGTexture);
			window.render(BackgroundE, 1);
			window.render(city, 1);
			window.render(borde, 1);
			window.render(title, 1);
			window.drawText("Cual es la matricula?", 550, 38, 240, 240, 240, 255, 21);
			//window.render(titleE, 1);
			

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					window.backgroundColor(0, 0, 0, 255);
					window.display();
					return 0;
				}
			
				if (event.button.button == SDL_BUTTON_LEFT) {
					SDL_Delay(20);
					clicks++;
					if (clicks == 1) {
						if (toggleMenu == false) {
							if (show == true) {

								carplates = false;


							}
							if (stop == true) {
								show = true;
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
			if (start == true and sound == true) {
				se.playSoundEffect(8);
				sound = false;
			}
			
			if (start == true and stop == false) {
				if (multiplicador >= 0.5) {
					if (opacidad > 0) {
						opacidad -= 30;

					}
					
				}
				if (multiplicador < 0.6) {
					multiplicador += 0.07;

				}
				if (opacidad < 0) {
					opacidad = 0;
					stop = true;
					
				}

				SDL_SetTextureAlphaMod(plateTexture, opacidad);
				SDL_SetTextureAlphaMod(carTexture, opacidad);
				window.renderCenter(car, multiplicador*2, 0, 0);
				window.renderCenter(plate, multiplicador*2, 0, 0);
				window.textCustom(matriculas[random][selected].c_str(), plateFont, 0, 0, 230, 230, 230, opacidad, 110 * multiplicador, true, (-5 * multiplicador)+3, (118 * multiplicador)+3);
				window.textCustom(matriculas[random][selected].c_str(), plateFont, 0, 0, 11, 20, 60, opacidad, 110 * multiplicador, true, -5*multiplicador, 118*multiplicador);
				
			}
			
			if (stop == true) {
				if (opacidad < 255) {
					opacidad+=15;
				}
				if (opacidad >= 255) {
					opacidad = 255;
				}
				SDL_SetTextureAlphaMod(plateTexture, opacidad); 
				int contador2 = 0;
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 3; j++) {
						if (show == true) {
							if (contador2 == selected) {
								Entity plateSelected(-130 + (288 * i), -155 + (110 * j), 900, 500, plateSelectedTexture);
								window.render(plateSelected, 1.4);
							}
						}
						Entity plate(-130+(288*i), -155 + (110 * j), 900, 500, plateTexture);
						window.render(plate, 1.4);
						contador2++;
					}
					
				}
				int contador = 0;
				
				for (int i = 0; i < 2; i++) {
					for (int j = 0; j < 3; j++) {
						tr.clear();
						tr << contador+1;
						tr >> aux;
						window.drawText(aux.c_str(), 220 + (410 * i)+3, 3+185 + (155 * j), 70, 70, 70, opacidad, 55);
						window.drawText(aux.c_str(), 220 + (410 * i), 185 + (155 * j), 230,230,230, opacidad, 55);
						window.textCustom(matriculas[random][contador].c_str(), plateFont, 300 + (405 * i)+4, 175 + (150 * j)+4, 230, 230, 230, opacidad, 75, false, 0, 0);
						window.textCustom(matriculas[random][contador].c_str(), plateFont, 300+(405*i), 175 + (150 * j), 11, 20, 60, opacidad, 75, false, 0, 0);
						contador++;
					}
	
					
				}
			}
			

			if (toggleMenu == true) {
				intmenu = menu(window, mouseX, mouseY, event, clicks);
		
				if (intmenu == 1) {
					toggleMenu = false;
					SDL_Delay(40);
				}
				if (intmenu == 2) {
					SDL_DestroyTexture(blackTexture);
					SDL_DestroyTexture(plateTexture);
					SDL_DestroyTexture(plateSelectedTexture);
					SDL_DestroyTexture(carTexture);
					SDL_DestroyTexture(bordeTexture);
					SDL_DestroyTexture(cityTexture);
					SDL_DestroyTexture(obTitleTexture);

					return 1;

				}
			
			}

			
		
			window.display();
			Sleep(40);
		}
	}
	
	//while (inPosition) {
	//	if (xpos > 1280) {
	//		xpos = 1280;
	//	}
	//	window.clear();
	//	Entity black(-1280 + xpos, 0, 1280, 720, blackTexture);
	//	Entity brain(-1280 + xpos, 50, 1280, 720, brainTexture);
	//	Entity Logo(-1280 + xpos, 0, 1280, 720, LogoTexture);
	//	window.render(black, 1);
	//	if (inPosition == true) {
	//		Entity BackgroundE(-1280 + xpos, 0, 1280, 720, BGTexture);
	//		window.render(BackgroundE, 1);
	//	}
	//	window.render(brain, 1);
	//	window.render(Logo, 1);
	//	window.backgroundColor(31, 82, 33, 255);
	//	Entity BackgroundE(0 + xpos, 0, 1280, 720, BGTexture);
	//	Entity title(0 + xpos, 0, 1280, 107, obTitleTexture);
	//	Entity borde(135 + xpos, 110, 1030, 530, bordeTexture);
	//	Entity city(135 + xpos, 110, 1030, 530, cityTexture);
	//	window.render(BackgroundE, 1);
	//	window.render(city, 1);
	//	window.render(borde, 1);
	//	window.render(title, 1);
	//	window.drawText("Cual es la matricula?", 550 + xpos, 38, 240, 240, 240, 255, 21);
	//	if (xpos < 1280) {
	//		inPosition = true;
	//	}
	//	else inPosition = false;
	//	xpos += 40;
	//	Sleep(16);
	//	window.display();
	//}


	SDL_DestroyTexture(blackTexture);
	SDL_DestroyTexture(plateTexture);
	SDL_DestroyTexture(plateSelectedTexture);
	SDL_DestroyTexture(carTexture);
	SDL_DestroyTexture(bordeTexture);
	SDL_DestroyTexture(cityTexture);
	SDL_DestroyTexture(obTitleTexture);

	
	return 0;
}

