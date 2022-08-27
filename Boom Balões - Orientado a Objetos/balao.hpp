#ifndef BALAO_H
#define BALAO_H


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

class Balao {


public:
	Balao(int, int); // construtor

	virtual void voar(); // movimenta o balao na tela
	bool estaEstourado(); // retorna se deletar é false ou true
	void set_del_true(); // seta true em deletar
	void set_del_false(); // seta false em deeltar
	sf::Texture retorna_textura_balao(); // retorna a textura do balao
	sf::Sprite retorna_balao_sprite(); // retorna o sprite do balao
	void muda_velocidade_y(float& v); // muda a velocidade do balao, o atrributo y
	virtual int pontua(int&, int); // modifica e retorna os pontos
	bool perde_vida;



protected:
	// variaveis
	sf::Texture textura_balao; // textura para os baloes

	sf::Sprite SBalao; // sprite

	bool deletar;
	float x, y;
	int soma;
	float xPosition;



};

#endif


