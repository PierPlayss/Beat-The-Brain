#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "Entity.hpp"
class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	SDL_Texture* Points(const char* msg, int x, int y, int r, int g, int b, int size,int& w, int& h);
	void cleanUp();
	void clear();
	void render(Entity& p_entity, double angle, float multiplicador);
	void render(Entity& p_entity,float multiplicador);
	void render(Entity& p_entity, SDL_Rect& rect);
	void renderFlip(Entity& p_entity, double angle, float multiplicador, bool flip);
	void display();
	void animation(Entity& p_entity, SDL_Rect &rect, SDL_Rect& pos);
	void drawText(const char* msg, int x, int y, int r, int g, int b, int a, int size);
	void backgroundColor(int r, int g, int b);
	/*static SDL_Texture* loadFont(const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);*/

	
private:
	SDL_Renderer* renderer;
	SDL_Window *window = nullptr;
	

};

class subRenderWindow
{
public:
	subRenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* subLoadTexture(const char* p_filePath);
	void subCleanUp();
	void subClear();
	void subRender(Entity& p_entity, float multiplicador);
	void subDisplay();
	void subAnimation(Entity& p_entity, SDL_Rect& rect, SDL_Rect& pos);
	void subDrawText(const char* msg, int x, int y, int r, int g, int b, int size);
	/*static SDL_Texture* loadFont(const std::string& font_path, int font_size, const std::string& message_text, const SDL_Color& color);*/


private:
	SDL_Renderer* subRenderer;
	SDL_Window* subWindow = nullptr;


};
