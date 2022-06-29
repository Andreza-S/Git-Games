#pragma once


#include <SFML/Graphics.hpp>
#include <iostream>
#include "boombaloes.hpp"

class MenuBoomBaloes {
	int pos;
	bool pressed, theselect;


	sf::RenderWindow* window;
	sf::RectangleShape* winclose;
	sf::RectangleShape* clique_jogar;
	sf::RectangleShape* clique_opcoes;
	sf::RectangleShape* clique_sair;
	sf::Font* fonte;
	sf::Texture* image;
	sf::Sprite* fundo;



	sf::Vector2i pos_mouse;
	sf::Vector2f mouse_coord;

	std::vector<const char*> options;
	std::vector<sf::Vector2f> coords;
	std::vector<sf::Text> texts;
	std::vector<std::size_t>sizes;

	Boombaloes jogo;

protected:
	void set_values();
	void loop_events();
	void draw_all();


public:
	MenuBoomBaloes();
	~MenuBoomBaloes();
	void run_menu();


};