#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "BloquesDestruibles.h"
#include"Bomba.h"
#include "Fuego.h"
#include "Mapa.h"
#include "Enemigo.h"
#include "Estadistica.h"
#include <list>
#include <algorithm>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace sf;

class Juego
{
public:
	Juego();
	void gamePlay();
	void dibujar();
	void generarEstadistica();
	void verEstadisticaEnConsola();
	void victoria();
	
	bool getVictoria() { return _victoria; }
	int getPuntaje() { return _puntaje; }

private:
	RenderWindow* _ventana1;
	Sprite _fondo;
	Texture _txtFondo;
	//Player  _player1;
	list <Player> _players;
	list <Enemigo> _enemigos;
	BloqueDestruibles* _bloquesito = new BloqueDestruibles(13, 11);
	int _vidas = 3;
	//Bomba* _bomba;
	Bomba* _bombas = new Bomba[2];
	bool _dosBombas;
	int _timer;
	Fuego* _fuegos = new Fuego[2];
	int _timer2;
	Mapa* _mapa1;
	int randomNumero;
	int _contadorCrear;
	int _tiempoBombas;
	bool _acelerar;
	int _timerVelocidad;
	int _timerBoostBomba;
	int _contadorEnemigosEliminados;
	int _puntaje;
	int _tiempoLimite;
	char _nombre[4];
	bool _victoria = false;
	SoundBuffer _bufBomba;
	Sound _sonBomba;

	SoundBuffer _bufItem;
	Sound _sonItem;

};

