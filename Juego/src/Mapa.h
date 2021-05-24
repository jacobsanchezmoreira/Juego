#pragma once

#include "ListaSuelos.h"
#include "ListaEnemigos.h"
#include "ListaBonus.h"
#include <string>

class Mapa
{
private:
	static const int fila_max = 16;
	static const int columna_max = 80;
	ListaSuelos suelos;
	int pantalla = 1;
	int pantallas_max;
	int pantallas_completada;
	string path = "..\\src\\Nivel0.txt";
	string str;

public:
	void inicia(ListaBonus& bonus, ListaEnemigos &enemigos);
	void dibuja();
	int getPantalla() { return pantalla; };
	const int getFila_Max() { return fila_max; };
	const int getColumna_Max() { return columna_max; };
	void setPantalla(int nivel) { pantalla = nivel; };
	void crear();
	int seleccion(int nivel);
	void estadisticas();
	void sumaPantallaCompletada();
	void reiniciar();
	
	friend class Interaccion;
	friend class ListaSuelos;
	friend class Mundo;
	friend class Coordinador;
};
