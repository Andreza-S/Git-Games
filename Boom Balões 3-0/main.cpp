#include "menuboombaloes.hpp"

int main() {
	MenuBoomBaloes* menu = new MenuBoomBaloes();
	menu->run_menu();
	delete menu;
	menu = nullptr;
	return EXIT_SUCCESS;

}