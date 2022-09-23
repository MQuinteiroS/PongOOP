#include "Jogo.h";
#include "Global.h";
#include "Graficos.h";
#include "Input.h"
#include "Mapa.h"
#include "Menu.h"

#include <SDL.h>
#include <SDL_image.h>

namespace {
	const int FPS = 60;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Jogo::Jogo(){
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG);
	gameLoop();
}

Jogo::~Jogo() {

}

void Jogo::gameLoop() {
	SDL_Rect spawnPlayer1 = { 10, globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2, globals::WIDTH_PLAYER, globals::HEIGHT_PLAYER };
	SDL_Rect spawnPlayer2 = { globals::WIDTH - 10 - globals::WIDTH_PLAYER, globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2, globals::WIDTH_PLAYER, globals::HEIGHT_PLAYER };
	Graficos graficos;
	Input input;
	SDL_Event event;
	int player, parede, comeca = 1, delay = 0, placar[2] = { 0 }, x, y, qlMenuVoltar = 0, qlMenuIr = 0;
	float angulo, PI = 3.14159265;
	bool menu = true, mouse = false, playerbl = false, acabou = false, comecou = false;

	_mapas = Mapa("Playing", graficos);
	_player1 = Players("Player1", graficos, spawnPlayer1, 1);
	_player2 = Players("Player2", graficos, spawnPlayer2, 2);
	_ball = Ball("Ball", graficos);
	_menu = Menu("FullMenu", graficos);

	int LAST_UPDATE_TIME = SDL_GetTicks();
	while (true) {
		SDL_GetMouseState(&x, &y);
		input.beginNewFrame();
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true && qlMenuVoltar == 0) {
				return;
			}
			if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true && qlMenuVoltar != 0 && acabou == false) {
				qlMenuVoltar = 0;
				qlMenuIr = 0;
				menu = true; 
				playerbl = false;
				placar[0] = 0;
				placar[1] = 0;
				_player1.placar(0);
				_player2.placar(0);
				_player1.reiniciar();
				_player2.reiniciar();
				_menu.menuInteraction(x, y, qlMenuVoltar);
				_ball.reiniciaDoZero();
			}
			if (menu == true) {	
				if (qlMenuVoltar == 2 || qlMenuVoltar == 5 || qlMenuVoltar == 6 || qlMenuVoltar == 7 || qlMenuVoltar == 8 || qlMenuVoltar == 69) {
					_menu.menuInteraction(x, y, 20);
					comecou = false;
					menu = false;
				}
				qlMenuIr = _menu.menuInteraction(x, y, qlMenuVoltar);
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					mouse = true;
				}
				if (event.type == SDL_MOUSEBUTTONUP && mouse == true) {
					qlMenuVoltar = _menu.menuInteraction(x, y, qlMenuIr);
					mouse = false;
				}
			}
		/*	else if (event.type == SDL_QUIT) {
				return;
			}*/
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true && acabou == true) {
			_ball.comecaDoZero();
			_player1.reiniciar();
			_player2.reiniciar();
			placar[0] = 0;
			placar[1] = 0;
			_player1.placar(0);
			_player2.placar(0);
			_player1.vitoria(acabou);
			_player1.vitoria(acabou);
			acabou = false;
		}
		if (qlMenuVoltar != 0 && qlMenuVoltar != 10 && comecou == false && qlMenuVoltar != 1 && qlMenuVoltar != 4 && qlMenuVoltar != 2) {
			comecou = true;
			SDL_Delay(100);
			_ball.comecaDoZero();
			_player1.reiniciar();
			_player2.reiniciar();

		}
		if (qlMenuVoltar == 2 && comecou == false) {
			playerbl = true;
			comecou = true;
			SDL_Delay(100);
			_ball.comecaDoZero();
			_player1.reiniciar();
			_player2.reiniciar();
		}

		//verifica como os jogadores estao jogando para o bot, só pegar o valor de qlMenuVoltar pra determinar a dificuldade
		if (input.isKeyHeld(SDL_SCANCODE_W) == true) {
			_player1.comecaMovimentoParaCima();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_S) == true) {
			_player1.comecaMovimentoParaBaixo();
		}
		if (input.isKeyHeld(SDL_SCANCODE_W) == false && input.isKeyHeld(SDL_SCANCODE_S) == false) {
			_player1.terminaMovimento();
		}
		if (input.isKeyHeld(SDL_SCANCODE_UP) == true && playerbl == true) {
			_player2.comecaMovimentoParaCima();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_DOWN) == true && playerbl == true) {
			_player2.comecaMovimentoParaBaixo();
		}
		if (input.isKeyHeld(SDL_SCANCODE_UP) == false && input.isKeyHeld(SDL_SCANCODE_DOWN) == false && playerbl == true) {
			_player2.terminaMovimento();
		}
		//Determinaa quando a bola bate em um player
		if (_player1.pegaAtualLocaly() <= (_ball.pegaLocalBolay() + globals::HEIGHT_BALL) && _player1.pegaAtualLocaly() + globals::HEIGHT_PLAYER >= _ball.pegaLocalBolay()) {
			if (_ball.pegaLocalBolax() < 25) {
				parede = 0;
				player = 1;
				angulo = (((_player1.pegaAtualLocaly() + globals::HEIGHT_PLAYER / 2) - (_ball.pegaLocalBolay() + globals::HEIGHT_BALL / 2)) * PI / 4) / (globals::HEIGHT_PLAYER / 2);
				_ball.direcaoBola(angulo, player, parede);
			}
		}
		if (_player2.pegaAtualLocaly() <= (_ball.pegaLocalBolay() + globals::HEIGHT_BALL) && _player2.pegaAtualLocaly() + globals::HEIGHT_PLAYER >= _ball.pegaLocalBolay()) {
			if (_ball.pegaLocalBolax() + globals::WIDTH_BALL > globals::WIDTH - 25) {
				parede = 0;
				player = 2;
				angulo = (((_player2.pegaAtualLocaly() + globals::HEIGHT_PLAYER / 2) - (_ball.pegaLocalBolay() + globals::HEIGHT_BALL / 2)) * PI / 4) / (globals::HEIGHT_PLAYER / 2);
				_ball.direcaoBola(angulo, player, parede);
			}
		}

		//determina quando a bola bate numa parede
		if (_ball.pegaLocalBolay() <= 15) {
			if (parede == 1) {
				parede = 0;
			}
			else {
				parede = 1;
			}
			player = 0;
			_ball.direcaoBola(angulo, player, parede);
		}
		else if (_ball.pegaLocalBolay() + globals::HEIGHT_BALL >= globals::HEIGHT - 15) {
			if (parede == 1) {
				parede = 0;
			}
			else {
				parede = 1;
			}
			player = 0;
			_ball.direcaoBola(angulo, player, parede);
		}	
		
		if (qlMenuVoltar == 5 && comecou == true) {
			_player2.botFacil(_ball);
		}
		if (qlMenuVoltar == 6 && comecou == true) {
			_player2.botNormal(_ball);
		}
		if (qlMenuVoltar == 7 && comecou == true) {
			_player2.botDificil(_ball);
		}
		if (qlMenuVoltar == 8 && comecou == true) {
			_player2.botImpossivel(_ball);
		}
		if (qlMenuVoltar == 69 && comecou == true) {
			_player2.botImpossivel(_ball);
			_player1.botImpossivelP1(_ball);
		}

		//Faz a contagem dos pontos e reinicia quando alguem ganha
		if (_ball.pegaLocalBolax() >= globals::WIDTH || _ball.pegaLocalBolax() + globals::WIDTH_BALL <= 0) {
			_ball.reiniciaJogo(comeca, delay);
			if (delay == 1000) {
				if (comeca == 1) {
					comeca = 2;
				}
				else {
					comeca = 1;
				}
				player = 1;
				delay = 0;
			}
			else if (delay == 999) {
				if (_ball.pegaLocalBolax() >= globals::WIDTH) {
					if (placar[0] >= 9) {
						_player1.vitoria(acabou);
						_ball.reiniciaDoZero();
						delay = 0;
						acabou = true;
					}
					else {
						placar[0]++;
					}
				}
				else if (_ball.pegaLocalBolax() + globals::WIDTH_BALL <= 0) {
					if (placar[1] >= 9) {
						_player2.vitoria(acabou);
						_ball.reiniciaDoZero();
						delay = 0;
						acabou = true;
					}
					else {
						placar[1]++;
					}
				}
				_player1.placar(placar[0]);
				_player2.placar(placar[1]);

			}
			delay++;
		}
		const int CURRENT_TIME_MS = SDL_GetTicks();
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
		update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));

		LAST_UPDATE_TIME = CURRENT_TIME_MS;
		desenha(graficos);
	}
}

void Jogo::desenha(Graficos& graficos) {
	graficos.limpa();
	_mapas.desenha(graficos);
	_ball.desenha(graficos);
	_menu.desenha(graficos);
	_player1.desenha(graficos);
	_player2.desenha(graficos);
	graficos.carrega();
}

void Jogo::update(float elapsedTime) {
	_player1.update(elapsedTime);
	_player2.update(elapsedTime);
	_ball.update(elapsedTime);
}