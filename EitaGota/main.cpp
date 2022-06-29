#include "eitagota.hpp"



int main() {
	Eitagota * eitagota = new Eitagota();
	eitagota->run_game();
	delete eitagota;
	eitagota = nullptr;

	return EXIT_SUCCESS;

}// fim do programa