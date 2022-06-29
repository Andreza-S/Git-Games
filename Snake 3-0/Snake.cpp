#include "Snake.hpp"
#include "game.hpp"

Snakegame s[100];
Fruit fruit;

// Construtor (Inicializa os objetos e a window (janela))
Snake::Snake() {
	cols = 17;
	lines = 10;
	size = 64;
	width = size * cols;
	height = size * lines;
	direction = 0;
	num = 4;
	timer = 0.f;
	delay = 0.1f;
	fruit.x = fruit.y = 5;
	points = 0;
	eh_game_over = false;
	paused = false;

	window.create(sf::VideoMode(width, height), "Snake 1.0", sf::Style::Titlebar | sf::Style::Close);
	window.setPosition(sf::Vector2i(0, 0));


	t1.loadFromFile("./assets/imagens/fundo.png");
	t2.loadFromFile("./assets/imagens/corpo.png"); // corpo snake
	t3.loadFromFile("./assets/imagens/fruta2.png");
	t4.loadFromFile("./assets/imagens/fundo_gameover.png");
	t5.loadFromFile("./assets/imagens/fundo_gameover.png");

	//cabecas da snake
	t6.loadFromFile("./assets/imagens/cabecaesquerda.png"); //cabeca esquerda
	t7.loadFromFile("./assets/imagens/cabecadireita.png"); // cabeca indo pra direita
	t8.loadFromFile("./assets/imagens/cabecacima.png"); // cabeca indo pra baixo
	t9.loadFromFile("./assets/imagens/cabecabaixo.png"); // cabeca indo pra cima



	sp1.setTexture(t1); //fundo
	sp2.setTexture(t2); //corpo
	sp3.setTexture(t3); //fruta
	sp4.setTexture(t4); //fundo gameover
	sp5.setTexture(t5); // fundo com pausa
	sp6.setTexture(t7); // cabeça (inicializada com cabeca para direita)

	//fontes
	fonte_gameover_pontos.loadFromFile("./assets/fontes/AGENTRED.TTF");
	fonte_pausa_f1.loadFromFile("./assets/fontes/atwriter.ttf");


	// textos

	texto_pontos.setFont(fonte_gameover_pontos);
	texto_pontos.setString("Pontos: " + std::to_string(points));
	texto_pontos.setFillColor(sf::Color::Black);
	texto_pontos.setPosition(10, 10);

	gameover_text.setFont(fonte_gameover_pontos);
	gameover_text.setString("Game Over");
	gameover_text.setFillColor(sf::Color::Black);
	gameover_text.setPosition(190, 200);
	gameover_text.setCharacterSize(75);

	pausa_text.setFont(fonte_pausa_f1);
	pausa_text.setString("Jogo em pausa\nAperte Esc para retornar");
	pausa_text.setFillColor(sf::Color::White);
	pausa_text.setPosition(20, 200);
	pausa_text.setCharacterSize(60);

	f1_text.setFont(fonte_pausa_f1);
	f1_text.setString("Aperte F1 para reiniciar");
	f1_text.setFillColor(sf::Color::Black);
	f1_text.setPosition(320, 550);
	f1_text.setCharacterSize(30);

}// FIM DO CONSTRUTOR


// execução do game
void Snake::run_game() {

	while (window.isOpen()) {

		if (!eh_game_over) {
			if (!paused) {
				float time = clock.getElapsedTime().asSeconds();
				clock.restart();
				timer += time;
				sf::Event event;

				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						window.close();

					}
				}
				if (timer > delay) {
					timer = 0;
					collision();
				}
				window.clear();
				// construção da tela de fundo
				for (int i{}; i < cols; ++i) {
					for (int j{}; j < lines; ++j) {
						sp1.setPosition(i * size, j * size);
						window.draw(sp1); // desenha o fundo

					}
				}
				//desenhando a snake
				for (int i{}; i < num; ++i) {
					if (i == 0) {
						sp6.setPosition(s[i].x * size, s[i].y * size);
						window.draw(sp6);
					}
					else {
						sp2.setPosition(s[i].x * size, s[i].y * size);
						window.draw(sp2);
					}
					

				}

				// desenhando a fruta
					// A FAZER desenha a fruta na posição diferente da Snake
						sp3.setPosition(fruit.x * size, fruit.y * size);
						window.draw(sp3);
	
				//desenhando o texto
				window.draw(texto_pontos);

				window.display();

			}
			else {
				pause_game();
			}
	
		}
		else {
			game_over();
		}
	}
}

