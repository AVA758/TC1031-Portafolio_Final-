# include "IP.h"

IP::IP(){
  this->ip="";
  this->repeticiones = 0;

}

IP::IP(std::string ip, int repeticiones){
  this->ip = ip;
  this->repeticiones = repeticiones;

}

bool IP::operator==(const IP &other) const {
  return this->repeticiones == other.repeticiones;
}

bool IP::operator!=(const IP &other) const {
  return this->repeticiones != other.repeticiones;
}

bool IP::operator>=(const IP &other) const {
  return this->repeticiones >= other.repeticiones;
}

bool IP::operator<=(const IP &other) const {
  return this->repeticiones <= other.repeticiones;
}

bool IP::operator>(const IP &other) const{
  return this->repeticiones > other.repeticiones;
}

bool IP::operator<(const IP &other) const {
  return this->repeticiones < other.repeticiones;
}



std::ostream& operator << (std::ostream& os, const IP& ip){
  os << ip.ip << " " << ip.repeticiones;
  return os;
}


