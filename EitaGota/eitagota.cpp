#include "eitagota.hpp"


Eitagota::Eitagota() {
	//window
	window.create(sf::VideoMode(1024, 576), "EitchaGota -1.4 ", sf::Style::Titlebar | sf::Style::Close), window.setFramerateLimit(60);
	window.setPosition(sf::Vector2i(0, 0));
	window.setMouseCursorVisible(false);

	//sonoplastia
	cliquesom.loadFromFile("./assets/sons/limpando.wav");
	gameoversom.loadFromFile("./assets/sons/game-over.wav");
	clique_sound.setBuffer(cliquesom);
	gameover_sound.setBuffer(gameoversom);
	music.openFromFile("./assets/sons/musica-de-fundo.wav");

	// variaveis de manipulação
	pressed = false; // pressionar o botao
	gameover = false; // gameover
	paused = false; // pausa
	velocity = 5.f;	//velocidade do movimento dos objetos
	points = 0;	//Pontos e vidas
	health = 50; //vidas

	//fontes
	fonte.loadFromFile("./assets/fontes/BAMBINA_.TTF");

	//texto pausa
	paused_text.setFont(fonte);
	paused_text.setFillColor(sf::Color::White);
	paused_text.setString("Jogo Pausado\nAperte Esc para retornar");
	paused_text.setPosition(180, 200);
	paused_text.setCharacterSize(40);

	//f1 - reiniciar o jogo
	f1.setFont(fonte);
	f1.setFillColor(sf::Color::Yellow);
	f1.setPosition(600, 10);
	f1.setString("Pressione a tecla F1 para Novo Jogo");
	f1.setCharacterSize(16);

	//gameover
	gameover_text.setFont(fonte);
	gameover_text.setFillColor(sf::Color::White);
	gameover_text.setString("Game Over");
	gameover_text.setPosition(150, 200);
	gameover_text.setCharacterSize(100);

	//score
	score.setFont(fonte);
	score.setString("Pontos: " + std::to_string(points));
	score.setFillColor(sf::Color::White);
	score.setPosition(5.f, 5.f);

	//life
	life.setFont(fonte);
	life.setString("Vidas: " + std::to_string(health));
	life.setFillColor(sf::Color::White);
	life.setPosition(800, 5.f);

	//Imagens e texturas do game
	texture.loadFromFile("./assets/imagens/gotadagua.png"); // gotas
	bg.loadFromFile("./assets/imagens/chuva-1024x576.jpg"); // fundo
	ponteiro.loadFromFile("./assets/imagens/pano.png"); // desenho para o mouse
	stop.loadFromFile("./assets/imagens/fundo-pausa.jpg"); //fundo da tela em pausa

	object.setTexture(texture);
	fundo.setTexture(bg);
	pano.setTexture(ponteiro);
	pausafundo.setTexture(stop);

	//inicializando variavel x
	x = static_cast<float> (1 + rand() % ((int)(window.getSize().x - texture.getSize().x) - 10));
	object.setPosition(sf::Vector2f(x , 0.f));

	//OBJETOS
	max_objs = 4;
	obj_vel_max = 10.f;
	obj_vel = obj_vel_max;

}


void Eitagota::code_game() {
	//Adiconando objetos ao nosso vector com atrasos
	if (objs.size() < max_objs) {
		if (obj_vel >= obj_vel_max) {
			x = static_cast<float> (1 + rand() % ((int)(window.getSize().x - texture.getSize().x)));
			object.setPosition(x, 0.f);
			objs.push_back(object);
			obj_vel = 0.f;
		}
		else {
			obj_vel += 1.f;
		}
	}

	//Mover e deletar os objetos do vector
	for (size_t i{}; i < objs.size(); ++i) {
		bool del = false;
		objs[i].move(0.f, velocity);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressed == false) {
			if (objs[i].getGlobalBounds().contains(pos_mouse_coord)) {
				clique_sound.play();
				del = true;
				points += 10.f;
				score.setString("Pontos: " + std::to_string(points));
				pressed = true;
				if (points % 100 == 0) {
					velocity += 0.2f; // aumentando a velociade a cada 100 pontos
				}
				if (points % 200 == 0) {
					health += 5;

				}
			}
		}

		if (objs[i].getPosition().y > window.getSize().y) { // se deixar passar
			--health;
			life.setString("Vidas: " + std::to_string(health));
			del = true;
			if (health <= 0) {
				gameover_sound.play();
				gameover = true;
			}
		}
		if (del) {
			objs.erase(objs.begin() + i);
		}

	}


	window.clear();
	window.draw(fundo);
	window.draw(score);
	window.draw(life);


	for (auto& e : objs) {
		window.draw(e);
	}
	window.draw(pano);
	window.display();
} // termino do else do gamerover

void Eitagota::game_over() {
	music.stop();

	window.setMouseCursorVisible(true);
	window.clear(sf::Color::Black);
	window.draw(score);
	window.draw(f1);
	window.draw(gameover_text);
	window.display();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
		objs.clear();
		health = 50;
		life.setString("Vidas: " + std::to_string(health));
		points = 0;
		score.setString("Pontos: " + std::to_string(points));
		gameover = false;
		velocity = 5.f;
		window.setMouseCursorVisible(false);

	}
}

void Eitagota::pause_gamer() {
	music.pause();
	window.clear();
	window.draw(pausafundo);
	window.draw(paused_text);
	window.display();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { //tecla Esc
		paused = false;
	}
	pano.setPosition(static_cast<sf::Vector2f>(current_position));
}

void Eitagota::loop_events() {
	sf::Event event;
	if (music.getStatus() == sf::Music::Stopped || music.getStatus() == sf::Music::Paused) {
		music.play();
		music.setLoop(true);
	}
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::Resized) {
			sf::FloatRect visible_area(0, 0, event.size.width, event.size.height);
			window.setView(sf::View(visible_area));
		}
		if (event.type == event.MouseButtonPressed) {
			current_position = sf::Mouse::getPosition(window);
			pressed = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) { // pausando o game com a tecla Enter
			paused = true;
		}
		pos_mouse_win = sf::Mouse::getPosition(window);
		pos_mouse_coord = window.mapPixelToCoords(pos_mouse_win);
		pano.setPosition((sf::Vector2f)pos_mouse_win);

	}

}

void::Eitagota::run_game() {
	while (window.isOpen()) {
		this->loop_events(); // loop dos eventos

		// execuscao do game se é gameover ou continuar
		if (gameover) {
			this->game_over();
		}
		else {
			if (paused) {
				this->pause_gamer();
			}
			else {
				this->code_game();
			}
		}// while loop principal fechamento
	}
}
