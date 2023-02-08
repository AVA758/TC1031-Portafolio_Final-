#include <cmath>
#include "ipAddress.h"

// Constructor
ipAddress::ipAddress(){
  ipString = "0.0.0.0";
  ipIndex = 0;
  outDegree = 0;
  ipValue = 0;
}

// Constructor
ipAddress::ipAddress(std::string _ip, int idx){
  ipString=_ip;
  ipIndex = idx;
  outDegree = 0;
  // Convertir IP a formato decimal
  int posInit = 0;
  int posFound = 0;
  std::string splitted;
  std::vector<std::string> results;   
  while(posFound >= 0) {
    posFound = ipString.find(".", posInit);
    splitted = ipString.substr(posInit, posFound - posInit);
    posInit = posFound + 1;
    results.push_back(splitted);
  }
  ipValue = std::stoi(results[0])*(pow(256,3)) + std::stoi(results[1])*(pow(256,2)) + std::stoi(results[2])*256 + std::stoi(results[3]);
}

// getIp
// Getter para obtener la dirección IP como string.
// Complejidad: O(1)
std::string ipAddress::getIp(){
  return ipString;
}

// getIpValue
// Getter para obtener el peso de adyacencia entre nodos.
// Complejidad: O(1)
unsigned int ipAddress::getIpValue(){
  return ipValue;
}

// getIpIndex
// Getter para obtener el índice de la dirección IP.
// Complejidad: O(1)
int ipAddress::getIpIndex(){
  return ipIndex;
}

// setOutDegree
// Setter para establecer el número de adyacencias que tiene 
// un nodo
// Complejidad: O(1)
void ipAddress::setOutDegree(int g){
  outDegree = g;
}

// addToOutDegree
// Suma 1 al número de adyacencias que tiene un nodo.
// Complejidad: O(1)
void ipAddress::addToOutDegree(){
  outDegree++;
}

// getOutDegree
// Getter para obtener el número de adyacencias que tiene 
// un nodo
// Complejidad: O(1)
int ipAddress::getOutDegree(){
  return outDegree;
}

// Sobrecarga de operadores
bool ipAddress::operator==(const ipAddress &other) const {
  return this->outDegree == other.outDegree;
}

bool ipAddress::operator!=(const ipAddress &other) const {
  return this->outDegree != other.outDegree;
}

bool ipAddress::operator>(const ipAddress &other) const {
  return this->outDegree > other.outDegree;
}

bool ipAddress::operator>=(const ipAddress &other) const {
  return this->outDegree >= other.outDegree;
}

bool ipAddress::operator<(const ipAddress &other) const {
  return this->outDegree < other.outDegree;
}

bool ipAddress::operator<=(const ipAddress &other) const {
  return this->outDegree <= other.outDegree;
}

std::ostream& operator<<(std::ostream& os, const ipAddress& ip) {
    os << ip.ipString << " " << " " << ip.outDegree; 
    return os;
}

