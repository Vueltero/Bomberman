#include "BloqueFijo.h"

BloqueFijo::BloqueFijo(int a, int b)
{
	_txt.loadFromFile("BloqueFijo.png");
	_sprite.setTexture(_txt);
	_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_sprite.setPosition(a * 45, b * 45);//(a*90 + 152.5f,b*90 + 97.7f );
	_estado = false;
}

void BloqueFijo::setTexture()
{
	_txt.loadFromFile("BloqueFijo.png");
	_sprite.setTexture(_txt);
	_estado = true;
}

void BloqueFijo::setPosicion(int a, int b)
{
	_sprite.setPosition(45 * a + 62.5f, 45.0 * b);
}

//FloatRect BloqueFijo::getBounds() const
//{
//	FloatRect nuevo;
//	nuevo.height = _sprite.getGlobalBounds().height - 5;
//	nuevo.width = _sprite.getGlobalBounds().width - 5;
//	nuevo.top = _sprite.getGlobalBounds().top;
//	nuevo.left = _sprite.getGlobalBounds().left;
//	return nuevo;
//	//return _sprite.getGlobalBounds();
//}

