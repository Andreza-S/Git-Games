#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(640, 480), "Aula 5 - Construindo anima��es- Carrinho"); // criando uma janela atrav�s da class Window

	sf::Event event;

	sf::Texture textura; //criando uma textura
	textura.loadFromFile("./resources/red.png"); //atribuindo uma imagem a textura

	sf::IntRect rect(0, 0, 32, 32);
	//IntRect cria um retangulo interno a partir do local e do tamanho indicados, para capturar uma aparte da imagem
	
	sf::Sprite spriteDaTextura(textura, rect); // o sprite � que � renderizado pela sfml
	

	sf::Clock clock; // clock da anima��o


	while (window.isOpen()) { // enquanto a janela estiver aberta - o loop de eventos

		while (window.pollEvent(event)) {  // loop de eventos

			if (event.type == sf::Event::EventType::Closed) { //se evento for do tipo closed
				window.close(); // fecha a janela
			}
		}

		if (clock.getElapsedTime().asSeconds() > 0.2f) { // a cada quantidade de clock, 0.2f define tamb�m a velocidade em que a imagem ser� atualizada

			if (rect.left == 224) { // se o lado esquerdo do rect estiver na seguinte posi��o, 255
				rect.left = 0; // o lado esquerdo do rect retorna a posi��o 0

			}
			else { // caso contr�rio a oposi��o do lado esquerdo recebe + 85 (tamanho(no eixo x) de cada desenho na imagem)
				rect.left += 32;
			}

			spriteDaTextura.setTextureRect(rect); // setando o rect no sprite, para atualizar a cada loop
			clock.restart(); // acada 0.4f segundos o clock � resetado


		}


		window.clear(); // limpa a janela
		window.draw(spriteDaTextura); // desenhando na tela a sprite
		window.display(); // renderiza

	}
}