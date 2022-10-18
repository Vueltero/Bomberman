#pragma once
#include <SFML/Graphics.hpp>
#include "BloqueFijo.h"
#include "BloquesDestruibles.h"
using namespace sf;
class Mapa 
{
public:
	Mapa();
	void generarMapa();
	//void draw(RenderTarget& target, RenderStates states) const override;
	void dibujarFijos(RenderWindow *v);
	void dibujarDestruibles(RenderWindow* v);
	bool comprobarColisionAmbos(Colisionable& c);
	void comprobarColisionDestruir(Colisionable& c);
	
private:
	int _mat[13][15];
	BloqueFijo * _bf[76];
	BloqueDestruibles * _bd[100];
	int _contRandom;
};

