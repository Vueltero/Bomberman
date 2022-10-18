#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"

using namespace sf;
class BloqueFijo: public Drawable, public Colisionable 
{
public:
	BloqueFijo(int a, int b);
	void setTexture();
	void setPosicion(int a, int b);

	bool getEstado();
	Sprite getBloque();
	FloatRect getBounds() const override;
	void draw(RenderTarget& target, RenderStates states) const override;

private:
	Texture _txt;
	Sprite _sprite;
	bool _estado = false;
	
};

