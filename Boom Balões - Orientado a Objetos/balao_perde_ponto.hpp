#ifndef BALAO_PERDE_PONTO_H
#define BALAO_PERDE_PONTO_H

#include "balao.hpp"
#include <cmath>

class Balao_perde_ponto : public Balao {

public:

	Balao_perde_ponto(int, int, float); // construtor

	virtual int pontua(int&, int); // modifica e retorna o valor dos pontos

	virtual void voar(); // movimenta o balao na tela sobrescrita



private:
	int subtracao;




};

#endif
