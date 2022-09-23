#ifndef PLAYERS_H
#define PLAYERS_H

#include "Graficos.h"
#include "Ball.h"


class Graficos;
class Ball;
struct SDL_Texture;
struct SDL_Rect;

class Players {
public:
	Players();
	Players(std::string qualPlayer, Graficos& graficos, SDL_Rect onde, int player);
	void update(float tempo);
	void desenha(Graficos& graficos);
	void carregarPlayer(std::string qualPlayer, Graficos& graficos);
	void comecaMovimentoParaCima();
	void comecaMovimentoParaBaixo();
	void terminaMovimento();
	void placar(int qtd);
	float pegaAtualLocaly();
	void reiniciar();
	void vitoria(bool acabou);
	void botFacil(Ball& ball);
	void botNormal(Ball& ball);
	void botDificil(Ball& ball);
	void botImpossivel(Ball& ball);
	void botImpossivelP1(Ball& ball);


protected:
	SDL_Texture* _textura;
	SDL_Texture* _vitoria;
	SDL_Texture* _placar;
	std::string _qualPlayer;
	SDL_Rect _spawn;
	float _mutante;
	int _qtd, _player, _qualVitoria;
	
private:
	float _dy, _y;
	int _x;

};


#endif // !PLAYERS_H
