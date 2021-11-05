/**
*@file Graph.h
*@version 1.0
*@date 4-11-21
*@author Gustavo Gamboa
*@brief Funciones necesarias para la creación de un grafo y el backtracking correspondiente
*/

#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include "stdlib.h"
#include <queue>
#include <list>
#include <stack>
using namespace std;
/**
 * @class Arista
 * @brief Clase para las aristas del grafo 
 * 
 */
class Arista;
/**
 * @class Vertice
 * @brief clase para los vertices del grafo
 * 
 */
class Vertice{
    /**
     * @brief se mueve al siguiente vértice
     * 
     */
    Vertice *sig;
    /**
     * @brief obtiene las adyacencias del vertice
     * 
     */
    Arista *ady;
    /**
     * @brief almacena el nombre de cada vertice
     * 
     */
    string nombre;
    friend class Graph;
};
class Arista {
    /**
     * @brief pasa a la siguiente arista
     * 
     */
    Arista *sig;
    /**
     * @brief obtiene las adyacencias
     * 
     */
    Vertice *ady;
    /**
     * @brief almacena los kilómetros que se recorren entre vertice y vertice
     * 
     */
    int km;
    friend class Graph;
};
/**
 * @class Graph 
 * @brief clase en la cual se crean todas las funciones principales del grafo así como el algoritmo de backtracking.
 */
class Graph{
    /**
     * @brief atributo de tipo vertice en el cual se obtiene la cabeza del grafo
     * 
     */
    Vertice *h;
    public:
    /**
     * @brief Método que inicializa el grafo
     * 
     */
    void Inicializa();
    /**
     * @brief Método que muestra si el grafo está vacío o no
     * 
     * @return true El grafo está vacío
     * @return false el grafo tiene vértices y aristas
     */
    bool Vacio();
    /**
     * @brief Retorna el tamaño del grafo
     * 
     * @return int tamaño del grafo
     */
    int Tamano();
    /**
     * @brief Get the Vertice object
     * 
     * @param nombre nombre del vértice específico
     * @return Vertice* 
     */
    Vertice *getVertice(string nombre);
    /**
     * @brief Inserta una arista en el grafo
     * 
     * @param origen inicio
     * @param destino final
     * @param km kilometros que se quieren añadir
     */
    void InsertaArista(Vertice *origen, Vertice *destino, int km);
    /**
     * @brief Inserta un vértice en el grafo
     * 
     * @param nombre nombre que se quiere dar al nuevo vértice
     */
    void InsertaVertice(string nombre);
    /**
     * @brief Método que muestra cada vértice con su adyacencia respectiva
     * 
     */
    void ListaAdyacencia();
    /**
     * @brief Elimina una arista del grafo
     * 
     * @param origen inicio
     * @param destino final
     */
    void EliminarArista(Vertice *origen, Vertice *destino);
    /**
     * @brief Anula una adyacencia
     * 
     */
    void Anular();
    /**
     * @brief Elimina un vértice 
     * 
     * @param vert vértice que se quiere eliminar
     */
    void EliminarVertice(Vertice *vert);
    /**
     * @brief Método principal donde se obtiene la ruta más corta para llegar de un vértice a otro
     * además de generar el tanque mínimo necesario
     * 
     * @param origen inicio del recorrido.
     * @param destino final del recorrido.
     */
    void Backtracking(Vertice *origen, Vertice *destino);
};
#endif //GRAPH_H