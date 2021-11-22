#include "button.h"

button::button(int xPos, int yPos, int width, int height) {
	buttonRect.x = xPos;
	buttonRect.y = yPos;
	buttonRect.w = width;
	buttonRect.h = height;
}

int button::isClicked(int* mouseCoordX, int* mouseCoordY, Uint32* mouseButtons) {
	if (*mouseButtons == SDL_BUTTON_LMASK && *mouseCoordX > buttonRect.x && *mouseCoordX<buttonRect.x + buttonRect.w && *mouseCoordY>buttonRect.y && *mouseCoordY < buttonRect.y + buttonRect.h)
		return 1;
	if (*mouseButtons == SDL_BUTTON_RMASK && *mouseCoordX > buttonRect.x && *mouseCoordX<buttonRect.x + buttonRect.w && *mouseCoordY>buttonRect.y && *mouseCoordY < buttonRect.y + buttonRect.h)
		return 2;
	return 0;
}

void button::draw(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &buttonRect);
}