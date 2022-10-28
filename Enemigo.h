#pragma once
#include <SFML/Graphics.hpp>
#include "Colisionable.h"
#include <string.h>
#include <random>
#include <iostream>
using namespace sf;
using namespace std;
class Enemigo : public Colisionable, public Drawable
{
public:
	Enemigo();
	void cmd();
	void choqueBloque();
	//void caminar();
	void animacionCaminar(int direccion);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	FloatRect getBounds() const;
	Sprite getSprite();
	void morir();
	void setEstado(bool a) { _estado = a; }
	bool getEstado() { return _estado; }
	bool getMuerte() { return _muerte; }

	//bool getTocandoBomba() { return _tocandoBomba; }
	//void setTocandoBomba(bool tocando) { _tocandoBomba = tocando; }
private:
	Vector2f _velocidad;
	Texture _txt;
	Sprite _sprite;
	int __timerCamina;
	int _path = 1;
	int __timerMuerte = 60 * 2;
	int random;
	int _tiempoMov = 60;
	bool _estado;
	bool _muerte;
	/*bool _tocandoBomba = false;*/
};

