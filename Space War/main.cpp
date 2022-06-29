#include <SFML/Graphics.hpp>
#include <memory>

int main() {
	std::srand(std::time(nullptr)); //para gerar numeros randomicos

	// criação da janela
	auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1280, 700), "Space War 1.0", sf::Style::Titlebar | sf::Style::Close);
	window->setPosition(sf::Vector2i(0, 0));
	window->setFramerateLimit(60); //definindo a velocidade da movimentação na tela

	// Inserindo imagens e sons

		// imagem nossa_nave
	std::shared_ptr<sf::Texture> textura_nossa_nave = std::make_shared<sf::Texture>();
	textura_nossa_nave->loadFromFile("./assets/imagens/nossaNAVE.png");
	std::shared_ptr<sf::Sprite> nossa_nave = std::make_shared<sf::Sprite>();
	nossa_nave->setTexture(*textura_nossa_nave);
	nossa_nave->setPosition(570, 610); // X e Y posicionando a nossa_nave na tela

		//bullet nossoLaser
	auto bullet_textura = std::make_shared<sf::Texture>();
	bullet_textura->loadFromFile("./assets/imagens/redimensionado_nossoLaser.png");
	auto bullet = std::make_shared<sf::Sprite>(*bullet_textura);

		//vetores
	std::vector<sf::Sprite> bullets, inimigos;


		//ints
	int disparos_nosso_laser = 20, spawn_inimigos = 1;

		//fundo
	auto fundo_textura = std::make_shared<sf::Texture>();
	fundo_textura->loadFromFile("./assets/imagens/fundo2.png");
	auto fundo = std::make_shared<sf::Sprite>(*fundo_textura);

		//inimigos
	auto inimigo_textura = std::make_shared<sf::Texture>();
	inimigo_textura->loadFromFile("./assets/imagens/naveINIMIGA.png");
	auto inimigo = std::make_shared<sf::Sprite>(*inimigo_textura);
	inimigo->setPosition(std::rand() % window->getSize().x - inimigo->getGlobalBounds().width, 0 - inimigo->getGlobalBounds().height);
	inimigos.push_back(*inimigo);

	

	// Loop dos eventos e execução do game
		//loop eventos
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) { // para fechar a tela com o mouse
				window->close();
			}

		}

		// condições de movimentação de nossa_nave
			// com encadeamento de if, podemos pressionar e capturar o movimento de mais de uma tecla, assim podemos mover na diagonal
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			nossa_nave->move(10.f, 0.f); // X, Y aumenta em X , dirieta
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			nossa_nave->move(-10.f, 0.f); // X, Y diminui em X, esquerda
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			nossa_nave->move(0.f, 10.f); // X, Y aumenta em Y, para baixo
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			nossa_nave->move(0.f, -10.f); // X, Y diminui em Y, para cima
		}
			// limitando o movimento de nossa_nave na tela para que não ultrasse os limites da janela
				// para eixo X
		if (nossa_nave->getPosition().x < 0) {
			nossa_nave->setPosition(0, nossa_nave->getPosition().y); //se a posicao em x for menor que 0, seta x pra 0 e Y atual
		}
		if (nossa_nave->getPosition().x > window->getSize().x - textura_nossa_nave->getSize().x) {
			nossa_nave->setPosition(window->getSize().x - textura_nossa_nave->getSize().x, nossa_nave->getPosition().y); //se a posicao em x for maior que o tamanho da janela em x, seta x pra o tamanho maximo da janela em e Y atual
		}
				// para o eixo Y
		if (nossa_nave->getPosition().y < 0) {
			nossa_nave->setPosition(nossa_nave->getPosition().x, 0); //se a posicao em y for menor que 0, seta y pra 0 e x atual
		}
		if (nossa_nave->getPosition().y > window->getSize().y - textura_nossa_nave->getSize().y) {
			nossa_nave->setPosition(nossa_nave->getPosition().x, window->getSize().y - textura_nossa_nave->getSize().x); //se a posicao em y for maior que o tamanho da janela em y, seta y pra o tamanho maximo da janela em y e X atual
		}


		//BULLETS
			
		if (disparos_nosso_laser < 20) {
			++disparos_nosso_laser;
		}

			// Setando a posição do laser
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && disparos_nosso_laser >= 20) {

			bullet->setPosition(nossa_nave->getPosition().x + textura_nossa_nave->getSize().x / 2.f - 33.f, nossa_nave->getPosition().y);
			bullets.push_back(*bullet);
			disparos_nosso_laser = 0; 
		}
			
			//movimentando cada objeto bullet do vetor e deletando da janela
		for (int i{}; i < bullets.size(); ++i) {
			bullets[i].move(0, -10.f); // movimenta cada bullet na tela
			
			if (bullets[i].getPosition().y < 0) { // caso o bullet ultrapasse o limite da janela
				bullets.erase(bullets.begin() + i); // retira-se um objeto do vetor na posição
			}

			for (int k{}; k < inimigos.size(); ++k) {
				if (bullets[i].getGlobalBounds().intersects(inimigos[k].getGlobalBounds())) {
					inimigos.erase(inimigos.begin() + k);
					bullets.erase(bullets.begin() + i);
	
				}
			}
		}

		//INIMIGOS
		if (spawn_inimigos < 20) {
			++spawn_inimigos;
		}
		if (spawn_inimigos >= 20) {
			inimigo->setPosition(std::rand() % window->getSize().x - inimigo->getGlobalBounds().width, 0 - inimigo->getGlobalBounds().height);
			inimigos.push_back(*inimigo);
			spawn_inimigos = 0;
		}

		for (int i{}; i < inimigos.size(); ++i) {
			inimigos[i].move(0.f, +3.f);
			if (inimigos[i].getPosition().y > window->getSize().y) {
				inimigos.erase(inimigos.begin() + i);
			}
		}


		// desenho na janela
		window->clear();

		window->draw(*fundo); // desenhando a nossa_nave

		window->draw(*nossa_nave); // desenhando a nossa_nave

		window->draw(*inimigo); // desenhando a nave Inimiga
		
		for (auto& b : bullets) { //loop que desenha os objetos do vetor bullets, nossos lasers
			window->draw(b);
		}

		for (auto& inim : inimigos) { //loop que desenha os objetos do vetor inimigos
			window->draw(inim);
		}


		window->display();

	}
	return EXIT_SUCCESS;
}





