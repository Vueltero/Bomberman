#include "Juego.h"


Juego::Juego()
{
	_ventana1 = new RenderWindow(VideoMode(800, 600), "Bomberman");
	_ventana1->setFramerateLimit(60);

	_txtFondo.loadFromFile("FondoSinMedio.png");
	_fondo.setTexture(_txtFondo);
	//_fondo.setOrigin(_fondo.getGlobalBounds().width / 2, _fondo.getGlobalBounds().height / 2);
	_fondo.setPosition(0, 0);

	Enemigo* _enemigo1 = new Enemigo;
	Enemigo* _enemigo2 = new Enemigo;
	Enemigo* _enemigo3 = new Enemigo;

	_enemigos.push_back(*_enemigo1);
	_enemigos.push_back(*_enemigo2);
	_enemigos.push_back(*_enemigo3);
	_vidas = 3;

	Player* _player1 = new Player;
	_players.push_back(*_player1);

	_bomba = new Bomba;
	_timer = 0;

	_fuego = new Fuego;
	_timer2 = 0;
	_mapa1 = new Mapa;
	randomNumero = 4;
	_contadorCrear = 0;

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
		list<Player>::iterator play;
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (!play->getMuriendo()) {
				play->cmd(event);
			}
			else {
				if (!play->getMuerto())
					play->morir(_contadorCrear);
			}
		}
		//fin de las 3 vidas y partida, luego cambiar
		if (_contadorCrear == 5) {
			_ventana1->close();
		}
		//crea nuevo pj, nueva vida en esquina
		if (_contadorCrear % 2 != 0) {
			Player* _player = new Player;
			_players.push_back(*_player);
			_contadorCrear++;
		}
		//CMD del enemigo, si esta vivo o muriendo.
		list<Enemigo>::iterator it;
		for (it = _enemigos.begin(); it != _enemigos.end(); ++it) {
			if (it->getEstado())
				it->cmd();
			else {
				it->morir();
			}
		}
		//Colisiones con bloques de PJ
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (_mapa1->comprobarColisionAmbos(*play)) {
				play->choqueBloque();
			}
		}
		//Colsiones con bloques del Enemigo
		for (it = _enemigos.begin(); it != _enemigos.end(); ++it) {
			if (_mapa1->comprobarColisionAmbos(*it) && it->getMuerte() == false) {
				it->choqueBloque();
			}
		}
		// Destruccion de bloques flojos
		_mapa1->comprobarColisionDestruir(*_fuego);

		//poner bomba, solo si no esta muriendo y naturalmente no muerto
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (Keyboard::isKeyPressed(Keyboard::Space) && _timer == 0 && play->getMuriendo() == false) {
				_timer = 60 * 5;
				_bomba->setSpritePosition(play->getSprite().getPosition());
			}
		}
		//timer de bomba
		if (_timer > 0) {
			_timer--;
		}
		//_fuego al estallar _bomba
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
		//colision y muerte del pj, primero por fuego, luego por chocar enemigos
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (_fuego->isColision(*play)) {
				play->setMuriendo(true);
			}
		}
		for (play = _players.begin(); play != _players.end(); ++play) {
			for (it = _enemigos.begin(); it != _enemigos.end(); ++it) {
				if (it->isColision(*play)) {
					play->setMuriendo(true);
				}
			}
		}
		//colision y muerte de los enemigos con el fuego.
		list<Enemigo>::iterator it2;
		for (it2 = _enemigos.begin(); it2 != _enemigos.end(); ++it2) {
			if (_fuego->isColision(*it2) && it2->getMuerte() == false) {
				it2->setEstado(false);
			}
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

	list<Player>::iterator play;
	for (play = _players.begin(); play != _players.end(); ++play) {
		_ventana1->draw(*play);
	}
	list<Enemigo>::iterator it;
	for (it = _enemigos.begin(); it != _enemigos.end(); ++it) {
		_ventana1->draw(*it);
	}
	_ventana1->display();
}
