//TCalendario

#ifndef TCALENDARIO_
#define TCALENDARIO_

#include <iostream>
#include <string.h>

using namespace std;


class TCalendario{
    //Clases amigas
    friend ostream& operator <<(ostream &, const TCalendario&);//el const es por que no vamos a modificar el dato
 
    private:
        int dia;
        int mes;
        int anyo;
        char * mensaje;
        bool compruebaBisiesto(int);
        bool comprobarFecha(int, int, int);

    public:

        //Constructores y destructor;

        //Contructor por defecto
        TCalendario();
        TCalendario(int dia, int mes, int anyo, char * mens);
        TCalendario(const TCalendario &);
        ~TCalendario();
        // Sobrecarga del operador asignación
        TCalendario & operator=(const TCalendario &);

        // Sobrecarga del operador: SUMA de fecha + un número de dias;
        TCalendario operator+(int);
        // Sobrecarga del operador: RESTA de fecha - un número de dias;
        TCalendario operator-(int);
        // Modifica la fecha incrementándola en un dia (con postincremento);
        TCalendario operator++(int);
        // Modifica la fecha incrementándola en un dia (con preincremento);
        TCalendario & operator++();

        // Modifica la fecha decrementándola en un dia (con postdecremento);
        TCalendario operator--(int);
        // Modifica la fecha decrementándola en un día (con predecremento);
        TCalendario & operator--();
        // Modifica la fecha
        bool ModFecha (int, int, int);
        // Modifica el mensaje
        bool ModMensaje(char *);
        // Sobrecarga del operador igualdad;
        bool operator ==(const TCalendario &)const;
        // Sobrecarga del operador desigualdad;
        bool operator !=( const TCalendario &)const;
        // Sobrecarga del operador >; (ver ACLARACIÓN sobre ORDENACIÓN)
        bool operator>(const TCalendario &)const;
        // Sobrecarga del operador <; (ver ACLARACIÓN sobre ORDENACIÓN)
        bool operator<(const TCalendario &)const;
        //TCalendario vacío
        bool EsVacio()const ;
        // Devuelve el día del calendario;
        int Dia(){
            return this->dia;
            //return dia;
        }
        // Devuelve el mes del calendario;
        int Mes(){
            return this->mes;
            //return mes;
        }
        // Devuelve el año del calendario;
        int Anyo(){
            return this->anyo;
            //retrurn anyo;
        }
        // Devuelve el mensaje del calendario;
        char *Mensaje(){
            return this->mensaje;
            //return mensaje;
        }
};


#endif
