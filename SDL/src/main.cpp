#include "game.hpp"
#include "pch.hpp"

#include <cstring>

int main(int argc, char **argv) {
	Game game;
	game.bUseEntt = true;
	game.CubeNum = 400 * 1000;
	if (argc > 1) {
		game.bUseEntt = (std::stoi(argv[1]) == 1);
		std::cout << "first para: " << argv[1] << "|" << std::endl;
	}
	if(argc > 2){
		game.CubeNum = std::stoi(argv[2]);
		std::cout << "second para: " << argv[2] << "|" << std::endl;
	}
	game.Init("sdl_test",0,30,1920,1080);
	

	game.RunLoop();
	game.Shutdown();
	return 0;
}
