#include "Players.h"
#include "Global.h"
#include "Ball.h"

#include <SDL_image.h>
#include <stdlib.h>
#include <sstream>
#include <random>

namespace Player_cte {
	const float VELOCIDADE = 0.5f;
	const float VELOCIDADE_FACIL = 0.2f;
	const float VELOCIDADE_NORMAL = 0.3f;
	const float VELOCIDADE_HARD = 0.4f;
	const float VELOCIDADE_IMPOSSIVEL = 0.9f;
}

Players::Players() {

}

Players::Players(std::string qualPlayer, Graficos& graficos, SDL_Rect onde, int player) :
	_dy(0),
	_qtd(0),
	_x(10),
	_player(player),
	_qualPlayer(qualPlayer),
	_spawn(onde),
	_mutante(onde.y),
	_qualVitoria(900){
	carregarPlayer(qualPlayer, graficos);
}


void Players::carregarPlayer(std::string qualPlayer, Graficos& graficos){
	std::stringstream ss;
	ss << "Images/" << qualPlayer << ".png";
	SDL_Texture* textura = SDL_CreateTextureFromSurface(graficos.pegaRenderer(), graficos.carregarImagem(ss.str()));
	SDL_Texture* placar = SDL_CreateTextureFromSurface(graficos.pegaRenderer(), graficos.carregarImagem("Images/Placar.png"));
	SDL_Texture* vitoria = SDL_CreateTextureFromSurface(graficos.pegaRenderer(), graficos.carregarImagem("Images/Victory.png"));
	_textura = textura;
	_placar = placar;
	_vitoria = vitoria;
}

void Players::comecaMovimentoParaCima() {
	if (_mutante == 15) {
		_dy = 0.0f;
	}
	else {
		_dy = -Player_cte::VELOCIDADE;
	}
}

void Players::comecaMovimentoParaBaixo() {
	if (_mutante == globals::HEIGHT - 15 - globals::HEIGHT_PLAYER) {
		_dy = 0.0f;
	}
	else {
		_dy = Player_cte::VELOCIDADE;
	}
}

void Players::botFacil(Ball& ball) {
	float ondevai = 0;
	if (ball.pegaLocalBolax() >= globals::WIDTH) {
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_FACIL;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_FACIL;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaLocalBolax() <= 0) {
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_FACIL;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_FACIL;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaVelocidadex() <= 0) {
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_FACIL;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_FACIL;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaVelocidadex() > 0) {
		if (ball.pegaVelocidadey() > 0) {
			ondevai = (_spawn.x - (ball.pegaLocalBolax() + globals::WIDTH_BALL)) * tan(-ball.pegaAngulo()) + (ball.pegaLocalBolay() + globals::HEIGHT_BALL);
			if (ondevai < 15) {
				_dy = -Player_cte::VELOCIDADE_FACIL;
			}
			else if (ondevai > globals::HEIGHT - 15) {
				_dy = Player_cte::VELOCIDADE_FACIL;
			}
			else if (_mutante + globals::HEIGHT_PLAYER / 2 > ondevai) {
				_dy = -Player_cte::VELOCIDADE_FACIL;
			}
			else if (_mutante + globals::HEIGHT_PLAYER / 2 < ondevai) {
				_dy = Player_cte::VELOCIDADE_FACIL;
			}
			else {
				_dy = 0.0f;
			}
		}
		else if (ball.pegaVelocidadey() < 0) {
			ondevai = (ball.pegaLocalBolay() + globals::HEIGHT_BALL) - (_spawn.x - (ball.pegaLocalBolax() + globals::WIDTH_BALL)) * tan(ball.pegaAngulo());
			if (ondevai < 15) {
				_dy = -Player_cte::VELOCIDADE_FACIL;
			}
			else if (ondevai > globals::HEIGHT - 15) {
				_dy = Player_cte::VELOCIDADE_FACIL;
			}
			else if (_mutante + globals::HEIGHT_PLAYER / 2 > ondevai) {
				_dy = -Player_cte::VELOCIDADE_FACIL;
			}
			else if (_mutante + globals::HEIGHT_PLAYER / 2 < ondevai) {
				_dy = Player_cte::VELOCIDADE_FACIL;
			}
			else {
				_dy = 0.0f;
			}
		}
	}
	printf("\n%f", ondevai);
}

