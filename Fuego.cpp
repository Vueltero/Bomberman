#include "Fuego.h"

Fuego::Fuego()
{
	_txt[0].loadFromFile("fuego.png");
	_txt[1].loadFromFile("fuegoh.png");
	_txt[2].loadFromFile("fuegov.png");
	_sprite.setTexture(_txt[0]);
	//_sprite.setPosition(800,600);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_estado = false;
	
	_bufFuego.loadFromFile("fuego.wav");
	_sonFuego.setBuffer(_bufFuego);
	_timer = 2 * 60;
}

void Fuego::setSpritePosition(Vector2f posicion)
{
	_sprite.setPosition(posicion);
}

void Fuego::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(_sprite, states);
}

FloatRect Fuego::getBounds() const
{
	return _sprite.getGlobalBounds();
}

void Fuego::setTexturaNueva(int nTextura)
{
	_sprite.setTexture(_txt[nTextura]);
}

void Fuego::crearLlama()
{
	if (_timer == 119) {
		_sonFuego.play();
	}
	if (_timer > 90) {
		_txt->loadFromFile("fuego1.png");
		_sprite.setTexture(*_txt);
		_timer--;
	}
	else if (_timer > 60) {
		_txt->loadFromFile("fuego2.png");
		_sprite.setTexture(*_txt);
		_timer--;
	}
	else if (_timer > 30) {
		_txt->loadFromFile("fuego3.png");
		_sprite.setTexture(*_txt);
		_timer--;
	}
	else if (_timer > 0) {
		_txt->loadFromFile("fuego4.png");
		_sprite.setTexture(*_txt);
		_timer--;
	}
	else if (_timer == 0) {
		_estado = false;
		_txt->loadFromFile("vacio.png");
		_sprite.setTexture(*_txt);
		_timer = 60 * 2;
	}
}
