#define OLC_PGE_APPLICATION
#include "engine.hpp"



int main()
{
	Connect4AI* game = new Connect4AI(7);
	game->simulateGames();
	return 0;
}
