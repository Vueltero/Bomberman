#pragma once
#include "Inamovibles.h"

using namespace sf;
class BloqueDestruibles : public Inamovibles
{
public:
	BloqueDestruibles();
	BloqueDestruibles(int a, int b);

	/*bool getEstado() { return _estado; }
	void setEstado(bool estado) { _estado = estado; };
	Sprite getSprite() { return _sprite; }
	Vector2f getSprite().getPosition() { return _sprite.getPosition(); }
	FloatRect getBounds() const override;
	void draw(RenderTarget& target, RenderStates states) const override;*/

private:
	/*Texture _txt;
	Sprite _sprite;
	bool _estado;*/

};

