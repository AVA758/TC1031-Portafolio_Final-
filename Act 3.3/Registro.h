#ifndef _REGISTRO_H_
#define _REGISTRO_H_

#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>

class Registro {
  private:
    //std::vector<Registro> listaRegistros;
    std::string mes, dia, horas, minutos, segundos, ip, puerto, falla;
    std::vector<std::string> meses = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    // Info struct tm    https://cplusplus.com/reference/ctime/tm/
    struct tm dateStruct;
    // Unix timestamp (segundos transcurridos desde el 1 de enero de 1970)
    time_t fechaHora;

    // Declaración para la convesión de ip a decimal en el constructor
    unsigned int ipDec;


  public:
    Registro();
    Registro(std::string _mes, std::string _dia, std::string _horas, std::string _minutos, std::string _segundos, std::string _ip, std::string _puerto, std::string _falla);
    
    std::string getAll() const;

    std::string getIp();
  
    // Sobre carga de operadores
    bool operator ==(const Registro&) const;
    bool operator !=(const Registro&) const;
    bool operator >(const Registro&) const;
    bool operator <(const Registro&) const;
    bool operator >=(const Registro&) const;
    bool operator <=(const Registro&) const;

    std::ostream& operator << (std::ostream& os);

    // Classe 
    friend std::ostream& operator<<(std::ostream& os, const Registro& reg);

};

#endif    
// w1q