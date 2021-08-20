#include "../include/tcalendario.h"
//Constructor
TCalendario::TCalendario(){
    this->dia = 1;
    this->mes = 1;
    this->anyo = 1900;
    this->mensaje = NULL;
}

TCalendario::TCalendario(const TCalendario &cal){
   if(comprobarFecha(cal.dia, cal.mes, cal.anyo)){
        this->dia= cal.dia;
        this->mes = cal.mes;
        this->anyo = cal.anyo;
        if (cal.mensaje != NULL) {
            
		    this->mensaje = new char[strlen(cal.mensaje) + 1];
		    strcpy(this->mensaje, cal.mensaje);
	    } else {
		    this->mensaje = NULL;
	    }
    }else{
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        this->mensaje = NULL;
    }
    
   /*this->dia = cal.dia;
	this->mes = cal.mes;
	this->anyo = cal.anyo;
	if (cal.mensaje != NULL) {
		this->mensaje = new char[strlen(cal.mensaje) + 1];
		strcpy(this->mensaje, cal.mensaje);
	} else {
		this->mensaje = NULL;
	}*/
}

TCalendario::~TCalendario(){
        
    this->dia = 1;
    this->mes = 1;
    this->anyo = 1900;
    if(mensaje!=NULL){
        delete[] mensaje;
        mensaje=NULL;
    }else{
        this->mensaje = NULL;
    }
    //TCalendario();//No se si es fumada

    
    
}
TCalendario::TCalendario(int dia, int mes, int anyo, char* mens){
    if(anyo>=1900){
        if(comprobarFecha(dia, mes, anyo)){
            this->dia= dia;
            this->mes = mes;
            this->anyo = anyo;
            if (mens != NULL) {
		        this->mensaje = new char[strlen(mens) + 1];
		        strcpy(this->mensaje, mens);
	        } else {
		        this->mensaje = NULL;
	        }
        }else{
            this->dia = 1;
            this->mes = 1;
            this->anyo = 1900;
            this->mensaje = NULL;
        }
    }else{
        this->dia = 1;
        this->mes = 1;
        this->anyo = 1900;
        this->mensaje = NULL;
    }
    
}


bool TCalendario::EsVacio()const{
    if(dia==1&& mes==1 && anyo ==1900&& mensaje==NULL){
        return true;
    }
    return false;
}

 bool TCalendario::operator ==(const TCalendario &cal)const{
    bool igual;
    if(anyo==cal.anyo&&mes==cal.mes&&dia==cal.dia){
        if(mensaje == NULL && cal.mensaje ==NULL){
            return true;
        }
        else if(mensaje==NULL ||cal.mensaje ==NULL){
            return false;
        }
        else if(strcmp(mensaje,cal.mensaje)==0){
            return true;
        }else{
            return false;
        }
    }
    return false;   


 }
 bool TCalendario::operator !=(const TCalendario &cal)const{
    return !(*this ==cal);//Negacion del operador igualdad(libro pag 110)
    
 }

ostream& operator <<(ostream&os, const TCalendario &obj){


    if (obj.mensaje==NULL)
    {
        //si el dia es menor que 10 ponemos un 0
        
        if (obj.dia<10)
        {
            os<<"0"<<obj.dia;
        }else{
            os<<obj.dia;
        }
                
        //si el mes es menor que 10 ponemos un0
        if (obj.mes<10)
        {
            os<<"/0"<<obj.mes<<"/"<<obj.anyo<<" \"\"";//no se si la comilla simple sirve
        }
        else{
            os<<"/"<<obj.mes<<"/"<<obj.anyo<<" \"\"";//no se si la comilla simple sirve
        }

        
        return os; 

    }else{

        if (obj.dia<10){
            os<<"0"<<obj.dia<<"/";
        }else{
            os<<obj.dia<<"/";
        }
        if(obj.mes <10){
            os<<"0"<<obj.mes<<"/"<<obj.anyo<< " \""<<obj.mensaje<<"\"";
        }
        else{
            os<<obj.mes<<"/"<<obj.anyo<< " \""<<obj.mensaje<<"\"";
        }
    
    }
    
    
    //os<<obj.dia<<"/"<<obj.mes<<"/"<<obj.anyo<<" \"\""<<obj.mensaje<<" \"\"";//no se si la comilla simple sirve
    return os; 

}

