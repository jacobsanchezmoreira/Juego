#include "Mapa.h"
#include <iostream>
#include <fstream>
#include "VariablesGlobales.h"

#pragma warning(disable : 4996)

void Mapa::inicia(ListaBonus& bonus, ListaEnemigos& enemigos)
{
	FILE* fichero = nullptr;
	char c = NULL;
	int fila = 0, columna = 0;
	Vector2D posicion;
	posicion.y = fila_max * Suelo::getLado();
	string nombre;

	nombre = to_string(pantalla);

	str = '\0';
	str.insert(0, "Nivel ");
	str.insert(6, to_string(pantalla));
	path.erase(13, 1);
	path.insert(13, nombre);
	fichero = fopen(&path[0], "rt");

	if (fichero)
	{
		while (!feof(fichero)) {
			fscanf(fichero, "%c", &c);
			if (c != '\n' && !feof(fichero) && columna <= columna_max && fila <= fila_max)
			{
				switch (c)
				{
				case '@': {suelos.agregar(new Suelo(posicion.x, posicion.y, 1)); break; }
				case '%': {suelos.agregar(new Suelo(posicion.x, posicion.y, 2)); break; }
				case '&': {suelos.agregar(new Suelo(posicion.x, posicion.y, 3)); break; }
				case '4': {suelos.agregar(new Suelo(posicion.x, posicion.y, 4)); break; }
				case '5': {suelos.agregar(new Suelo(posicion.x, posicion.y, 5)); break; }
				case '6': {suelos.agregar(new Suelo(posicion.x, posicion.y, 0)); break; } 
				case '7': {suelos.agregar(new Suelo(posicion.x, posicion.y, 6)); break; }
				case 'A': {suelos.agregar(new Suelo(posicion.x, posicion.y, 7)); break; }
				case 'N': {suelos.agregar(new Suelo(posicion.x, posicion.y, 8)); break; }
				case 'D': {suelos.agregar(new Suelo(posicion.x, posicion.y, 9)); break; }
				case 'F': {suelos.agregar(new Suelo(posicion.x, posicion.y, 10)); break; }
				case 'H': {suelos.agregar(new Suelo(posicion.x, posicion.y, 11)); break; }
				case 'J': {suelos.agregar(new Suelo(posicion.x, posicion.y, 12)); break; }
				case 'M': {bonus.agregar(bonus.setBonus("imagenes/mascarilla.png", posicion.x, posicion.y, 5, 4, Bonus::MASCARILLAS)); break; } //bonus mascarilla
				case 'P': {bonus.agregar(bonus.setBonus("imagenes/papel.png", posicion.x, posicion.y, 4, 4, Bonus::PAPEL)); break; } //bonus papel
				case 'V': {bonus.agregar(bonus.setBonus("imagenes/vacuna.png", posicion.x, posicion.y, 4, 4, Bonus::VACUNA)); break; } //bonus vacuna
				case 'B': {bonus.agregar(bonus.setBonus("imagenes/botiquin.png", posicion.x, posicion.y, 7, 4, Bonus::BOTIQUIN)); break; } //bonus botiquin
				case 'S': {bonus.agregar(bonus.setBonus("imagenes/escudo.png", posicion.x, posicion.y, 5, 6, Bonus::ESCUDO)); break; } //bonus escudo
				case 'L': {bonus.agregar(bonus.setBonus("imagenes/espiral.png", posicion.x, posicion.y, 5, 5, Bonus::ESPIRAL)); break; } //bonus espiral
				case 'E': {enemigos.agregar(new Ladron(5,6, posicion.x, posicion.y, -3, 0)); break; }
				case 'C': {enemigos.agregar(new Contagiado(6, 6, posicion.x, posicion.y+2.4, -2, 0)); break; }
				case 'X': {enemigos.agregar(new Murcielago(5,4, posicion.x, posicion.y, -1, 0)); break; }
				case 'Z': {enemigos.agregar(new Minivirus(6,6, posicion.x, posicion.y, -5, 0)); break; }
				case 'G': {enemigos.agregar(new GranVirus(10,12, posicion.x, posicion.y+3, -1, 0)); break; }
				}
				columna++;
				posicion.x += Suelo::getLado();
			}
			if (c == '\n' && columna <= columna_max && fila <= fila_max)
			{
				columna = 0;
				fila++;
				posicion.x = 0;
				posicion.y -= Suelo::getLado();
			}
		}
		fclose(fichero);
		fichero = nullptr;
	}
}

