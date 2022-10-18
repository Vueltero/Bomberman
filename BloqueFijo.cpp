#include "BloqueFijo.h"

BloqueFijo::BloqueFijo(int a, int b)
{
	_txt.loadFromFile("BloqueFijo.png");
	_sprite.setTexture(_txt);
	//_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_sprite.setPosition(a * 45, b * 45);//(a*90 + 152.5f,b*90 + 97.7f );
}

void BloqueFijo::setTexture()
{
	_txt.loadFromFile("BloqueFijo.png");
	_sprite.setTexture(_txt);
	_estado = true;
}

void BloqueFijo::setPosicion(int a, int b)
{
	_sprite.setPosition(45 * a + 62.5f, 45 * b);
}

bool BloqueFijo::getEstado()
{
	return _estado;
}

Sprite BloqueFijo::getBloque()
{
	return _sprite;
}

FloatRect BloqueFijo::getBounds() const
{
	return _sprite.getGlobalBounds();
}

void BloqueFijo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}
