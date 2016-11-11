#include <stdio.h>
#include "GameManager.h"

int main(int argc, char* argv[])
{
	GameManager* game = new GameManager();

	do
	{
		game->Update();
		//getchar();
	} while (!game->CheckEscape());

	delete game;
	game = nullptr;

	return 0;
}