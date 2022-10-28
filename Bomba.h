#pragma once
#include <SFML/Graphics.hpp>
#include "colisionable.h"
using namespace sf;
class Bomba : public Drawable , public Colisionable
{
public:
	Bomba();
	Sprite getSprite();
	//bool getEstado();
	void crearExplotar(bool &actLLama);
	void crearBomba(Vector2f posicion);
	void setSpritePosition(Vector2f posicion);
	FloatRect getBounds() const override;
	void draw(RenderTarget& target, RenderStates states) const override;

	bool getEstado() { return _estado; }
	void setEstado(bool estado) { _estado = estado; }

private:
	Texture _txt;
	Sprite _sprite;
	bool _estado = false;
	int _timer;
};

