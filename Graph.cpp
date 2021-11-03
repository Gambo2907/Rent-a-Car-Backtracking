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
int Graph::Tamaño(){
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
            cout<<Aristaux->ady->nombre<<"->";
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

void Graph::RecorridoEnAnchura(Vertice *origen){
    int band, band2;
    Vertice *actual;
    queue<Vertice*> cola;
    list<Vertice*> lista;
    list<Vertice*>::iterator i;
    cola.push(origen);

    while(!cola.empty()){
        band = 0;
        actual = cola.front();
        cola.pop();

        for(i = lista.begin(); i != lista.end(); i++){
            if(*i == actual){
                band = 1;
            }
        }
        if(band == 0){
            cout<<actual->nombre<<",";
            lista.push_back(actual);

            Arista *aux;
            aux = actual->ady;
            while(aux != NULL){
                band2 = 0;
                for(i = lista.begin(); i != lista.end(); i++){
                    if(aux->ady == *i){
                        band2 = 1;
                    }
                }
                if(band2 == 0){
                    cola.push(aux->ady);
                }
                aux = aux->sig;
            }
        }

    }

}
void Graph::RecorridoEnProfundidad(Vertice *origen){
    int band, band2;
    Vertice *actual;
    stack<Vertice*> pila;
    list<Vertice*> lista;
    list<Vertice*>::iterator i;
    pila.push(origen);
    while(!pila.empty()){
        band = 0;
        actual = pila.top();
        pila.pop();

        for(i=lista.begin(); i != lista.end(); i++){

            if(*i == actual){
                band = 1;
            }
        }
        if(band == 0){
            cout<<actual->nombre<<",";
            lista.push_back(actual);

            Arista *aux;
            aux = actual->ady;

            while(aux != NULL){
                band2 = 0;
                for(i=lista.begin(); i != lista.end(); i++){
                    if(*i == aux->ady){
                        band2 = 1;
                    }
                }
                if(band == 0){
                    pila.push(aux->ady);
                }
                aux = aux->sig;
            }
        }

    }
}

bool Comparación(pair <Vertice*, int> a, pair<Vertice*, int> b){
    return a.second < b.second;
}

void Graph::PrimeroElMejor(Vertice *origen, Vertice *destino){
    int CostoActual = 0, band, band2 = 0;
    Vertice *VerticeActual, *DestinoActual;
    Arista *aux;
    typedef pair<Vertice*, int> VerticeCosto;
    typedef pair<Vertice*, Vertice*> VerticeVertice;
    list<VerticeCosto> ListaCostos;
    list<VerticeCosto> ListaOrdenada;
    stack<VerticeVertice> Pila;
    list<VerticeCosto>::iterator i, j;

    ListaCostos.push_back(VerticeCosto(origen,0));
    ListaOrdenada.push_back(VerticeCosto(origen,0));

    while(!ListaOrdenada.empty()){

        VerticeActual = ListaOrdenada.front().first;
        CostoActual = ListaOrdenada.front().second;
        ListaOrdenada.pop_front();

        if(VerticeActual == destino){
            
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
            CostoActual = CostoActual + aux->km;
            for(i = ListaCostos.begin(); i != ListaCostos.end(); i++){
                if(aux->ady = i->first){
                    band = 1;
                    if(CostoActual < i->second){
                        (*i).second = CostoActual;

                        for(j=ListaOrdenada.begin(); j != ListaOrdenada.end(); j++){
                            if(j->first = aux->ady){
                                (*j).second = CostoActual;
                            }
                        }
                        ListaOrdenada.sort(Comparación);
                        Pila.push(VerticeVertice(VerticeActual, aux->ady));
                        CostoActual = CostoActual - aux->km;

                    }
                }
            }
            if(band = 0){
                ListaCostos.push_back(VerticeCosto(aux->ady,CostoActual));
                ListaOrdenada.push_back(VerticeCosto(aux->ady, CostoActual));
                ListaOrdenada.sort(Comparación);
                Pila.push(VerticeVertice(VerticeActual,aux->ady));
                CostoActual = CostoActual - aux->km;
            }

            aux = aux->sig;
        }


    }
    if(band2 == 0){
        cout<<"No se encontró una ruta"<<endl;
    }
}