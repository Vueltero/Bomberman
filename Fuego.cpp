#include "Fuego.h"

Fuego::Fuego()
{
	_txt.loadFromFile("fuegos1.png");
	_sprite.setTexture(_txt);
    //_sprite.setOrigin(20,20);
	_estado = false;
	
	_bufSonido.loadFromFile("fuego.wav");
	_sonido.setBuffer(_bufSonido);
	_timer = 2 * 60;
}

void Fuego::setSpritePosition(Vector2f posicion)
{
	_sprite.setPosition(posicion);
}

void Fuego::crearLlama()
{
	if (_timer == 119) {
		_sonido.play();
	}
	if (_timer > 90) {
		_txt.loadFromFile("fuegos1.png");
		_sprite.setTexture(_txt);
		_timer--;
	}
	else if (_timer > 60) {
		_txt.loadFromFile("fuegos2.png");
		_sprite.setTexture(_txt);
		_timer--;
	}
	else if (_timer > 30) {
		_txt.loadFromFile("fuegos3.png");
		_sprite.setTexture(_txt);
		_timer--;
	}
	else if (_timer > 0) {
		_txt.loadFromFile("fuegos4.png");
		_sprite.setTexture(_txt);
		_timer--;
	}
	else if (_timer == 0) {
		_estado = false;
		_txt.loadFromFile("vacio.png");
		_sprite.setTexture(_txt);
		_timer = 60 * 2;
	}
}

void Fuego::rotarVertical()
{
	_sprite.setRotation(90);
	//_sprite.setOrigin(20,20);
}