TCalendario& TCalendario::operator=(const TCalendario &cal){
    //Podria hacerse con dos TCalendarios

    //Borramos el contenido del mensaje antes de nada

    this->~TCalendario();

    //Asignamos los nuevos valores de dia/mes/anyo
    dia =cal.dia;
    mes = cal.mes;
    anyo = cal.anyo;
    //Si el mensaje nuevo es null, lo chafamos
    if(cal.mensaje==NULL){
        mensaje==NULL;
    }else{

        mensaje = new char[strlen(cal.mensaje)+1];//crea un array del tamaño del mensaje pasado +1 por el \0 que añade al fginal
        strcpy(mensaje, cal.mensaje);//copiamos el mensaje
    }
    return *this;
}
bool TCalendario::ModFecha(int diaN,int mesN, int anyoN){
    if(!comprobarFecha(diaN,mesN,anyoN)){
        return false;
    }else{
        this->dia = diaN;
        this->mes = mesN;
        this->anyo = anyoN;
        return true;
    }
}

bool TCalendario::ModMensaje(char * mesage){
    if(mesage == NULL ){
        mensaje = NULL;
    }else{
        //delete[]this->mensaje;//???????????
        mensaje = new char [strlen(mesage)+1];
        strcpy(this->mensaje, mesage);
    }
    return true;

}

bool TCalendario::operator>(const TCalendario &cal)const{
    
    if(*this == cal){
        return false;
    }
    else{
        /**Caso 1 **/
        if(this->anyo >cal.anyo){
            return true;
        }
        if(this->anyo==cal.anyo && this->mes > cal.mes){
            return true;
        }
        if(this->anyo==cal.anyo && this->mes == cal.mes&& this->dia > cal.dia){
            return true;
        }
        /** Caso 2 **/
        if(this->anyo==cal.anyo && this->mes == cal.mes&& this->dia == cal.dia){
            if(this->mensaje == NULL&&cal.mensaje ==NULL){
                return false;
            }
            if(this->mensaje == NULL && cal.mensaje!=NULL){
                return false;
            }
            if(this-> mensaje!= NULL&& cal.mensaje==NULL){
                return true;
            }           
            if(strcmp(this->mensaje, cal.mensaje)<0){//la cadena 1 es mas pequeña
                return false;
            }else{
                return true;
            }            
        }
    }
    return false;
}
    
bool TCalendario::operator<(const TCalendario &cal)const{
    if(*this == cal){
            return false;
    }
    else{
        /**Caso 1 **/
        if(this->anyo < cal.anyo){
            return true;
        }
        if(this->anyo==cal.anyo && this->mes < cal.mes){
            return true;
        }
        if(this->anyo==cal.anyo && this->mes == cal.mes&& this->dia < cal.dia){
            return true;
        }
        /** Caso 2 **/
        if(this->anyo==cal.anyo && this->mes == cal.mes&& this->dia == cal.dia){
            if(this->mensaje == NULL&&cal.mensaje ==NULL){
                return false;
            }
            if(this->mensaje == NULL && cal.mensaje!=NULL){
                return true;
            }
            if(this-> mensaje!= NULL&& cal.mensaje==NULL){
                return false;
            }           
            if(strcmp(this->mensaje, cal.mensaje)<0){//la cadena 1 es mas pequeña
                return true;
            }else{
                return false;
            }            
        }
    }
    return false;
}

// Sobrecarga del operador: SUMA de fecha + un número de dias;
TCalendario TCalendario::operator+(int cont){
    if(cont<0){
        return (*this);
    }
    TCalendario aux(*this);
    while (cont!=0){
        //cout<<cont<<"-->"<<aux<<endl;
        aux++;
        cont --;
        //(*this ++);//no se puede modificar el objeto, hay que crear un auxiliar
        
    }
    //*this=aux;//??
    return (aux);
}
// Sobrecarga del operador: RESTA de fecha - un número de dias;
TCalendario TCalendario::operator-(int cont){
    TCalendario temp(*this);
	while(cont!=0){
		temp--;
		cont--;
	}

	if(!comprobarFecha(temp.dia, temp.mes, temp.anyo)){
		temp.dia = 1;
		temp.mes = 1;
		temp.anyo = 1900;
        delete[] temp.mensaje;
		temp.mensaje = NULL;
	}
	return temp;
}

