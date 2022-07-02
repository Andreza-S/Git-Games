#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode(256, 256), "Aula 3 - Usando SFML/Graphics"); // criando uma janela através da class Window

	sf::Event event;

	sf::Texture textura; //criando uma textura
	textura.loadFromFile("./resources/red.png"); //atribuindo uma imagem a textura

	sf::Sprite spriteDaTextura(textura, sf::IntRect(0,0, 32,32)); // o sprite é que é renderizado pela sfml
	//IntRect cria um retangulo interno a partir do local e do tamanho indicados


	while (window.isOpen()) { // enquanto a janela estiver aberta

		while (window.pollEvent(event)) {  // loop de eventos

			if (event.type == sf::Event::EventType::Closed) { //se evento for do tipo closed
				window.close(); // fecha a janela
			}
		}
		window.clear(); // limpa a janela
		window.draw(spriteDaTextura); // desenhando na tela a sprite
		window.display(); // renderiza

	}
}