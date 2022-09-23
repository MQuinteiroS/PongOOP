#ifndef GRAFICOS_H
#define GRAFICOS_H

#include <SDL.h>
#include <string>
#include <map>

struct SDL_Window;
struct SDL_Renderer;

class Graficos {
public:
	Graficos();
	~Graficos();

	void desenha(SDL_Texture* qual, SDL_Rect* ondeNaImagem, SDL_Rect* ondeNaTela);
	void carrega();
	void limpa();

	SDL_Renderer* pegaRenderer() const;
	SDL_Surface* carregarImagem(const std::string& onde);

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::map<std::string, SDL_Surface*> _textura;
};

#endif // !GRAFICOS_H
