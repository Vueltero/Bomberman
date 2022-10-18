#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
#include <string.h>
using namespace std;
using namespace sf;

class Player : public Colisionable, public Drawable
{
public:
	Player();
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
	int __timerCamina;
	int _path = 1;
	int __timerMuerte=60*2;

};