#ifndef TORNEO_H_INCLUDED
#define TORNEO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

typedef char cadena[30];

struct Golfista {
    cadena licencia;
    float handicap;
    cadena nombre;
    cadena apellidos;
    int golpes;
    int resultado;
};


class Torneo
{
    fstream fichero;
    int numGolfistas;
    cadena nomFichero;
    cadena nomTorneo;
public:
    ~Torneo();
    Torneo();
    int getNumGolfistas();
    void putNumGolfistas(int n);
    void getNomTorneo(cadena nombre);
    void getNomFichero(cadena nombre);
    void putNomTorneo(cadena nombre);
    void putNomFichero(cadena nombre);
    void crearFichero(char nombreFichero[]);
    void mostrar(float hdcp);
    Golfista consultar(int posicion);
    int buscar(cadena licencia);
    void insertar(Golfista g);
    void modificar(Golfista c, int posicion);
    void eliminar(int posicion);
    void Clasificar();
};

#endif // TORNEO_H_INCLUDED
