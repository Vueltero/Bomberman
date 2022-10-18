#pragma once
#include "Colisionable.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class Fuego : public Drawable, public Colisionable
{
private:
	Texture _txt[3];
	Sprite _sprite;
public:
	Fuego();
	void setSpritePosition(Vector2f posicion);
	void draw(RenderTarget& target, RenderStates states) const override;
	FloatRect getBounds() const override;
	void setTexturaNueva(int nTextura);
};

