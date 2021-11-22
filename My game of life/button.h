#pragma once
#include<SDL.h>

class button{
public:
	int isClicked(int* mouseCoordX, int* mouseCoorY, Uint32 *mouseButtons);
	button(int xPos, int yPos, int width, int height);
	void draw(SDL_Renderer* renderer);
private:
	SDL_Rect buttonRect;
	
};
