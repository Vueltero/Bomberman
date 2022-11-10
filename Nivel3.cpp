#include "Nivel3.h"

Nivel3::Nivel3(RenderWindow* _ventana1, int puntaje, int vidas)
{
	_ventana1->setFramerateLimit(60);

	_txtFondo.loadFromFile("fondoRojo.png");
	_fondo.setTexture(_txtFondo);

	_txtFondoGameOver.loadFromFile("gameOver.jpg");
	_fondoGameOver.setTexture(_txtFondoGameOver);

	_txPantalla.loadFromFile("fondoVictoria.jpg");
	_pantallaFinal.setTexture(_txPantalla);

	_fuegosV[0].rotarVertical();
	_fuegosV[1].rotarVertical();

	Enemigo* _enemigo1 = new Enemigo(kloster);
	Enemigo* _enemigo2 = new Enemigo(kloster);
	Enemigo* _enemigo3 = new Enemigo(kloster);

	_enemigos.push_back(*_enemigo1);
	_enemigos.push_back(*_enemigo2);
	_enemigos.push_back(*_enemigo3);


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

	_fuente.loadFromFile("fuente.ttf");
	_textoVidas.setFont(_fuente);
	_textoVidas.setScale(0.5, 0.5);
	_textoVidas.setPosition(590, 45);
	_textoPuntaje.setFont(_fuente);
	_textoPuntaje.setScale(0.5, 0.5);
	_textoPuntaje.setPosition(590, 90);

	_vidas = vidas;
	_puntaje = puntaje;
	_totalDestruibles = _mapa1->getNumeroDestruibles();
	_enemigosAMatar = 3;


	_acelerar = false;
	_timerVelocidad = 0;

	_contadorEnemigosEliminados = 0;

	_tiempoLimite = 5 * 60 * 60;
}

void Nivel3::pantallaVictoria(RenderWindow* _ventana1)
{
	_fuente.loadFromFile("fuente.ttf");
	_textoPuntaje.setFont(_fuente);
	_textoPuntaje.setString("PUNTAJE TOTAL: " + to_string(_puntaje));
	_textoPuntaje.setScale(1, 1);
	_textoPuntaje.setPosition(180, 400);
	_textoPuntaje.setOutlineThickness(.7);
	if (_timerVictoria == (60 * 5) - 1) {

	}
	while (_timerVictoria > 0) {
		_ventana1->clear();
		_ventana1->draw(_pantallaFinal);
		_ventana1->draw(_textoPuntaje);
		_ventana1->display();
		_timerVictoria--;
		Event event;
		while (_ventana1->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				_ventana1->close();
			}
		}
	}
}
