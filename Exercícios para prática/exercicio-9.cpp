#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(380, 512), "Aula 9 -  Movimentando e animando Personagem"); // criando uma janela atrav�s da class Window
	window.setFramerateLimit(60); // limita a quantidade de frames por segundo

	float currentFrame = 0; //


	sf::Texture textura; //criando uma textura
	textura.loadFromFile("./resources/fang.png"); //atribuindo uma imagem a textura
	
	sf::IntRect rect(0, 244, 40, 50);
	sf::Sprite spriteDaTextura(textura, rect); // o sprite � que � renderizado pela sfml
	spriteDaTextura.setPosition(50, 100); // posicionando a imagem na janela
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

			if (spriteDaTextura.getPosition().x > 0) { // se a posi��o for maior que 0 em X
				spriteDaTextura.move(-1, 0); // movimentando em X (negativamente)
			} 

			currentFrame += 0.15;
			if (currentFrame > 6) currentFrame -= 6;
			spriteDaTextura.setTextureRect(sf::IntRect(40 * int(currentFrame) + 40, 244, - 40, 50)); // setando uma nova posi��o do rect para mudan�a da imagem
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { // movimentando para direita


			if (spriteDaTextura.getPosition().x < 380 - 80) { // se a posi��o for menor que 380 - (o tamanho da imagem, porque a referencia � o lado esquerdo da textura)  em X
				spriteDaTextura.move(1, 0); // Movimentando em X (positivamente)
			}	
			currentFrame += 0.15;
			if (currentFrame > 6) currentFrame -= 6;
			spriteDaTextura.setTextureRect(sf::IntRect(40 * int(currentFrame), 244, 40, 50)); // setando uma nova posi��o do rect para mudan�a da imagem
		}

		


		window.clear(sf::Color::White); // limpa a janela, colocando uma cor
		window.draw(spriteDaTextura); // desenhando na tela a sprite
		window.display(); // renderiza

	}
}