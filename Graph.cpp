#include "Graph.h"


void Graph::Inicializa(){
    h = NULL;
}

bool Graph::Vacio(){
    if(h == NULL){
        return true;
    }
    else{
        return false;
    }
}
int Graph::Tamano(){
    int cont = 0;
    Vertice *aux;
    aux = h;
    while(aux != NULL){
        aux = aux-> sig;
    }
    return cont;
}

Vertice *Graph::getVertice(string nombre){
    Vertice *aux;
    aux = h;
    while(aux != NULL){
        if(aux->nombre == nombre){
            return aux;
        }
        aux = aux->sig;
    }
    return NULL;
}
void Graph::InsertaVertice(string nombre){
    Vertice *nuevo = new Vertice;
    nuevo->nombre = nombre;
    nuevo->sig = NULL;
    nuevo->ady = NULL;
    if(Vacio()){
        h = nuevo;
    }
    else{
        Vertice *aux;
        aux = h;
        while(aux->sig != NULL){
            aux = aux->sig;

        }
        aux->sig = nuevo;
    }
}

void Graph::InsertaArista(Vertice *origen, Vertice *destino, int km){
    Arista *nueva = new Arista;
    nueva->km = km;
    nueva->sig = NULL;
    nueva->ady = NULL;

    Arista *aux;
    
    aux = origen->ady;
    if(aux == NULL){
        origen->ady = nueva;
        nueva->ady = destino;
    }
    else{
        while(aux->sig!=NULL){
            aux = aux->sig;
        }
        aux->sig = nueva;
        nueva->ady = destino;
    }
}
void Graph::ListaAdyacencia(){
    Vertice *Vertaux;
    Arista *Aristaux;
    Vertaux = h;
    while(Vertaux != NULL){
        cout<<Vertaux->nombre<<"->";
        Aristaux = Vertaux->ady;
        while(Aristaux != NULL){
            cout<<Aristaux->km<<" km "<<Aristaux->ady->nombre<<",";
            Aristaux = Aristaux->sig;
        }
        Vertaux = Vertaux->sig;
        cout<<endl;
    }
}

void Graph::Anular(){
    Vertice *aux;

    while(h != NULL){
        aux = h;
        h = h->sig;
        delete(aux);
    }
}

void Graph::EliminarArista(Vertice *origen, Vertice *destino){
    int band = 0;
    Arista *actual, *anterior;
    actual = origen->ady;
    if(actual == NULL){
        cout<<"El vértice origen no tiene aristas"<<endl;
    }
    else if(actual->ady == destino){
        origen->ady = actual->sig;
        delete(actual);
    }
    else{
        while(actual->ady != NULL){
            if(actual->ady == destino){
                band = 1;
                anterior->sig = actual->sig;
                delete(actual);
                break;
            }
            anterior = actual;
            actual = actual->sig;
        }
        if(band == 0){
            cout<<"Esos dos vértices no están conectados"<<endl;
        }
    }

}
void Graph::EliminarVertice(Vertice *vert){
    Vertice *actual, *anterior;
    Arista *aux;
    actual = h;
    while(actual != NULL){
        aux = actual->ady;
        while(aux != NULL){
            if(aux->ady == vert){
                EliminarArista(actual,aux->ady);
                break;
            }
            aux = aux->sig;
        }


        actual = actual->sig;
    }
    actual = h;
    if(h == vert){
        h = h->sig;
        delete(actual);
    }
    else{
        
        while(actual != vert){
            anterior = actual;
            actual = actual->sig;
        }
        anterior->sig = actual->sig;
        delete(actual);
    }
}


bool Comparacion(pair <Vertice*, int> a, pair<Vertice*, int> b){
    return a.second < b.second;
}



void Graph::Backtracking(Vertice *origen, Vertice *destino){
    string Destino;
    int KmRecorridos = 0, band, band2 = 0, necesario = 0, Recorrido = 0, suma = 0;
    Vertice *VerticeActual, *DestinoActual, *puente, *puente2;
    Arista *aux, *aux_2;
    typedef pair<Vertice*, int> VerticeKM;
    typedef pair<Vertice*, Vertice*> VerticeVertice;
    list<VerticeKM> ListaKM;
    list<int> ListaOrdenadaKm;
    list<VerticeKM> ListaOrdenada;
    stack<VerticeVertice> Pila;
    list<VerticeKM>::iterator i, j;

    ListaKM.push_back(VerticeKM(origen,0));
    ListaOrdenada.push_back(VerticeKM(origen,0));

    while(!ListaOrdenada.empty()){

        VerticeActual = ListaOrdenada.front().first;
        KmRecorridos = ListaOrdenada.front().second;
        ListaOrdenada.pop_front();
        necesario = ListaOrdenadaKm.back();

        if(VerticeActual == destino){
            cout<<"\r\n"<<"La ruta total es de: "<<KmRecorridos<<" km"<<"\r\n";
            band2 = 1;
            DestinoActual = destino;
            while(!Pila.empty()){
                cout<<DestinoActual->nombre<<"<-";
                
            
                while(!Pila.empty() && Pila.top().second != DestinoActual){
                    Pila.pop();
                }

                if(!Pila.empty()){
                    DestinoActual = Pila.top().first;
                }
                
            }
            
            
            break;
        }
        
        aux = VerticeActual->ady;
        
        while(aux != NULL){
            band = 0;
            KmRecorridos = KmRecorridos + aux->km;
           
            if(KmRecorridos < aux->km){
                KmRecorridos = aux->km;
                

            }
            for(i = ListaKM.begin(); i != ListaKM.end(); i++){ 
                if(aux->ady == i->first){
                    band = 1;
                    if(KmRecorridos < i->second){
                        (*i).second = KmRecorridos;
                        ListaOrdenadaKm.push_back(aux->km); 
                        

                        for(j=ListaOrdenada.begin(); j != ListaOrdenada.end(); j++){
                            if(j->first == aux->ady){
                                (*j).second = KmRecorridos;
                                ListaOrdenadaKm.push_back(aux->km);
                                
                                
                                
                            }
                        }
                        ListaOrdenada.sort(Comparacion);
                        Pila.push(VerticeVertice(VerticeActual, aux->ady));
                        KmRecorridos = KmRecorridos - aux->km;
                        


                    }
                }
            }
            if(band == 0){
                ListaKM.push_back(VerticeKM(aux->ady,KmRecorridos));
                ListaOrdenada.push_back(VerticeKM(aux->ady, KmRecorridos));
                ListaOrdenada.sort(Comparacion);
                Pila.push(VerticeVertice(VerticeActual,aux->ady));
                KmRecorridos = KmRecorridos - aux->km;
                
                
            }
            puente = Pila.top().second;
            Destino = puente->nombre;
            Recorrido = aux->km;
            aux = aux->sig;
            
            cout<<"\r\n"<<"De: "<<VerticeActual->nombre<< "->"<<Destino<<" hay "<<Recorrido<<" km"<<"\r\n";
            
        }
        
        
    }
    if(band2 == 0){
        cout<<"No se encontró una ruta"<<endl;
    }
    cout<<"\r\n"<<"Se necesita un tanque de: "<<necesario<<" para realizar la ruta"<<"\r\n";
}

