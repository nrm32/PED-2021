//tnodo
//tlistpos
//tlista

#include "../include/tlistacalendario.h"

//Clase TNodo

    TNodoCalendario::TNodoCalendario(){
        //Si ponemos en la linea de la declaracion :c() estariamos llamando por la composion al 
        // constructor por defecto de Tcalendario, ya que en se lo estamos pasando por valor
        //al no ponerlo el compilador lo llama por defecto igualmente por lo que no hace falta que lo
        // pongamos en este construcor;
        this->siguiente = NULL;
        
    }
    TNodoCalendario::TNodoCalendario(const TNodoCalendario &nodo):c(nodo.c){
        // A diferencia del anterior, en este constructor si que tenemos que ponerlo en la linea de declaracion
        // ya que sino llamariamos al constructor por defecto y no serviria de nada que le pasemos un nodo
        //por lo que tendremos que poner ....): c(nodo.c){..}
        //De esta forma estaremos llamando al constructor de copia de TCalendario
        this->siguiente=NULL;

    }
    TNodoCalendario::~TNodoCalendario(){
        //De la misma manera que en el constructor por defecto en el ddestructor no hace falta que llamemos al
        //desturctor de c , ya que por defecto se llama automaticamente
        this->siguiente == NULL;
        //c.~TCalendario();//Esto creo que se puede quitar

    }
    TNodoCalendario& TNodoCalendario::operator= (const TNodoCalendario &nodo){//puede que se necesite un const denro
        if(this!=&nodo){
            (*this).~TNodoCalendario();   
            this->siguiente = nodo.siguiente;//Esto non se si debe ser null o asi
            this->c = nodo.c;

        }
        
        return *this;
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////
    //En esta clase no hace falta ponerlo en la declaracion ya que no lo lo pasamos por valor (*)
    //por lo que lo haremos de la misma manera que siempre
    TListaPos::TListaPos(){
        
        this->pos =NULL;
    }
        // Constructor de copia
    TListaPos::TListaPos(const TListaPos &lista){
        this->pos= lista.pos;
    }
        // Destructor
    TListaPos::~TListaPos(){
        this->pos =NULL;

    }
        // Sobrecarga del operador asignación
    TListaPos & TListaPos::operator=(const TListaPos &lista){
        if(this!=&lista){
            (*this).~TListaPos();
            this->pos=lista.pos;
        }

        return *this;
    }
        // Sobrecarga del operador igualdad
    bool TListaPos::operator==(const TListaPos &lista){
        if(this->pos ==lista.pos ){
            return true;
        }else{
            return false;
        }

    }
        // Sobrecarga del operador desigualdad
    bool TListaPos::operator!=(const TListaPos &lista){
        return !(*this==lista);
    }
        // Devuelve la posición siguiente
    TListaPos TListaPos::Siguiente(){
        //Como TListaPos tiene un Nodo como atributo, creamos uno auxiliar para poder enviarlo
        //De tal modo que le asignamos la posicion siguiente(cogido de la clase TNodoCalendario)
        //Para devolver ese valor. Es posible que sirva tambien el retornarn this->pos->siguiente

        TListaPos lista;
        lista.pos= this->pos->siguiente;
        return lista;
    }
        // Posición vacía
    bool TListaPos::EsVacia(){
        //Comprobamos que no sea null y devolvolemos true o false
        if(this->pos != NULL){
            return false;
        }
        return true;
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////


        // Constructor por defecto
    TListaCalendario::TListaCalendario(){
        this->primero=NULL;
    }
        // Constructor de copia
    TListaCalendario::TListaCalendario(const TListaCalendario &listaCal){
        //TListaCalendario();
        //this->primero = NULL;
        //this->~TListaCalendario();
        //*this=listaCal;
        this->primero = NULL;
       
        TListaPos aux = listaCal.Primera();
        //(*this).~TListaCalendario();
        while (!aux.EsVacia())
        {
            this->Insertar(aux.pos->c);
            aux = aux.Siguiente();
        }  
    }
        //Destructor
    TListaCalendario::~TListaCalendario(){
        //como tenemos que poner todas las posiciones a null, para de esa forma borrar el contenido de la lista
        //Creamos una lista a la que le asignamos la primera posicion que tenemos, despues vamos pasando por cada elemento
        //de esa lista de posiciones asignandole a la posicion el valor siguioente, de tal modo que llegara un pomento que el 
        //Valor de esa posicion sera null y no existira ya esa lista
        TNodoCalendario *listaPos = primero;
        TNodoCalendario *aux;

        //if(listaPos!=NULL){
        for (int i = 0; listaPos!=NULL; i++)
        {
            aux = listaPos;
            listaPos =listaPos->siguiente;//Esto es lo que hace que en algun punto se llegue a NUlL
            delete aux;
        }
        this->primero =NULL;            
        //}    

    }
        // Sobrecarga del operador asignación
    TListaCalendario & TListaCalendario::operator=(const TListaCalendario &lista){//Posible falta de un const
        //Comprobamos que no sean la misma lista y en caso de serlo devolvemos la que ya teniamos
        //En caso contrario eliminamos lo que teniamos y asignamos el primer elelento de la lista a this
        if(this == &lista){
            return *this;
        }
        else{
            TNodoCalendario *aux = lista.primero;
            (*this).~TListaCalendario();
            while (aux!= NULL)
            {
                this->Insertar(aux->c);
                aux = aux->siguiente;
            }
        }
        return *this;
    }
        // Sobrecarga del operador igualdad
    bool TListaCalendario::operator==(const TListaCalendario &lista){
        //Como tenemos que comprobar cada uno de los nodos que ha y el la lista creamos dos ndos auxiliares que usaremos
        //para cambiar al siguiente.
        //Primero comprobamos que no sean sean la misma posicion de memoria, isno comprobamoss la longitud de ambas listas
        //Si no con el for comprobamos ino por uno los nodos , y en caso de ser iguales le asignamos el valor del
        //siguiente nodo, si salimos del for por que son iguales todos los nodos, devolvemos true
        TListaPos aux1 =Primera();
        TListaPos aux2=lista.Primera();
        bool iguales = false;

            if(this->Longitud()!=lista.Longitud()){
                return false;
            }else{
                while (!aux1.EsVacia()){
                                        
                    if(aux1.pos->c !=aux2.pos->c){
                        return false;
                    }
                    aux1 = aux1.Siguiente();
                    aux2 = aux2.Siguiente(); 
                    iguales = true;
                }
                return true;                
            }
        return iguales;
    }
        //Sobrecarga del operador suma
    TListaCalendario TListaCalendario::operator+ ( const TListaCalendario &lista)const{
        TListaCalendario *nueva = new TListaCalendario(*this); //creamos una auxilar que le damos el valor para despues hacer la suma
        TNodoCalendario *actual;//, *anterior;
        actual = lista.primero;
        for(int i =0;actual!=NULL;i++){//triple rico
            nueva->Insertar(actual->c);
            actual = actual->siguiente;
        }
        
        return *nueva;
    }
        //Sobrecarga del operador resta
    TListaCalendario TListaCalendario::operator- (const TListaCalendario &lista)const{
        TListaCalendario *nueva = new TListaCalendario(*this); //creamos una auxilar que le damos el valor para despues hacer la suma
        TNodoCalendario *actual;//, *anterior;
        actual = lista.primero;
        while(actual!=NULL){//triple rico
            nueva->Borrar(actual->c);
            actual = actual->siguiente;
        }
        
        return *nueva;
    }
    // Inserta el elemento en la posición que le corresponda dentro de la lista
    bool TListaCalendario::Insertar(const TCalendario &calendarioEX){
        bool hecho = false;
        TNodoCalendario *nodoAux;
        nodoAux= this->primero;
        TNodoCalendario *nuevoCal =new TNodoCalendario();

            if(Buscar(calendarioEX))return false;

            if(this->primero == NULL){
                this->primero = new TNodoCalendario();
                primero->c = calendarioEX;
                return true;
            }

            if (this->primero->c > calendarioEX )
            {
                nuevoCal->c = calendarioEX;
                nuevoCal->siguiente =primero;
                primero = nuevoCal;
                //primero = primero->siguiente;//Invent
                return true;
            }
            //Si el siguiente elemento es null (solo hay un elemento en la lista)
            if (this->primero->siguiente == NULL){
                //Si el calendario que nos pasan es mayor que el que tenemos
                if(calendarioEX > nodoAux->c){//primero->c
                    nuevoCal->c=calendarioEX;
                    primero->siguiente =nuevoCal;
                    //hecho =true;
                    return true;
                }else{
                    nuevoCal->c = calendarioEX;
                    nuevoCal->siguiente= primero;
                    primero = nuevoCal;
                    //primero = primero->siguiente;
                    //hecho= true;
                    return true;
                }
            }
            while(nodoAux != NULL){
                if(calendarioEX > nodoAux->c){
                    if(nodoAux->siguiente == NULL || calendarioEX < nodoAux->siguiente->c){
                        nuevoCal->c= calendarioEX;
                        nuevoCal->siguiente=nodoAux->siguiente;
                        nodoAux->siguiente=nuevoCal;
                        //nodoAux->c= calendarioEX;
                        //nodoAux->siguiente
                        hecho=true;
                        return hecho;
                    }
                }
                nodoAux = nodoAux->siguiente;

            }
            return false;
        }
        // Busca y borra el elemento
    bool TListaCalendario::Borrar(const TCalendario &calendario){
        
        TNodoCalendario *aux = primero;
        TNodoCalendario *borra;
        bool borrado = false;
        while (aux!=NULL)
        {
            if(aux->siguiente != NULL && aux->siguiente->c == calendario){//Este va debajo
                    //borra = aux->siguiente;
                    aux->siguiente = aux->siguiente->siguiente;
                    //delete borra;
                    return true;
            }
            else if (primero->c == calendario){
                //borra = this->primero;
                primero = primero->siguiente;
                //delete borra;                
                return true;                
            }
            else{
                aux= aux->siguiente;
            }    
        }
        return borrado;
    }
    // Borra el elemento que ocupa la posición indicada
    bool TListaCalendario::Borrar (const TListaPos &listacal){
        //Creamos un calendario dada la posicion que se nos pasa
        //Con ese calendario se lo enviamos a la funcion de borrar un calendario
        TCalendario calen = Obtener(listacal);
        bool borrado = Borrar(calen);
        return borrado;
    }
    //Borra todos los Calendarios con fecha ANTERIOR a la pasada.
    bool TListaCalendario::Borrar(int dia ,int mes,int anyo){
            
        TNodoCalendario *aux = primero;
        TCalendario *calendario = new TCalendario(dia, mes, anyo, NULL);
       
        bool borrado = false;
        while (aux!=NULL)
        {
            calendario->ModMensaje(aux->c.Mensaje());
            
            if (aux->c == *calendario)
                break;
            if(aux->siguiente != NULL && primero->c.Dia() == dia 
                && primero->c.Mes()==mes && primero->c.Anyo()==anyo){//Este va debajo
                    
                    aux->siguiente = aux->siguiente->siguiente;                    
            }
            else if (primero->c < *calendario){
                
                primero = this->primero->siguiente;
                aux = aux->siguiente;
                
                borrado = true;
            }
            else{
                    aux= aux->siguiente;
                }    
        }
        return borrado;
    }
        // Devuelve true si la lista está vacía, false en caso contrario
    bool TListaCalendario::EsVacia()const{
        if (this->primero == NULL)
        {
            return true;
        }
        return false;         

    }
        // Obtiene el elemento que ocupa la posición indicada
    TCalendario TListaCalendario::Obtener(const TListaPos &posicion)const{
        //Como nos pasan una posicion creamos una posicion a la que le pasamos la primera posicion
        //Vamos comprobando 1 por 1 si es la posicion buscada, en caso de serlo devovemos el ccalendadrio que hay
        //en esa posicion, si asignamos a la lista auxiliar la sifuiente posicion
        //Si no hemos encontrado nada, devolvemos un calendario vacio;
         
        
        TNodoCalendario *actual;
        actual= primero;
        while (actual!=NULL)
        {
            if (posicion.pos == actual)
            {
                return actual->c;
            }
            actual = actual->siguiente;
        }
        
        TCalendario noEncontrado;
        return noEncontrado;            
    }
        // Devuelve true si el Calendario está en la lista.
    bool TListaCalendario::Buscar(const TCalendario &calendario){
        //Creamoss un nodo para poder ir comparar nodos, a ese nodo le pasamos el calendario como c, de modo
        //que el nodo que usaremos para comparar tendra el calendario a buscar
        //Despues creamos un puntero(ojala saber por que) de TNodo al que le pasamos la primera posicion de la liista
        //Vamos comprobado si es iogual o no, en caso de no serlo asignamos al nodo auxiliar el siguiente nodo
        TNodoCalendario nodo ;
        nodo.c =calendario;
        TNodoCalendario *aux = this->primero;

        for (int i = 0; i < this->Longitud(); i++){
            if(aux->c==calendario){
                return true;
            }
            aux =aux->siguiente;
        }
        return false;     
    }
        // Devuelve la longitud de la lista
    int TListaCalendario::Longitud()const{
        //creamos una posicion a la que le pasamos la posicion primera de la lista
        //despues mientras que no sea la ultima(posicion vacia) vamos actualizando esa 
        //posicion a la siguiente e incrementando el contador
        int longitud=0;
        TListaPos posi=Primera();
        //posi=this->Primera();
        while(!posi.EsVacia()){
            posi=posi.Siguiente();
            longitud++;
        }
        return longitud;
    }
        // Devuelve la primera posición en la lista
    TListaPos TListaCalendario::Primera()const{
        //Como necesitamos devolver una posicion creamos una posicion y le asignamos el valor del primero de la lista
        TListaPos posi;
        if (this->primero == NULL)
        {
            return posi;
        }
        posi.pos = this->primero;
        return posi;
    }
        // Devuelve la última posición en la lista
    TListaPos TListaCalendario::Ultima()const{
        //Al igual que en longiud creamos una posicion y le pasamos la primera posicion de la lista
        //despues mientras que el contador sea menor que la lingitud total de la lista vamos pasando
        //la siguiente 'casilla' a la posicion creada, y retornamos la ultima que hemos pasado
        TListaPos posi = Primera();
        for (int i = 1; posi.pos!=NULL && posi.pos->siguiente!=NULL; i++)//posible que se inicialice a 1
        {
            posi= posi.Siguiente();
        }         
        return posi;
    }
        // Suma de dos sublistas en una nueva lista
        TListaCalendario TListaCalendario::SumarSubl (int I_L1, int F_L1, TListaCalendario & L2, int I_L2, int F_L2)const{
           

            /* 
            I_L1-->Inicio de la primera sublista
            F_L1-->Fin de la primera sublista
            I_L2-->Inicio de la segunda sublista
            F_L2-->Fin de la segunda sublista
            this-->Para la primera sublista
            L2  -->Para la segunda sublista
            
            Si la F_L1 > this->longitud()

                F_L1 = subLista1longitud;

            Si la F_L2 > subLista2.longitud()

                F_L2 = L2.longitud();
            
            Si I_L1 o I_L2 <= 0
            
                I_L1 = 1
                    o
                I_L2 = 1
            
            Si I_L1 > F_L1
            
                lista vacia
            
            Si I_L2 > F_L2
            
                lista vacia
           
            */

           
            TListaCalendario subLista1 = (*this);
            TListaCalendario subLista2 = (L2);
            TListaCalendario nuevaLista;
            bool lista1Valida =false;
            bool lista2Valida = false;

            

            if(F_L1 > subLista1.Longitud()){//Si la F_L1 > sublista1->longitud()

                F_L1 = subLista1.Longitud();
            }
           
            if(F_L2 > subLista2.Longitud()){//Si la F_L2 > sublista1->longitud()

                F_L2 = subLista2.Longitud();
            }
            if (I_L1 <= 0)//S el inicio es menor que 1
            {
                I_L1 = 1;
            }
            if (I_L2 <= 0)//Si el inicio es menor que 1
            {
                I_L2 = 1;
            }
            
            
            if(I_L1> F_L1 ){//Si no es un rango logico
                //creamos una lista vacia
                subLista1.~TListaCalendario();
                //TListaCalendario nueva;
                lista1Valida= true;
                subLista1.primero= NULL;//CHAPUZA
                //cout<< "---->I-->"<<subLista1<<"<-----"<<endl;
            }


            if( I_L2 > F_L2){//Si no es un rango logico
                //creamos una lista vacia
                subLista2.~TListaCalendario();
                lista2Valida = true;
                subLista2.primero = NULL;
            }              
            
            
            

            nuevaLista = subLista1.ExtraerRango(I_L1, F_L1) + subLista2.ExtraerRango(I_L2,F_L2) ;
            return nuevaLista;


            

        }
        // Extraer un rango de nodos de la lista
    TListaCalendario TListaCalendario::ExtraerRango (int n1, int n2){
        TListaCalendario listaNueva;
        TNodoCalendario *aux, *aux2;
        
        aux = this->primero;
        //Si n1 > n2: devolverá una lista VACÍA sin modificar a la llamante, pues los límites no engloban elemento alguno.
        if(n1>n2){
            return listaNueva;
        }
        //Si n1 es menor o igual a 0: se seleccionan sólo los elementos contenidos entre la posición 1 de la lista y n2 .
        if (n1<=0){
            n1=1;
        }

        //Si n2 sobrepasa la longitud de la lista invocante “por exceso”: se seleccionan 
        //sólo los elementos contenidos entre n1 y la longitud de la lista.
        if(n2 > this->Longitud()){
            n2 = this->Longitud();
        }


        int tam = n2 - n1;
        int i =1;
        while (i <= n2)
        {
            if(i>=n1){
                
                listaNueva.Insertar(aux->c);
                aux2 = aux->siguiente;
                this->Borrar(aux->c);
                aux = aux2;
            }if(i<n1){
                aux = aux->siguiente;
            }
            
            i++;                
        }
        
        return listaNueva;
    }
    ostream & operator<<(ostream &os,const TListaCalendario &lista){
        TListaPos posiciones;
        posiciones = lista.Primera();
        os<<"<";
        if(lista.EsVacia()){
            os<<">";
            return os;
        }
        for (int i = 0; i < lista.Longitud(); i++)
        {
            if(i==0){
                os<<lista.Obtener(posiciones);
                posiciones = posiciones.Siguiente();
            }
            else{
                os<<" ";
                os<<lista.Obtener(posiciones);
                posiciones = posiciones.Siguiente();
            }
        }
        os<<">";
        return os;
    }
