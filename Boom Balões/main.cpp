#include "boombaloes.hpp"



int main() {
	Boombaloes* boombaloes = new Boombaloes();
	boombaloes->run_game();
	delete boombaloes;
	boombaloes = nullptr;

	return EXIT_SUCCESS;

}// fim do programa