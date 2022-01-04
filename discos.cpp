
//C++
#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <ctime>
//Headers
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "SDL2SoundEffects.h"

#include "discos.h"
#include "Memory.h"

int discosGame(SDL_Texture* BGTexture, RenderWindow window) {
	int clicks = -1;
		
	SDL_Texture* bordeTexture = window.loadTexture("res/gfx/bordeDiscos.png");
	SDL_Texture* disco1Texture = window.loadTexture("res/gfx/disco.png");
	SDL_Texture* disco2Texture = window.loadTexture("res/gfx/disco2.png");
	SDL_Texture* agujasTexture = window.loadTexture("res/gfx/agujas.png");
	SDL_Texture* titleTexture = window.loadTexture("res/gfx/multitaskingTitle.png");

	Entity borde(135, 110, 1030, 530, bordeTexture);
	Entity agujas(135, 110, 1030, 530, agujasTexture);
	Entity disco1(260, 225, 370, 370, disco1Texture);
	Entity disco2(675, 225, 370, 370, disco2Texture);
	Entity background(0, 0, 1280, 720, BGTexture);
	Entity title(0, 0, 1280, 107, titleTexture);

	srand(time(NULL));
	clock_t time;
	SDL_Event event;
	stringstream results;
	string resultados;

	for (int i = 0; i < 3; i++) {
		float speed[2] = { 0,0 };
		float angulo[2] = { 0,360 };
		int cont[2] = { 0,0 };
		bool canCount[2] = { 0,0 };
		int ranDivisor[2];
		int anterior = -1;
		int random =  3 + rand() % 8;
		for (int j = 0; j < 2; j++) {
			generadorRandom(anterior, random, 3, 8);
			//m = 3 + rand() % 6;
			//ranDivisor[j] = 20 + rand() % 55;
			speed[j] = random;
		}
		bool start = false;
		bool stop = false;
		int timer = 0;
		bool discoGame = true;
		bool showResults = false;
		bool over[2] = {0,0};
		int restador = 0;
		
		while (discoGame) {

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					window.backgroundColor(0, 0, 0);
					window.display();
					return 0;
				}
				if (event.button.button == SDL_BUTTON_LEFT) {
					clicks++;
					if (clicks == 1) {
						if (showResults == true) {
							discoGame = false;
						}
						if (stop == true) {
							showResults = true;
						}
						else {
							time = clock();
							start = true;
						}
					}
					else clicks = 0;

				}
			}
			
			if (angulo[0] < 280-speed[0]) {
				canCount[0] = true;
			}
			if (angulo[1] > 80 + speed[1]) {
				canCount[1] = true;
			}
		
			window.clear();
			if (start == true and stop==false) {
				//cout << time << endl;
				time = (clock() - time);
				if (float(time) / CLOCKS_PER_SEC >= 0.51 and float(time) / CLOCKS_PER_SEC <= 1.30) {
					timer++;
					//cout << timer << endl;
					time = 0;
				}
			}

			if (start == true and stop==false) {
				angulo[0] += speed[0];//ranDivisor[0];
				angulo[1] -= speed[1];//ranDivisor[1];
				

				if (angulo[0] >= 360) {
						angulo[0] = 0;
				}
				if (angulo[1] < 0) {
					angulo[1] = 360;
				}
				
				Sleep(20);

				//cout << angulo[0] << endl;
			}

			if (stop == true and (over[0] == false or over[1] == false)) {
				if (angulo[0] > 260 and angulo[0] < 350) {
					angulo[0] += speed[0];
				}
				else over[0] = true;
				if (angulo[1] < 100 and angulo[1] >= 0) {
					angulo[1] -= speed[1];
				}
				else over[1] = true;
				Sleep(20);
			}

			if (canCount[0] == true and angulo[0] > 280 - speed[0] and angulo[0] < 280 + speed[0]) {
				cont[0]++;
				canCount[0] = false;
				//cout << cont[0] << endl;
			}

			if (canCount[1] == true and angulo[1] > 80 - speed[1] and angulo[1] < 80 + speed[1]) {
				cont[1]++;
				canCount[1] = false;
				//cout << cont[1] << endl;
			}
			
			window.backgroundColor(57,85, 163);
			window.render(background, 1);
			SDL_SetTextureAlphaMod(bordeTexture, 200);
			window.render(borde, 1);
			window.render(title, 1);
			window.drawText("Cuantas veces la flecha pasa la aguja?", 490, 38, 240, 240, 240, 255, 22);
			window.render(disco1, angulo[0], 1);
			window.render(disco2, angulo[1], 1);
			window.render(agujas, 1);

			if (showResults == true) {
				
				for (int i = 0; i < 2; i++) {
					results.clear();
					results << cont[i];;
					results >> resultados;
					if (cont[i] > 9) {
						restador = 60;
					}
					else restador = 0;
					window.drawText(resultados.c_str(), 375+5 + (415 * i)-restador, 325+5, 70, 70, 70, 160, 150);
					window.drawText(resultados.c_str(),375+(415*i)-restador, 325, 240, 240, 240, 255, 150);
				
				}
				

			}
			
	
			

			if (timer >= 7) {
				stop = true;
			}

			window.display();
		}
	
	}
	SDL_DestroyTexture(bordeTexture);
	SDL_DestroyTexture(disco1Texture);
	SDL_DestroyTexture(disco2Texture);
	SDL_DestroyTexture(agujasTexture);
	SDL_DestroyTexture(titleTexture);
	
	window.backgroundColor(0, 0, 0);
	
	return 0;
}
