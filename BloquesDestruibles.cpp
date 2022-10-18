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

FloatRect BloqueDestruibles::getBounds() const
{
	return _sprite.getGlobalBounds();
}

void BloqueDestruibles::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(_sprite, states);
}
bool BloqueDestruibles::getEstado() {
	return _estado;
}
