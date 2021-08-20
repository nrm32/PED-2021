#include "tavlcalendario.h"

//Class TNodoAVL
/*
Llamamos por layering a los constructores de cada uno de los elementos, podriamos ponerlo de la otra manera
*/
TNodoAVL::TNodoAVL():item(),iz(),de(),fe(){
       //this->fe = 0;
}      
/*
Igual que en Tlista podemos llamar a los constructores de los otros metodos
*/
TNodoAVL::TNodoAVL(const TNodoAVL &nodo):item(nodo.item), iz(nodo.iz),de(nodo.de),fe(nodo.fe){//Da error por el constructor de TAVLCalendario
}
/*
Por el layering no hay que hacer nada, ya que llama a los destructores de forma implicita
si no deberiamos llamar a los desttuctores a mano ~TVectorCalendario(); ~TCalendario();
*/
TNodoAVL::~TNodoAVL(){
       //this->fe = 0;
}
TNodoAVL & TNodoAVL::operator=(const TNodoAVL &nodo){
       if(this == &nodo){
              return *this;
       }else{
              this->~TNodoAVL();
              this->item = nodo.item;
              this->de = nodo.de;
              this->iz = nodo.iz;
              this->fe = nodo.fe;
       }
       return *this;
}

//TCalendarioabb

 // Constructor por defecto
       TAVLCalendario::TAVLCalendario (){
              this->raiz = NULL;
       }
       
       void TAVLCalendario::Copia(const TAVLCalendario &tabbcalen){
              if(tabbcalen.raiz!=NULL){
                     TNodoAVL *aux = new TNodoAVL();
                     aux->item=tabbcalen.raiz->item;
                     this->raiz= aux;
                     aux->fe = tabbcalen.raiz->fe;
                     this->raiz->iz.Copia(tabbcalen.raiz->iz);
                     this->raiz->de.Copia(tabbcalen.raiz->de);
              }else{
                     this->raiz = NULL;
              }
       }
        // Constructor de copia
       TAVLCalendario::TAVLCalendario (const TAVLCalendario &tabbcalen){
              this->raiz = NULL;
              this->Copia(tabbcalen);
       }
        // Destructor
       TAVLCalendario::~TAVLCalendario (){
              if(this->raiz!=NULL){
                     delete this->raiz;
                     raiz=NULL;
              }
              //Se supone que no hay que hacer nada si es null ya que YA es null
       }
        // Sobrecarga del operador asignación
       TAVLCalendario & TAVLCalendario::operator=(const TAVLCalendario &tabbcalen){
              if(this!=&tabbcalen){

              (*this).~TAVLCalendario();
              this->Copia(tabbcalen);
              }

              return *this;              
       }
       bool TAVLCalendario::operator!=( const TAVLCalendario &tabb) {

              return !(*this == tabb);
       }
        // Sobrecarga del operador igualdad
       bool TAVLCalendario::operator==( const TAVLCalendario &tabb)const {

	return (this->Inorden()==tabb.Inorden());

             
       }
        // Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
       bool TAVLCalendario::EsVacio()const{
              if(this->raiz == NULL){
                     return true;
              }else{
                     return false;
              }
       }
       

        //Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
       bool TAVLCalendario::Buscar(const TCalendario &calen)const{

              if (this->EsVacio())
              {
                     return false;
              }
              else if(this->Raiz() == calen){
                     return true;
              }
              else if(calen < this->raiz->item){
                     return this->raiz->iz.Buscar(calen);
              }
              else {
                     return this->raiz->de.Buscar(calen);
              }
       }
        // Devuelve el elemento dela raíz del árbol
       TCalendario TAVLCalendario::Raiz()const{
              if (this->EsVacio()){
                     TCalendario *aux = new TCalendario();
                     return *aux;
                     //return TCalendario();
              }
              else{
                     return this->raiz->item;
              }            

       }
        // Devuelve la altura del árbol (la altura de un árbol vacío es 0)
       int TAVLCalendario::Altura(){
              //si es vacion devolvemos 0
              //si no devolvemos el maximo entre el nodo izq y nodo derecha +1
              int altura = 0;
              if(this->raiz == NULL){
                     altura = 0;
                     return altura;
              }
              altura = max(raiz->de.Altura(),raiz->iz.Altura()) + 1;

              return altura;
       }
        // Devuelve el número de nodos del árbol (un árbol vacío posee 0 nodos)
        /**
         vamos a tener que llamar a la recursividad para llamar a cada uno de los lados 
         */
       int TAVLCalendario::Nodos()const{
              if(this->EsVacio()){
                     return 0;
              }
                            
              return 1+raiz->de.Nodos()+raiz->iz.Nodos();
       }
        // Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
       int TAVLCalendario::NodosHoja(){
              int nodosHoja = 0;

              if(!this->EsVacio()){
                     if (this->raiz->de.EsVacio()&&this->raiz->iz.EsVacio())        
                     {
                            nodosHoja = 1;      
                     }else{
                            nodosHoja = (this->raiz->de.NodosHoja() + this->raiz->iz.NodosHoja()); //Funcionara??
                     }
                     
              }
              return nodosHoja;

       }
        // Devuelve el recorrido en INORDEN sobre un vector
       TVectorCalendario TAVLCalendario::Inorden()const{
              int tam = this->Nodos();
              TVectorCalendario vect(tam);
              int pos = 1;
              InordenAux(vect,pos);
              return vect;
             // TVectorCalendario recorrido(Nodos());
	      // int pos = 1;

	      // InordenAux(recorrido, pos);	
	      // return recorrido;

       }
        // Devuelve el recorrido en PREORDEN sobre un vector
       TVectorCalendario TAVLCalendario::Preorden()const{
              int tam = this->Nodos();
              TVectorCalendario vect(tam);
              int pos = 1;
              PreordenAux(vect,pos);
              return vect;
       }
        // Devuelve el recorrido en POSTORDEN sobre un vector
       TVectorCalendario TAVLCalendario::Postorden()const{
              int tam = this->Nodos();
              TVectorCalendario vect(tam);
              int pos = 1;
              PostordenAux(vect,pos);
              return vect;
       }
       // Devuelve el recorrido en NIVELESsobre un vector
       
        //Sobrecarga del operador salida
       ostream & operator<<(ostream & os, const TAVLCalendario &tabb){
              //TAVLCalendario arbol(tabb);
              os<< tabb.Inorden();
              return os;
       }
        // Suma de dos ABB
       
       /**
       algoritmo inorden ( a : arbin )
	si ( no esvacio( a ) ) entonces

	inorden ( hijoiz ( a ) )
	escribe ( raiz ( a ) )
	inorden ( hijode ( a ) )

	fsi
	falgoritmo
       */
       void TAVLCalendario::InordenAux(TVectorCalendario &vect, int &pos)const{
	       if(raiz != NULL)
              {
                     this->raiz->iz.InordenAux(vect,pos);
                     vect[pos] = Raiz();
                     pos++;
                     this->raiz->de.InordenAux(vect, pos);

              }        /*    
              if(raiz != NULL){
		raiz->iz.InordenAux(vect, pos);
		vect[pos] = raiz->item;
		pos++;
		raiz->de.InordenAux(vect, pos);*/
	       //}  
       }
       /**
       algoritmo preorden ( a : arbin )
	si ( no esvacio( a ) ) entonces

	escribe ( raiz ( a ) )
	preorden ( hijoiz ( a ) )
	preorden ( hijode ( a ) )

	fsi
	falgoritmo
        */
       void TAVLCalendario::PreordenAux(TVectorCalendario &vect, int &pos)const{
              if(raiz != NULL)
              {
              vect[pos] = raiz->item;
              pos++;              
              this->raiz->iz.PreordenAux(vect,pos);
              this->raiz->de.PreordenAux(vect, pos); 
              }
              
              
       }
       /**
       algoritmo postden ( a : arbin )
	si ( no esvacio( a ) ) entonces

	postden ( hijoiz ( a ) )
	postden ( hijode ( a ) )
	escribe ( raiz ( a ) )

	fsi
	falgoritmo
        */
       void TAVLCalendario::PostordenAux(TVectorCalendario &vect, int &pos)const{
	       if(raiz != NULL)
              {
              this->raiz->iz.PostordenAux(vect,pos);
              this->raiz->de.PostordenAux(vect, pos); 
              vect[pos] = Raiz();
              pos++;
              }
       }
