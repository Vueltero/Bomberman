#include "Bomba.h"

Bomba::Bomba()
{
	_txt.loadFromFile("bomb.png");
	_sprite.setTexture(_txt);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_timer = 60 * 5;
}

Sprite Bomba::getSprite()
{
	return _sprite;
}

/*bool Bomba::getEstado()
{
	return _estado;
}*/

void Bomba::crearExplotar(bool &actLlama)
{
	_estado = true;
	_timer--;
	actLlama = false;

	if (_timer == 0) {
			_estado = false;
			actLlama = true;
			_timer = 60 * 5;
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

void Bomba::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(_sprite, states);
}
