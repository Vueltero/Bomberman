#pragma once
#include "Colisionable.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
class Fuego : public Drawable, public Colisionable
{
private:
	Texture _txt;
	Sprite _sprite;
	bool _estado;
	int _timer;
	SoundBuffer _bufFuego;
	Sound _sonFuego;
public:
	Fuego();
	void setSpritePosition(Vector2f posicion);
	void draw(RenderTarget& target, RenderStates states) const override;
	FloatRect getBounds() const override;
	void crearLlama();
	void rotarVertical();

	void setEstado(bool estado) { _estado = estado; }
	bool getEstado() { return _estado; }
};

