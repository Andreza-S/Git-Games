#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(769, 411), "Tarefa-1 Knight - 8 directions"); // criando uma janela através da class Window
	window.setFramerateLimit(60); // limita a quantidade de frames por segundo

	int speed = 2;

	float currentFrame = 0; //


	sf::Texture t1, t2, t3; //criando texturas
	t1.loadFromFile("./resources/red.png"); //atribuindo uma imagem a textura carrinho
	t2.loadFromFile("./resources/bg.png"); //atribuindo uma imagem a textura fundo
	t3.loadFromFile("./resources/bg2.png"); //atribuindo uma imagem a textura fundo2

	
	sf::IntRect rect(160, 0, 32, 32);

	sf::Sprite sCar(t1, rect), sBackground(t2), sPredios(t3); // o sprite é que é renderizado pela sfml
	sCar.setPosition(30, 360); // posicionando a imagem na janela
	sCar.setScale(2, 2); // multiplica x e y pelos valores passados

	sPredios.setTextureRect(sf::IntRect(415, 90, 260, 320));
	sPredios.setPosition(410, 90);
	
	sf::Event event;
	while (window.isOpen()) { // enquanto a janela estiver aberta - o loop de eventos

		while (window.pollEvent(event)) {  // loop de eventos

			if (event.type == sf::Event::EventType::Closed) { //se evento for do tipo closed
				window.close(); // fecha a janela
			}
		}

		//INPUTS - Teclas direcionais
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // movitando para ESQUERDA

			sCar.move(-speed, 0); // movimentando em X (negativamente)	
			currentFrame = 1;

			if (currentFrame > 6) currentFrame -= 6;
			sCar.setTextureRect(sf::IntRect(32 * int(currentFrame), 0, 32, 32)); // setando uma nova posição do rect para mudança da imagem

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // movimentando para DIREITA
			sCar.move(speed, 0); // Movimentando em X (positivamente)
			currentFrame = 1;

			if (currentFrame > 6) currentFrame -= 6;
			sCar.setTextureRect(sf::IntRect(160 + int(currentFrame), 0, 32, 32)); // setando uma nova posição do rect para mudança da imagem

		}


		window.clear(sf::Color::White); // limpa a janela, colocando uma cor
		window.draw(sBackground); // desenhando o fundo
		window.draw(sCar); // desenhando o carrinho vermelho
		window.draw(sPredios); // desenhando os predios
		window.display(); // renderiza

	}
}