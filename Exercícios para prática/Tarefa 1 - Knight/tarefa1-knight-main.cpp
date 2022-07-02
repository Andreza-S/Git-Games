#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(1024, 512), "Tarefa-1 Knight - 8 directions"); // criando uma janela através da class Window
	window.setFramerateLimit(12); // limita a quantidade de frames por segundo

	int speed = 10;

	float currentFrame = 0; //


	sf::Texture t1; //criando texturas
	t1.loadFromFile("./resources/Knight.png"); //atribuindo uma imagem a textura carrinho

	
	sf::IntRect rect(133, 99, 40, 43);

	sf::Sprite personagem(t1, rect); // o sprite é que é renderizado pela sfml
	personagem.setPosition(300, 100); // posicionando a imagem na janela
	personagem.setScale(2, 2); // multiplica x e y pelos valores passados

	
	sf::Event event;
	while (window.isOpen()) { // enquanto a janela estiver aberta - o loop de eventos

		while (window.pollEvent(event)) {  // loop de eventos

			if (event.type == sf::Event::EventType::Closed) { //se evento for do tipo closed
				window.close(); // fecha a janela
			}
		}

		//INPUTS - Teclas direcionais
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { // movitando para ESQUERDA
			if (personagem.getPosition().x > 0) { // se a posição for maior que 0 em X
				personagem.move(-speed, 0); // movimentando em X (negativamente)	
			}

			if (currentFrame > 60) currentFrame -= 90;
			personagem.setTextureRect(sf::IntRect(69 - int(currentFrame), 50, 30, 43)); // setando uma nova posição do rect para mudança da imagem
			currentFrame += 30;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // movimentando para DIREITA
			if (personagem.getPosition().x < 1024 - 80){
				personagem.move(speed, 0); // Movimentando em X (positivamente)
			}
			if (currentFrame > 60) currentFrame -= 90;
			personagem.setTextureRect(sf::IntRect(196 + int(currentFrame), 50, 30, 43)); // setando uma nova posição do rect para mudança da imagem
			currentFrame += 30;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { // movitando para CIMA
			if (personagem.getPosition().y > 0) {
				personagem.move(0, -speed); // movimentando em Y (negativamente)
			}
			if (currentFrame > 60) currentFrame -= 90;
			personagem.setTextureRect(sf::IntRect(101 + int(currentFrame), 1, 30, 43)); // setando uma nova posição do rect para mudança da imagem
			currentFrame += 30;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { // movimentando para BAIXO
			if (personagem.getPosition().y < 436){
				personagem.move(0, speed); // Movimentando em Y (positivamente)
			}
			if (currentFrame > 60) currentFrame -= 90;
			personagem.setTextureRect(sf::IntRect(101 + int(currentFrame), 98, 30, 43)); // setando uma nova posição do rect para mudança da imagem
			currentFrame += 30;
		}

		//DIAGONAIS
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) and // Para CIMA e DIREITA
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))){
			if (currentFrame > 60) currentFrame -= 90;
			personagem.setTextureRect(sf::IntRect(201 + int(currentFrame), 1, 30, 43)); // setando uma nova posição do rect para mudança da imagem
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) and // Para BAIXO e DIREITA
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))){
			if (currentFrame > 60) currentFrame -= 90;
			personagem.setTextureRect(sf::IntRect(201 + int(currentFrame), 99, 30, 43)); // setando uma nova posição do rect para mudança da imagem
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) and // Para CIMA e ESQUERDA
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) { 
			if (currentFrame > 60) currentFrame -= 90;
			personagem.setTextureRect(sf::IntRect(69 - int(currentFrame), 2, 30, 43)); // setando uma nova posição do rect para mudança da imagem
			
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) and // Para BAIXO e DIREITA
			(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) { 
			if (currentFrame > 60) currentFrame -= 90;
			personagem.setTextureRect(sf::IntRect(73 - int(currentFrame), 99, 30, 43)); // setando uma nova posição do rect para mudança da imagem
			
		}

		// Se nenhum botão estiver sendo pressionado, seta a posição do sprite para a posição inicial
		if ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) and
			(!sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) and
			(!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) and
			(!sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {

			personagem.setTextureRect(sf::IntRect(133, 99, 35, 43)); // posição INICIAL
			currentFrame = 0;
		}

		window.clear(sf::Color::Black); // limpa a janela, colocando uma cor
		window.draw(personagem); // desenhando na tela a sprite
		window.display(); // renderiza

	}
}