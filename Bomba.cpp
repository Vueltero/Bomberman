#include "Bomba.h"

Bomba::Bomba()
{
	_txt.loadFromFile("bomb.png");
	_sprite.setTexture(_txt);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_timer = 60 * 5;
	_timerFuego = 60 * 2;
	_estados = desactivada;
}

void Bomba::crearExplotar()
{
	/*_estado = true;
	_timer--;
	actLlama = false;

	if (_timer == 0) {

		_estado = false;
		actLlama = true;
		_timer = 60 * 5;

	}*/
	_estados = activada;
	_timer--;
	if (_timer == 0) {
		_estados = fuego;
		_timer = 60 * 5;
	}
	if (_estados == fuego) {
		_timerFuego--;
		lanzarFuego();
	}
	if (_timerFuego == 0) {
		_estados = desactivada;
	}
	
}
void Bomba::lanzarFuego() {
	if (_timerFuego == 119) {
		_sonido.play();
	}
	if (_timerFuego > 90) {
		_txt.loadFromFile("fuegos1.png");
		_sprite.setTexture(_txt);
		_timerFuego--;
	}
	else if (_timerFuego > 60) {
		_txt.loadFromFile("fuegos2.png");
		_sprite.setTexture(_txt);
		_timerFuego--;
	}
	else if (_timerFuego > 30) {
		_txt.loadFromFile("fuegos3.png");
		_sprite.setTexture(_txt);
		_timerFuego--;
	}
	else if (_timerFuego > 0) {
		_txt.loadFromFile("fuegos4.png");
		_sprite.setTexture(_txt);
		_timerFuego--;
	}
	else if (_timerFuego == 0) {
		_estados = desactivada;
		_txt.loadFromFile("vacio.png");
		_sprite.setTexture(_txt);
		_sprite.setOrigin(0, 0);
		_timerFuego = 60 * 2;
	}
}

void Bomba::crearBomba(Vector2f posicion)
{
	_estado = true;
	_sprite.setPosition(posicion);
}

void Bomba::setSpritePosition(Vector2f posicion)
{
	_sprite.setPosition(posicion);
}
