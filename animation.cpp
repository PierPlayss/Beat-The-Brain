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
#include <sstream>
//Headers
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "SDL2SoundEffects.h"

using namespace std;

int hover[3] = { 0,0,0 };
int selected = -1;

void deleteTextures(SDL_Texture* menu, SDL_Texture* menuButton, SDL_Texture* menuHover, SDL_Texture* cursor) {
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(menuButton);
	SDL_DestroyTexture(menuHover);
	SDL_DestroyTexture(cursor);

}

int menu(RenderWindow window, int mouseX, int mouseY ,SDL_Event event,int clicks){
	SDL_Texture* menuTexture = window.loadTexture("res/gfx/menuButton.png");
	SDL_Texture* menuButtonTexture = window.loadTexture("res/gfx/menuButtonButton.png");
	SDL_Texture* menuHoverTexture = window.loadTexture("res/gfx/menuHover.png");
	SDL_Texture* cursorTexture = window.loadTexture("res/gfx/cursor.png");

	string font = "res/font/MicroExtendFLF.ttf";
	Entity menu(0, 0, 342, 162, menuTexture);
	Entity menuButton(0, 0, 158, 40, menuButtonTexture);
	Entity menuHover(0, 0, 168, 44, menuHoverTexture);
	Entity cursor(mouseX-5, mouseY-5, 11, 11, cursorTexture);
	int opacidad = 200;
	SDL_SetTextureAlphaMod(menuTexture, opacidad);
	SDL_SetTextureAlphaMod(menuButtonTexture, opacidad);
	bool ceros = false;

	
	SDL_Event event2;

	if (GetAsyncKeyState(VK_DOWN)) {
		selected++;
		if (selected >= 3) {
			selected= 0;
			cout << selected << endl;
		}
		//cout << selected << endl;
		Sleep(80);
	}
	if (GetAsyncKeyState(VK_UP)) {
		selected--;
		if (selected <= -1) {
			selected = 2;

		}
		//cout << selected << endl;
		Sleep(80);
	}
	
	if (mouseX > 560 and mouseX < 720 and mouseY>295 and mouseY < 337) {
		selected = 0;
	}
	if (mouseX > 560 and mouseX < 720 and mouseY>338 and mouseY < 380) {
		selected = 1;
	}
	if (mouseX > 560 and mouseX < 720 and mouseY>381 and mouseY < 420) {
		selected = 2;
	}
	if (selected == 0) {
		hover[0] = 1;
		hover[1] = 0;
		hover[2] = 0;
	}

	if (selected == 1) {
		hover[1] = 1;
		hover[0] = 0;
		hover[2] = 0;
	}
	if (selected == 2) {
		hover[1] = 0;
		hover[0] = 0;
		hover[2] = 1;
	}

	window.renderCenter(menu, 1, 0, 0);

	for (int i = 0; i < 3; i++) {
		if (i == 1) {
			SDL_SetTextureColorMod(menuButtonTexture, 40, 40, 40);
		}
		else SDL_SetTextureColorMod(menuHoverTexture, 255, 255, 255);
		window.renderCenter(menuButton, 1, 0, -45 + (45 * i));
		if (i!=1 and hover[i] == 1) {
			window.renderCenter(menuHover, 1, 0, -45 + (45 * i));
		}
	}
	window.textCustom("Resume", font, 0, 0, 229, 207, 112,255,28, true, 0, -45);
	window.textCustom("Fullscreen", font, 0, 0, 70, 70, 70, 255, 22, true, 0, 0);
	window.textCustom("Exit", font, 0, 0, 229, 207, 112,255, 30, true, 0, 45);

	if (GetAsyncKeyState(VK_RETURN) and selected == 0) {
		deleteTextures(menuTexture, menuButtonTexture, menuHoverTexture, cursorTexture);
		return 1;
	}
	/*if (GetAsyncKeyState(VK_RETURN) and selected == 2) {
		deleteTextures(menuTexture, menuButtonTexture, menuHoverTexture, cursorTexture);
		return 2;
	}*/
	if (GetAsyncKeyState(VK_RETURN) and selected == 1) {
		window.ToggleFullscreen();
		return 3;
	}
	if (clicks == 1 ) {
		
		if (mouseX > 560 and mouseX < 720 and mouseY>295 and mouseY < 337 ) {
			deleteTextures(menuTexture, menuButtonTexture, menuHoverTexture, cursorTexture);
			return 1;
		}
		/*if (mouseX > 560 and mouseX < 720 and mouseY>338 and mouseY < 380) {
			deleteTextures(menuTexture, menuButtonTexture, menuHoverTexture, cursorTexture);
			window.ToggleFullscreen();
		}*/
		if (mouseX > 560 and mouseX < 720 and mouseY>381 and mouseY < 420 ) {
			deleteTextures(menuTexture, menuButtonTexture, menuHoverTexture, cursorTexture);
			return 2;
		}
		//cout << "click" << endl;
		
	}
	window.render(cursor,1);
	//cout << mouseX << "," << mouseY << endl;
	deleteTextures(menuTexture, menuButtonTexture, menuHoverTexture,cursorTexture);
	return 0;

}
void animationIn(RenderWindow window,
	SDL_Texture* blackTexture,
	SDL_Texture* brainTexture,
	SDL_Texture* LogoTexture,
	SDL_Texture* BGTexture,
	SDL_Texture* titleTexture,
	SDL_Texture* bordeTexture,
	SDL_Texture* extraTexture,
	std::string text, int textX, int textY, int textSize,
	int BGr,int BGg,int BGb) {

	int xpos = 1280;
	bool inPosition = false;

	while (!inPosition) {
		if (xpos < 0) {
			xpos = 0;
		}
		window.clear();
		Entity black(-1280 + xpos, 0, 1280, 720, blackTexture);
		Entity brain(-1280 + xpos, 50, 1280, 720, brainTexture);
		Entity Logo(-1280 + xpos, 0, 1280, 720, LogoTexture);
		window.render(black, 1);
		if (inPosition == false) {
			Entity BackgroundE(-1280 + xpos, 0, 1280, 720, BGTexture);
			window.render(BackgroundE, 1);
		}
		window.render(brain, 1);
		window.render(Logo, 1);
		window.backgroundColor(BGr, BGg, BGb, 255);
		Entity BackgroundE(0 + xpos, 0, 1280, 720, BGTexture);
		Entity title(0 + xpos, 0, 1280, 107, titleTexture);
		Entity borde(135 + xpos, 110, 1030, 530, bordeTexture);
		Entity extra(135 + xpos, 110, 1030, 530, extraTexture);
		window.render(BackgroundE, 1);
		window.render(extra, 1);
		window.render(borde, 1);
		window.render(title, 1);
		window.drawText(text.c_str(), textX + xpos, textY, 240, 240, 240, 255, textSize);
		if (xpos > 0) {
			inPosition = false;
		}
		else inPosition = true;
		xpos -= 40;
		Sleep(16);
		window.display();
	}
}