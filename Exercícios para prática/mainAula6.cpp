#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(320, 480), "Aula 6 -  Movimentando o Carrinho - setando inputs"); // criando uma janela através da class Window
	window.setFramerateLimit(60); // limita a quantidade de frame por segundo

	sf::Event event;

	sf::Texture textura; //criando uma textura
	textura.loadFromFile("./resources/car.png"); //atribuindo uma imagem a textura

	
	sf::Sprite spriteDaTextura(textura); // o sprite é que é renderizado pela sfml
	spriteDaTextura.setPosition(60, 300); // posicionando a imagem na janela
	

	sf::Clock clock; // clock da animação


	while (window.isOpen()) { // enquanto a janela estiver aberta - o loop de eventos

		while (window.pollEvent(event)) {  // loop de eventos

			if (event.type == sf::Event::EventType::Closed) { //se evento for do tipo closed
				window.close(); // fecha a janela
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // movitando para cima

			spriteDaTextura.move(0, -8); // movimentando em Y (negativamente)
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // movimentando para baixo

			spriteDaTextura.move(0, 8.); // Movimentando em Y (positivamente)
		}

		window.clear(sf::Color::White); // limpa a janela, colocando uma cor
		window.draw(spriteDaTextura); // desenhando na tela a sprite
		window.display(); // renderiza

	}
}