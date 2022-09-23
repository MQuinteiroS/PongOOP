#ifndef MENU_H
#define MENU_H

#include "Graficos.h"

#include <SDL.h>
#include <string>

class Graficos;

class Menu {
public:
	Menu();
	Menu(std::string menu, Graficos& graficos);
	int menuInteraction(int x, int y, int qualMenuVoltar);
	void carregarMenu(std::string menu, Graficos& graficos);
	void desenha(Graficos& graficos);

protected:
	SDL_Texture* _textura;
	std::string _menu;
	int _qualMenu, _ondeMenux, _ondeMenuy, _qualMenuOriginal;
};


#endif // !MENU_H