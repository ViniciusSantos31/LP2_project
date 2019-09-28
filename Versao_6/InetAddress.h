#ifndef INETADDRESS_H
#define INETADDRESS_H

#include <string>
#include<winsock2.h>
#include "UnknownHostException.h"

using namespace std;

class InetAddress{
    public:
        //Retorna o endereço IP (objeto InetAddress) de um host, dando o nome do host.
    	static InetAddress *getByName(string host) throw (UnknownHostException);
    	//Retorna o endereço IP (objeto InetAddress), dando o endereço IP bruto.
    	static InetAddress *getByAddress(string addr) throw (UnknownHostException);
    	//Retorna o endereço IP (objeto InetAddress) do host local.
    	static InetAddress *getLocalHost() throw (UnknownHostException);

    	//Fornece o nome do host
    	string getHostName();
    	//Fornece o endereço IP do host
    	string getHostAddress();

    	~InetAddress(){}//destrutor

    private:
        InetAddress(){}
        string hostName;
        string hostAddr;
        sockaddr_in ip_address;

        friend class Socket;
        friend class ServerSocket;
};

#endif // INETADDRESS_H
