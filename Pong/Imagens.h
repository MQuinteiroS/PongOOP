#ifndef IMAGENS_H
#define IMAGENS_H

#include "Graficos.h"

#include <SDL.h>

struct SDL_Texture;
class Graficos;

class Imagens {
public:
	Imagens();
	Imagens(SDL_Texture* imagen);
	void update(int elalsedTime);
	void desenha(Graficos& graficos);

protected:
	SDL_Texture* _textura;
};

#endif // !IMAGENS_H