void Players::botNormal(Ball& ball) {
	float ondevai;
	if (ball.pegaLocalBolax() >= globals::WIDTH) {
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_NORMAL;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_NORMAL;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaLocalBolax() <= 0) {
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_NORMAL;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_NORMAL;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaVelocidadex() <= 0) {
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_NORMAL;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_NORMAL;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaVelocidadex() > 0) {
		if (ball.pegaVelocidadey() > 0) {
			ondevai = (_spawn.x - (ball.pegaLocalBolax() + globals::WIDTH_BALL)) * tan(-ball.pegaAngulo()) + ball.pegaLocalBolay() + globals::HEIGHT_BALL / 2;
			if (_mutante + globals::HEIGHT_PLAYER / 2 > ondevai) {
				_dy = -Player_cte::VELOCIDADE_NORMAL;
			}
			else if (_mutante + globals::HEIGHT_PLAYER / 2 < ondevai) {
				_dy = Player_cte::VELOCIDADE_NORMAL;
			}
			else {
				_dy = 0.0f;
			}
		}
		if (ball.pegaVelocidadey() < 0) {
			ondevai = (ball.pegaLocalBolay() + globals::HEIGHT_BALL / 2) - (_spawn.x - (ball.pegaLocalBolax() + globals::WIDTH_BALL)) * tan(ball.pegaAngulo());
			if (_mutante + globals::HEIGHT_PLAYER / 2 > ondevai) {
				_dy = -Player_cte::VELOCIDADE_NORMAL;
			}
			else if (_mutante + globals::HEIGHT_PLAYER / 2 < ondevai) {
				_dy = Player_cte::VELOCIDADE_NORMAL;
			}
			else {
				_dy = 0.0f;
			}
		}
		else if (ball.pegaVelocidadey() == 0) {
			_dy = 0.0f;
		}
	}
}

void Players::botDificil(Ball& ball) {
	float ondevai;
	if (ball.pegaLocalBolax() >= globals::WIDTH) {
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_HARD;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_HARD;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaLocalBolax() <= 0) {
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_HARD;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_HARD;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaVelocidadex() <= 0) {
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_HARD;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_HARD;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaVelocidadex() > 0) {
		if (ball.pegaVelocidadey() > 0) {
			ondevai = (_spawn.x - (ball.pegaLocalBolax() + globals::WIDTH_BALL)) * tan(-ball.pegaAngulo()) + ball.pegaLocalBolay() + globals::HEIGHT_BALL / 2;
			if (_mutante + globals::HEIGHT_PLAYER / 2 > ondevai) {
				_dy = -Player_cte::VELOCIDADE_HARD;
			}
			else if (_mutante + globals::HEIGHT_PLAYER / 2 < ondevai) {
				_dy = Player_cte::VELOCIDADE_HARD;
			}
			else {
				_dy = 0.0f;
			}
		}
		if (ball.pegaVelocidadey() < 0) {
			ondevai = (ball.pegaLocalBolay() + globals::HEIGHT_BALL / 2) - (_spawn.x - (ball.pegaLocalBolax() + globals::WIDTH_BALL)) * tan(ball.pegaAngulo());
			if (_mutante + globals::HEIGHT_PLAYER / 2 > ondevai) {
				_dy = -Player_cte::VELOCIDADE_HARD;
			}
			else if (_mutante + globals::HEIGHT_PLAYER / 2 < ondevai) {
				_dy = Player_cte::VELOCIDADE_HARD;
			}
			else {
				_dy = 0.0f;
			}
		}
		else if (ball.pegaVelocidadey() == 0) {
			_dy = 0.0f;
		}
	}
}

