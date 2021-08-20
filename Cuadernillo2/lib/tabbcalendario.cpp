#include "tabbcalendario.h"

//Class TNodoABB
/*
Llamamos por layering a los constructores de cada uno de los elementos, podriamos ponerlo de la otra manera
*/
TNodoABB::TNodoABB():item(),iz(),de(){
}      
/*
Igual que en Tlista podemos llamar a los constructores de los otros metodos
*/
TNodoABB::TNodoABB(const TNodoABB &nodo):item(nodo.item), iz(nodo.iz),de(nodo.de){//Da error por el constructor de tabbcalendario
}
/*
Por el layering no hay que hacer nada, ya que llama a los destructores de forma implicita
si no deberiamos llamar a los desttuctores a mano ~TVectorCalendario(); ~TCalendario();
*/
TNodoABB::~TNodoABB(){

}
TNodoABB & TNodoABB::operator=(const TNodoABB &nodo){
       if(this == &nodo){
              return *this;
       }else{
              this->~TNodoABB();
              this->item = nodo.item;
              this->de = nodo.de;
              this->iz = nodo.iz;
       }
       return *this;
}

//TCalendarioabb

 // Constructor por defecto
       TABBCalendario::TABBCalendario (){
              this->raiz = NULL;
       }
       
       void TABBCalendario::Copia(const TABBCalendario &tabbcalen){
              if(tabbcalen.raiz!=NULL){
                     TNodoABB *aux = new TNodoABB();
                     aux->item=tabbcalen.raiz->item;
                     this->raiz= aux;
                     this->raiz->iz.Copia(tabbcalen.raiz->iz);
                     this->raiz->de.Copia(tabbcalen.raiz->de);
              }else{
                     this->raiz = NULL;
              }
       }
        // Constructor de copia
       TABBCalendario::TABBCalendario (const TABBCalendario &tabbcalen){
              this->raiz = NULL;
              this->Copia(tabbcalen);
       }
        // Destructor
       TABBCalendario::~TABBCalendario (){
              if(this->raiz!=NULL){
                     delete this->raiz;
                     raiz=NULL;
              }
              //Se supone que no hay que hacer nada si es null ya que YA es null
       }
        // Sobrecarga del operador asignación
       TABBCalendario & TABBCalendario::operator=(const TABBCalendario &tabbcalen){
              if(this!=&tabbcalen){

              (*this).~TABBCalendario();
              this->Copia(tabbcalen);
              }

              return *this;              
       }

        // Sobrecarga del operador igualdad
       bool TABBCalendario::operator==( const TABBCalendario &tabb)const {

	return (this->Inorden()==tabb.Inorden());

             
       }
        // Devuelve TRUE si el árbol está vacío, FALSE en caso contrario
       bool TABBCalendario::EsVacio()const{
              if(this->raiz == NULL){
                     return true;
              }else{
                     return false;
              }
       }
        // Inserta el elemento en el árbol
       bool TABBCalendario::Insertar(const TCalendario &calen){
              if (this->Buscar(calen))
              {
                     //No pueden haber dos calendarios iguales en el arbol
                     return false;
              }else{
                     if (this->raiz == NULL)
                     {
                            //Si no hay un nodo
                            TNodoABB *nodo = new TNodoABB;
                            this->raiz = nodo;
                            this->raiz->item = calen;
                            return true; 
                     }else{
                            if (this->raiz->item < calen)
                            {
                                   return this->raiz->de.Insertar(calen);
                            }if (this->raiz->item > calen)
                            {
                                   return this->raiz->iz.Insertar(calen);
                            }
                     }
              }
              return false;                     
       }
        // Borra el elemento en el árbol
       bool TABBCalendario::Borrar(const TCalendario &calen){

	       if (!this->EsVacio()){
                     if(this->Buscar(calen)){
                     
                            if(this->raiz->item > calen){

                                   return  raiz->iz.Borrar(calen);

                            }
                             if(this->raiz->item < calen){

                                   return  raiz->de.Borrar(calen);

                            }
                            if(this->raiz->de.EsVacio() && this->raiz->iz.EsVacio()){//no tiene hijos

                                   delete this->raiz;
                                   this->raiz = NULL;
                                   return true;

                            }
                            if(!raiz->iz.EsVacio()  && raiz->de.EsVacio()){//si es nodo hoja iz

                                   this->raiz = this->raiz->iz.raiz;
                                   return  true;

                            }
                            if(raiz->iz.EsVacio() && !raiz->de.EsVacio()){//si es nodo hoja derecho

                                   this->raiz = this->raiz->de.raiz;
                                                        
                                   return true;

                            }                
                            if(!this->raiz->iz.EsVacio() && !this->raiz->de.EsVacio()){//Tenemos los dos hijos
                                   TCalendario izquierda= this->raiz->iz.ordenar();
                                   this->raiz->item = izquierda;
                                   this->raiz->iz.Borrar(izquierda);

                            }
                     }
              }
              return false;

       }

       TCalendario TABBCalendario::ordenar() const{
	       TCalendario c;
	       if(!this->EsVacio()){
		       if(raiz->de.EsVacio())
			       return raiz->item;
		       
		       else
		       	return raiz->de.ordenar();
	       	
	       }
	       return c;
       }

        //Devuelve TRUE si el elemento está en el árbol, FALSE en caso contrario
       bool TABBCalendario::Buscar(const TCalendario &calen)const{

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
       TCalendario TABBCalendario::Raiz()const{
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
       int TABBCalendario::Altura(){
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
       int TABBCalendario::Nodos()const{
              if(this->EsVacio()){
                     return 0;
              }
                            
              return 1+raiz->de.Nodos()+raiz->iz.Nodos();
       }
        // Devuelve el número de nodos hoja en el árbol (la raíz puede ser nodo hoja)
       int TABBCalendario::NodosHoja(){
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
       TVectorCalendario TABBCalendario::Inorden()const{
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
       TVectorCalendario TABBCalendario::Preorden()const{
              int tam = this->Nodos();
              TVectorCalendario vect(tam);
              int pos = 1;
              PreordenAux(vect,pos);
              return vect;
       }
        // Devuelve el recorrido en POSTORDEN sobre un vector
       TVectorCalendario TABBCalendario::Postorden()const{
              int tam = this->Nodos();
              TVectorCalendario vect(tam);
              int pos = 1;
              PostordenAux(vect,pos);
              return vect;
       }
       // Devuelve el recorrido en NIVELESsobre un vector
       TVectorCalendario TABBCalendario::Niveles()const{
              //int tam = this->Nodos();
              int i = 1;
              TVectorCalendario vect(this->Nodos());
              //TABBCalendario arbol(*this);
              //TNodoABB *aux;
              //TNodoABB arbol;

              //TABBCalendario temp(*this);
	       TNodoABB* aux;
	       queue<TNodoABB*> cola;

              cola.push(raiz);
              if (raiz != NULL)//CUIDAOOOOOOOOOO
              {
                     while(!cola.empty()){//mientras noesvacia(c) hacer
                            aux = cola.front();//aux = cabeza(c)
                            vect[i] = aux->item;//escribir
                            i++;
                            cola.pop();//desencolar
                            if(this->raiz->iz.EsVacio() == false){//si no es vacio iz entonces encolar
                                   cola.push((aux->iz.raiz));
                            }
                     
                            if(this->raiz->de.EsVacio() == false){//si no es vacio de entonces encolar
                                   cola.push((aux->de.raiz));
                            }
                     }
              }
              return vect;
              
       }
        //Sobrecarga del operador salida
       ostream & operator<<(ostream & os, const TABBCalendario &tabb){
              TABBCalendario arbol(tabb);
              os<< arbol.Niveles();
              return os;
       }
        // Suma de dos ABB
       TABBCalendario TABBCalendario::operator+( TABBCalendario &tabb){
              TABBCalendario suma(*this);
              TABBCalendario aux(tabb);
              TVectorCalendario vect = aux.Inorden();

              for (int i = 1; i <=vect.Tamano(); i++)
              {
                     suma.Insertar(vect[i]);
              }
              return suma;
       }
        // Resta de dos ABB
       TABBCalendario TABBCalendario::operator-( TABBCalendario &tabb){
             //TABBCalendario resta(*this);
             //TABBCalendario aux(tabb);
             //TVectorCalendario vect (this->Inorden());
              TVectorCalendario vect(Inorden());
              TABBCalendario resta;

              for (int i = 1; i <=vect.Tamano(); i++)
              {
                     TCalendario calen = vect[i];
                     if(!tabb.Buscar(calen)){
                            resta.Insertar(calen);
                     }
                     
              }
              return resta;
       }
       /**
       algoritmo inorden ( a : arbin )
	si ( no esvacio( a ) ) entonces

	inorden ( hijoiz ( a ) )
	escribe ( raiz ( a ) )
	inorden ( hijode ( a ) )

	fsi
	falgoritmo
       */
       void TABBCalendario::InordenAux(TVectorCalendario &vect, int &pos)const{
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
       void TABBCalendario::PreordenAux(TVectorCalendario &vect, int &pos)const{
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
       void TABBCalendario::PostordenAux(TVectorCalendario &vect, int &pos)const{
	       if(raiz != NULL)
              {
              this->raiz->iz.PostordenAux(vect,pos);
              this->raiz->de.PostordenAux(vect, pos); 
              vect[pos] = Raiz();
              pos++;
              }
       }