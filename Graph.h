#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include "stdlib.h"
#include <queue>
#include <list>
#include <stack>
using namespace std;

class Arista;
class Vertice{
    Vertice *sig;
    Arista *ady;
    string nombre;
    friend class Graph;
};
class Arista {
    Arista *sig;
    Vertice *ady;
    int km;
    friend class Graph;
};
class Graph{
    Vertice *h;
    public:
    void Inicializa();
    bool Vacio();
    int Tamano();
    Vertice *getVertice(string nombre);
    void InsertaArista(Vertice *origen, Vertice *destino, int km);
    void InsertaVertice(string nombre);
    void ListaAdyacencia();
    void EliminarArista(Vertice *origen, Vertice *destino);
    void Anular();
    void EliminarVertice(Vertice *vert);
    void RecorridoEnAnchura(Vertice *origen);
    void RecorridoEnProfundidad(Vertice *origen);
    void RutaMasCorta(Vertice *origen, Vertice *destino);
};
#endif //GRAPH_H