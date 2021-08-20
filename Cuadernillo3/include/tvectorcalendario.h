#include <iostream>
#include <string.h>
#include "tcalendario.h"
using namespace std;

#ifndef TVECTORCALENDARIO_
#define TVECTORCALENDARIO_





class TVectorCalendario{
    friend ostream& operator <<(ostream &, const TVectorCalendario&);//el const es por que no vamos a modificar el dato

    private:
        TCalendario *c;
        int tamano;
        TCalendario error;
        bool compruebaBisiestoVector(int);
        bool comprobarFechaVector(int, int, int);
    public:
        // Constructor por defecto
        TVectorCalendario();
        // Constructor a partir de un tamaño
        TVectorCalendario(int);
        // Constructor de copia
        TVectorCalendario(const TVectorCalendario &);
        // Destructor
        ~TVectorCalendario();
        // Sobrecarga del operador asignación
        TVectorCalendario & operator=(const TVectorCalendario &);
        // Sobrecarga del operador igualdad
        bool operator==(const TVectorCalendario &);
        // Sobrecarga del operador desigualdad
        bool operator!=(const TVectorCalendario &);
        // Sobrecarga del operador corchete (parte IZQUIERDA)
        TCalendario & operator[](int);
        // Sobrecarga del operador corchete (parte DERECHA)
        TCalendario operator[](int) const;
        // Tamaño del vector (posiciones TOTALES)
        int Tamano(){
            return tamano;
        }
        // Cantidad de posiciones OCUPADAS (no vacías) en el vector
        int Ocupadas();
        // Devuelve TRUE si existe el calendario en el vector
        bool ExisteCal(TCalendario &);
        // Mostrar por pantalla mensajes de TCalendario en el vector, de fecha IGUAL O POSTERIOR a la pasada
        void MostrarMensajes(int,int,int);
        // REDIMENSIONAR el vectorde TCalendario
        bool Redimensionar(int);
};


#endif
