#include "balao_perde_ponto.hpp"


Balao_perde_ponto::Balao_perde_ponto(int tamanhoJanela, int yPosition, float xMovimento) : Balao(tamanhoJanela, yPosition) { // construtor
	
	textura_balao.loadFromFile("./assets/imagens/baloesCopia.png");
	subtracao = 0;
	x = xMovimento / 2;
	perde_vida = false;

}


int Balao_perde_ponto::pontua(int& pontos, int v) {
	auto valor = v * 2;
	subtracao = pontos - valor;
	return subtracao;

}

void Balao_perde_ponto::voar() {
	x = sin(x);
	SBalao.move(x, y);
}
