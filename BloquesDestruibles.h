#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"

using namespace sf;
class BloqueDestruibles : public Drawable, public Colisionable
{
public:
	BloqueDestruibles();
	BloqueDestruibles(int a, int b);


	bool getEstado();
	void setEstado(bool estado) { _estado = estado; };
	Sprite getSprite() { return _sprite; }
	Vector2f getSpritePosition() { return _sprite.getPosition(); }
	FloatRect getBounds() const override;
	void draw(RenderTarget& target, RenderStates states) const override;

private:
	Texture _txt;
	Sprite _sprite;
	bool _estado;

};

