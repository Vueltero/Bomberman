#pragma once
#include "Movibles.h"
class Enemigo :public Movibles
{
public:
	Enemigo();
	void cmd();
	void morir();

private:
	int random;
	int _tiempoMov = 60;

};

