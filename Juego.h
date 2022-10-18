#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "BloquesDestruibles.h"
#include"Bomba.h"
#include "Fuego.h"
#include "Mapa.h"


using namespace sf;

class Juego
{
public:
	Juego();
	void gamePlay();
	void dibujar();

private:
	RenderWindow* _ventana1;
	Sprite _fondo;
	Texture _txtFondo;
	Player  _player1;
	BloqueDestruibles* _bloquesito = new BloqueDestruibles(13, 11);
	int _vidas = 3;
	Bomba* _bomba;
	int _timer;
	Fuego* _fuego;
	int _timer2;
	Mapa* _mapa1;
};

