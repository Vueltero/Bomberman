#include "Fuego.h"

Fuego::Fuego()
{
    _txt[0].loadFromFile("fuego.png");
    _txt[1].loadFromFile("fuegoh.png");
    _txt[2].loadFromFile("fuegov.png");
    _sprite.setTexture(_txt[0]);
    _sprite.setPosition(800,600);
    _sprite.setOrigin(_sprite.getGlobalBounds().width / 2, _sprite.getGlobalBounds().height / 2);
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