void Players::botImpossivel(Ball& ball) {
	float ondevai;
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution2(0, globals::HEIGHT_PLAYER);
	if (ball.pegaLocalBolax() >= globals::WIDTH) {
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaLocalBolax() + globals::WIDTH_BALL <= 0) {
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaVelocidadex() < 0) {
		_x = distribution2(generator);
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
		}
		else{
			_dy = 0.0f;
		}
	}
	else if (ball.pegaVelocidadex() > 0) {
		if (ball.pegaVelocidadey() > 0) {
			ondevai = (_spawn.x - (ball.pegaLocalBolax() + globals::WIDTH_BALL)) * tan(-ball.pegaAngulo()) + ball.pegaLocalBolay() + globals::HEIGHT_BALL / 2;
			if (ondevai > 15 && ondevai < globals::HEIGHT - 15) {
				if (_mutante + _x > ondevai && _mutante + globals::HEIGHT_BALL / 2 >= 16) {
					if (ball.pegaVelocidadey() > Player_cte::VELOCIDADE_IMPOSSIVEL) {
						_dy = -ball.pegaVelocidadey();
					}
					else {
						_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
					}
				}
				else if (_mutante + _x < ondevai && _mutante + globals::HEIGHT_PLAYER + globals::HEIGHT_BALL / 2 <= globals::HEIGHT - 16) {
					if (ball.pegaVelocidadey() > Player_cte::VELOCIDADE_IMPOSSIVEL) {
						_dy = ball.pegaVelocidadey();
					}
					else {
						_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;
					}
				}
			}
			else if (_mutante + _x > ondevai && _mutante + globals::HEIGHT_BALL / 2 >= 16) {
				_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
			}
			else if (_mutante + _x < ondevai && _mutante + globals::HEIGHT_PLAYER + globals::HEIGHT_BALL / 2 <= globals::HEIGHT - 16) {
				_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;
			}
			else{
				_dy = 0.0f;
			}
		}
		if (ball.pegaVelocidadey() < 0) {
			ondevai = (ball.pegaLocalBolay() + globals::HEIGHT_BALL / 2) - (_spawn.x - (ball.pegaLocalBolax() + globals::WIDTH_BALL)) * tan(ball.pegaAngulo());	
			 if (ondevai > 15 && ondevai < globals::HEIGHT - 15) {
				if (_mutante + _x > ondevai && _mutante + globals::HEIGHT_BALL / 2 >= 16) {
					if (-ball.pegaVelocidadey() > Player_cte::VELOCIDADE_IMPOSSIVEL) {
						_dy = ball.pegaVelocidadey();
					}
					else {
						_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
					}
				}
				else if (_mutante + _x < ondevai && _mutante + globals::HEIGHT_PLAYER + globals::HEIGHT_BALL / 2 <= globals::HEIGHT - 16) {
					if (-ball.pegaVelocidadey() > Player_cte::VELOCIDADE_IMPOSSIVEL) {
						_dy = -ball.pegaVelocidadey();
					}
					else {
						_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;
					}
				}
			}
			else if (_mutante + _x > ondevai && _mutante + globals::HEIGHT_BALL / 2 >= 16) {
				_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
			}
			else if (_mutante + _x < ondevai && _mutante + globals::HEIGHT_PLAYER + globals::HEIGHT_BALL / 2 <= globals::HEIGHT - 16) {
				_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;	
			}
			else{
				_dy = 0.0f;
			}
		}
		else if (ball.pegaVelocidadey() == 0) {
			_dy = 0.0f;
		}
	}
	if (_mutante <= 17) {
		_dy = Player_cte::VELOCIDADE_HARD;
	}
	else if (_mutante >= globals::HEIGHT - 17) {
		_dy = -Player_cte::VELOCIDADE_HARD;
	}
}

