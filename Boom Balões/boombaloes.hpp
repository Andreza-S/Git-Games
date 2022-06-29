#ifndef BOOMBALOES_H
#define BOOMBALOES_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>


class Boombaloes {

public:
	Boombaloes();

	sf::RenderWindow window;

	//sonoplastia
	sf::SoundBuffer cliquesom, gameoversom;
	sf::Sound clique_sound, gameover_sound;
	sf::Music music;


	// variaveis de manipulação
	bool pressed, gameover, paused;

	//velocidade do movimento dos objetos
	float velocity, x, obj_vel_max, obj_vel;

	//Pontos e vidas
	int points, health;

	sf::Font fonte, fontegameover;
	sf::Text score, life, gameover_text, f1, paused_text;
	sf::Texture texture, bg, ponteiro, stop;
	sf::Sprite object, fundo, agulha, pausafundo;

	unsigned seed = time(0);

	sf::Vector2i pos_mouse_win, current_position; // posicao do mouse em relacao a janela(window)
	sf::Vector2f pos_mouse_coord; // Aramazena as coordenadas mapeadas

	//OBJETOS
	std::vector<sf::Sprite> objs;
	size_t max_objs;

	void code_game();
	void game_over();
	void pause_gamer();
	void loop_events();
	void run_game();

};

#endif