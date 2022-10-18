#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
#include <string.h>
using namespace sf;
class Enemigo : public Colisionable, public Drawable
{
public:
	void cmd(Event event);
	void choqueBloque();
	void caminar();
	void animacionCaminar(int direccion);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	FloatRect getBounds() const;
	Sprite getSprite();
	void morir();
private:
	Vector2f _velocidad;
	Texture _txt;
	Sprite _sprite;
};

