#include "Torneo.h"
#include "Clasificacion.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef char cadena[30];

Torneo::~Torneo(){
     fichero.close();
};

Torneo::Torneo(){
    strcpy(nomTorneo, "");
    strcpy(nomFichero, "");
    numGolfistas=0;
};

int Torneo::getNumGolfistas(){
    return numGolfistas;
};

void Torneo::putNumGolfistas(int n){
    numGolfistas=n;
};

void Torneo::getNomTorneo(cadena nombre){
    strcpy(nombre, nomTorneo);
};

void Torneo::getNomFichero(cadena nombre){
    strcpy(nombre, nomFichero);
};

void Torneo::putNomTorneo(cadena nombre){
    strcpy(nomTorneo,nombre);
};

void Torneo::putNomFichero(cadena nombre){
    strcpy(nomFichero,nombre);
};

void Torneo::crearFichero(char nombreFichero[]){
    fichero.open(nombreFichero, ios::out |ios::in |ios::binary);

    if(fichero.fail()){
        fichero.clear();
        fichero.close();
        fichero.open(nombreFichero, ios::out|ios::binary);
        fichero.close();
        fichero.open(nombreFichero, ios::in|ios::out|ios::binary);
        numGolfistas=0;
        fichero.write((char*) &numGolfistas, sizeof(int));
        cout<<"Fichero creado"<<endl;
    }

    else{
        fichero.read ((char*) &numGolfistas, sizeof(int));
        cout<<"Fichero ya existe"<<endl;
    }
    strcpy(nomFichero, nombreFichero);
};

void Torneo:: mostrar(float hdcp){
    if(fichero.fail()){
        cout<<"Error en fichero.mostrar()"<<endl;
    }
    Golfista g;
    fichero.seekg(sizeof(int),ios::beg);
    if(hdcp!=-1){
        fichero.seekg(0,ios::beg);
        fichero.read((char*)&numGolfistas,sizeof(int));
        cout << "Numero de golfistas: " << numGolfistas << endl;
        fichero.seekg(sizeof(int),ios::beg);
        for(int i=0; i<numGolfistas; i++){
            fichero.read((char*)&g, sizeof(Golfista));
            if(g.handicap==hdcp){
                cout << "Golfista: " << i + 1 << endl;
                cout << "Licencia: " << g.licencia << endl;
                cout<<"Handicap: "<<g.handicap<<endl;
                cout << "Nombre: " << g.nombre << endl;
                cout << "Apellidos: " << g.apellidos << endl;
                cout << "Golpes: " << g.golpes << endl;
                cout << "Resultado: " << g.resultado << endl;
                cout<<" "<<endl;
            }
        }
    }
    else{
        fichero.seekg(0,ios::beg);
        fichero.read((char*)&numGolfistas,sizeof(int));
        cout << "Numero de golfistas: " << numGolfistas << endl;
        fichero.seekg(sizeof(int),ios::beg);
        for(int i=0; i<numGolfistas; i++){
            fichero.read((char*)&g, sizeof(Golfista));
            cout << "Golfista: " << i + 1 << endl;
            cout << "Licencia: " << g.licencia << endl;
            cout<<"Handicap: "<<g.handicap<<endl;
            cout << "Nombre: " << g.nombre << endl;
            cout << "Apellidos: " << g.apellidos << endl;
            cout << "Golpes: " << g.golpes << endl;
            cout << "Resultado: " << g.resultado << endl;
            cout<<" "<<endl;
        }
    }

};

Golfista Torneo::consultar(int posicion){
    if(fichero.fail()){
        cout<<"Error en fichero.consultar()"<<endl;
    }
    Golfista g;
    /* fichero.read((char*)&numGolfistas, sizeof(int));
     if (posicion < 1 || posicion > numGolfistas)
     {
         cout << "Error: La posición no es válida. Debe estar entre 1 y " << numGolfistas << endl;
     }*/

    //posiciono al inicio y leo
    fichero.seekg(sizeof(int) + (posicion-1) * sizeof(Golfista), ios::beg);
    fichero.read((char*)&g, sizeof(Golfista));

    cout << "Datos del golfista ubicado en la posicion " << posicion << " : " << endl;
    cout << "Licencia: " << g.licencia << endl;
    cout<<"Handicap: "<<g.handicap<<endl;
    cout << "Nombre: " << g.nombre << endl;
    cout << "Apellidos: " << g.apellidos << endl;
    cout << "Golpes: " << g.golpes << endl;
    cout << "Resultado: " << g.resultado << endl;

    return g; //devuelvo golfista encontrado
};

int Torneo::buscar(cadena licencia){
    if(fichero.fail()){
        cout<<"Error en fichero.buscar()"<<endl;
    }
    Golfista g;
    bool encontrado=false;
    int i=0;
    int pos=-1;
    fichero.seekg(sizeof(int),ios::beg);
    while(i<numGolfistas && !encontrado){
        fichero.read((char*)&g, sizeof(Golfista));
        if(strcmp(g.licencia,licencia)==0){
            pos=i+1;
            encontrado=true;
        }
        i++;
    }
    return pos; //devuelve posicion golfista encontrado
};

