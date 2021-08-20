#include "../include/tvectorcalendario.h"


TVectorCalendario::TVectorCalendario():error(){
    this->tamano =0;
    //c = new TCalendario[tamano];//??
    c=NULL;
}
// Constructor a partir de un tamaño
TVectorCalendario::TVectorCalendario(int dim):error(){
    if (dim>1)
    {
        this->tamano=dim;
        c=new TCalendario[tamano];
    }
    if (dim<1)
    {
        tamano=0;
        c=NULL;
    }
    

}
// Constructor de copia
TVectorCalendario::TVectorCalendario(const TVectorCalendario& nuevo):error(nuevo.error) {//no se por que es lo del error asi
    if (nuevo.tamano<1)
    {
        tamano=0;
        c=NULL;
    }
    
    this->tamano=nuevo.tamano;
    this->c=new TCalendario[tamano];
    
    if (c==NULL)
    {
        tamano=0;
        return;
    }
    for (int i = 0; i < tamano; i++)
    {
        c[i]=nuevo[i+1];//no se por que el mas 1
    }
    
}
// Destructor
TVectorCalendario::~TVectorCalendario(){
    if(c!=NULL){
        delete[]c;
    }
    tamano =0;//COMPROBAR
    c=NULL;
}
// Sobrecarga del operador asignación
TVectorCalendario & TVectorCalendario::operator=(const TVectorCalendario & vect){//igua que el libro
    if (this ==&vect)
    {
        return *this;
        
    }else{
        (*this).~TVectorCalendario();
        this->tamano =vect.tamano;
        c=new TCalendario[tamano];
        for (int i = 0; i < tamano; i++)
        {
            c[i]=vect.c[i];
        }
        return *this;
    }
}
// Sobrecarga del operador igualdad
bool TVectorCalendario::operator==(const TVectorCalendario & vect){
    int tamVect = vect.tamano;
    bool igual = true;
    if(this->tamano!=vect.tamano){
        return false;
    }
    /*for (int i = 1; i < this->tamano; i++)//Se puede quitar este for
    {
        for (int j = 0; j < tamVect; j++)
        {
            if(this->c[i-1]==vect[i]){//No tiene mucho sentido
                igual = true;
            }
            else{
                igual = false;
            }
        }
        
    }*/
    for (int i = 0; i < tamVect&& igual; i++)
        {
            if(this->c[i]==vect.c[i]){//No tiene mucho sentido
                igual = true;
            }
            else{
                igual = false;
            }
        }

    return igual;
    
}
// Sobrecarga del operador desigualdad
bool TVectorCalendario::operator!=(const TVectorCalendario & vect){
    return !(*this==vect);
}
// Sobrecarga del operador corchete (parte IZQUIERDA)
TCalendario & TVectorCalendario::operator[](int indice ){
    if(indice >=1 && indice <=this->tamano){
        return c[indice -1];
    }
    return error;
}
// Sobrecarga del operador corchete (parte DERECHA)
TCalendario TVectorCalendario::operator[](int indice) const{
    if(indice >=1 && indice <= this->tamano){
        return c[indice -1];
    }
    return error;    
}

// Cantidad de posiciones OCUPADAS (no vacías) en el vector
int TVectorCalendario::Ocupadas(){
    int ocupadas =0;
    for (int i = 0; i < this->tamano; i++)
    {
        if (c[i].EsVacio()==false)
        {
            ocupadas ++;
        }         
    }
    
    return ocupadas;

}
// Devuelve TRUE si existe el calendario en el vector
bool TVectorCalendario::ExisteCal(TCalendario & calen){
    for (int i = 0; i < this->tamano; i++)
    {
        if (c[i]==calen)
        {
            return true;
        }
        
    }
    return false;
}
// Mostrar por pantalla mensajes de TCalendario en el vector, de fecha IGUAL O POSTERIOR a la pasada
void TVectorCalendario::MostrarMensajes(int dia ,int mes ,int anyo){
    if(!comprobarFechaVector(dia,mes, anyo)){
        cout<<"[]";
    }
    else{
        cout<<"[";
        for (int i = 0; i <= this->tamano; i++)
        {
            if (this->c[i].Dia() == dia && this->c[i].Mes()== mes &&this->c[i].Anyo()== anyo)//Si el dia es igual lo sacamos
            {
                cout<<c[i]<< ", ";
                if(i>0 && i<tamano -1){
                    //cout << ", ";
                }
            }
            else if(this->c[i].Dia() >= dia && this->c[i].Mes()== mes &&this->c[i].Anyo()== anyo)//Si es dia mayor del mismo mes y anyo
            {
                cout<<c[i];
                if(i>0 && i<tamano -1){
                    cout << ", ";
                }
            }
            else if(this->c[i].Mes() >= mes && this-> c[i].Anyo()== anyo)//Si cualquier dia del mes mayor y mismo anyo
            {
                cout<<c[i];
                if(i>0 && i<tamano - 1){
                    cout << ", ";
                }
            }
            else if(this->c[i].Anyo() > anyo)//si cualquier dia y cualquier mes y mas anyo
            {
                cout<<c[i];
                if(i>0 && i<tamano -1){
                    cout << ", ";
                }
            }
            
        }
        cout<<']';
    }
}
// REDIMENSIONAR el vectorde TCalendario
bool TVectorCalendario::Redimensionar(int num){
    
    if(num<=0){
        return false;
    }
    if(num==this->tamano){
        return false;
    }
    else{
        TCalendario *aux= new TCalendario[num];
        if (num>this->tamano)
        {

            for (int i = 0; i < tamano; i++)
            {
                    aux[i]=c[i];
            }
            (*this).~TVectorCalendario();
            this->c = aux;
            tamano = num;
            return true;    
        }
        if(num<tamano) 
        {
            for (int i = 0; i < num; i++)
            {    
                aux[i]=c[i];          
            }
            (*this).~TVectorCalendario();
            this->c = aux;
            tamano = num;
            return true;
        }
    }
    return false;
}
ostream &operator<<(ostream &os,const TVectorCalendario &vector) {
    
    if (vector.tamano==0)
    {
        os<<"[]";
        return os;
    }
    
    os<<"[";
    for (int i = 1; i <= vector.tamano; i++)
    {
        if(i<=1){
            os<<"(" << i << ") " << vector[i];
        }
        else if (i==vector.tamano-1)//si es el ultimo
        {
            os<<", (" << i << ") " << vector[i];
        }
        else{
            os<<", (" << i << ") " << vector[i];
        }
    }
    
    os<<"]";
    return os;

}
bool TVectorCalendario::compruebaBisiestoVector(int anyo){
    bool bisiesto =false;

    if(anyo%4==0 && anyo%100==0 || anyo %400 ==0){
        bisiesto=true;
    }
    return bisiesto;
}

bool TVectorCalendario::comprobarFechaVector(int dia, int mes, int anyo){

    if(dia<1 ||dia>31 || mes <1 || mes >12 || anyo<1900){
        return false;
    }
    //Si es febrero y es bisiesto
    if(mes==2 && compruebaBisiestoVector(anyo)){
        if(dia>29){
            return false;//si es bisiesto y tiene mas de 29 dias
        }
    }
    if(mes==2 && !compruebaBisiestoVector(anyo)){
        if(dia>28){
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