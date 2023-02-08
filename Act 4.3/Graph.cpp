#include "Graph.h"

// Constructor
Graph::Graph() {
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
  IPobt.clear();
}



// Destructor
Graph::~Graph() {
  numNodes = 0;
  numEdges = 0;
  adjList.clear();
  IPobt.clear();
}



// Split
// Aplicado en la lectura del archivo, sirve para separar 
// los números en las líneas y así poder asignar
// correctamente los valores a sus variables.
// Complejidad: O(n)
void Graph::split(std::string line, std::vector<int> & res) {
    size_t strPos = line.find(" ");
    size_t lastPos = 0;
    while (strPos != std::string::npos) {
      res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
      lastPos = strPos + 1;
      strPos = line.find(" ", lastPos);
    }
    res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}



// findIpIndex
// Ecuentra el índice del nodo de la dirección IP
// Complejidad: O(1)
int Graph::findIpIndex(std::string ipString) {
  ipAddress tmpIp(ipString, 0);
  std::map<unsigned int, ipAddress>::iterator it;
  int ipIndex = -1;
  it = mapIP.find(tmpIp.getIpValue());
  if(it != mapIP.end())
    ipIndex = it->second.getIpIndex();
  return ipIndex;
}



// loadGraph
// Lee el archivo de registros de la bitacora y acomoda 
// los valores en las líneas para ejectuar las demás funciones
// Complejidad: O(n^2)
void Graph::loadGraph(std::string fileName) {
  std::string line, ip1, ip2, peso; 
  int i = 0;
  std::ifstream file(fileName);
  if (!file.good()) {
    file.close();
    throw std::invalid_argument("File not found");
  }
  else {
    while(std::getline(file,line)) { 
      if (i == 0) {
        std::vector<int> res;
        split(line, res);
        numNodes = res[0];
        numEdges = res[1];
        // Reservar memoria para los renglones de la lista de adyacencia
        // Nodos son uno basados (renglon 0 no sera usado)
        adjList.resize(numNodes + 1);
        IPobt.resize(numNodes + 1);
        // Declarar una lista ligada vacia de pares (vertice, peso)
        // para cada renglon y se almacena en el vector
        for (int k = 1; k <= numNodes; k++) {
          LinkedList<std::pair<int, int>> tmpList;
          adjList[k] = tmpList;
        }
      }
      else if (i > 0 && i <= numNodes) {
        ipAddress tmpIP(line, i);
        mapIP.insert({tmpIP.getIpValue(), tmpIP});
        IPobt[i] = tmpIP.getIp();
        //std::cout << tmpIP << std::endl;
      }
      else if (i > numNodes) {
        std::size_t found = line.find(":", 15);
        ip1 = line.substr(15, found-15);
        std::size_t found2 = line.find(" ", found+1);
        std::size_t found3 = line.find(":", found2+1);
        ip2 = line.substr(found2, found3-found2);
        std::size_t found4 = line.find(" ", found3+1);
        std::size_t found5 = line.find(" ", found4+1);
        peso = line.substr(found4, found5-found4);
        // Crear arista ip1 a ip2 con un peso
        ipAddress tmpIP1(ip1, 0);
        //ipAddress tmpIP2(ip2, 0);
        int ip1Index = findIpIndex(ip1); 
        int ip2Index = findIpIndex(ip2);
        if (ip1Index != -1 && ip2Index != -1) {
          adjList[ip1Index].addLast({ip2Index, stoi(peso)});
          mapIP[tmpIP1.getIpValue()].addToOutDegree();
        }
        else {
          throw std::out_of_range("Incorrect IPs in the edge");
          file.close();
        }
      }
      i++;
    }
    file.close();
  }
}



// printGraph
// Imprime el grafo según su número de nodos, vértices, 
// adyacencias.
// Complejidad: O(n^2)
void Graph::printGraph() {
  std::cout << "numNode: " << numNodes << std::endl;
  std::cout << "numEdges: " << numEdges << std::endl;
  std::cout << "Adjacency List" << std::endl;
  for (int nodeU = 1; nodeU <= numNodes; nodeU++) {
    std::cout << "vertex " << nodeU << ": ";
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      std::cout << "{" << par.first << "," << par.second << "} ";
      ptr = ptr->next;
    }
    std::cout << std::endl;
  }
}



