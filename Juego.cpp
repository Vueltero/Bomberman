#include "Juego.h"

Juego::Juego()
{
	_ventana1 = new RenderWindow(VideoMode(800, 600), "Bomberman");
	_ventana1->setFramerateLimit(60);

	_txtFondo.loadFromFile("FondoSinMedio.png");
	_fondo.setTexture(_txtFondo);
	//_fondo.setOrigin(_fondo.getGlobalBounds().width / 2, _fondo.getGlobalBounds().height / 2);
	_fondo.setPosition(0, 0);

	_vidas = 3;

	_bomba = new Bomba;
	_timer = 0;

	_fuego = new Fuego;
	_timer2 = 0;
	_mapa1 = new Mapa;

	gamePlay();
}

void Juego::gamePlay()
{
	while (_ventana1->isOpen()) {
		sf::Event event;
		while (_ventana1->pollEvent(event)) {
			if (event.type == Event::Closed) {
				_ventana1->close();
			}
		}
		//CMD
		_player1.cmd(event);
		if (_mapa1->comprobarColisionAmbos(_player1)) {
			_player1.choqueBloque();
		}
		_mapa1->comprobarColisionDestruir(*_fuego);

		if (Keyboard::isKeyPressed(Keyboard::Space) && _timer == 0) {
			_timer = 60 * 5;
			_bomba->setSpritePosition(_player1.getSprite().getPosition());
		}
		if (_timer > 0) {
			_timer--;
		}
		//_fuego al estallar _bomba (no funciona)
		if (_timer == 1) {
			_timer2 = 60 * 2;
			_fuego->setSpritePosition(_bomba->getSprite().getPosition());

		}
		if (_timer2 == 0) {
			_fuego->setSpritePosition({ 800, 600 });
		}
		if (_timer2 > 0) {
			_timer2--;
		}
		//colision y muerte del pj
		if (_fuego->isColision(_player1)) {
			_player1.morir();
		}
		dibujar();
	}
}

void Juego::dibujar()
{
	_ventana1->clear();
	_ventana1->draw(_fondo);
	_mapa1->dibujarDestruibles(_ventana1);
	if (_timer2 > 0) {
		_ventana1->draw(*_fuego);
	}
	_mapa1->dibujarFijos(_ventana1);

	if (_timer > 0) {
		_ventana1->draw(*_bomba);
	}
	_ventana1->draw(_player1);
	_ventana1->display();
}
