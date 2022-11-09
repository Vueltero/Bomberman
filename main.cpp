//#include <SFML/Graphics.hpp>
//#include "BloqueFijo.h"
//#include "Bomba.h"
//#include <iostream>
//#include "Player.h"
//#include "Fuego.h"

#include "Juego.h"
#include "Nivel2.h"
#include "Nivel3.h"

using namespace sf;

int main() {
	RenderWindow* _ventana1 = new RenderWindow(VideoMode(800, 600), "Bomberman"); //deberia ser un atributo de menu y menu contener todo.
	Juego* _juego1 = new Juego(_ventana1);
	_juego1->mostarStage(_ventana1, 1);
	_juego1->gamePlay(_ventana1);//transcurre el juego mientras no gane o pierda.
	if (_juego1->getVidas() == 0) {
		//si muere en primer pantalla no pasa de nivel. y asi con los siguientes niveles.
		_juego1->pantallaGameOver(_ventana1);
	}
	else {
		Nivel2* _nivel2 = new Nivel2(_ventana1, _juego1->getPuntaje(), _juego1->getVidas());
		_nivel2->mostarStage(_ventana1, 2);
		_nivel2->gamePlay(_ventana1);
		if (_nivel2->getVidas() == 0) {
			_nivel2->pantallaGameOver(_ventana1);
		}
		else {
			Nivel3* _nivel3 = new Nivel3(_ventana1, _nivel2->getPuntaje(), _nivel2->getVidas());
			_nivel3->mostarStage(_ventana1, 3);
			_nivel3->gamePlay(_ventana1);
			if (_nivel3->getVidas() == 0) {
				_nivel3->pantallaGameOver(_ventana1);
			}
			else {
				_nivel3->pantallaVictoria(_ventana1);
				int puntosAcumulados = _nivel3->getPuntaje();
				// se toma en cuenta los puntos al final del ultimo nivel para el archivo y estadisticas.
				// de acá se toma _ventana1 para mostrar resultados, siempre nos manejamos con esa ventana.
				// y Solo puntua cuando gana las 3 pantalalas
			}
		}
	}
	return 0;
}