/*************************************************************************************/

// /*Rotaciones*/

// void TAVLCalendario::actualizaFE(){
//        //if (this->raiz!=NULL){
//               this->raiz->fe = this->raiz->de.Altura() - this->raiz->iz.Altura(); 
//               this->raiz->iz.actualizaFE();
//               this->raiz->de.actualizaFE();
//        //}
       
// }
// void TAVLCalendario::RotacionIzquierda(){
//        TNodoAVL *izquierdo = this->raiz->iz.raiz;
//        if(this->raiz->iz.raiz->fe == 1){//ID

//               //izquierdo = raiz->iz.raiz;
//               raiz->iz.raiz = izquierdo->de.raiz->de.raiz;
//               izquierdo->de.raiz->de.raiz = raiz;
//               raiz = izquierdo->de.raiz;
//               izquierdo->de.raiz = raiz->iz.raiz;
//               raiz->iz.raiz = izquierdo;

//        }else{//II
       
//               //izquierdo = this->raiz->iz.raiz;
//               this->raiz->iz.raiz = this->raiz->iz.raiz->de.raiz;
//               izquierdo->de.raiz = this->raiz;
//               this->raiz = izquierdo;
//        }
//        actualizaFE();
// }

// void TAVLCalendario::RotacionDerecha(){
//        TNodoAVL *derecho = this->raiz;
//        if(this->raiz->iz.raiz->fe == 1){//DD
//               this->raiz = this->raiz->de.raiz;
//               derecho->de.raiz = this->raiz->iz.raiz;
//               this->raiz->iz.raiz = derecho;

