#include "arquivo.hpp"

Arquivo::Arquivo() {
	p = 0; 
	v = 0;
	veloci = 0;
	ta_salvo = 0;

} // construtor


void Arquivo::salvar_dados(int salvar, int &pontos, int &vidas, float &velocidade) { //// salva os dados em um arquivo txt
	ofstream dados("ArqGrav.txt", ios::out);

	if (!dados) {
		cout << "ERRO DE GRAVACAO";
	
	}
	else {
		dados << salvar << " " << pontos << " " << vidas << " " << velocidade << endl;
	}

	dados.close();
}


void Arquivo::ler_dados() { // ler os dados do arquivo txt
	ifstream arqDados("ArqGrav.txt", ios::in);

	if (!arqDados) {
		cout << "ERRO DE LEITURA";

	} else {

		while (arqDados >> ta_salvo >> p >> v >> veloci) {

		}
	}

	arqDados.close();

}

int Arquivo::retorna_ta_salvo() {
	return ta_salvo;
}

int Arquivo::retorna_pontos() {
	return p;
}

int Arquivo::retorna_vidas() {
	return v;
}

int Arquivo::retorna_velocidade() {
	return veloci;
}


