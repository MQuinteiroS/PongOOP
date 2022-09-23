#include "Input.h"

/*Classe de input
* verifica o estado do teclado
*/

void Input::beginNewFrame() { //função é chamada no inicio de cada frame paraa reiniciar os comandos que não são mais relevantes
	_pressedKeys.clear();
	_releasedKeys.clear();
}

//chamado quando algum botão é apertado
void Input::keyDownEvent(const SDL_Event& event) {
	_pressedKeys[event.key.keysym.scancode] = true;
	_heldKeys[event.key.keysym.scancode] = true;
}

//chamado quando algum botão é solto
void Input::keyUpEvent(const SDL_Event& event) {
	_releasedKeys[event.key.keysym.scancode] = true;
	_heldKeys[event.key.keysym.scancode] = false; //não é mais verdadeiro pq a tecla foi solta, visto que esta released (pode refazer o código em portugues se quiser)
}

//verifica se o botão foi apertado durante o frame atual
bool Input::wasKeyPressed(SDL_Scancode key) {
	return _pressedKeys[key];
}


//verifica se algum botão foi solto durante o frame atual
bool Input::wasKeyReleased(SDL_Scancode key) {
	return _releasedKeys[key];
}

//verifica se o botão atual esta sendo segurado
bool Input::isKeyHeld(SDL_Scancode key) {
	return _heldKeys[key];
}