//        }else{//DI
//               raiz = derecho->de.raiz->iz.raiz;
// 		derecho->de.raiz->iz.raiz = raiz->de.raiz;
// 		raiz->de.raiz = derecho->de.raiz;
// 		derecho->de.raiz = raiz->iz.raiz;
// 		raiz->iz.raiz = derecho;
//        }
//        actualizaFE();
// }
int TAVLCalendario::calculaFE()
{
    int derecha = raiz->de.Altura();
    int izquierda = raiz->iz.Altura();
    int fe = derecha - izquierda;
    return fe;
}
void TAVLCalendario::actualizaFE(){

    int fe = calculaFE();
    if(raiz->de.raiz!=NULL){
		raiz->de.raiz->fe = fe;
    }
    if(raiz->iz.raiz!=NULL){
		raiz->iz.raiz->fe = fe;
    }

}
void TAVLCalendario::equilibrar(){
    TNodoAVL *nodo;
    
    this->raiz->fe = calculaFE();
    //DERECHA
    if(this->raiz->fe > 1){
        RotacionDerecha();
        
        this->raiz->fe =calculaFE();
        actualizaFE();

    }
    //IZQUIERDA
    else if (this->raiz->fe < -1){
        RotacionIzquierda();
        this->raiz->fe =calculaFE();
        actualizaFE();

    }
}
void TAVLCalendario::RotacionIzquierda(){
       TNodoAVL *izquierdo;
       if(this->raiz->iz.raiz->fe <= 0){//ID
            /*
              //izquierdo = raiz->iz.raiz;
              raiz->iz.raiz = izquierdo->de.raiz->de.raiz;
              izquierdo->de.raiz->de.raiz = raiz;
              raiz = izquierdo->de.raiz;
              izquierdo->de.raiz = raiz->iz.raiz;
              raiz->iz.raiz = izquierdo;*/
            izquierdo = raiz->iz.raiz;
			raiz->iz.raiz = raiz->iz.raiz->de.raiz;
			izquierdo->de.raiz = raiz;
			raiz = izquierdo; 

       }else{//II
                /*
              //izquierdo = this->raiz->iz.raiz;
              this->raiz->iz.raiz = this->raiz->iz.raiz->de.raiz;
              izquierdo->de.raiz = this->raiz;
              this->raiz = izquierdo;*/
            izquierdo = raiz->iz.raiz;
			raiz->iz.raiz = izquierdo->de.raiz->de.raiz;
			izquierdo->de.raiz->de.raiz = raiz;
			raiz = izquierdo->de.raiz;
			izquierdo->de.raiz = raiz->iz.raiz;
			raiz->iz.raiz = izquierdo;
       }
}

