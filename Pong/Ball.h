#ifndef BALL_H
#define BALL_H

#include "Graficos.h"

class Graficos;
struct SDL_Texture;
struct SDL_Rect;

class Ball {
public:
	Ball();
	Ball(std::string ball, Graficos& graficos);
	void update(float tempo);
	void desenha(Graficos& graficos);
	void carregarBall(std::string ball, Graficos& graficos);
	float pegaLocalBolax();
	float pegaLocalBolay(); 
	void direcaoBola(float Angulo, int player, int parede);
	void reiniciaJogo(int player, int delay);
	void comecaDoZero();
	void reiniciaDoZero();
	float pegaVelocidadex();
	float pegaVelocidadey();
	float pegaAngulo();

protected:
	SDL_Texture* _textura;
	std::string _ball;
	SDL_Rect _onde;
	float _mutantey;
	float _mutantex;
	float _angulo;

private:
	float _dy, _dx, _y, _x;

};


#endif // !BALL_H
