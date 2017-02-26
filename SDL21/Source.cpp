#include "gameon.hpp"

int main(int argc, char **argv){
	basegame::Game game;
	if (game.init()) {
		game.execute();
	}
	game.cleanup();

	return 0;
}