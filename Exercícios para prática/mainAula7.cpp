#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(320, 480), "Aula 7 -  Movimentando e animando o Carro"); // criando uma janela através da class Window
	window.setFramerateLimit(60); // limita a quantidade de frame por segundo


	sf::Texture textura; //criando uma textura
	textura.loadFromFile("./resources/car2.png"); //atribuindo uma imagem a textura
	
	sf::IntRect rect(0, 0, 250, 140);
	sf::Sprite spriteDaTextura(textura, rect); // o sprite é que é renderizado pela sfml
	spriteDaTextura.setPosition(45, 300); // posicionando a imagem na janela
		

	sf::Clock clock; // clock da animação


	sf::Event event;
	while (window.isOpen()) { // enquanto a janela estiver aberta - o loop de eventos

		while (window.pollEvent(event)) {  // loop de eventos

			if (event.type == sf::Event::EventType::Closed) { //se evento for do tipo closed
				window.close(); // fecha a janela
			}
		}

		//INPUTS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // movitando para cima

			spriteDaTextura.move(0, -8); // movimentando em Y (negativamente)
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // movimentando para baixo

			spriteDaTextura.move(0, 8.); // Movimentando em Y (positivamente)
		}

		//ANIMAÇÃO
		if (clock.getElapsedTime().asSeconds() > 0.4f) { // se o clock atigir esse valor (0.4F) 

			if (rect.left == 250) { // se o lado esquerdo de rect (rectangulo interno do sprite) atigir 250 no eixo X
				rect.left = 0; // rect é reposicionado em X = 0
			}
			else { // caso contrário
				rect.left += 250; // rect recebe +250 no eixo X
			}
			spriteDaTextura.setTextureRect(rect); // seta a cada lopp rect no sprite
			clock.restart(); // a cada 0.4f segundos o clock recebe restart
		}


		window.clear(sf::Color::White); // limpa a janela, colocando uma cor
		window.draw(spriteDaTextura); // desenhando na tela a sprite
		window.display(); // renderiza

	}
}