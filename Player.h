#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Colisionable.h"
#include <string.h>
using namespace std;
using namespace sf;

class Player : public Colisionable, public Drawable
{
public:
	Player();
	void cmd(Event event,bool acelerar);
	void choqueBloque();
	//void caminar();
	void animacionCaminar(int direccion);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	FloatRect getBounds() const override;
	Sprite getSprite();
	void morir(int&);

	bool getMuriendo() { return _muriendo; }
	bool getMuerto() { return _muerto; }
	void setMuriendo(bool muere) { _muriendo = muere; }

private:
	Vector2f _velocidad;
	Texture _txt;
	Sprite _sprite;
	int __timerCamina;
	int _path = 1;
	int __timerMuerte=60*2;
	bool _muriendo;
	bool _muerto;
	SoundBuffer _bufCamina;
	Sound _caminar;

	SoundBuffer _bufPer;
	Sound _sonPerderVida;
};