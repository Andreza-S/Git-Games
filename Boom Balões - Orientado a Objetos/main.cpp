#include "jogo.hpp"

int main() {
	Jogo* jogo = new Jogo();
	jogo->run_game();
	delete jogo;
	jogo = nullptr;

	return EXIT_SUCCESS;

}// fim do programa