// função Game Over
void Snake::game_over() {

	//music.stop();
	//texto_pontos.setFillColor(sf::Color::White);
	//f1_text.setFillColor(sf::Color::White);
	//gameover_text.setFillColor(sf::Color::White);

	window.clear(); // preparando a tela de Game Over
	window.draw(sp4);
	window.draw(texto_pontos);
	window.draw(f1_text);
	window.draw(gameover_text);
	window.display();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) { // reiniciando com F1
		texto_pontos.setFillColor(sf::Color::Black);
		cols = 17;
		lines = 10;
		size = 64;
		width = size * cols;
		height = size * lines;
		direction = 0;
		num = 4;
		timer = 0.f;
		delay = 0.1f;
		fruit.x = fruit.y = 5;
		points = 0;
		eh_game_over = false;
		paused = false;

	}
}


// funcao para construção da tela do jogo, com movimentação e condições de jogabilidade
void Snake::collision() {
	// movimentação

	for (int i = num; i > 0; --i) {
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction != 1) {
		direction = 0;
		sp6.setTexture(t7); // recebe cabeca para a direita
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction != 0) {
		direction = 1;
		sp6.setTexture(t6); //  recebe cabeca para a esquerda
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction != 3) {
		direction = 2;
		sp6.setTexture(t8); //  recebe cabeca para para cima
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && direction != 2) {
		direction = 3;
		sp6.setTexture(t9); // recebe cabeca para para baixo
	}

	switch (direction) // setando a direção do movimento
	{
	case 0:
		s[0].x += 1;
		break;
	case 1:
		s[0].x -= 1;
		break;
	case 2:
		s[0].y -= 1;
		break;
	case 3:
		s[0].y += 1;
		break;
	}

	// condições para pegar a fruta e crescer o tamanho da snake
	if (s[0].x == fruit.x && s[0].y == fruit.y) {

		// aumentando os pontos cada vez que pega a fruta
		points += 10;
		texto_pontos.setString("Pontos: " + std::to_string(points));
		++num; // aumentando o tamanho da snake

		fruit.x = std::rand() % cols; // SETANDO posicao x de fruit
		fruit.y = std::rand() % lines; // SETANDO posicao y de fruit
	}

	if (s[0].x > cols) { // fazendo com que a snake volte para a tela, caso ela saia da tela pela direita
		s[0].x = 0;
	}
	if (s[0].x < 0) {// fazendo com que a snake volte para a tela, caso ela saia da tela pela esquerda
		s[0].x = cols;
	}
	if (s[0].y > lines) { // fazendo com que a snake volte para a tela, caso ela saia da tela por cima
		s[0].y = 0;
	}
	if (s[0].y < 0) {
		s[0].y = lines; // fazendo com que a snake volte para a tela, caso ela saia da tela por baixo
	}

	// condições para gameover
	for (int i = 1; i < num; i++) {
		if (s[i].y == s[0].y && s[i].x == s[0].x) { // se a snake colidir em seu proprio corpo
			eh_game_over = true;
			break;
		}
	}
	//para pausar o game

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) { // pausando o game com a tecla Enter
		paused = true;
	}

}


//Função de Pausa
void Snake::pause_game() {
	//music.pause();
	window.clear();
	window.draw(sp5);
	window.draw(pausa_text);
	window.display();


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { //tecla Esc para sair do pausa
		paused = false;
	}
}



//void Snake::colorindo_snake() {
//	for (int i{}; i <= num; i++) {
//
//	}
//}
