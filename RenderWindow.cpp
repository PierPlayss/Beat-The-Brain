#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

#include "RenderWindow.hpp"
#include "Entity.hpp"

using namespace std;



RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}


void RenderWindow::drawText(const char* msg, int x, int y, int r, int g, int b, int a, int size) {
	SDL_Surface* surf;
	SDL_Texture* texture;
	TTF_Font* font = TTF_OpenFont("res/font/MicroExtendFLF.ttf", size);
	
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;
	SDL_Rect rect;
	surf = TTF_RenderText_Solid(font, msg, color);
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_SetTextureAlphaMod(texture, a);
	rect.x = x;
	rect.y = y;
	rect.w = surf -> w  ;
	rect.h = surf -> h  ;
	TTF_CloseFont(font); 
	//IMG_SavePNG(surf, "image.png");
	//SDL_SaveBMP(surf, "image.bmp");
	SDL_FreeSurface(surf);
	
	

	SDL_RenderCopy(renderer,texture,NULL,&rect);
	SDL_DestroyTexture(texture);

}



void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity, double angle, float multiplicador) {

	SDL_Point pt;
	pt.x = p_entity.getCurrentFrame().x;
	pt.y = p_entity.getCurrentFrame().y;

	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getX() * multiplicador;
	dst.y = p_entity.getY() * multiplicador;
	dst.w = p_entity.getCurrentFrame().w * multiplicador;
	dst.h = p_entity.getCurrentFrame().h * multiplicador;

	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst,angle,NULL, SDL_FLIP_NONE);
}

void RenderWindow::renderFlip(Entity& p_entity, double angle, float multiplicador, bool flip) {
	SDL_RendererFlip flipType;
	SDL_Point pt;
	pt.x = p_entity.getCurrentFrame().x;
	pt.y = p_entity.getCurrentFrame().y;

	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getX() * multiplicador;
	dst.y = p_entity.getY() * multiplicador;
	dst.w = p_entity.getCurrentFrame().w * multiplicador;
	dst.h = p_entity.getCurrentFrame().h * multiplicador;

	if (flip == 1) {
		flipType = SDL_FLIP_HORIZONTAL;
	
	}
	else flipType = SDL_FLIP_NONE;


	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, angle, NULL, flipType);
}

void RenderWindow::render(Entity& p_entity, float multiplicador)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getX() * multiplicador;
	dst.y = p_entity.getY() * multiplicador;
	dst.w = p_entity.getCurrentFrame().w * multiplicador;
	dst.h = p_entity.getCurrentFrame().h *multiplicador;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

void RenderWindow::render(Entity& p_entity, SDL_Rect &rect)
{
	SDL_Rect src;
	src.x = rect.x;
	src.y = rect.y;
	src.w = rect.w;
	src.h = rect.h;

	SDL_Rect dst;
	dst.x = p_entity.getX();
	dst.y = p_entity.getY();
	dst.w = p_entity.getCurrentFrame().w;
	dst.h = p_entity.getCurrentFrame().h/4;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}


void RenderWindow::animation(Entity& p_entity,SDL_Rect &rect, SDL_Rect& pos) {
	
	SDL_Rect dst;
	dst.x = rect.x;
	dst.y = rect.y;
	dst.w = rect.w;
	dst.h = rect.h;

	SDL_Rect final;
	final.x = pos.x;
	final.y = pos.y;
	final.w = pos.w;
	final.h = pos.h;


	SDL_RenderCopy(renderer, p_entity.getTex(), &dst, &final);
}

void RenderWindow::backgroundColor(int r, int g, int b) {
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

////////////////////////////////////////////////////////////////////////////////////
subRenderWindow::subRenderWindow(const char* p_title, int p_w, int p_h)
	:subWindow(NULL), subRenderer(NULL)
{
	subWindow = SDL_CreateWindow(p_title,100,100, p_w, p_h, SDL_WINDOW_SHOWN);

	if (subWindow == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	subRenderer = SDL_CreateRenderer(subWindow, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* subRenderWindow::subLoadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(subRenderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void subRenderWindow::subCleanUp()
{
	SDL_DestroyWindow(subWindow);
}

void subRenderWindow::subClear()
{
	SDL_RenderClear(subRenderer);
}
void subRenderWindow::subRender(Entity& p_entity, float multiplicador)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getX() * multiplicador;
	dst.y = p_entity.getY() * multiplicador;
	dst.w = p_entity.getCurrentFrame().w * multiplicador;
	dst.h = p_entity.getCurrentFrame().h * multiplicador;

	SDL_RenderCopy(subRenderer, p_entity.getTex(), &src, &dst);
}

void subRenderWindow::subDrawText(const char* msg, int x, int y, int r, int g, int b, int size) {
	SDL_Surface* surf;
	SDL_Texture* texture;
	TTF_Font* font = TTF_OpenFont("res/fonts/DezenPro.ttf", size);

	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 255;
	SDL_Rect rect;
	surf = TTF_RenderText_Solid(font, msg, color);
	texture = SDL_CreateTextureFromSurface(subRenderer, surf);
	rect.x = x;
	rect.y = y;
	rect.w = surf->w;
	rect.h = surf->h;
	TTF_CloseFont(font);
	//IMG_SavePNG(surf, "image.png");
	//SDL_SaveBMP(surf, "image.bmp");
	SDL_FreeSurface(surf);



	SDL_RenderCopy(subRenderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);

}

void subRenderWindow::subDisplay()
{
	SDL_RenderPresent(subRenderer);
}
