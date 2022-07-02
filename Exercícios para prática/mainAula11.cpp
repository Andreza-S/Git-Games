#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(1024, 512), "Aula 11 -  Movimentando (com diagonal) e animando Carrinho vermelho - 2"); // criando uma janela através da class Window
	window.setFramerateLimit(60); // limita a quantidade de frames por segundo

	int speed = 2;

	float currentFrame = 0; //


	sf::Texture t1, t2; //criando texturas
	t1.loadFromFile("./resources/red.png"); //atribuindo uma imagem a textura carrinho
	t2.loadFromFile("./resources/bgcar.png"); //atribuindo uma imagem a textura fundo
	
	sf::IntRect rect(160, 0, 32, 32);

	sf::Sprite sCar(t1, rect), sBackground(t2); // o sprite é que é renderizado pela sfml
	sCar.setPosition(50, 100); // posicionando a imagem na janela
	sCar.setScale(2, 2); // multiplica x e y pelos valores passados

	
	sf::Event event;
	while (window.isOpen()) { // enquanto a janela estiver aberta - o loop de eventos

		while (window.pollEvent(event)) {  // loop de eventos

			if (event.type == sf::Event::EventType::Closed) { //se evento for do tipo closed
				window.close(); // fecha a janela
			}
		}

		//INPUTS
		
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
			sCar.setTextureRect(sf::IntRect(160 * int(currentFrame), 0, 32, 32)); // setando uma nova posição do rect para mudança da imagem
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // movitando para CIMA

			sCar.move(0, -speed); // movimentando em Y (negativamente)

			currentFrame = 1;
			if (currentFrame > 6) currentFrame -= 6;
			sCar.setTextureRect(sf::IntRect(96 * int(currentFrame), 0, 32, 32)); // setando uma nova posição do rect para mudança da imagem
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // movimentando para BAIXO
			
			sCar.move(0, speed); // Movimentando em Y (positivamente)

			currentFrame = 1;
			if (currentFrame > 6) currentFrame -= 6;
			sCar.setTextureRect(sf::IntRect(224 * int(currentFrame), 0, 32, 32)); // setando uma nova posição do rect para mudança da imagem
		}

		//DIAGONAIS
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) and
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))){

			currentFrame = 1;
			if (currentFrame > 6) currentFrame -= 6;
			sCar.setTextureRect(sf::IntRect(128 * int(currentFrame), 0, 32, 32)); // setando uma nova posição do rect para mudança da imagem
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) and 
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))){

			currentFrame = 1;
			if (currentFrame > 6) currentFrame -= 6;
			sCar.setTextureRect(sf::IntRect(192 * int(currentFrame), 0, 32, 32)); // setando uma nova posição do rect para mudança da imagem
		}


		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) and 
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) { // movitando para CIMA

			currentFrame = 1;
			if (currentFrame > 6) currentFrame -= 6;
			sCar.setTextureRect(sf::IntRect(64 * int(currentFrame), 0, 32, 32)); // setando uma nova posição do rect para mudança da imagem
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) and 
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) { // movimentando para BAIXO

			currentFrame = 1;
			if (currentFrame > 6) currentFrame -= 6;
			sCar.setTextureRect(sf::IntRect(0 * int(currentFrame), 0, 32, 32)); // setando uma nova posição do rect para mudança da imagem
		}

		


		window.clear(sf::Color::White); // limpa a janela, colocando uma cor
		window.draw(sBackground); // desenhando o fundo
		window.draw(sCar); // desenhando na tela a sprite
		window.display(); // renderiza

	}
}