// gradosIPs
// Imprime en archivo .txt la dirección IP y su número de
// apariciones en la bitácora.
// Complejidad: O(n)
void Graph::gradosIPs() {
  std::ofstream grados;
  grados.open("grados_ips.txt");
  if (!grados.good()) {
    grados.close();
    throw std::invalid_argument("File not found");
  }
  else {
    grados<<"Grado de salida de cada nodo del grafo (IP, grado de        salida): "<<std::endl;
    // fijar la capacidad de tu maxheap
    mayoresGrados.setCapacity((int)mapIP.size()+1);
    std::map<unsigned int, ipAddress>::iterator it;
    for (it = mapIP.begin(); it != mapIP.end(); it++) {
      grados << it->second << std::endl;
      mayoresGrados.push(it->second);
    }
  grados.close();
  }
}



// cincoMayores
// Abre un archivo para poder registrar los IPS con mayores 
// salidas hacia otros nodos.
// Manda a llamar al top del heap ordenado, y una vez que es // impreso en el archivo, se elimina ese top, y vuelve a 
// inciar el ciclo hasta imprimir las 5 direcciones IP 
// con mayor número de adyacencias.
// Complejidad: O(n)
void Graph::cincoMayores(){
  std::ofstream cincoM;
  cincoM.open("mayores_grados_ips.txt");
  if (!cincoM.good()) {
    cincoM.close();
    throw std::invalid_argument("File not found");
  }
  else {
    std::pair<std::string, int> guardar;
    cincoM<<"5 IPs con mayor grado de salida" << std::endl;
    cincoM << std::endl;
    cincoM << "(IP, grado de salida)" <<std::endl;

    std::string bootMaster = mayoresGrados.top().getIp();
    int bootMasterIndex = mayoresGrados.top().getIpIndex();
    std::cout << std::endl;
    std::cout << "Bootmaster: " << std::endl;
    std::cout << bootMaster << std::endl;

    for (int i = 0; i <= 4; i++){
      cincoM << mayoresGrados.top().getIp() << " " << mayoresGrados.top().getOutDegree() << std::endl;
      mayoresGrados.pop();
    }
    cincoM.close();
    dijkstra(bootMasterIndex); 
  }
} 



// dijkstra
// Imprime la distancia que tiene un nodo del grafo del nodo 
// bootmaster, que en este caso viene siendo el nodo con mayor
// número de adyacencias (ver función cincoMayores())
// Complejidad: O((|V|+|E|)*log(|V|))
void Graph::dijkstra(int v) {
  // Crear una priority queue del STL de C++
  // https://www.geeksforgeeks.org/implement-min-heap-using-stl/
  std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
  // vector de distancias con el resultado del algoritmo
  std::vector<int> dist(numNodes+1, INF);
  // Insertar el nodo de origen v en el priority queue (pares dist, vertice)
  // e inicializar su distancia a cero
  pq.push(std::make_pair(0, v)); // pares (dist, vertice)
  dist[v] = 0;
  // Mientras el priority queue no este vacio
  while (!pq.empty()) {
    // Extraemos un vertice del priority queue
    int nodeU = pq.top().second; // pares (dist, vertice)
    pq.pop();
    // Obtener los vecinos del vertice nodeU
    NodeLinkedList<std::pair<int, int>> *ptr = adjList[nodeU].getHead();
    while (ptr != nullptr) {
      std::pair<int, int> par = ptr->data;
      int nodeV = par.first; // nodeV es vecino de nodeU
      int peso = par.second; // peso de la arista (nodeU, nodeV)
      // Si hay un camino mas corto hacia nodeV pasando por nodeU
      if (dist[nodeV] > dist[nodeU] + peso) {
          // Updating distance of v
          dist[nodeV] = dist[nodeU] + peso;
          pq.push(std::make_pair(dist[nodeV], nodeV));
      }
      ptr = ptr->next;
    }
  }
  // Imprimir las distancias mas cortas entre v y todos los nodos del grafo
  std::ofstream BM;
  BM.open("distancia_bootmaster.txt");
  if (!BM.good()) {
    BM.close();
    throw std::invalid_argument("File not found");
  }
  BM << "Vertex\tDistance from source" << std::endl;
  int mayor = 0;
  int mayorIdx = -1;
  for (int i = 1; i <= numNodes; i++){
    if (dist[i] != INF) {
      if (mayor < dist[i]) {
        mayor = dist[i];
        mayorIdx = i;
      }
      BM << IPobt[i]   << "\t" << dist[i] << std::endl;
    }
    else{
      BM << IPobt[i]  << "\tINF" << std::endl;
    }
  } 

  std::cout << std::endl;
  std::cout << "Dirección IP que requiere mayor esfuerzo de ataque del boot master: " << std::endl;
  
  std::cout << IPobt[mayorIdx] << std::endl;

  BM.close();
}