void TAVLCalendario::RotacionDerecha(){
       TNodoAVL *derecho = this->raiz;
        if (raiz->de.raiz->fe >= 0){//DD
        /*
              this->raiz = this->raiz->de.raiz;
              derecho->de.raiz = this->raiz->iz.raiz;
              this->raiz->iz.raiz = derecho;
        */
                derecho = raiz->de.raiz;
				raiz->de.raiz = raiz->de.raiz->iz.raiz;
				derecho->iz.raiz = raiz;
				raiz = derecho;
       }else{//DI
       /*
        raiz = derecho->de.raiz->iz.raiz;
		derecho->de.raiz->iz.raiz = raiz->de.raiz;
		raiz->de.raiz = derecho->de.raiz;
		derecho->de.raiz = raiz->iz.raiz;
		raiz->iz.raiz = derecho;*/
            derecho = raiz->de.raiz;
            raiz->de.raiz = derecho->iz.raiz->iz.raiz;
            derecho->iz.raiz->iz.raiz = raiz;
            raiz = derecho->iz.raiz;
            derecho->iz.raiz = raiz->de.raiz;
            raiz->de.raiz = derecho;
       }
       
}


/************/

       
 
        // Inserta el elemento en el árbol
       bool TAVLCalendario::Insertar(const TCalendario &calen){
              bool metido = false;
              if (this->Buscar(calen))
              {
                     //No pueden haber dos calendarios iguales en el arbol
                     return false;
              }else{
                     if (this->raiz == NULL)
                     {
                            //Si no hay un nodo
                            TNodoAVL *nodo = new TNodoAVL;
                            this->raiz = nodo;
                            this->raiz->item = calen;
                            metido = true; 
                     }else{
                            if (this->raiz->item < calen)
                            {
                                   metido= this->raiz->de.Insertar(calen);
                            }if (this->raiz->item > calen)
                            {
                                   metido = this->raiz->iz.Insertar(calen);
                            }
                     }
              }
              if(metido){
                     this->equilibrar();
              }
              return metido;                     
       }
        // Borra el elemento en el árbol
       bool TAVLCalendario::Borrar(const TCalendario &calen){
              bool boorado= false;
	       if (!this->EsVacio()){
                     if(this->Buscar(calen)){
                     
                            if(this->raiz->item > calen){

                                   boorado= raiz->iz.Borrar(calen);

                            }
                            else if(this->raiz->item < calen){

                                   boorado=  raiz->de.Borrar(calen);

                            }
                            else if(this->raiz->de.EsVacio() && this->raiz->iz.EsVacio()){//no tiene hijos

                                   delete this->raiz;
                                   this->raiz = NULL;
                                   boorado= true;

                            }
                            else if(!raiz->iz.EsVacio()  && raiz->de.EsVacio()){//si es nodo hoja iz

                                   this->raiz = this->raiz->iz.raiz;
                                   boorado=  true;

                            }
                            else if(raiz->iz.EsVacio() && !raiz->de.EsVacio()){//si es nodo hoja derecho

                                   this->raiz = this->raiz->de.raiz;
                                                        
                                   boorado= true;

                            }                
                            else if(!this->raiz->iz.EsVacio() && !this->raiz->de.EsVacio()){//Tenemos los dos hijos
                                   TCalendario izquierda= this->raiz->iz.ordenar();
                                   this->raiz->item = izquierda;
                                   this->raiz->iz.Borrar(izquierda);

                            }
                     }
              }
              if (raiz!=NULL)
			equilibrar();
              
              return boorado;

       }
       

       TCalendario TAVLCalendario::ordenar() const{
	       TCalendario c;
	       if(!this->EsVacio()){
		       if(raiz->de.EsVacio())
			       return raiz->item;
		       
		       else
		       	return raiz->de.ordenar();
	       	
	       }
	       return c;
       }