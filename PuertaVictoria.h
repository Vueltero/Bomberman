#pragma once
#include <SFML/Graphics.hpp>
#include "colisionable.h"

using namespace sf;
class PuertaVictoria : public Drawable, public Colisionable
{
public:
	PuertaVictoria();
	//PuertaVictoria(int a, int b);
	Sprite getSprite() { return _sprite; }
	FloatRect getBounds() const override;
	void draw(RenderTarget& target, RenderStates states) const override;

	bool getEstado() { return _estado; }
	void setEstado(bool estado) { _estado = estado; }
	void setPosicionSprite(Vector2f v) { _sprite.setPosition(v); }
	void abrirPuerta();

private:
	Texture _txt;
	Sprite _sprite;
	bool _estado;
	int _timer;
};

