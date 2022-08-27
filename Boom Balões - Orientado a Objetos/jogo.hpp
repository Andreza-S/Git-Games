#ifndef JOGO_H
#define JOGO_H

#include "balao.hpp"
#include "balao_perde_ponto.hpp"
#include "arquivo.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>

class Jogo {

public:

	Jogo(); // CONSTRUTOR

	void code_game(); // DINÂMICA DO GAME,ADICONA BALOES, DELETA BALOES E ALTERA VALORES DOS ATRIBUTOS
	void game_over(); // DEFINE A TELA DE GAME OVER
	void pause_game(); // DEFINE A TELA DE PAUSA QUANDO PRESSIONADO A TECLA ENTER DO TECLADO
	void loop_events(); // LOOP EM QUE OS EVENTOS DE MUSICA, JANELA E MOUSE SÃO MONITORADOS
	void run_game(); // FUNÇÃO QUE INVOCACA AS DEMAIS FUNÇÕES DO GAME DE ACORDO COM AS CONDICOES BOOLEANAS
	void muda_coord_x(); // MUDA O VALOR DA VARIAVEL X, COORDENADA DOS SPRITES PARA DESENHO NA TELA

	sf::Texture bg, ponteiro, stop;

private:
	// Atributos

	sf::RenderWindow janela;

	////sonoplastia
	sf::SoundBuffer cliquesom, gameoversom;
	sf::Sound clique_sound, gameover_sound;
	sf::Music music;


	//// variaveis de condição (verdadeiro ou falso)
	bool pressed, gameover, paused;

	////coordenada e variaveis de controle do tamanho do vector
	float obj_vel_max, balao_vel, velocity;

	////Pontos e vidas
	int points, health;

	////Textos, Texturas e Sprites
	sf::Font fonte, fonteGameover;
	sf::Text score, life, gameover_text, f1, paused_text;

	sf::Sprite fundo, agulha, pausafundo;

	unsigned seed = time(0);

	//// Vetores para guardar as coordenadas do mouse e janela
	sf::Vector2i pos_mouse_win, current_position; // posicao do mouse em relacao a janela(window)
	sf::Vector2f pos_mouse_coord; // Aramazena as coordenadas mapeadas

	//OBJETOS
	std::vector<Balao*> vector_baloes;
	size_t max_objs;


};

#endif