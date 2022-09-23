#include "Mapa.h"
#include "Global.h"
#include "Graficos.h"
#include "Ball.h"

#include <SDL_image.h>
#include <sstream>

Mapa::Mapa() {

}

Mapa::Mapa(std::string nomeMapa, Graficos& graficos) :
	_nomeMapa(nomeMapa){
	carregaMapa(nomeMapa, graficos);
}

Mapa::~Mapa() {

}

void Mapa::confereBatida() {
}

void Mapa::carregaMapa(std::string nomeMapa, Graficos& graficos) {
	std::stringstream ss;
	ss << "Images/" << nomeMapa << ".png";
	SDL_Texture* textura = SDL_CreateTextureFromSurface(graficos.pegaRenderer(), graficos.carregarImagem(ss.str()));
	_textura = textura;
}

void Mapa::desenha(Graficos& graficos) {
	graficos.desenha(_textura, NULL, NULL);
}