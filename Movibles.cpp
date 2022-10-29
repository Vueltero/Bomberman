#include "Movibles.h"

void Movibles::choqueBloque()
{
	_sprite.move(-_velocidad);
}

void Movibles::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

FloatRect Movibles::getBounds() const
{

	return _sprite.getGlobalBounds();
}

Sprite Movibles::getSprite()
{
	return _sprite;
}
void Movibles::animacionCaminar(int direccion) {

	string cadena = "globo";
	if (__timerCamina > 0) {
		switch (direccion)
		{
		case 1:
			cadena += to_string(_path) + ".png";
			_txt.loadFromFile(cadena);
			_sprite.setTexture(_txt);
			break;
		case 2:
			cadena += to_string(_path) + ".png";
			_txt.loadFromFile(cadena);
			_sprite.setTexture(_txt);
			break;
		case 3:
			cadena += to_string(_path) + ".png";
			_txt.loadFromFile(cadena);
			_sprite.setTexture(_txt);
			break;
		}
	}
	else {
		__timerCamina = 30;
		if (_path < 2) {
			_path++;
		}
		else {
			_path = 1;
		}
	}
	__timerCamina--;
}