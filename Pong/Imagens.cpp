#include "Imagens.h"

Imagens:: Imagens() {

}

Imagens::Imagens(SDL_Texture* textura):
	_textura(textura) {
	}

void Imagens::desenha(Graficos& graficos) {
	graficos.desenha(_textura, NULL, NULL);
}