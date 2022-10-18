#include "Bomba.h"

Bomba::Bomba()
{
	_txt.loadFromFile("bomb.png");
	_sprite.setTexture(_txt);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
}

Sprite Bomba::getSprite()
{
	return _sprite;
}

/*bool Bomba::getEstado()
{
	return _estado;
}*/

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
