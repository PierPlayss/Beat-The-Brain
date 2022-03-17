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
//Headers
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "SDL2SoundEffects.h"

#include "language.h"
#include "animation.h"


using namespace std;

int languageGame(SDL_Texture* brainTexture, SDL_Texture* LogoTexture, RenderWindow window,Mix_Music* bgm) {
	
	SDL_Texture* paperTexture[4] = {
		window.loadTexture("res/gfx/language/paper1.png"),
		window.loadTexture("res/gfx/language/paper2.png"),
		window.loadTexture("res/gfx/language/paper3.png"),
		window.loadTexture("res/gfx/language/paper4.png") };
	SDL_Texture* bordeTexture = window.loadTexture("res/gfx/bordeLanguage.png");
	SDL_Texture* titleTexture = window.loadTexture("res/gfx/titleLanguage.png");
	SDL_Texture* BGTexture = window.loadTexture("res/gfx/background.png");
	SDL_Texture* timerTexture = window.loadTexture("res/gfx/time.png");
	SDL_Texture* blackTexture = window.loadTexture("res/gfx/black.png");
	Entity borde(135,110, 1035, 535, bordeTexture);
	Entity title(0, 0, 1280, 107, titleTexture);
	Entity BGEntity(0, 0, 1280, 720, BGTexture);
	string fontPeriodico[4] = {
		"res/font/periodico.otf",
		"res/font/periodico2.ttf",
		"res/font/periodico4.ttf",
		"res/font/periodico3.ttf"
	};
	struct posiciones {
		int x;
		int y;
	}Pos[4],posfinal[4];

	srand(time(NULL));

	clock_t time;
	time = clock();
	int clicks = 0;
	int clickMenu = 0;
	int array[4] = { 0,1,2,3 };
	int array2[4] = { 0,1,2,3 };
	string s[100];
	string delimiter = ">=";
	string respuesta;

	int usado[3] = { -1,-1,-1 };
	int random;
	

	animationIn(window,
		blackTexture, brainTexture, LogoTexture, BGTexture, titleTexture, bordeTexture, bordeTexture,
		"Ordena los recortes para formar palabras", 490, 38, 21,
		121, 46, 146);

	//std::cout << s << std::endl;

	for (int i = 0; i < 6; i++) {
		int restador = 0;
		int opacidad = 0;
		int opacidadstart = 0;
		int lineas;
		string aux;
		stringstream translate;
		fstream words;
		words.open("./res/gfx/language/words.txt", ios::in);
		getline(words, aux);
		translate.clear();
		translate << aux;
		translate >> lineas;
		Usado(usado, random, lineas);
		usado[i] = random;
		//cout << random << endl;
		for (int i = 0; i < lineas; i++) {
			getline(words, s[i]);
			//cout << s[i] << endl;
		}
		words.close();

		size_t pos = 0;
		string token[15];
		int contador = 0;
		while ((pos = s[random].find(delimiter)) != string::npos) {
			token[contador] = s[random].substr(0, pos);
			//cout << token[contador] << std::endl;
			s[random].erase(0, pos + delimiter.length());
			contador++;
		}

		//cout << contador << endl;
		//135 110
		if (contador == 4) {
			Pos[0].x = 285;
			Pos[0].y = 305;
			Pos[1].x = 535;
			Pos[1].y = 160;
			Pos[2].x = 535;
			Pos[2].y = 410;
			Pos[3].x = 800;
			Pos[3].y = 305;
			sorteador(array, contador);

			posfinal[0].x = 185;
			posfinal[0].y = 230;
			posfinal[1].x = 420;
			posfinal[1].y = 225;
			posfinal[2].x = 680;
			posfinal[2].y = 225;
			posfinal[3].x = 910;
			posfinal[3].y = 225;

		}
		if (contador == 3) {
			Pos[0].x = 405;
			Pos[0].y = 200;
			Pos[1].x = 705;
			Pos[1].y = 200;
			Pos[2].x = 550;
			Pos[2].y = 400;
			sorteador(array, contador);


			posfinal[0].x = 280;
			posfinal[0].y = 225;
			posfinal[1].x = 530;
			posfinal[1].y = 225;
			posfinal[2].x = 775;
			posfinal[2].y = 225;
		
		}

		bool toggleMenu = false;
		int intmenu = 0;
		int mouseX, mouseY;
		

		SDL_Event event;
		bool language = true;
		bool showResult = false;
		
		while (language) {

			window.clear();
			window.backgroundColor(121, 46, 146, 255);
			
			window.render(BGEntity, 1);
			window.render(borde,1);
			window.render(title, 1);

			window.drawText("Ordena los recortes para formar palabras", 490, 38, 240, 240, 240, 255, 21);

			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					language = false;

				if (event.type == SDL_MOUSEBUTTONUP) {
					if (event.button.state == SDL_RELEASED) {
						clicks++;
						clickMenu++;
						if (clicks == 1) {
							if (toggleMenu == false) {
								if (showResult == true) {
									language = false;
								
								}
								else {
									showResult = true;
									opacidadstart = 255;
								
								}
							}
							clicks = 0;
						}
						
					}
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


		
			

			if (showResult == true) {
				for (int i = 0; i < 4; i++) {
					SDL_SetTextureAlphaMod(paperTexture[i], opacidadstart);
				}
				for (int i = 0; i < contador; i++) {
					if (Pos[i].x < posfinal[array[i] - 1].x) {
						Pos[i].x+=5;
					}
					if (Pos[i].x > posfinal[array[i] - 1].x) {
						Pos[i].x-=5;
					}
					if (Pos[i].y < posfinal[array[i] - 1].y) {
						Pos[i].y+=5;
					}
					if (Pos[i].y > posfinal[array[i] - 1].y) {
						Pos[i].y-=5;
					}
					//cout << array[i] - 1 << endl;
					//cout << token[array[i] - 1] << endl;
					//cout << i << endl;
					///*system("pause");*/


					Entity paper(Pos[i].x, Pos[i].y, 240, 220, paperTexture[array[i] - 1]);
					window.render(paper, 1);
					window.textCustom(token[array[i] - 1].c_str(), fontPeriodico[i], Pos[i].x + 40, Pos[i].y + 50, 0, 0, 0, 255, 90,0,0,0);
					if (Pos[i].x == posfinal[array[i] - 1].x and Pos[i].y == posfinal[array[i] - 1].y) {
						translate.clear();
						for (int i = 0; i < contador; i++) {
							translate << token[i];
						}
						if (opacidad < 255) {
							opacidad++;
						}
						translate >> respuesta;
						if (respuesta.length() >= 10) {
							restador = 75;
						}
						else if (respuesta.length() > 13) {
							restador = 100;
						}
						else restador = 0;
						window.drawText(respuesta.c_str(), 500 - restador+3, 450+3,90, 90, 90, opacidad, 50);
						window.drawText(respuesta.c_str(), 500 - restador , 450, 230, 230, 230, opacidad, 50);

					}
				}
			}
			else {

				if (opacidadstart < 255)
				{
					opacidadstart += 10;
				}
				if (opacidadstart > 255) {
					opacidadstart = 255;
				}
				for (int i = 0; i < 4; i++) {
					SDL_SetTextureAlphaMod(paperTexture[i], opacidadstart);
				}

				Sleep(40);
				
				for (int i = 0; i < contador; i++) {
					//cout << token[i] << endl;

					Entity paper(Pos[i].x, Pos[i].y, 240, 220, paperTexture[array[i] - 1]);
					window.render(paper, 1);
					window.textCustom(token[array[i] - 1].c_str(), fontPeriodico[i], Pos[i].x + 40, Pos[i].y + 50, 0, 0, 0, opacidadstart, 90,0,0,0);

				}
			}
			

			if (toggleMenu == true) {
				intmenu = menu(window, mouseX, mouseY, event, clickMenu, bgm);

				if (intmenu == 1) {
					toggleMenu = false;
					SDL_Delay(40);
				}
				if (intmenu == 2) {
					window.backgroundColor(0, 0, 0, 255);
					SDL_DestroyTexture(paperTexture[0]);
					SDL_DestroyTexture(paperTexture[1]);
					SDL_DestroyTexture(paperTexture[2]);
					SDL_DestroyTexture(paperTexture[3]);
					SDL_DestroyTexture(bordeTexture);
					SDL_DestroyTexture(titleTexture);
					SDL_DestroyTexture(blackTexture);
					return 1;

				}
			}
			clickMenu = 0;

			window.display();
		}


	}
	window.backgroundColor(0, 0, 0, 255);
	SDL_DestroyTexture(paperTexture[0]);
	SDL_DestroyTexture(paperTexture[1]);
	SDL_DestroyTexture(paperTexture[2]);
	SDL_DestroyTexture(paperTexture[3]);
	SDL_DestroyTexture(bordeTexture);
	SDL_DestroyTexture(titleTexture);
	SDL_DestroyTexture(blackTexture);
	return 0;
}
void sorteador(int array[],int cantidad) {
	int contador = 0;
	srand(time(NULL));

	vector<int> myvector;

	for (int i = 1; i < cantidad+1; i++) {
		myvector.push_back(i);
	}
	random_shuffle(myvector.begin(), myvector.end());



	for (vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it) {
		array[contador] = *it;
		//cout << array[contador] << endl;
		contador++;
	}

}
void Usado(int usado[], int& random, int lineas) {
	random = rand() % lineas;
	for (int i = 0; i < 6; i++) {
		if (random == usado[i]) {
			Usado(usado, random, lineas);
		}
	}
}