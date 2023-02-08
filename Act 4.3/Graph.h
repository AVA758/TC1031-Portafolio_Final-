#ifndef __GRAPH_H_
#define __GRAPH_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "LinkedList.h"
#include "ipAddress.h"
#include <queue>
#include "maxHeap.h"
#include <utility> 
#include "QueueLinkedList.h"
#define INF 0x3f3f3f3f

class Graph {
  private:
    int numNodes;
    int numEdges;

    // Lista de adyacencia (vector de listas de pares (verticeDestino, peso))
    std::vector<LinkedList<std::pair<int,int>>> adjList;

    // map - permite buscar el indice (numero de vertice) que corresponde a una ip
    // La llave es una ip en formato decimal, almacena un objeto ipAddress
    // ver metodo findIpIndex
    std::map<unsigned int, ipAddress> mapIP;

    std::vector<std::string> IPobt;

    // Maxheap
    MaxHeap<ipAddress> mayoresGrados;


    void split(std::string line, std::vector<int> & res);
    int findIpIndex(std::string ipString);
    

  public:
    Graph();
    ~Graph();
    void loadGraph(std::string fileName);

    void printGraph();

    void printIPs();

    void gradosIPs();

    void cincoMayores();

    void dijkstra(int v);

    
    
};

#endif // __GRAPH_H_