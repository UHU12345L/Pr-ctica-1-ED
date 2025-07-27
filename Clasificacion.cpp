#include "Clasificacion.h"
#include <iostream>
using namespace std;

const int SALTO=4;

Clasificacion::Clasificacion(){
    Jugadores=0;
    tamano=0;
    elementos=new Jugador[tamano];
};

Clasificacion::~Clasificacion(){
    delete[]elementos;
};

void Clasificacion::anadirjugador(Jugador j){
    if (elementos==nullptr){
        cout<<"Error en anadirjugador clasificacion"<<endl;
    }

    if(Jugadores==tamano){
        Jugador *nuevoJugador=new Jugador[tamano+SALTO];
    //copiar jugaores (elementos de jugador) a nueva tabla (nuevoJugador)
    for(int i=0; i<Jugadores; i++){
        nuevoJugador[i]=elementos[i];
    }
    delete[] elementos;
    elementos=nuevoJugador;
    tamano+=SALTO;

    }
    elementos[Jugadores]=j;
    Jugadores++;
};

void Clasificacion::eliminar(int n){
    if (elementos==nullptr){
        cout<<"Error en eliminar clasificacion"<<endl;
    }

    if(n<0 || n>=Jugadores){
        cout<<"Posicion no valida para eliminar"<<endl;
    }

    for (int i=n; i<Jugadores; i++){
        elementos[i]=elementos[i+1];
    }

    Jugadores--;
};

Jugador Clasificacion::consultar (int n){
    if (elementos==nullptr){
        cout<<"Error en consultar clasificacion"<<endl;
    }

        if(n<0||n>=Jugadores){
            cout<<"Posicion no valida para consultar"<<endl;
        }else{
            return elementos[n];
        }
    };


bool Clasificacion::vacio(){
    return Jugadores==0; //true si no hay jugadores
};

int Clasificacion::numjugadores(){
    return Jugadores; //contador de jugadores
};

void Clasificacion::ordenar(){
    if (elementos==nullptr){
        cout<<"Error en ordenar clasificacion"<<endl;
    }

    for (int i=0; i<Jugadores-1; i++){
        for (int j=0; j<Jugadores-i-1; j++){
             if (elementos[j].resultado > elementos[j + 1].resultado) {
                // Intercambiar jugadores si en orden incorrecto
                Jugador temp = elementos[j];
                elementos[j] = elementos[j + 1];
                elementos[j + 1] = temp;
            }
        }
    }
};
