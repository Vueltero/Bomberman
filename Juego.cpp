#include "Juego.h"


Juego::Juego()
{
	_ventana1 = new RenderWindow(VideoMode(800, 600), "Bomberman");
	_ventana1->setFramerateLimit(60);

	_txtFondo.loadFromFile("FondoSinMedio.png");
	_fondo.setTexture(_txtFondo);
	//_fondo.setOrigin(_fondo.getGlobalBounds().width / 2, _fondo.getGlobalBounds().height / 2);
	_fondo.setPosition(0, 0);
	_txtFondoGameOver.loadFromFile("gameOver.jpg");
	_fondoGameOver.setTexture(_txtFondoGameOver);

	_fuegosV[0].rotarVertical();
	_fuegosV[1].rotarVertical();

	Enemigo* _enemigo1 = new Enemigo;
	Enemigo* _enemigo2 = new Enemigo;
	Enemigo* _enemigo3 = new Enemigo;

	_enemigos.push_back(*_enemigo1);
	_enemigos.push_back(*_enemigo2);
	_enemigos.push_back(*_enemigo3);

	_vidas = 3;

	Player* _player1 = new Player;
	_players.push_back(*_player1);

	_bufBomba.loadFromFile("ponerBomba.wav");
	_sonBomba.setBuffer(_bufBomba);

	_bufItem.loadFromFile("item.wav");
	_sonItem.setBuffer(_bufItem);

	_timer = 0;

	_timer2 = 0;
	_mapa1 = new Mapa;
	randomNumero = 4;
	_contadorCrear = 0;			//contar muerte de pj

	_dosBombas = false;
	_timerBoostBomba = 0;
	_tiempoBombas = 0;


	_acelerar = false;
	_timerVelocidad = 0;

	_contadorEnemigosEliminados = 0;

	_puntaje = 0;
	_tiempoLimite = 5 * 60 * 60;

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
		/*if (_victoria == true) {
			_ventana1->close();
		}*/
		_tiempoLimite--;
		//CMD

		list<Player>::iterator play;
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (!play->getMuriendo()) {
				play->cmd(event, _acelerar);
			}
			else {
				if (!play->getMuerto())
					play->morir(_contadorCrear);
			}
		}
		//fin de las 3 vidas y partida, luego cambiar
		if (_contadorCrear == 5) {
			//va pantalla de game over
			_gameOver = true;
		}
		//crea nuevo pj, nueva vida en esquina
		if (_contadorCrear % 2 != 0) {
			Player* _player = new Player;
			_players.push_back(*_player);
			_contadorCrear++;
		}
		//Colision con boosterVelocidad (20 seg)
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (_mapa1->comprobarColisionVelocidad(*play)) {
				_timerVelocidad = 20 * 60;
				_acelerar = true;
				_sonItem.play();
			}
		}
		_timerVelocidad--;
		if (_timerVelocidad <= 0) {
			_acelerar = false;
		}
		//Colision con boosterBOmba (20 seg)
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (_mapa1->comprobarColisionBoostBomba(*play)) {
				_timerBoostBomba = 20 * 60;
				_dosBombas = true;
				_sonItem.play();
			}
		}
		_timerBoostBomba--;
		if (_timerBoostBomba <= 0) {
			_dosBombas = false;
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
		for (int i = 0; i < 2; i++) {
			if (_fuegos[i].getEstado()) {
				_mapa1->comprobarColisionDestruir(_fuegos[i]);
			}
			if (_fuegosV[i].getEstado()) {
				_mapa1->comprobarColisionDestruir(_fuegosV[i]);
			}
		}

		//poner bomba, solo si no esta muriendo y naturalmente no muerto
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (!_dosBombas) {
				if (Keyboard::isKeyPressed(Keyboard::Space) && _bombas[0].getEstado() == false && play->getMuriendo() == false) {
					_sonBomba.play();
					bool estado;
					_bombas[0].crearExplotar(estado);
					_bombas[0].setSpritePosition(play->getSprite().getPosition());
				}
			}
			else {
				for (int i = 0; i < 2; i++) {
					if (Keyboard::isKeyPressed(Keyboard::Space) && play->getMuriendo() == false) {
						if (_bombas[i].getEstado() == false && _tiempoBombas < 0) {
							_sonBomba.play();
							bool estado = false;
							_bombas[i].crearExplotar(estado);
							_bombas[i].setSpritePosition(play->getSprite().getPosition());

							_tiempoBombas = 60;
						}
					}
				}
				//tiempo entre 2 bombas
				_tiempoBombas--;
			}
		}
		for (int i = 0; i < 2; i++) {
			if (_bombas[i].getEstado() == true) {
				bool estado = false;
				_bombas[i].crearExplotar(estado);
				_fuegos[i].setEstado(estado);
				_fuegos[i].setSpritePosition(_bombas[i].getSprite().getPosition());
				_fuegosV[i].setEstado(estado);
				_fuegosV[i].setSpritePosition(_bombas[i].getSprite().getPosition());
			}
		}
		for (int i = 0; i < 2; i++) {
			if (_fuegos[i].getEstado() && _fuegosV[i].getEstado()) {
				_fuegos[i].crearLlama();
				_fuegosV[i].crearLlama();
			}
		}

		//colision y muerte del pj, primero por fuego, luego por chocar enemigos
		for (play = _players.begin(); play != _players.end(); ++play) {
			for (int i = 0; i < 2; i++) {
				if ((_fuegos[i].isColision(*play) && _fuegos[i].getEstado()) || (_fuegosV[i].isColision(*play) && _fuegosV[i].getEstado())) {
					play->setMuriendo(true);	
				}
			}
		}
		for (play = _players.begin(); play != _players.end(); ++play) {
			for (it = _enemigos.begin(); it != _enemigos.end(); ++it) {
				if (it->isColision(*play) && it->getEstado()) {
					play->setMuriendo(true);
			
				}
			}
		}
		//colision y muerte de los enemigos con el fuego.
		list<Enemigo>::iterator it2;
		for (it2 = _enemigos.begin(); it2 != _enemigos.end(); ++it2) {
			for (int i = 0; i < 2; i++) {
				if ((_fuegos[i].isColision(*it2) && _fuegos[i].getEstado() && it2->getMuerte() == false) || (_fuegosV[i].isColision(*it2) && _fuegosV[i].getEstado() && it2->getMuerte() == false)) {
					it2->setEstado(false);
				}
			}
		}
		//Puerta de la victoria
		_contadorEnemigosEliminados = 0;
		for (it2 = _enemigos.begin(); it2 != _enemigos.end(); ++it2) {
			if (it2->getMuerte()) {
				_contadorEnemigosEliminados++;
			}
		}
		if (_contadorEnemigosEliminados > 2) {
			_mapa1->setEstadoPV(true);
		}
		if (_mapa1->getEstadoPV()) {
			_mapa1->abrirPuerta();
		}
		for (play = _players.begin(); play != _players.end(); ++play) {
			if (_mapa1->comprobarColisionPuerta(*play)) {
				//ganar
				//victoria();
				_victoria = true;
				_gameOver = true;
			}
		}
		dibujar();
	}
}

void Juego::dibujar()
{
	_ventana1->clear();
	_ventana1->draw(_fondo);

	_mapa1->dibujarVelocidad(_ventana1);
	_mapa1->dibujarBoostBomba(_ventana1);

	_mapa1->dibujarPuertaVictoria(_ventana1);


	_mapa1->dibujarDestruibles(_ventana1);

	for (int i = 0; i < 2; i++) {
		if (_fuegos[i].getEstado()) {
			_ventana1->draw(_fuegos[i]);
		}
		if (_fuegosV[i].getEstado()) {
			_ventana1->draw(_fuegosV[i]);
		}
	}

	_mapa1->dibujarFijos(_ventana1);

	for (int i = 0; i < 2; i++) {
		if (_bombas[i].getEstado() == true) {
			_ventana1->draw(_bombas[i]);
		}
	}

	list<Player>::iterator play;
	for (play = _players.begin(); play != _players.end(); ++play) {
		_ventana1->draw(*play);
	}
	list<Enemigo>::iterator it;
	for (it = _enemigos.begin(); it != _enemigos.end(); ++it) {
		_ventana1->draw(*it);
	}
	if (_gameOver) {
		_ventana1->draw(_fondoGameOver);
	}
	_ventana1->display();
}

