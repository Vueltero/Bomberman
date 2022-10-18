#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"

using namespace sf;
class BloqueDestruibles : public Drawable, public Colisionable
{
public:
	BloqueDestruibles();
	BloqueDestruibles(int a, int b);
	void setTexture();
	void setPosicion(int a, int b);

	bool getEstado();
	void setEstado(bool estado) { _estado = estado; };
	Sprite getSprite();
	FloatRect getBounds() const override;
	void draw(RenderTarget& target, RenderStates states) const override;

private:
	Texture _txt;
	Sprite _sprite;
	bool _estado;

};

