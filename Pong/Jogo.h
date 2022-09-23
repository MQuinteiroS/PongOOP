#ifndef JOGO_H
#define JOGO_H

#include "Graficos.h"
#include "Players.h"
#include "Mapa.h"
#include "Ball.h"
#include "Menu.h"

class Graficos;

class Jogo {

public:
	Jogo();
	~Jogo();

private:
	void desenha(Graficos& graficos);
	void gameLoop();
	void update(float elapsedTime);
	Mapa _mapas;
	Players _player1;
	Players _player2;
	Ball _ball;
	Menu _menu;

};

#endif // !JOGO_H
