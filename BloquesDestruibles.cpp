#include "BloquesDestruibles.h"

BloqueDestruibles::BloqueDestruibles() {

}

BloqueDestruibles::BloqueDestruibles(int a, int b)
{
	_txt.loadFromFile("bloqueDestruible.png");
	_sprite.setTexture(_txt);
	//_sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
	_sprite.setPosition(a*45, b*45);
	_estado == true;
}