#ifndef IP_H
#define IP_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "Registro.h"
#include "MaxHeap.h"

class IP{
  private:
    int repeticiones;
    std::string ip;

  public:
    IP();
    IP(std::string ip, int repeticiones);

    bool operator ==(const IP&) const ;
    bool operator !=(const IP&) const;
    bool operator >(const IP&) const;
    bool operator <(const IP&) const;
    bool operator >=(const IP&) const;
    bool operator <=(const IP&) const;

    friend std::ostream& operator<<(std::ostream& os, const IP& ip);


};



#endif 