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

#include "Memory.h"


using namespace std;

int ColorGame(SDL_Texture* BGT, RenderWindow window,SDL2SoundEffects se) {
	SDL_Texture* pinkTexture = window.loadTexture("res/gfx/Memory/pink.png");
	SDL_Texture* redTexture = window.loadTexture("res/gfx/Memory/red.png");
	SDL_Texture* whiteTexture = window.loadTexture("res/gfx/Memory/white.png");
	SDL_Texture* blueTexture = window.loadTexture("res/gfx/Memory/blue.png");
	SDL_Texture* blackTexture = window.loadTexture("res/gfx/Memory/black.png");
	SDL_Texture* greenTexture = window.loadTexture("res/gfx/Memory/green.png");
	SDL_Texture* yellowTexture = window.loadTexture("res/gfx/Memory/yellow.png");
	SDL_Texture* purpleTexture = window.loadTexture("res/gfx/Memory/purple.png");
	SDL_Texture* bordeTexture = window.loadTexture("res/gfx/bordeMemory.png");
	SDL_Texture* titleTexture = window.loadTexture("res/gfx/MemoryTitle.png");
	int completo[8] = { 1,1,1,1,1,1,1,1 };
	int clicks = -1;
	int contador = 5;
	srand(time(NULL));
	SDL_Event event;


	for (int i = 0; i < 3; i++) {
		int colores[8];
		int random = 0;
		setCero(colores);
		int orden[10][1];
		bool memory = true;
		int anterior = -1;
		bool start = false;
		bool stop = false;
		bool showAnswers = false;
		while (memory) {
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
						if (showAnswers == true) {
							memory = false;
						}
						if (stop == true) {
							showAnswers = true;
						}
						else start = true;

					}
					else clicks = 0;

				}
			}
			window.clear();
			renderBG(BGT, bordeTexture, titleTexture, window);
			
			
			if (start == true and stop == false) {
				for (int i = 0; i < contador; i++) {
					window.clear();
					renderBG(BGT, bordeTexture, titleTexture, window);
					setCero(colores);
					displayColors(colores, window, pinkTexture, redTexture, whiteTexture, blueTexture, blackTexture, greenTexture, yellowTexture, purpleTexture);
					window.display();
					generadorRandom(anterior, random,0,8);
					orden[i][0] = random;
					colores[random] = 1;
					se.playSoundEffect(random);
					window.clear();
					renderBG(BGT, bordeTexture, titleTexture, window);
					displayColors(colores, window, pinkTexture, redTexture, whiteTexture, blueTexture, blackTexture, greenTexture, yellowTexture, purpleTexture);;
		
					window.display();
					Sleep(750);
				}
				window.clear();
				renderBG(BGT, bordeTexture, titleTexture, window);
				window.display();
				/*for (int i = 0; i < contador; i++) {
					std::cout << orden[i][0] << std::endl;
				}*/
				stop = true;
			}
			
			if (showAnswers == true) {
				displayAnswers(orden, contador, window);
			}
			if (stop == true and showAnswers == false) {
				displayColors(completo, window, pinkTexture, redTexture, whiteTexture, blueTexture, blackTexture, greenTexture, yellowTexture, purpleTexture);
			}

			window.display();
		}
			
		contador++;
	}
	window.backgroundColor(0, 0, 0);
	window.display();
	SDL_DestroyTexture(pinkTexture);
	SDL_DestroyTexture(redTexture);
	SDL_DestroyTexture(whiteTexture);
	SDL_DestroyTexture(blueTexture);
	SDL_DestroyTexture(blackTexture);
	SDL_DestroyTexture(greenTexture);
	SDL_DestroyTexture(yellowTexture);
	SDL_DestroyTexture(purpleTexture);
	SDL_DestroyTexture(bordeTexture);
	SDL_DestroyTexture(titleTexture);
	return 0;
}
void renderBG(SDL_Texture* BGTexture, SDL_Texture* bordeTexture, SDL_Texture* titleTexture, RenderWindow window) {
	window.backgroundColor(161, 113, 16);
	Entity BGEntity(0, 0, 1280, 720, BGTexture);
	window.render(BGEntity, 1);
	SDL_SetTextureAlphaMod(bordeTexture, 200);
	Entity borde(135, 110, 1030, 530, bordeTexture);
	window.render(borde, 1);
	Entity title(0, 0, 1280, 109, titleTexture);
	window.render(title, 1);

}
void setCero(int array[]) {
	for (int i = 0; i < 8; i++) {
		array[i] = 0;
	}
}
void generadorRandom(int& anterior, int &random,int x,int y) {
	if (anterior == random) {
		random = x+ rand() % y;
		generadorRandom(anterior, random,0, 8);
	}
	else{
		anterior = random;
	}
	
}
void displayColors(int array[],
	RenderWindow window,
	SDL_Texture* pinkTexture,
	SDL_Texture* redTexture,
	SDL_Texture* whiteTexture,
	SDL_Texture* blueTexture,
	SDL_Texture* blackTexture,
	SDL_Texture* greenTexture,
	SDL_Texture* yellowTexture,
	SDL_Texture* purpleTexture) {
	

	if (array[0] == 1) {
		Entity pink(270, 150, 201,201, pinkTexture);
		window.render(pink, 1);
	}
	if (array[1] == 1) {
		Entity red(470, 150, 201, 201, redTexture);
		window.render(red, 1);
	}
	if (array[2] == 1) {
		Entity white(670, 150, 201, 201, whiteTexture);
		window.render(white, 1);
	}
	if (array[3] == 1) {
		Entity blue(870, 150, 201, 201, blueTexture);
		window.render(blue, 1);
	}
	if (array[4] == 1) {
		Entity black(270, 401, 201, 201, blackTexture);
		window.render(black, 1);
	}
	if (array[5] == 1) {
		Entity green(470, 401, 201, 201, greenTexture);
		window.render(green, 1);
	}
	if (array[6] == 1) {
		Entity yellow(670, 401, 201, 201, yellowTexture);
		window.render(yellow, 1);
	}
	if (array[7] == 1) {
		Entity purple(870, 401, 201, 201, purpleTexture);
		window.render(purple, 1);
	}
	


}
void displayAnswers(int array[10][1],int contador,RenderWindow window) {
	int x = 550;
	int y = 150;
	int sumadordey = 65;
	for (int i = 0; i < contador; i++) {
		if (array[i][0] == 0) {
			window.drawText("PINK", x+3, y+3 + (sumadordey * i), 70, 70, 70, 160, 50);
			window.drawText("PINK", x, y + (sumadordey * i), 242, 76, 147, 255, 50);
		}
		if (array[i][0] == 1) {
			window.drawText("RED", x + 3, y + 3 + (sumadordey * i), 70, 70, 70, 160, 50);
			window.drawText("RED", x, y + (sumadordey * i), 193,6,5, 255, 50);
		}
		if (array[i][0] == 2) {
			window.drawText("WHITE", x + 3, y + 3 + (sumadordey * i), 70, 70, 70, 160, 50);
			window.drawText("WHITE", x, y + (sumadordey * i), 236, 236, 236, 255, 50);
		}
		if (array[i][0] == 3) {
			window.drawText("BLUE", x + 3, y + 3 + (sumadordey * i), 70, 70, 70, 160, 50);
			window.drawText("BLUE", x, y + (sumadordey * i),6,13,196, 255, 50);
		}
		if (array[i][0] == 4) {
			window.drawText("BLACK", x + 3, y + 3 + (sumadordey * i), 70, 70, 70, 160, 50);
			window.drawText("BLACK", x, y + (sumadordey * i), 0,0,0, 255, 50);
		}
		if (array[i][0] == 5) {
			window.drawText("GREEN", x + 3, y + 3 + (sumadordey * i), 70, 70, 70, 160, 50);
			window.drawText("GREEN",x,y + (sumadordey * i), 44,208,3, 255, 50);
		}
		if (array[i][0] == 6) {
			window.drawText("YELLOW", x + 3, y + 3 + (sumadordey * i), 70, 70, 70, 160, 50);
			window.drawText("YELLOW", x, y + (sumadordey * i), 241, 212, 20, 255, 50);
		}
		if (array[i][0] == 7) {
			window.drawText("PURPLE", x + 3, y + 3 + (sumadordey * i), 70, 70, 70, 160, 50);
			window.drawText("PURPLE", x, y + (sumadordey * i), 105,3,202, 255, 50);
		}
	}
}
