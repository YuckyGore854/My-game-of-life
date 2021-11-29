#pragma once

void countNeighbors(gameBoard& board, int i, int j, int& numNeighbors);

void updateBoard(gameBoard& board, int& numNeighbors, gameBoard& board2);

void drawRunningBoard(gameBoard& board, SDL_FRect& boardRect, int screenX, int screenY, SDL_Renderer* renderer);

void drawEditingBoard(gameBoard& board, SDL_FRect& boardRect, int screenX, int screenY, SDL_Renderer* renderer);
