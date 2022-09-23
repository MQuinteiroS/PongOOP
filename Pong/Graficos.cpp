#include "Graficos.h"
#include "Global.h"
#include "Mapa.h"

#include <SDL_image.h>


Graficos::Graficos(){
	SDL_CreateWindowAndRenderer(globals::WIDTH, globals::HEIGHT, 0, &_window, &_renderer);
	SDL_SetWindowTitle(_window, "Pong");
}

Graficos::~Graficos() {
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

void Graficos::desenha(SDL_Texture* qual, SDL_Rect* ondeNaImagem, SDL_Rect* ondeNaTela) {
	SDL_RenderCopy(_renderer, qual, ondeNaImagem, ondeNaTela);
}

void Graficos::carrega() {
	SDL_RenderPresent(_renderer);
}

void Graficos::limpa() {
	SDL_RenderClear(_renderer);
}

SDL_Renderer* Graficos::pegaRenderer() const {
	return _renderer;
}

SDL_Surface* Graficos::carregarImagem(const std::string &onde) {
	if (_textura.count(onde) == 0) {
		_textura[onde] = IMG_Load(onde.c_str());
	}
	return _textura[onde];
}
