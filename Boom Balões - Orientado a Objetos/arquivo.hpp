#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Arquivo {

public:
	Arquivo(); //construtor

	void salvar_dados(int, int &, int &, float &); // salva os dados em um arquivo txt

	void ler_dados(); // ler os dados do arquivo txt

	int retorna_ta_salvo();

	int retorna_pontos();
	int retorna_vidas();
	int retorna_velocidade();

private:
	int p, v, veloci, ta_salvo;
	

};
