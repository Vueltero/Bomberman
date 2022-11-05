#include "Nivel3.h"

Nivel3::Nivel3(RenderWindow* _ventana1, int puntaje, int vidas)
{
	_ventana1->setFramerateLimit(60);

	_txtFondo.loadFromFile("fondoRojo.png");
	_fondo.setTexture(_txtFondo);

	_txtFondoGameOver.loadFromFile("gameOver.jpg");
	_fondoGameOver.setTexture(_txtFondoGameOver);

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