void Torneo::insertar(Golfista g){
    if(fichero.fail()){
        cout<<"Error en fichero.insertar()"<<endl;
    }

    g.golpes=0;
    g.resultado=0;

    int pos = 0;
    Golfista temp;
    fichero.seekg(sizeof(int), ios::beg);
    for(int i=0; i<numGolfistas; i++){
        fichero.read((char*)&temp, sizeof(Golfista));
        if(temp.handicap > g.handicap){
            break;
        }
        pos++;
    }

    // Mover los golfistas posteriores para hacer espacio
    for(int i=numGolfistas; i>pos; i--){
        fichero.seekg(sizeof(int) + (i-1)*sizeof(Golfista), ios::beg);
        fichero.read((char*)&temp, sizeof(Golfista));
        fichero.seekp(sizeof(int) + i*sizeof(Golfista), ios::beg);
        fichero.write((char*)&temp, sizeof(Golfista));
    }

    // Insertar nuevo golfista
    fichero.seekp(sizeof(int) + pos*sizeof(Golfista), ios::beg);
    fichero.write((char*)&g, sizeof(Golfista));
    numGolfistas++;

    fichero.seekp(0,ios::beg);
    fichero.write((char*)&numGolfistas,sizeof(int));
    cout << "Golfista insertado correctamente." << endl;
};

void Torneo::modificar(Golfista c, int posicion){
if(fichero.fail()){
        cout<<"Error en fichero.modificar()"<<endl;
    }
if(posicion <1 || posicion >numGolfistas){
    cout << "Error, golfista no encontrado" << endl;
}

Golfista golfistaexistente;
//me posiciono en el golfista que quiero modificar
fichero.seekg(sizeof(int)+ (posicion-1)*sizeof(Golfista),ios::beg);
fichero.read((char*)&golfistaexistente,sizeof(Golfista));
    cout  << "Nueva licencia: " << endl;
    cin >> golfistaexistente.licencia;
    cin.ignore();
    cout << "Nuevo nombre: " << endl;
    cin.getline(golfistaexistente.nombre,30);
    cout << "Nuevos apellidos: " << endl;
    cin.getline(golfistaexistente.apellidos,30);
    c.handicap=golfistaexistente.handicap;

    fichero.seekp(sizeof(int)+(posicion-1)*sizeof(Golfista),ios::beg);
    fichero.write((char*)&golfistaexistente,sizeof(Golfista));
    cout << "Golfista modificado correctamente" << endl;
    cout << "Mostrando datos actualizados: " << endl;
    mostrar(-1);
};

void Torneo::eliminar(int posicion){
    if(fichero.fail()){
        cout<<"Error en fichero.eliminar()"<<endl;
    }
if(posicion <0 || posicion >numGolfistas){
    cout << "Error, golfista no encontrado" << endl;
}

else{
    Golfista golfistaexistente;
    for(int i=posicion;i<numGolfistas;i++){
        //leo siguiente
        fichero.seekg(sizeof(int)+ i *sizeof(Golfista),ios::beg);
        fichero.read((char*)&golfistaexistente,sizeof(Golfista));

        //lo escribo en anterior
        fichero.seekp(sizeof(int)+ (i-1) * sizeof(Golfista),ios::beg);
        fichero.write((char*)&golfistaexistente,sizeof(Golfista));
    }
    numGolfistas--;

    fichero.seekp(0,ios::beg);
    fichero.write((char*)&numGolfistas,sizeof(int));
    cout << "Golfista eliminado correctamente" << endl;
    cout << "Mostrando datos actualizados: " << endl;
    mostrar(-1);
}
};

void Torneo:: Clasificar(){
    if(fichero.fail()){
        cout<<"Error en fichero.clasificar()"<<endl;
    }
    fichero.clear();
    fichero.seekp(0,ios::beg);
    fichero.read((char*)&numGolfistas, sizeof(int));
    if (numGolfistas==0){
        cout<<"No hay golfistas inscritos"<<endl;
    }
    srand(time(0)); //inicializo semilla para numeros aleatorios
    const int PAR=72;

    Clasificacion clasif;

    cout<<"Resultados del torneo: "<<nomTorneo<<endl;
    cout << "Puesto\tNombre\tApellidos\tHandicap\tGolpes\tResultado"<<endl;
    cout<<"----------------------------------------------------------------------"<<endl;

    for(int i=0; i<numGolfistas; i++){
        Golfista g;
        fichero.seekp(sizeof(int) +i*sizeof(Golfista), ios::beg);
        fichero.read((char*)&g, sizeof(Golfista));

        g.golpes=50+rand()%51; // de 50 a 100
        g.resultado=g.golpes-PAR; //negativo es mejor resultado
        //Golfista
        fichero.seekp(sizeof(int) +i*sizeof(Golfista), ios::beg);
        fichero.write((char*)&g, sizeof(Golfista));
        //Clasificacion
        Jugador j;
        j.indice=i;
        j.resultado=g.resultado;
        clasif.anadirjugador(j);
    }

    clasif.ordenar();

    for (int i=0; i<clasif.numjugadores(); i++){
        Jugador j=clasif.consultar(i);
        Golfista g;
        fichero.seekp(sizeof(int) +j.indice*sizeof(Golfista), ios::beg);
        fichero.read((char*)&g, sizeof(Golfista));
        cout<<i+1<<"\t";
        cout<<g.nombre<<"\t";
        cout<<g.apellidos<<"\t\t";
        cout<<g.handicap<<"\t\t";
        cout<<g.golpes<<"\t";
        cout<<g.resultado<<endl;
    }
    cout<<"----------------------------------------------------------------------"<<endl;
};
