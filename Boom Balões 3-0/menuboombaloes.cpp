#include "menuboombaloes.hpp"



MenuBoomBaloes::MenuBoomBaloes() {
	window = new sf::RenderWindow();
	winclose = new sf::RectangleShape();
	fonte = new sf::Font();
	image = new sf::Texture();
	fundo = new sf::Sprite();

	set_values();
}

MenuBoomBaloes::~MenuBoomBaloes() {
	delete window;
	delete winclose;
	delete fonte;
	delete image;
	delete fundo;
}

void MenuBoomBaloes::set_values() {
	window->create(sf::VideoMode(1024, 576), "Menu Boom Baloes", sf::Style::Titlebar | sf::Style::Close);
	window->setPosition(sf::Vector2i(0, 0));

	pos = 0;
	pressed = theselect = false;
	fonte->loadFromFile("./assets/fontes/BAMBINA_.TTF");
	image->loadFromFile("./assets/imagens/imagens para desenv/fundoMENUOFICIAL.png");

	fundo->setTexture(*image);

	pos_mouse = { 0,0 };
	mouse_coord = { 0,0 };

	options = { "Jogar", "Opcoes", "Sair" };
	texts.resize(3);
	coords = { {550,191 }, { 590,282 }, { 630,370 } };
	sizes = { 45,35,35 };

	for (std::size_t i{}; i < texts.size(); ++i) {
		texts[i].setFont(*fonte);
		texts[i].setString(options[i]);
		texts[i].setCharacterSize(sizes[i]);
		texts[i].setOutlineColor(sf::Color::Black);
		texts[i].setPosition(coords[i]);
	}

	texts[0].setOutlineThickness(4);

	winclose->setSize(sf::Vector2f(78, 80));
	winclose->setPosition(917, 18);
	winclose->setFillColor(sf::Color::Transparent);

	// tem que encontrar um modo de subrepor o retangulo e o texto, ou utilizar somente o texto
	//clique_jogar->setSize(sf::Vector2f(45,45));
	//clique_jogar->setPosition(550, 191);
	//clique_jogar->setFillColor(sf::Color::Transparent);


	//clique_opcoes->setSize(sf::Vector2f(35, 35));
	//clique_opcoes->setPosition(590, 282);
	//clique_opcoes->setFillColor(sf::Color::Transparent);


	//clique_sair->setSize(sf::Vector2f(35, 35));
	//clique_sair->setPosition(630, 370);
	//clique_sair->setFillColor(sf::Color::Transparent);
}

void MenuBoomBaloes::loop_events() {
	sf::Event event;
	while (window->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window->close();
		}
		// Armazenando a posição do mouse
		pos_mouse = sf::Mouse::getPosition(*window);
		mouse_coord = window->mapPixelToCoords(pos_mouse);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed) {
			if (pos < 2) {
				++pos;
				pressed = true;
				texts[pos].setOutlineThickness(4);
				texts[pos - 1].setOutlineThickness(0);
				pressed = false;
				theselect = false;
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed) {
			if (pos > 0) {
				--pos;
				pressed = true;
				texts[pos].setOutlineThickness(4);
				texts[pos + 1].setOutlineThickness(0);
				pressed = false;
				theselect = false;
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect) {
			theselect = true;
			if (pos == 0) {
				jogo.run_game(); // Executa o game, a função run_game em Boombaloes
			}
			std::cout << options[pos] << '\n'; // aqui chama a função para para entrar na opção selecionada
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && !theselect) {
			theselect = true;
			if (pos == 2) {
				window->close();
			}
			std::cout << options[pos] << '\n'; // aqui chama a função para para entrar na opção selecionada
		}

		// Capturando os cliques do mouse no Menu
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (winclose->getGlobalBounds().contains(mouse_coord)) {
				window->close(); // para fechar na posicao do X desenhado na tela
			}

			//capturando a posicao para interação na opcoes do menu
			/*if (clique_jogar ->getGlobalBounds().contains(mouse_coord)) {
				std::cout << "opcao 0 selecionada, JOGAR";
			}
			if (clique_opcoes->getGlobalBounds().contains(mouse_coord)) {
				std::cout << "opcao 0 selecionada, OPCOES";
			}
			if (clique_sair->getGlobalBounds().contains(mouse_coord)) {
				std::cout << "opcao 0 selecionada, SAIR";*/
				//window->close();
			//}
		}



	}

}


void MenuBoomBaloes::draw_all() {
	window->clear();
	window->draw(*fundo);
	for (auto t : texts) {
		window->draw(t);
	}

	window->display();


}


void MenuBoomBaloes::run_menu() {
	while (window->isOpen()) {
		loop_events();
		draw_all();
	}
}