void Mapa::dibuja()
{
	suelos.dibuja();
	fondo.ponerFondo(getPantalla());
}

void Mapa::crear()
{
	FILE* fichero = nullptr, * registro = nullptr;
	char c, tmp;
	int fila, columna;
	int num;

	registro = fopen("niveles/Registro_Numeros_Niveles.txt", "rt");
	fscanf(registro, "%d", &num);
	num++;
	fclose(registro);

	registro = fopen("niveles/Registro_Numeros_Niveles.txt", "w+");
	fprintf(registro, "%d", num);
	fclose(registro);

	pantallas_max++;
	str = '\0';
	str.insert(0, "Nivel.txt");
	str.insert(5, to_string(pantallas_max));
	path.erase(13, 1);
	path.insert(13, to_string(pantallas_max));

	registro = fopen("niveles/Registro_Nombres_Niveles.txt", "at");
	fputs(&str[0], registro);
	fputs("\n", registro);
	fclose(registro);

	fichero = fopen(&path[0], "w+");

	if (fichero)
	{
		cout << "Introduce el numero de filas y columnas: ";
		cin >> fila >> columna;
		cout << "Ahora, introduce el dise�o" << endl;
		scanf("%c", &tmp);
		for (int i = 0; i < fila; i++)
		{
			for (int j = 0; j <= columna; j++)
			{
				c = getc(stdin);
				fprintf(fichero, "%c", c);
			}
		}
		fclose(fichero);
		fichero = nullptr;
	}
}

int Mapa::seleccion(int nivel)
{
	FILE* registro;
	char tmp;
	char nombre[100];

	registro = fopen("niveles/Registro_Numeros_Niveles.txt", "rt");

	if (registro)
	{
		estadisticas();
		fscanf(registro, "%d", &pantallas_max);
		fclose(registro);

		registro = fopen("niveles/Registro_Nombres_Niveles.txt", "rt");

		if (pantalla <= pantallas_max && pantalla <= pantallas_completada)
		{
			str = '\0';
			for (int i = 0; i < pantalla; i++)
			{
				nombre[0] = '\0';
				fgets(nombre, 100, registro);
			}
			str.insert(0, nombre);
			fclose(registro);
			registro = nullptr;
		}
	}
}

void Mapa::estadisticas()
{
	FILE* registro = fopen("niveles/Registro_Estadisticas.txt", "rt");

	if (registro)
	{
		fscanf(registro, "%d", &pantallas_completada);
		fclose(registro);
		registro = nullptr;
	}
}

void Mapa::reiniciar()
{
	FILE* registro;
	int num;

	registro = fopen("niveles/Registro_Estadisticas.txt", "wt");
	if (registro)
	{
		fprintf(registro, "%d", 0);
		fclose(registro);
		registro = nullptr;
	}

	registro = fopen("niveles/Registro_Nombres_Niveles.txt", "wt");
	if (registro)
	{
		fprintf(registro, "Nivel1.txt\nNivel2.txt\nNivel3.txt\nNivel4.txt\nNivel5.txt\nNivel6.txt\nNivel7.txt\n");
		fclose(registro);
		registro = nullptr;
	}

	registro = fopen("niveles/Registro_Numeros_Niveles.txt", "rt");
	if (registro)
	{
		fscanf(registro, "%d", &num);
		fclose(registro);
		registro = nullptr;
	}

	registro = fopen("niveles/Registro_Numeros_Niveles.txt", "wt");
	if (registro)
	{
		fprintf(registro, "7");
		fclose(registro);
		registro = nullptr;
	}

	int i = 8;
	while (true)
	{
		string str = "niveles/Nivel.txt";
		str.insert(13, &to_string(i)[0]);
		FILE* fd = fopen(&str[0], "rt");
		if (fd)
		{
			fclose(fd);
			remove(&str[0]);
		}
		else{
			break;
		}
		i++;
	}
}

void Mapa::sumaPantallaCompletada()
{
	pantallas_completada++;
	FILE* registro = fopen("niveles/Registro_Estadisticas.txt", "wt");

	if (registro)
	{
		fprintf(registro, "%d", pantallas_completada);
		fclose(registro);
		registro = nullptr;
	}
}