#include "Ball.h"
#include "Global.h"

#include <sstream>
#include <math.h>
#include <random>

namespace Ball_cte {
	float velocidade = 0.6f;
}

Ball::Ball() {

}
Ball::Ball(std::string ball, Graficos& graficos) :
	_ball(ball),
	_dx(0.0f),
	_dy(0.0f),
	_mutantex(globals::WIDTH / 2),
	_mutantey(globals::HEIGHT / 2){
	carregarBall(ball, graficos);
}


void Ball::carregarBall(std::string ball, Graficos& graficos) {
	std::stringstream ss;
	ss << "Images/" << ball << ".png";
	SDL_Texture* textura = SDL_CreateTextureFromSurface(graficos.pegaRenderer(), graficos.carregarImagem(ss.str()));
	_textura = textura;
}

void Ball::direcaoBola(float Angulo, int player, int parede) {
	_angulo = Angulo;
	if (player == 1 && parede == 0) {
		_dx = Ball_cte::velocidade;
		_dy = -tan(Angulo) * _dx;
	}
	else if (player == 2 && parede == 0) {
		_dx = -Ball_cte::velocidade;
		_dy = tan(Angulo) * _dx;
	}
	else if (parede != 0) {
		_dy = -_dy;
	}
}


void Ball::reiniciaJogo(int player, int delay) {
	_dx = 0;
	_dy = 0;
	if (delay == 1000) {
		float Angulo, PI = 3.14159265;
		std::random_device rd;
		std::mt19937 generator(rd());
		std::uniform_real_distribution<> distribution(0.0, 0.523598775);
		std::uniform_int_distribution<int> distribution2(220, 420);
		Angulo = distribution(generator);
		if (player == 1) {
			_dx = -0.3f;
			_dy = tan(Angulo) * _dx;
		}
		else if (player == 2) {
			_dx = 0.3f;
			_dy = -tan(Angulo) * _dx;
		}
		_angulo = Angulo;
		_mutantex = globals::WIDTH / 2;
		_mutantey = distribution2(generator);
	}
}

void Ball::comecaDoZero() {
	_mutantex = globals::WIDTH / 2;
	_mutantey = globals::HEIGHT / 2;
	_dx = 0.2f;
	_dy = 0.0f;
}

void Ball::reiniciaDoZero() {
	_mutantex = globals::WIDTH / 2;
	_mutantey = globals::HEIGHT / 2;
	_dx = 0.0f;
	_dy = 0.0f;
}

void Ball::update(float tempo) {
	_x = _dx * tempo;
	_y = _dy * tempo;
}

void Ball::desenha(Graficos& graficos) {
	if (_mutantey <= 15){
		_mutantey = 16;
		_y = 0;
	}
	else if (_mutantey + globals::HEIGHT_BALL >= globals::HEIGHT - 15) {
		_mutantey = globals::HEIGHT - globals::HEIGHT_BALL - 16;
		_y = 0;
	}
	_mutantex = _mutantex + _x;
	_mutantey = _mutantey + _y;
	SDL_Rect destino = { _mutantex, _mutantey, globals::WIDTH_BALL, globals::HEIGHT_BALL };
	graficos.desenha(_textura, NULL, &destino);
}


float Ball::pegaLocalBolax() {
	return _mutantex;
}

float Ball::pegaLocalBolay() {
	return _mutantey;
}

float Ball::pegaVelocidadex() {
	return _dx;
}


float Ball::pegaVelocidadey() {
	return _dy;
}

float Ball::pegaAngulo() {
	return _angulo;
}