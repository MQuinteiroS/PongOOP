#include "Menu.h"
#include "Global.h"

#include <sstream>
#include <SDL.h>

Menu::Menu() {

}

Menu::Menu(std::string menu, Graficos& graficos):
	_menu(menu),
	_qualMenu(0),
	_ondeMenux(globals::WIDTH / 2 - globals::WIDTH_MENU / 2),
	_ondeMenuy(globals::HEIGHT / 2 - globals::HEIGHT_MENU / 2),
	_qualMenuOriginal(0){
		carregarMenu(_menu, graficos);
	}

void Menu::carregarMenu(std::string menu, Graficos& graficos) {
	std::stringstream ss;
	ss << "Images/" << menu << ".png";
	SDL_Texture* textura = SDL_CreateTextureFromSurface(graficos.pegaRenderer(), graficos.carregarImagem(ss.str()));
	_textura = textura;
}

int Menu::menuInteraction(int x, int y, int qualMenuVoltar) {
	_qualMenuOriginal = qualMenuVoltar;
	if (x >= _ondeMenux + 12 * 4 && x <= _ondeMenux + globals::WIDTH_MENU - 12 * 4 && y >= _ondeMenuy + 17 * 4 && y <= _ondeMenuy + globals::HEIGHT_MENU - 43 * 4 && _qualMenuOriginal == 0) {
		_qualMenu = 65;
		return 1;
	}
	else if (x >= _ondeMenux + 12 * 4 && x <= _ondeMenux + globals::WIDTH_MENU - 12 * 4 && y >= _ondeMenuy + 30 * 4 && y <= _ondeMenuy + globals::HEIGHT_MENU - 30 * 4 && _qualMenuOriginal == 0) {
		_qualMenu = 65 * 2;
		return 2;
	}
	else if (x >= _ondeMenux + 12 * 4 && x <= _ondeMenux + globals::WIDTH_MENU - 12 * 4 && y >= _ondeMenuy + 43 * 4 && y <= _ondeMenuy + globals::HEIGHT_MENU - 17 * 4 && _qualMenuOriginal == 0) {
		_qualMenu = 65 * 3;
		return 3;
	}
	else if (x >= _ondeMenux + 12 * 4 && x <= _ondeMenux + globals::WIDTH_MENU - 12 * 4 && y >= _ondeMenuy + 19 * 4 && y <= _ondeMenuy + globals::HEIGHT_MENU - 41 * 4 && _qualMenuOriginal == 1 
		|| x >= _ondeMenux + 12 * 4 && x <= _ondeMenux + globals::WIDTH_MENU - 12 * 4 && y >= _ondeMenuy + 19 * 4 && y <= _ondeMenuy + globals::HEIGHT_MENU - 41 * 4 && _qualMenuOriginal == 4) {
		if (_qualMenuOriginal == 1) {
			_qualMenu = 65 * 5;
			return 4;
		}
		else if (_qualMenuOriginal == 4) {
			_qualMenu = 65 * 5;
			return 5;
		}
	}
	else if (x >= _ondeMenux + 12 * 4 && x <= _ondeMenux + globals::WIDTH_MENU - 12 * 4 && y >= _ondeMenuy + 30 * 4 && y <= _ondeMenuy + globals::HEIGHT_MENU - 30 * 4 && _qualMenuOriginal == 1 
		|| x >= _ondeMenux + 12 * 4 && x <= _ondeMenux + globals::WIDTH_MENU - 12 * 4 && y >= _ondeMenuy + 30 * 4 && y <= _ondeMenuy + globals::HEIGHT_MENU - 30 * 4 && _qualMenuOriginal == 4) {
		_qualMenu = 65 * 6;
		return 6;
	}
	else if (x >= _ondeMenux + 12 * 4 && x <= _ondeMenux + globals::WIDTH_MENU - 12 * 4 && y >= _ondeMenuy + 41 * 4 && y <= _ondeMenuy + globals::HEIGHT_MENU - 19 * 4 && _qualMenuOriginal == 1 
		|| x >= _ondeMenux + 12 * 4 && x <= _ondeMenux + globals::WIDTH_MENU - 12 * 4 && y >= _ondeMenuy + 41 * 4 && y <= _ondeMenuy + globals::HEIGHT_MENU - 19 * 4 && _qualMenuOriginal == 4) {
		_qualMenu = 65 * 7;
		return 7;
	}
	else if (x >= _ondeMenux + 12 * 4 && x <= _ondeMenux + globals::WIDTH_MENU - 12 * 4 && y >= _ondeMenuy + 52 * 4 && y <= _ondeMenuy + globals::HEIGHT_MENU - 8 * 4 && _qualMenuOriginal == 1 
		|| x >= _ondeMenux + 12 * 4 && x <= _ondeMenux + globals::WIDTH_MENU - 12 * 4 && y >= _ondeMenuy + 52 * 4 && y <= _ondeMenuy + globals::HEIGHT_MENU - 8 * 4 && _qualMenuOriginal == 4) {
		_qualMenu = 65 * 8;
		return 8;
	}
	else if(_qualMenuOriginal == 0){
		_qualMenu = 0;
		return 0;
	}
	else if (_qualMenuOriginal == 1 || _qualMenuOriginal == 4) {
		_qualMenu = 65 * 4;
		return 1;
	}
	else if (_qualMenuOriginal == 10 && x >= _ondeMenux + 58 * 4 && x <= _ondeMenux + globals::WIDTH_MENU - 2 * 4 && y >= _ondeMenuy + 59 * 4 && y <= _ondeMenuy + globals::HEIGHT_MENU - 2 * 4) {
		_qualMenu = 65 * 10;
		return 69;
	}
	else if (_qualMenuOriginal == 3 || _qualMenuOriginal == 10) {
		_qualMenu = 65 * 9;
		return 10;
	}
	else if (_qualMenuOriginal == 2) {
		return 2;
	}
	else if (_qualMenuOriginal == 5) {
		return 5;
	}
	else if (_qualMenuOriginal == 6) {
		return 6;
	}
	else if (_qualMenuOriginal == 7) {
		return 7;
	}
	else if (_qualMenuOriginal == 8) {
		return 8;
	}
	else if (_qualMenuOriginal == 69) {
		return 69;
	}
	else if (_qualMenuOriginal == 20) {
		_qualMenu = 65 * 11;
		return 30;
	}
}

void Menu::desenha(Graficos& graficos) {
	SDL_Rect qualMenu = { _qualMenu, 0, 65, 65 };
	SDL_Rect ondeMenu = { _ondeMenux, _ondeMenuy, globals::WIDTH_MENU, globals::HEIGHT_MENU };
	graficos.desenha(_textura, &qualMenu, &ondeMenu);
}