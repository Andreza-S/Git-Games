#include "jogo.hpp"


Jogo::Jogo() { // CONSTRUTOR

	//janela
	janela.create(sf::VideoMode(1024, 576), "Projeto Final POO - Andreza Santos =D", sf::Style::Titlebar | sf::Style::Close), janela.setFramerateLimit(60);
	janela.setPosition(sf::Vector2i(0, 0));
	janela.setMouseCursorVisible(false);

	//sonoplastia
	cliquesom.loadFromFile("./assets/sons/estouro.wav");
	gameoversom.loadFromFile("./assets/sons/game-over.wav");
	clique_sound.setBuffer(cliquesom);
	gameover_sound.setBuffer(gameoversom);
	music.openFromFile("./assets/sons/fundo.wav");

	// variaveis de manipulação
	pressed = false; // pressionar o botao
	gameover = false; // gameover
	paused = false; // pausa
	points = 0;	//Pontos e vidas
	health = 50; //vidas
	velocity = -0.9f;

	//fontes
	fonte.loadFromFile("./assets/fontes/BAMBINA_.TTF");
	fonteGameover.loadFromFile("./assets/fontes/JI_Balloon_Caps.TTF");

	//texto pausa
	paused_text.setFont(fonte);
	paused_text.setFillColor(sf::Color::Black);
	paused_text.setString("Jogo Pausado\nAperte Esc para retornar\n\nPressione S para salvar e SAIR");
	paused_text.setPosition(180, 200);
	paused_text.setCharacterSize(30);

	//f1 - reiniciar o jogo
	f1.setFont(fonte);
	f1.setFillColor(sf::Color::White);
	f1.setPosition(600, 10);
	f1.setString("Pressione a tecla F1 para Novo Jogo");
	f1.setCharacterSize(17);

	//gameover
	gameover_text.setFont(fonteGameover);
	gameover_text.setFillColor(sf::Color::Black);
	gameover_text.setString("Game Over");
	gameover_text.setPosition(110, 200);
	gameover_text.setCharacterSize(150);

	//score
	score.setFont(fonte);
	score.setString("Pontos: " + std::to_string(points));
	score.setFillColor(sf::Color::Black);
	score.setPosition(5.f, 5.f);

	//life
	life.setFont(fonte);
	life.setString("Vidas: " + std::to_string(health));
	life.setFillColor(sf::Color::Black);
	life.setPosition(800, 5);

	bg.loadFromFile("./assets/imagens/fundo2.jpg");
	ponteiro.loadFromFile("./assets/imagens/agulha.png");


	fundo.setTexture(bg);
	agulha.setTexture(ponteiro);
	

	//OBJETOS
	max_objs = 10;
	obj_vel_max = 10;
	balao_vel = obj_vel_max;

}

// Adicionando os baloes ao vector e muda a coordenada de x
void Jogo::muda_coord_x() {

	if (vector_baloes.size() < max_objs) {
		if (balao_vel >= obj_vel_max) {

			if (std::rand() % 3 <= 0) {
				vector_baloes.push_back(new Balao_perde_ponto(janela.getSize().x, 500, std::rand() % 100));
			}
			else {
				vector_baloes.push_back(new Balao(janela.getSize().x, 500));
			}

			balao_vel = 0.f;
		}
		else {
			balao_vel += 1.f;
		}
	}
}

//dinamica do game
void Jogo::code_game() {

	// Adicionando os baloes ao vector
	this->muda_coord_x();

	//iterando
	for (size_t i{}; i < vector_baloes.size(); ++i) {
		vector_baloes[i]->set_del_false();


		// mudando velocidade e fazendo o balao voar
		vector_baloes[i]->muda_velocidade_y(velocity);
		vector_baloes[i]->voar();


		//verificando se o botao do mouse foi pressionado caso não...
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressed == false) {

			//verificando se o balao foi estourado, se foi...
			if (vector_baloes[i]->retorna_balao_sprite().getGlobalBounds().contains(pos_mouse_coord)) {
				clique_sound.play();
				vector_baloes[i]->set_del_true();

				points = vector_baloes[i]->pontua(points, 10);

				score.setString("Ponto: " + std::to_string(points));
				pressed = true;

				//a cada 100 pontos a velocidade aumenta em 0.2
				if (points % 100 == 0) {

					velocity -= 0.3; // aumentando a velocidade

					//a cada 200 pontos ganha-se mais 2 vidas
				}
				if (points % 200 == 0) {
					health += 1;
				}
			}
		}

		// se a posição do balão for menor que 0, se ele sair da tela
		if (vector_baloes[i]->retorna_balao_sprite().getPosition().y < 0) {
			
			if (vector_baloes[i]->perde_vida == true) { // verificando se o balao faz perder vida
				--health;
			}

			life.setString("Vidas: " + std::to_string(health));
			vector_baloes[i]->set_del_true();

			// se a quantidade de vidas chegar a 0 (zero)
			if (health <= 0 or points < 0) {
				gameover_sound.play();
				gameover = true; // gameover é true
			}
		}

		//se o balao estiver estourado, retira-se o balao e aloca-se mais um no vector
		if (vector_baloes[i]->estaEstourado()) {
			vector_baloes.erase(vector_baloes.begin() + i);
		}

	}

	//desenhando a tela
	janela.clear();
	janela.draw(fundo);
	janela.draw(score);
	janela.draw(life);

	//desenhando os baloes
	for (size_t i = 0; i < vector_baloes.size(); ++i) {

		janela.draw(vector_baloes[i]->retorna_balao_sprite());
	}

	//desenhando a agulha (ponteiro do mouse)
	janela.draw(agulha);
	janela.display();
}

