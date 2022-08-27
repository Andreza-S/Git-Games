#include "balao.hpp"

Balao::Balao(int tamanho_janela, int yPosition) {

	textura_balao.loadFromFile("./assets/imagens/baloes.png");
	SBalao.setTexture(textura_balao);
	deletar = false;
	x = 0;
	y = -0.9f;
	soma = 0;
	xPosition = static_cast<float> (1 + rand() % ((int)(tamanho_janela - (textura_balao.getSize().x) - 10)));
	SBalao.setPosition((sf::Vector2f(xPosition, yPosition)));
	perde_vida = true;
}

int Balao::pontua(int& pontos, int valor) {
	soma = pontos + valor;
	return soma;
}

void Balao::voar() {
	return (SBalao.move(x, y));
}


void Balao::muda_velocidade_y(float& v) {
	y = v;
}


sf::Sprite Balao::retorna_balao_sprite() { // retorna o sprite SBalao
	return SBalao;
}


sf::Texture Balao::retorna_textura_balao() { // Retorna textura_balao
	return textura_balao;
}


bool Balao::estaEstourado() { // retorna variavel de controle deletar
	return deletar;
}

void Balao::set_del_true() { // insere o valor true na variavel deletar
	deletar = true;
}

void Balao::set_del_false() { // insere o valor false na variavel deletar
	deletar = false;
}

