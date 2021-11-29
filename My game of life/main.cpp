/*
* Welcome to Conway's game of life
* This is a recreation of that game made entirely from scratch by me
* I began work on this on 11/20/21
* I will use no outside guide other than the basic rules of Conway's game of life
* 
* Written with SDL2 in C++
*/

#include<iostream>
#include<SDL.h>
#include<SDL_ttf.h>
#include"gameBoard.h"
#include"button.h"
#include "main.h"


using namespace std;

int main(int argc, char* argv[]) {
	enum gameState {
		mainMenu, editing, running, paused
	};
	enum cellState {
		dead, alive
	};

	int screenX = 1024;
	int screenY = 576;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	gameBoard board; //import the game map to prevent 
	gameBoard board2; //import the game map to prevent 
	SDL_Window* window = SDL_CreateWindow("Conway's game of life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenX, screenY, SDL_WINDOW_RESIZABLE);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, NULL);
	SDL_Event event;
	SDL_FRect boardRect;

	TTF_Font* impact = TTF_OpenFont("C:\\Windows\\Fonts\\impact.ttf", 60);
	SDL_Color White = { 255,255,255 };
	SDL_Color Black = { 0,0,0 };


	//Setting up main menu text
	SDL_Surface* mainMenuTextSurf = TTF_RenderText_Solid(impact, "CONWAY'S GAME OF LIFE", Black);
	SDL_Texture* mainMenuText = SDL_CreateTextureFromSurface(renderer, mainMenuTextSurf);
	SDL_FreeSurface(mainMenuTextSurf);
	SDL_Rect mainMenuRect;
	mainMenuRect.x = screenX / 4;
	mainMenuRect.y = 0;//(screenY + 30);
	mainMenuRect.w = 500;
	mainMenuRect.h = 100;

	//Setting up main menu button text
	SDL_Surface* startButtonSurf = TTF_RenderText_Solid(impact, "START", White);
	SDL_Texture* startButtonText = SDL_CreateTextureFromSurface(renderer, startButtonSurf);
	SDL_FreeSurface(startButtonSurf);
	SDL_Rect startButtonRect = { screenX / 2 - 50,screenY / 2 - 150,100,60 };
	
	boardRect.h = screenY / 113;
	boardRect.w = screenX / 200;
	int mouseX = 0;
	int mouseY = 0;
	Uint32 mouseButtons;
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	int gameState = mainMenu;
	button mainMenuButton(startButtonRect.x, startButtonRect.y, startButtonRect.w, startButtonRect.h);
	int numNeighbors = 0;
	double generationSpeed = 100;

	double adjustedMousePosX = screenX / 200;
	double adjustedMousePosY = screenY / 113;



	while (true) {
		//INPUT SECTION////////////////////////////////////////////////////////////////
		while (SDL_PollEvent(&event) != 0) {
			if (event.type == SDL_QUIT) {
				SDL_Quit();
			}
			if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
				keyboard = SDL_GetKeyboardState(NULL);
			}


		}
		mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		//GAMEPLAY SECTION/////////////////////////////////////////////////////////////
		if (gameState == mainMenu) {
			SDL_RenderCopy(renderer, mainMenuText, NULL, &mainMenuRect);
			
			mainMenuButton.draw(renderer);
			SDL_RenderCopy(renderer, startButtonText, NULL, &startButtonRect);
			if (mainMenuButton.isClicked(&mouseX, &mouseY, &mouseButtons) == 1) {
				gameState = editing;
			}

		}
		if (gameState == editing) {
			
			if (mouseButtons == SDL_BUTTON_LMASK) {
				board.board[(int(mouseY / adjustedMousePosY))][(int(mouseX / adjustedMousePosX))] = alive;
			}
			if (mouseButtons == SDL_BUTTON_RMASK) {
				board.board[(int(mouseY / adjustedMousePosY))][(int(mouseX / adjustedMousePosX))] = dead;
			}
			if (keyboard[SDL_SCANCODE_P]) {
				gameState = running;
			}

			drawEditingBoard(board, boardRect, screenX, screenY, renderer);
		}
		if (gameState == running) {

			updateBoard(board, numNeighbors, board2);
			SDL_Delay(100);
			drawRunningBoard(board, boardRect, screenX, screenY, renderer);
		}

		SDL_RenderPresent(renderer);
	}

	std::cout << "Hello world" << endl;
	return 0;
}

void drawEditingBoard(gameBoard& board, SDL_FRect& boardRect, int screenX, int screenY, SDL_Renderer* renderer)
{
	for (int i = 0; i < 113; i++) {
		for (int j = 0; j < 200; j++) {
			if (board.board[i][j] == 1) {
				boardRect.x = j * (screenX / 200);
				boardRect.y = i * (screenY / 113);
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderFillRectF(renderer, &boardRect);

			}
			else {
				boardRect.x = j * (screenX / 200);
				boardRect.y = i * (screenY / 113);
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRectF(renderer, &boardRect);
			}

		}
	}
}

void drawRunningBoard(gameBoard& board, SDL_FRect& boardRect, int screenX, int screenY, SDL_Renderer* renderer)
{
	for (int i = 0; i < 113; i++) {
		for (int j = 0; j < 200; j++) {
			if (board.board[i][j] == 1) {
				boardRect.x = j * (screenX / 200);//screenX/200
				boardRect.y = i * (screenY / 113);//screenY/113
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRectF(renderer, &boardRect);
			}
		}
	}
}

void updateBoard(gameBoard& board, int& numNeighbors, gameBoard& board2)
{
	enum cellState {
		dead, alive
	};
	for (int i = 0; i < 113; i++) {
		for (int j = 0; j < 200; j++) {
			//numNeighbors = 0;
			if (i - 1 > 0 && i + 1 < 113 && j - 1 > 0 && j + 1 < 200) {//make sure the game only checks cells that are right next to eachother

				countNeighbors(board, i, j, numNeighbors);

				if (board.board[i][j] == alive && numNeighbors < 2) {
					board2.board[i][j] = dead;
				}
				else if (board.board[i][j] == alive && (numNeighbors == 2 || numNeighbors == 3)) {
					board2.board[i][j] = alive;
				}
				else if (board.board[i][j] == alive && numNeighbors > 3) {
					board2.board[i][j] = dead;
				}
				else if (board.board[i][j] == dead && numNeighbors == 3) {
					board2.board[i][j] = alive;
				}
				//numNeighbors = 0;
			}
			numNeighbors = 0;//
		}

		//numNeighbors = 0;
	}
	board = board2;
}

void countNeighbors(gameBoard& board, int i, int j, int& numNeighbors)
{
	//count the number of neighbors a cell has
	for (int a = -1; a < 2; a++) {
		for (int b = -1; b < 2; b++) {
			//if (a != 0 && b != 0) {
			if (board.board[i + a][j + b] == 1 && abs(a) + abs(b) != 0) {
				numNeighbors++;
			}
			//}
		}
	}
}
