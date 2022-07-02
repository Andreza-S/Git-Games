#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(1024, 512), "Aula 8 -  Movimentando o carrinho na tela"); // criando uma janela através da class Window
	window.setFramerateLimit(60); // limita a quantidade de frames por segundo

	float currentFrame = 0; //


	sf::Texture textura; //criando uma textura
	textura.loadFromFile("./resources/red.png"); //atribuindo uma imagem a textura
	
	sf::IntRect rect(160, 0, 32, 32);
	sf::Sprite spriteDaTextura(textura, rect); // o sprite é que é renderizado pela sfml
	spriteDaTextura.setPosition(96, 96); // posicionando a imagem na janela
	spriteDaTextura.setScale(2, 2); // multiplica x e y pelos valores passados

	
	sf::Event event;
	while (window.isOpen()) { // enquanto a janela estiver aberta - o loop de eventos

		while (window.pollEvent(event)) {  // loop de eventos

			if (event.type == sf::Event::EventType::Closed) { //se evento for do tipo closed
				window.close(); // fecha a janela
			}
		}

		//INPUTS
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // movitando para esquerda

			spriteDaTextura.move(-1, 0); // movimentando em X (negativamente)
			currentFrame = 1;
			spriteDaTextura.setTextureRect(sf::IntRect(32 * int(currentFrame), 0, 32, 32)); // setando uma nova posição do rect para mudança da imagem
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // movimentando para direita

			spriteDaTextura.move(1, 0); // Movimentando em X (positivamente)
			currentFrame = 1;
			spriteDaTextura.setTextureRect(sf::IntRect(160 * int(currentFrame), 0, 32, 32)); // setando uma nova posição do rect para mudança da imagem
		}


		window.clear(sf::Color::White); // limpa a janela, colocando uma cor
		window.draw(spriteDaTextura); // desenhando na tela a sprite
		window.display(); // renderiza

	}
}