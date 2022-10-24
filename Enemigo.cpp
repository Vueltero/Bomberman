#include "Enemigo.h"

Enemigo::Enemigo() {
	//_timerCamina = 20;
	_velocidad = { 0,0 };
	//_txt[0].loadFromFile("down1.png");
	//_txt[1].loadFromFile("up1.png");
	//_txt[2].loadFromFile("right1.png");
	//_txt[3].loadFromFile("left1.png");
	_txt.loadFromFile("globo1.png");
	_sprite.setTexture(_txt);
	_sprite.setOrigin((_sprite.getGlobalBounds().width) / 2, (_sprite.getGlobalBounds().height) / 2);
	_sprite.setPosition(607.5, 517.5);
	random = 0;
	_estado = true;
	_muerte = false;
}

void Enemigo::cmd()
{
	float mov = 2;
	_velocidad = {};
	random_device rd;
	if (_tiempoMov == 0) {
		mt19937 gen(rd());
		uniform_int_distribution<> dis(0, 4);
		cout << random << endl;
		random = dis(gen);
		_tiempoMov = 60;
	}
	_tiempoMov--;
	 
	switch (random)
	{
	case 1:
		//_sprite.setPosition(_sprite.getPosition().x, _sprite.getPosition().y - mov);
		_velocidad.y = -1 * mov;
		animacionCaminar(1);
		break;
	case 2:
		//_sprite.setPosition(_sprite.getPosition().x, _sprite.getPosition().y + mov);
		_velocidad.y = mov;
		animacionCaminar(2);
		break;

	case 3:
		//_sprite.setPosition(_sprite.getPosition().x-mov, _sprite.getPosition().y);
		_velocidad.x = -1 * mov;
		animacionCaminar(4);
		break;
	case 0:
		//_sprite.setPosition(_sprite.getPosition().x+mov, _sprite.getPosition().y);
		_velocidad.x = mov;
		animacionCaminar(3);
		break;
	}
	_sprite.move(_velocidad);

	//BORDES
	float margenAncho = 47 + _sprite.getGlobalBounds().width / 2, margenAlto = 47 + _sprite.getGlobalBounds().height / 2;
	if (_sprite.getPosition().x < margenAncho) {
		_sprite.setPosition(margenAncho, _sprite.getPosition().y);
	}
	if (_sprite.getPosition().x > 800 - margenAncho) {
		_sprite.setPosition(800 - margenAncho, _sprite.getPosition().y);
	}
	if (_sprite.getPosition().y < margenAlto) {
		_sprite.setPosition(_sprite.getPosition().x, margenAlto);
	}
	if (_sprite.getPosition().y > 600 - margenAlto) {
		_sprite.setPosition(_sprite.getPosition().x, 600 - margenAlto);
	}
}


void Enemigo::choqueBloque()
{
	_sprite.move(-_velocidad);
}

void Enemigo::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

FloatRect Enemigo::getBounds() const
{

	return _sprite.getGlobalBounds();
}

Sprite Enemigo::getSprite()
{
	return _sprite;
}
void Enemigo::animacionCaminar(int direccion) {

	string cadena= "globo";
	if (__timerCamina > 0) {
		switch (direccion)
		{
		case 1:
			cadena += to_string(_path) + ".png";
			_txt.loadFromFile(cadena);
			_sprite.setTexture(_txt);
			break;
		case 2:
			cadena +=to_string(_path) + ".png";
			_txt.loadFromFile(cadena);
			_sprite.setTexture(_txt);
			break;
		case 3:
			cadena +=to_string(_path) + ".png";
			_txt.loadFromFile(cadena);
			_sprite.setTexture(_txt);
			break;
		}
	}
	else {
		__timerCamina = 30;
		if (_path < 2) {
			_path++;
		}
		else {
			_path = 1;
		}
	}
	__timerCamina--;
}
void Enemigo::morir() {
	if (!_estado) {
		if (__timerMuerte > 100) {
			_txt.loadFromFile("globoMuerte1.png");
			_sprite.setTexture(_txt);

			__timerMuerte--;
		}
		else if (__timerMuerte > 80) {
			_txt.loadFromFile("globoMuerte2.png");
			_sprite.setTexture(_txt);

			__timerMuerte--;
		}
		else if (__timerMuerte > 60) {

			_txt.loadFromFile("globoMuerte3.png");
			_sprite.setTexture(_txt);

			__timerMuerte--;
		}
		else if (__timerMuerte > 40) {
			_sprite.move(-_velocidad);
			_txt.loadFromFile("globoMuerte4.png");
			_sprite.setTexture(_txt);

			__timerMuerte--;
		}
		else if (__timerMuerte > 20) {
			_txt.loadFromFile("globoMuerte5.png");
			_sprite.setTexture(_txt);

			__timerMuerte--;
		}
		else if (__timerMuerte > 0) {
			
			_txt.loadFromFile("globoMuerte6.png");
			_sprite.setTexture(_txt);

			__timerMuerte--;
		}
		else {
			_txt.loadFromFile("vacio.png");
			_sprite.setTexture(_txt);
			_muerte = true;
		}

	}
}