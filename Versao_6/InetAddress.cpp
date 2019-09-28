#include "InetAddress.h"
#include <ws2tcpip.h>
#include <iostream>

using namespace std;

//Fun��o faz pesquisa por DNS e retorna IP
InetAddress * InetAddress::getByName(string host)throw (UnknownHostException){

    struct hostent *h =  gethostbyname(host.c_str());//Passa string sendo convertida para um ponteiro para um array de char
    if(h == NULL){
        throw UnknownHostException(host + " Nao encontrado!");
    }
    InetAddress *address =  new InetAddress();
     // zera a estrutura local_address
    memset(&(*address).ip_address, 0, sizeof(address->ip_address));

    memcpy(&(*address).ip_address.sin_addr.s_addr, h->h_addr_list[0],h->h_length);//Copia ip do host e coloca no addres ip host
    address->ip_address.sin_family = AF_INET;//padr�o de IPV4

    address->hostName = string(h->h_name);
    //A fun��o inet_ntoa converte um struct in_addr para uma string numerica com IP
    address->hostAddr = string(inet_ntoa(*(struct in_addr*)h->h_addr));

    return address;
}
//Fun��o retorna o endere�o local da pc
InetAddress * InetAddress::getLocalHost()throw(UnknownHostException){
    return InetAddress::getByName("localhost");
}
//Fun��o faz pesquisa por IP e retorna IP
InetAddress * InetAddress::getByAddress(string addr)throw (UnknownHostException){
    struct in_addr ip;//ip de entrada
    ip.s_addr =  inet_addr(addr.c_str());

    struct hostent *host = gethostbyaddr((const char*)&ip,sizeof(ip),AF_INET);

    if(host == NULL){
        throw UnknownHostException(addr + " Nao encontrado!");
    }
    /**Esse trecho de c�digo est� repetido, � melhor criar uma fun��o separada**/
    InetAddress *address =  new InetAddress();
     // zera a estrutura local_address
    memset(&(*address).ip_address, 0, sizeof(address->ip_address));

    memcpy(&(*address).ip_address.sin_addr.s_addr, host->h_addr_list[0],host->h_length);//Copia ip do host e coloca no addres ip host
    address->ip_address.sin_family = AF_INET;//padr�o de IPV4

    address->hostName = string(host->h_name);
    //A fun��o inet_ntoa converte um struct in_addr para uma string numerica com IP
    address->hostAddr = string(inet_ntoa(*(struct in_addr*)host->h_addr));
    return address;
}
//Fun��o retorna o nome do host
string InetAddress::getHostName(){
    return this->hostName;
}
//Fun��o retorna o IP do host
string InetAddress::getHostAddress(){
    return this->hostAddr;
}
