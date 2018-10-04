#include "Scene.h"


#include "Window.h"
#include "Input.h"
#include "Renderer.h"
#include "Textures.h"

#include "Pieces.h"
#include "Board.h"
#include "Game.h"

#include <SDL.h>



Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init(Window* w, Renderer* r, Textures* t)
{
	pieces = new Pieces();
	board = new Board(pieces, w->GetHeight());
	game = new Game(board, pieces, w->GetHeight(), r);

	game->pieceSprite = t->LoadTexture("Tetris_piece.png", r);

	time1 = SDL_GetTicks();
}

void Scene::CleanUp()
{
}

void Scene::BeginFrame(Window* w, Input* i)
{
	if (!w || !i) return;


	if (i->GetKeyDown(SDL_SCANCODE_RIGHT) || i->GetKeyDown(SDL_SCANCODE_D))
	{
		if (board->IsPossibleMovement(game->posX + 1, game->posY, game->piece, game->rotation))
			game->posX++;
	}

	if (i->GetKeyDown(SDL_SCANCODE_LEFT) || i->GetKeyDown(SDL_SCANCODE_A))
	{
		if (board->IsPossibleMovement(game->posX - 1, game->posY, game->piece, game->rotation))
			game->posX--;
	}

	if (i->GetKeyDown(SDL_SCANCODE_DOWN) || i->GetKeyDown(SDL_SCANCODE_S))
	{
		if (board->IsPossibleMovement(game->posX, game->posY + 1, game->piece, game->rotation))
			game->posY++;
	}

	if (i->GetKeyDown(SDL_SCANCODE_X) || i->GetKeyDown(SDL_SCANCODE_F))
	{
		while (board->IsPossibleMovement(game->posX, game->posY, game->piece, game->rotation))
		{
			game->posY++;
		}

		board->StorePiece(game->posX, game->posY - 1, game->piece, game->rotation);
		board->DeletePossibleLines();

		if (board->IsGameOver())
		{
			// TODO: End game
			i->quitEvent = true;
			//exit(0);
		}

		game->CreateNewPiece();
	}

	if (i->GetKeyDown(SDL_SCANCODE_Z) || i->GetKeyDown(SDL_SCANCODE_R))
	{
		if (board->IsPossibleMovement(game->posX, game->posY, game->piece, game->rotation + 1))
			game->rotation = (game->rotation + 1) % 4;
	}

	if (SDL_GetTicks() - time1 > WAIT_TIME)
	{
		if (board->IsPossibleMovement(game->posX, game->posY + 1, game->piece, game->rotation))
		{
			game->posY++;
		}
		else
		{
			board->StorePiece(game->posX, game->posY, game->piece, game->rotation);

			board->DeletePossibleLines();

			if (board->IsGameOver())
			{
				// TODO: End game
				i->quitEvent = true;
				//exit(0);
			}

			game->CreateNewPiece();
		}

		time1 = SDL_GetTicks();
	}
}

void Scene::Draw()
{
	game->DrawScene();
}