// Game Over
void Jogo::game_over() {

	music.stop(); // pausa a musica de fundo
	score.setFillColor(sf::Color::White); // muda a cor do texto

	janela.setMouseCursorVisible(true); // ativa o mouse
	janela.draw(fundo); // desenha o fundo
	janela.draw(score); // desenha os pontos
	janela.draw(f1); // desenha textos f1, para reiniciar o jogo com a tecla f1
	janela.draw(gameover_text); // desenha texto sobre game over
	janela.display();

	//se a tecla F1 for pressionada, reinicia os valores dos atributos 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
		gameover_sound.stop();
		score.setFillColor(sf::Color::Black);
		vector_baloes.clear();
		health = 50;
		life.setString("Vidas: " + std::to_string(health));
		points = 0;
		score.setString("Pontos: " + std::to_string(points));
		gameover = false;
		velocity = -0.9;
		janela.setMouseCursorVisible(false);

	}
}

//Jogo estiver pausado
void Jogo::pause_game() {
	music.pause(); // pausa a musica de fundo
	//desenha nova tela
	janela.clear();
	janela.draw(fundo);
	janela.draw(paused_text);
	janela.display();
	agulha.setPosition(static_cast<sf::Vector2f>(current_position));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { // se a tecla Esc for pressionada sai do pausa
		paused = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { // se a tecla S for pressionada sai do pausa
		Arquivo *arquivo = new Arquivo();
		arquivo->salvar_dados(1, points, health, velocity);
		delete arquivo;
		arquivo = nullptr;
		janela.close();
		
	}
}

// Loop de eventos do game
void Jogo::loop_events() {
	sf::Event event;

	//musica
	if (music.getStatus() == sf::Music::Stopped || music.getStatus() == sf::Music::Paused) {
		music.play();
		music.setLoop(true);
	}
	// capatura os eventos que ocorrem na janela
	while (janela.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			janela.close();
		}
		if (event.type == sf::Event::Resized) {
			sf::FloatRect visible_area(0, 0, event.size.width, event.size.height);
			janela.setView(sf::View(visible_area));
		}
		if (event.type == event.MouseButtonPressed) {
			current_position = sf::Mouse::getPosition(janela);
			pressed = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) { // pausando o game com a tecla Enter
			paused = true;
		}
		pos_mouse_win = sf::Mouse::getPosition(janela);
		pos_mouse_coord = janela.mapPixelToCoords(pos_mouse_win);
		agulha.setPosition((sf::Vector2f)pos_mouse_win);

	}

}

// Inicia o programa
void Jogo::run_game() {

	Arquivo* arquivo = new Arquivo(); 
	arquivo->ler_dados();
	auto ta_salvo = arquivo->retorna_ta_salvo();

	if (ta_salvo == 1) {
		points = arquivo->retorna_pontos();
		cout << points; // para debugar
		health = arquivo->retorna_vidas();
		cout << health; // para debugar
		velocity = arquivo->retorna_velocidade();
		cout << velocity; // para debugar
	}

	delete arquivo;
	arquivo = nullptr;


	while (janela.isOpen()) {

		this->loop_events(); // loop dos eventos

		// verifica s eé game over ou não
		if (gameover) {
			this->game_over();
		}
		else {
			if (paused) { // se o jogo estiver pausado
				this->pause_game();
			}
			else { // executa o game
				this->code_game();
			}
		}
	}
}