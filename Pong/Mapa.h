#ifndef MAPA_H
#define MAPA_H

#include "Graficos.h"

#include <string>

class Graficos;
struct SDL_Texture;
struct Desenhos;

class Mapa {
public:
	Mapa();
	Mapa(std::string nomeMapa, Graficos& graficos);
	~Mapa();
	void desenha(Graficos& graficos);
	void carregaMapa(std::string nomeMapa, Graficos& graficos);
	void confereBatida();

protected:
	SDL_Texture* _textura;
	std::string _nomeMapa;
};



#endif // !MAPA_H
