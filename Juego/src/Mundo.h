#pragma once

#include "Plataforma.h"
#include "Suelo.h"
#include "Personaje.h"
#include "Mapa.h"
#include "Disparo.h"
#include"ListaDisparos.h"

class Mundo
{
public:
	Mapa nivel;
	//Plataforma base;
	//Plataforma plataforma1, plataforma2;
	Personaje personaje;
	Disparo disparo;
	ListaDisparos disparos;
	void Tecla(unsigned char key);
	void teclaEspecial(unsigned char key);
	void Inicializa();
	void Mueve();
	void Dibuja();

	float x_ojo;
	float y_ojo;
	float z_ojo;

	
	virtual ~Mundo();
};