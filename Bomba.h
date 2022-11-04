#pragma once
#include "Inamovibles.h"
using namespace sf;
enum estado {desactivada, activada,fuego};
class Bomba : public Inamovibles
{
public:
	Bomba();
	void crearExplotar(bool &actLLama);
	void crearBomba(Vector2f posicion);
	void setSpritePosition(Vector2f posicion);
	void lanzarFuego();

	void setEstadob(estado estados) { _estados = estados; }
	estado getEstados() { return _estados; }

private:
	int _timer;
	int _timerFuego;
	estado _estados;
};

