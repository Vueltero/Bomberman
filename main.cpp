//#include <SFML/Graphics.hpp>
//#include "BloqueFijo.h"
//#include "Bomba.h"
//#include <iostream>
//#include "Player.h"
//#include "Fuego.h"

#include "Juego.h"

using namespace sf;




int main() {
	RenderWindow* _ventana1 = new RenderWindow(VideoMode(800, 600), "Bomberman");
	Juego _juego1(_ventana1);
	
	return 0;
}