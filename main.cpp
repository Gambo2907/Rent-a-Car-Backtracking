#include <iostream>
#include "stdlib.h"
#include "Graph.h"

using namespace std;

int main()
{
    int Vert = 7;
    Graph G;
    G.Inicializa();
    string cities[7] = {"CAR","ALA","HER","LIM","SJ","GUA","PUN"};

    for(int x = 0; x < Vert; x++){
        G.InsertaVertice(cities[x]);
    }

    srand((unsigned int)time(NULL));

    int y = 0;
    int i, j, f;
    while(y<(Vert*2)-2){
        i = rand()%Vert;
        j = rand()%Vert;
        f = (rand()%30)+1;
        if(i==j){
            continue;
        }
        G.InsertaArista(G.getVertice(cities[i]),G.getVertice(cities[j]), f);
        y++;
    }

    G.ListaAdyacencia();
    cout<<endl;

    string O,D;

    cout<<"Ingrese la ciudad de origen ";
    std::cin >> O;
    cout<<"Ingrese la ciudad de destino";
    std::cin >> D;


    if(G.getVertice(O)==NULL && G.getVertice(D)==NULL){
        cout<<"No existe"<<endl;
    }
    else{
        G.Backtracking(G.getVertice(O),G.getVertice(D));
        cout<<f<<endl;
    }
    return 0;
}