void Players::botImpossivelP1(Ball& ball) {
	float ondevai;
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution2(0, globals::HEIGHT_PLAYER);
	if (ball.pegaLocalBolax() >= globals::WIDTH) {
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaLocalBolax() + globals::WIDTH_BALL <= 0) {
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaVelocidadex() > 0) {
		_x = distribution2(generator);
		if (_mutante < globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;
		}
		else if (_mutante > globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2) {
			_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
		}
		else {
			_dy = 0.0f;
		}
	}
	else if (ball.pegaVelocidadex() < 0) {
		if (ball.pegaVelocidadey() > 0) {
			ondevai = ((ball.pegaLocalBolax()) - _spawn.x - globals::WIDTH_PLAYER) * tan(-ball.pegaAngulo()) + ball.pegaLocalBolay() + globals::HEIGHT_BALL / 2;
			if (ondevai > 15 && ondevai < globals::HEIGHT - 15) {
				if (_mutante + _x > ondevai && _mutante + globals::HEIGHT_BALL / 2 >= 16) {
					if (ball.pegaVelocidadey() > Player_cte::VELOCIDADE_IMPOSSIVEL) {
						_dy = -ball.pegaVelocidadey();
					}
					else {
						_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
					}
				}
				else if (_mutante + _x < ondevai && _mutante + globals::HEIGHT_PLAYER + globals::HEIGHT_BALL / 2 <= globals::HEIGHT - 16) {
					if (ball.pegaVelocidadey() > Player_cte::VELOCIDADE_IMPOSSIVEL) {
						_dy = ball.pegaVelocidadey();
					}
					else {
						_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;
					}
				}
			}
			else if (_mutante + _x > ondevai && _mutante + globals::HEIGHT_BALL / 2 >= 16) {
				_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
			}
			else if (_mutante + _x < ondevai && _mutante + globals::HEIGHT_PLAYER + globals::HEIGHT_BALL / 2 <= globals::HEIGHT - 16) {
				_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;
			}
			else {
				_dy = 0.0f;
			}
		}
		if (ball.pegaVelocidadey() < 0) {
			ondevai = (ball.pegaLocalBolay() + globals::HEIGHT_BALL / 2) - (ball.pegaLocalBolax() - _spawn.x - globals::WIDTH_PLAYER) * tan(ball.pegaAngulo());
			if (ondevai > 15 && ondevai < globals::HEIGHT - 15) {
				if (_mutante + _x > ondevai && _mutante + globals::HEIGHT_BALL / 2 >= 16) {
					if (-ball.pegaVelocidadey() > Player_cte::VELOCIDADE_IMPOSSIVEL) {
						_dy = ball.pegaVelocidadey();
					}
					else {
						_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
					}
				}
				else if (_mutante + _x < ondevai && _mutante + globals::HEIGHT_PLAYER + globals::HEIGHT_BALL / 2 <= globals::HEIGHT - 16) {
					if (-ball.pegaVelocidadey() > Player_cte::VELOCIDADE_IMPOSSIVEL) {
						_dy = -ball.pegaVelocidadey();
					}
					else {
						_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;
					}
				}
			}
			else if (_mutante + _x > ondevai && _mutante + globals::HEIGHT_BALL / 2 >= 16) {
				_dy = -Player_cte::VELOCIDADE_IMPOSSIVEL;
			}
			else if (_mutante + _x < ondevai && _mutante + globals::HEIGHT_PLAYER + globals::HEIGHT_BALL / 2 <= globals::HEIGHT - 16) {
				_dy = Player_cte::VELOCIDADE_IMPOSSIVEL;
			}
			else {
				_dy = 0.0f;
			}
		}
		else if (ball.pegaVelocidadey() == 0) {
			_dy = 0.0f;
		}
	}
	if (_mutante <= 17) {
		_dy = Player_cte::VELOCIDADE_HARD;
	}
	else if (_mutante >= globals::HEIGHT - 17) {
		_dy = -Player_cte::VELOCIDADE_HARD;
	}
}

void Players::terminaMovimento() {
	_dy = 0.0f;
}

void Players::update(float tempo) {
	_y = _dy * tempo;
}

void Players::placar(int qtd) {
	_qtd = qtd;
}

void Players::reiniciar() {
	_mutante = globals::HEIGHT / 2 - globals::HEIGHT_PLAYER / 2;
	_qualVitoria = 999;
	_dy = 0.0f;
}

void Players::vitoria(bool acabou) {
	if (_player == 1 && acabou == false){
		_qualVitoria = 0;
		_dy = 0.0f;
	}
	else if(_player == 2 && acabou == false) {
		_qualVitoria = 102;
		_dy = 0.0f;
	}
	else if(acabou == true){
		_qualVitoria = 999;
	}
}

void Players::desenha(Graficos& graficos) {
	_mutante = _mutante + _y;
	if (_mutante < 15) {
		_mutante = 15;
		_y = 0;
	}
	else if (_mutante + globals::HEIGHT_PLAYER > globals::HEIGHT - 15) {
		_mutante = globals::HEIGHT - (15 + globals::HEIGHT_PLAYER);
		_y = 0;
	}
	SDL_Rect destination = { _spawn.x, _mutante, _spawn.w, _spawn.h };
	float x = destination.y;
	graficos.desenha(_textura, NULL, &destination);
	SDL_Rect numPlacar = { _qtd * 16, 0, 16, 20 }; 
	if (_player == 1) {
		SDL_Rect ondPlacar = { globals::WIDTH / 2 - 100 - numPlacar.w * 4, 30, numPlacar.w * 4, numPlacar.h * 4 };
		graficos.desenha(_placar, &numPlacar, &ondPlacar);
	}
	else {
		SDL_Rect ondPlacar = { globals::WIDTH / 2 + 100, 30, numPlacar.w * 4, numPlacar.h * 4 };
		graficos.desenha(_placar, &numPlacar, &ondPlacar);
	}
	SDL_Rect qualVitoria = { _qualVitoria, 0, 104, 27 };
	SDL_Rect ondeVitoria = { globals::WIDTH / 2 - qualVitoria.w * 2, globals::HEIGHT / 2 - qualVitoria.h * 2, qualVitoria.w * 4, qualVitoria.h * 4 };
	graficos.desenha(_vitoria, &qualVitoria, &ondeVitoria);
}


float Players::pegaAtualLocaly() {
	return _mutante;
}