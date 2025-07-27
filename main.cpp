#include <iostream>
#include <cstring>
#include "Torneo.h"
#include "Clasificacion.h"

using namespace std;
typedef char cadena[30];

struct TorneoAux
{
    int nG;
    cadena nTorneo;
    cadena Nfichero;
};

int main()
{
    const int N=10;
    int op;
    int opTorneo;
    int nT=0; //numero de torneos efectivos
    Torneo t[N]; //vector tipo torneo, array de objetos torneo
    TorneoAux aux;
    cadena nombreTorneo;
    cadena nombreFichero;

    fstream fichero("TORNEOS.dat", ios::binary | ios::in | ios::out);
    if(fichero.fail())
    {
        fichero.clear();
        fichero.close();
        fichero.open("TORNEOS.dat", ios::out|ios::binary);
        TorneoAux r;

        t[nT].crearFichero("AUDI.dat");
        t[nT].putNomTorneo("AUDI");
        r.nG = t[nT].getNumGolfistas();
        t[nT].getNomFichero(r.Nfichero);
        t[nT].getNomTorneo(r.nTorneo);
        fichero.write((char*)&r, sizeof(TorneoAux));
        nT++;

        t[nT].crearFichero("SONY.dat");
        t[nT].putNomTorneo("SONY");
        r.nG = t[nT].getNumGolfistas();
        t[nT].getNomFichero(r.Nfichero);
        t[nT].getNomTorneo(r.nTorneo);
        fichero.write((char*)&r, sizeof(TorneoAux));
        nT++;

        t[nT].crearFichero("IBM.dat");
        t[nT].putNomTorneo("IBM");
        r.nG = t[nT].getNumGolfistas();
        t[nT].getNomFichero(r.Nfichero);
        t[nT].getNomTorneo(r.nTorneo);
        fichero.write((char*)&r, sizeof(TorneoAux));
        nT++;


    }
    else
    {
        fichero.seekg(0, ios::beg);
        while (fichero.read((char*)&aux, sizeof(TorneoAux)))
        {
            cout<<"Fichero: "<<aux.Nfichero<<", Torneo: "<<aux.nTorneo<<endl;

            //configuro cada torneo con los datos leidos
            t[nT].crearFichero(aux.Nfichero);
            t[nT].putNumGolfistas(aux.nG);
            t[nT].putNomFichero(aux.Nfichero);
            t[nT].putNomTorneo(aux.nTorneo);
            nT++;
        }
        fichero.clear();
        cout<<"Se han cargado "<<nT<<" torneos"<<endl;
        cout<< " "<<endl;
    }
    fichero.close();
    do
    {
        cout<<"CLUB DE GOLF"<<endl;
        cout<<"Torneos: "<<nT<<endl;
        cout<<"1. Listado de torneos abiertos"<<endl;
        cout<<"2. Alta Torneo"<<endl;
        cout<<"3. Elegir Torneo"<<endl;
        cout<<"4. Salir"<<endl;
        cout<<"Indique la opcion deseada: "<<endl;
        cin>>op;

        switch(op)
        {
        case 1:
        {
            cout<<"Listado torneos abiertos: "<<endl;
            if(nT==0)
            {
                cout<<"No hay torneos abiertos"<<endl;
            }
            else
            {
                for(int i=0; i<nT; i++)
                {
                    cadena nombreTorneo, nombreFichero;
                    t[i].getNomTorneo(nombreTorneo);
                    t[i].getNomFichero(nombreFichero);
                    cout<<"Torneo"<<i+1<<". "<<endl;
                    cout<<"Nombre: "<<nombreTorneo<<endl;
                    cout<<"Fichero: "<<nombreFichero<<endl;
                    cout<<""<<endl;
                    t[i].mostrar(-1);
                }
            }
            break;
        }

        case 2:
        {
            cout<<"Alta de torneo"<<endl;
            cout<<"Introduzca el nombre del torneo: ";
            cin>>aux.nTorneo;
            t[nT].putNomTorneo(aux.nTorneo);

            cout<<"Introduzca el nombre del fichero: "<<endl;
            cin>>aux.Nfichero;
            t[nT].crearFichero(aux.Nfichero);
            t[nT].putNomFichero(aux.Nfichero);

            aux.nG=0;

            fichero.open("TORNEOS.dat", ios::binary | ios::in | ios::out);
            if(fichero.fail())
            {
                cout << "Error al abrir el fichero de torneos" << endl;
                break;
            }
            fichero.seekp(0,ios::end);
            fichero.write((char*)&aux, sizeof(TorneoAux));
            fichero.close();
            nT++;

            cout<<"Datos con el nuevo torneo: "<<endl;
            for(int i=0; i<nT; i++)
            {
                t[i].getNomTorneo(nombreTorneo);
                t[i].getNomFichero(nombreFichero);
                cout<<"Torneo"<<i+1<<": "<<endl;
                cout<<"Nombre: "<<nombreTorneo<<endl;
                cout<<"Fichero: "<<nombreFichero<<endl;
                cout<<"Numero de golfistas inscritos: " <<t[i].getNumGolfistas() <<endl;
                cout<<"Golfistas inscritos: "<<endl;
            }
            break;
        }

        case 3:
        {
            if(nT==0)
            {
                cout<<"No hay torneos disponibles"<<endl;
                break;
            }

            cout<<"Seleccione un torneo: "<<endl;
            for(int i=0; i<nT; i++)
            {
                cadena nombre;
                t[i].getNomTorneo(nombre);
                cout<<i+1<<". "<<nombre<<endl;
            }

            int seleccion;
            cout<<"Opcion (1-"<<nT<<"):";
            cin>>seleccion;

            Torneo& torneoSeleccionado=t[seleccion-1];

            do
            {
                cadena nombre;
                torneoSeleccionado.getNomTorneo(nombre);
                cout<<"Torneo: "<<nombre<<endl;
                cout<<"Golfistas: "<<torneoSeleccionado.getNumGolfistas()<<endl;
                cout<<"1. Consulta de insripciones"<<endl; //por handicap
                cout<<"2. Inscripcion al torneo"<<endl;
                cout<<"3. Busqueda de una inscripcion"<<endl; //por licencia
                cout<<"4. Modificar datos de una inscripcion"<<endl; //por licencia
                cout<<"5. Eliminar una inscripcion"<<endl; //por licencia
                cout<<"6. Mostrar resultados del torneo"<<endl; //simular y mostrar clasificacion
                cout<<"7. Salir"<<endl;
                cout<<"Seleccione opcion: ";
                cin>>opTorneo;
                switch(opTorneo)
                {
                case 1:
                {
                    float hdcp;
                    cout<<"Introduzca handicap (-1 para todos)"<<endl;
                    cin>>hdcp;
                    torneoSeleccionado.mostrar(hdcp);
                    cout<<" "<<endl;
                    break;
                }

                case 2:
                {
                    Golfista g2;
                    cout << "Datos del golfista: " << endl;
                    cout << "Licencia: " <<endl;
                    cin>> g2.licencia;
                    cout << "Handicap: " <<endl;
                    cin>> g2.handicap;
                    cout << "Nombre: " <<endl;
                    cin.ignore();
                    cin.getline(g2.nombre,30);
                    cout << "Apellidos: " <<endl;
                    cin.getline(g2.apellidos,30);
                    torneoSeleccionado.insertar(g2);
                    break;
                }

                case 3:
                {
                    cadena licencia;
                    cout<<"Licencia a buscar: "<<endl;
                    cin>>licencia;
                    int pos=torneoSeleccionado.buscar(licencia);
                    if (pos!=-1)
                    {
                        cout<<"Golfista encontrado: "<<endl;
                        Golfista g=torneoSeleccionado.consultar(pos);
                    }
                    else
                    {
                        cout<<"Golfista no encontrado"<<endl;
                    }
                    break;
                }

                case 4:
                {
                    cadena licencia;
                    cout<<"Licencia a modificar: "<<endl;
                    cin>>licencia;
                    int pos=torneoSeleccionado.buscar(licencia);
                    if (pos!=-1)
                    {
                        Golfista g=torneoSeleccionado.consultar(pos);
                        cin.ignore();
                        torneoSeleccionado.modificar(g,pos);
                    }
                    else
                    {
                        cout<<"Golfista no encontrado"<<endl;
                    }
                    break;
                }

                case 5:
                {
                    cadena licencia;
                    cout<<"Licencia a eliminar: "<<endl;
                    cin>>licencia;
                    int pos=torneoSeleccionado.buscar(licencia);
                    if (pos!=-1)
                    {
                        torneoSeleccionado.eliminar(pos);
                    }
                    else
                    {
                        cout<<"Golfista no encontrado"<<endl;
                    }
                    break;
                }

                case 6:
                {
                    torneoSeleccionado.Clasificar();
                    break;
                }

                case 7:
                {
                    cout<<"Volviendo al menu club de golf"<<endl;
                    break;
                }

                default:
                {
                    cout<<"Opcion no valida"<<endl;
                    break;
                }
                }
            }
            while(opTorneo !=7);

            break;
        }
        case 4:
        {
            cout<<"Saliendo del programa"<<endl;
            break;
        }
        default:
        {
            cout<<"Opcion no valida"<<endl;
            break;
        }
        }
    }
    while(op!=4);

    return 0;
}
