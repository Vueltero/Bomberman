#pragma once
#include "Movibles.h"
class Player : public Movibles
{
public:
	Player();
	void cmd(Event event,bool acelerar);
	void animacionCaminar(int direccion);
	void morir(int&);

	bool getTocandoBomba() { return _tocandoBomba; }
	void setTocandoBomba(bool tocando) { _tocandoBomba = tocando; }

private:
	bool _tocandoBomba = false;
};