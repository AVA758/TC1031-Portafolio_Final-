
#include "Registro.h"


Registro::Registro() {
  mes = "";
  dia = "";
  horas = "";
  minutos = "";
  segundos = "";
  ip = "";
  puerto = "";
  falla = "";
  fechaHora = 0;
  ipDec = 0;
}

Registro::Registro(std::string _mes, std::string _dia, std::string _horas, std::string _minutos, std::string _segundos, std::string _ip, std::string _puerto, std::string _falla) {
  mes = _mes;
  dia = _dia;
  horas = _horas;
  minutos = _minutos;
  segundos = _segundos;
  ip = _ip;
  puerto = _puerto;
  falla = _falla;
  
  // Almacenar los campos en el struct tm
  dateStruct.tm_hour = std::stoi(horas);
  dateStruct.tm_min = std::stoi(minutos);
  dateStruct.tm_sec = std::stoi(segundos);
  dateStruct.tm_mday = std::stoi(dia);
  
  // Resolver problemas de compatibilidad Windows
  dateStruct.tm_isdst = 0;
  for (int i = 0; i < (int)meses.size(); i++) {
    if (meses[i] == mes) 
      dateStruct.tm_mon = i;
  }
  dateStruct.tm_year = 2023 - 1900; // Asumimos el año 2023
  // Obtener el Linux timestamp
  // https://cplusplus.com/reference/ctime/mktime/
  fechaHora = mktime(&dateStruct);
  //std::cout << "fechaHora: " << fechaHora << std::endl;

  
  // Conversión de dirección ip a unsigned int decimal
  // Método basado en explicación del profesor y en la 
  // tranformación explicada en Mkyong.com.
  std::istringstream lss(ip);
  std::string a, b, c, d;
  int i,j,k,l;
  std::getline(lss, a, '.');
  std::getline(lss, b, '.');
  std::getline(lss, c, '.');
  std::getline(lss, d);
  i = std::stoi(a);
  j = std::stoi(b);
  k = std::stoi(c);
  l = std::stoi(d); 

  ipDec = i*pow(256,3) + j*pow(256,2) + k*pow(256,1) + l*pow(256,0);
  
 
}

std::string Registro::getAll() const {
  return mes + " " + dia + " " + horas + ":" + minutos + ":" + segundos + " " + ip + ":" + puerto + " " + falla;
}

std::string Registro::getIp(){
  return ip;
}

// Comparacion de objetos de la clase Registro usando el Linux timestamp
bool Registro::operator==(const Registro &other) const {
  return this->ipDec == other.ipDec;
}

bool Registro::operator!=(const Registro &other) const {
  return this->ipDec != other.ipDec;
}

bool Registro::operator>=(const Registro &other) const {
  return this->ipDec >= other.ipDec;
}

bool Registro::operator<=(const Registro &other) const {
  return this->ipDec <= other.ipDec;
}

bool Registro::operator>(const Registro &other) const  {
  return this->ipDec > other.ipDec;
}

bool Registro::operator<(const Registro &other) const {
  return this->ipDec < other.ipDec;
}



// Sobre arga de operador de salida
std::ostream& operator << (std::ostream& os, const Registro& reg){
  os << reg.getAll();
  return os;
}