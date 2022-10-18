#include "Mapa.h"
#include <time.h>
#include <stdlib.h>

Mapa::Mapa()
{
	generarMapa();
}
void Mapa::generarMapa() {

	_mat[13][15] = {};
	int cont = 0;
	int random = 1;
	_contRandom = 0;
	for (int i = 0; i < 13; i++) { // 2 ES BLOQUE FIJO, 0 ES LIBRE Y 1 ROMPIBLE
		for (int j = 0; j < 15; j++) {
			if (i == 0 || j == 0 || i == 12 || j == 14) {
				_mat[i][j] = 2;
			}
			else if (i % 2 == 0 && j % 2 == 0) {
				_mat[i][j] = 2;
			}
			else if (i == 1 && j == 1 || i == 1 && j == 2 || i == 2 && j == 1) {
				_mat[i][j] = 0;
			}
			else if (cont < 100) {
				random = rand() % 2 + 0;
				_mat[i][j] = random;
				cont++;
				if (random == 1) {
					_contRandom++;
				}
			}
		}
	}
	int posD = 0, posF = 0;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 15; j++) {
			if (_mat[i][j] == 1) {
				_bd[posD] = new BloqueDestruibles(j, i);
				posD++;
			}
			else if (_mat[i][j] == 2) {
				_bf[posF] = new BloqueFijo(j, i);
				posF++;
			}
		}
	}
}

void Mapa::dibujarFijos(RenderWindow* v)
{
	for (int i = 0; i < 76; i++) {
		v->draw(*_bf[i]);
	}
}
void Mapa::dibujarDestruibles(RenderWindow* v) {
	for (int i = 0; i < _contRandom; i++) {
		if (_bd[i]->getEstado())
			v->draw(*_bd[i]);
	}
}

bool Mapa::comprobarColisionAmbos(Colisionable& c) {
	for (int i = 0; i < 76; i++) {
		if (c.isColision(*_bf[i])) {
			return true;
		}
	}
	for (int i = 0; i < _contRandom; i++) {
		if (c.isColision(*_bd[i])) {
			if (_bd[i]->getEstado()) {
				return true;
			}
		}
	}
	return false;
}

void Mapa::comprobarColisionDestruir(Colisionable& c) {
	for (int i = 0; i < _contRandom; i++) {
		if (c.isColision(*_bd[i])) {
			if (_bd[i]->getEstado()) {
				_bd[i]->setEstado(false);
			}
		}
	}
}