// Modifica la fecha incrementándola en un dia (con postincremento);
TCalendario TCalendario::operator++(int num){//hay que poner el (*this)
    TCalendario temp (*this);
    if(mes == 2){
        if(dia ==29 && compruebaBisiesto(anyo)){
                dia = 1;
                mes ++;             
        }else if(dia==28 && !compruebaBisiesto(anyo)){
                dia = 1;
                mes++;
        }
        else{
            dia++;
        }        
    }
    else if(mes == 12 ){
        if (dia == 31){
            dia = 1;
            anyo++;
            mes = 1;
            
        }else{
            dia++;
        }
    }
    else if(mes ==4|| mes ==6 || mes==9 || mes==11){
        if(dia==30){
            mes ++;
            dia=1;
        }
        else{
            dia ++;
        }
    }
    else if(mes ==1|| mes ==3 || mes==5 || mes==7 ||mes ==8 ||mes ==10 ){
        if(dia==31){
            dia=1;
            mes ++;
            
        }
        else{
            dia ++;
        }
    }
    
    
    //cout<<"-->"<< *this<<endl;
    return temp;
}
// Modifica la fecha incrementándola en un dia (con preincremento);
TCalendario & TCalendario::operator++(){

    TCalendario temp (*this);
    if(mes == 2){
        if(dia ==29 && compruebaBisiesto(anyo)){
                dia = 1;
                mes ++;             
        }else if(dia==28 && !compruebaBisiesto(anyo)){
                dia = 1;
                mes++;
        }
        else{
            dia++;
        }        
    }
    else if(mes == 12 ){
        if (dia == 31){
            dia = 1;
            anyo++;
            mes = 1;
            
        }else{
            dia++;
        }
    }
    else if(mes ==4|| mes ==6 || mes==9 || mes==11){
        if(dia==30){
            mes ++;
            dia=1;
        }
        else{
            dia ++;
        }
    }
    else if(mes ==1|| mes ==3 || mes==5 || mes==7 ||mes ==8 ||mes ==10 ){
        if(dia==31){
            dia=1;
            mes ++;
            
        }
        else{
            dia ++;
        }
    }


    
    //cout<<"-->"<< *this<<endl;
    return (*this);//creo que esto se puede

}


TCalendario & TCalendario::operator--(){

    dia --;
    if(dia==0){
        mes--;
        if(mes==0){
            mes =12;
            anyo--;
        }
        if(mes == 2 && !compruebaBisiesto(this->anyo)){
            dia = 28;
        }
        else if(mes ==2 && compruebaBisiesto(this->anyo)){
            dia =29;
        }
        else if(mes ==1 ||mes ==3||mes== 5||mes ==7 ||mes==8||mes ==10||mes==12){
            dia =31;
        }
        else{
            dia =30;
        }
    }
    if (!comprobarFecha(dia,mes,anyo)){
        dia=1;
        mes=1;
        anyo=1900;
        delete[] mensaje;
        mensaje=NULL;
    }
    

    return *this;
}
TCalendario  TCalendario::operator--(int num){
    TCalendario temp(*this);
    dia --;
    if(dia==0){
        mes--;
        if(mes==0){
            mes =12;
            anyo--;
        }
        if(mes == 2 && !compruebaBisiesto(this->anyo)){
            dia = 28;
        }
        else if(mes ==2 && compruebaBisiesto(this->anyo)){
            dia =29;
        }
        else if(mes ==1 ||mes ==3||mes== 5||mes ==7 ||mes==8||mes ==10||mes==12){
            dia =31;
        }
        else{
            dia =30;
        }
    }
     if (!comprobarFecha(dia,mes,anyo)){
        dia=1;
        mes=1;
        anyo=1900;
        delete[] mensaje;
        mensaje=NULL;
    }
    return temp;
}



bool TCalendario::compruebaBisiesto(int anyo){
    bool bisiesto =false;

    if(anyo%4==0 && anyo%100==0 || anyo %400 ==0){
        bisiesto=true;
    }
    return bisiesto;
}

bool TCalendario::comprobarFecha(int dia, int mes, int anyo){

    if(dia<1 ||dia>31 || mes <1 || mes >12 || anyo<1900){
        return false;
    }
    //Si es febrero y es bisiesto
    if(mes==2 && compruebaBisiesto(anyo)){
        if(dia>=30){
            return false;//si es bisiesto y tiene mas de 29 dias
        }
    }
    if(mes==2 && !compruebaBisiesto(anyo)){
        if(dia>=29){
            return false;//si no bisiesto y tiene mas de 28 dias
        }
    }
    //si el mes es Abril(4) o Junio(6) o Septiembre (9) o noviembre(11) y tiene mas de 30 dias falso
    if(mes == 4 || mes == 6||mes ==9 || mes ==11){
        if(dia > 30){
            return false;
        }
    }
    return true;
}

