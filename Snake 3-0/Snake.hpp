#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>


class Snake {

public:
	Snake();

	int cols, lines, size, width, height, direction, num, points;
	bool eh_game_over, paused;

	sf::RenderWindow window;
	sf::Texture t1, t2, t3, t4, t5, t6, t7, t8, t9;
	sf::Sprite sp1, sp2, sp3, sp4, sp5, sp6;
	sf::Clock clock;
	sf::Font fonte_gameover_pontos, fonte_pausa_f1;
	sf::Text texto_pontos, gameover_text, f1_text, pausa_text;

		// adicionar sons:
		// 1 - para quando a snake se mexer
		// 2 - quando pega a fruta
		// 3 - quando gera gameover
		// 4 - musica de fundo

	float timer, delay;


	void game_over();
	void pause_game();
	void run_game();
	void collision();
	void colorindo_snake();





};