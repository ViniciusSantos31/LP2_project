#include "Socket.h"
#include <iostream>
using namespace std;
//Cria um objeto socket
Socket::Socket(){
    this->descritor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
};

//Cria um socket e o conecta  IP/porta 
Socket::Socket(InetAddress *addr, int port)  throw (IOException){
    
	this->descritor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->descritor == INVALID_SOCKET){
       throw IOException("Error Init Socket");
    }
    this->remotePort = port;
   	this->remoteAddr  = addr;
    this->remoteAddr->ip_address.sin_port = htons(port);

    this->localAddr = InetAddress::getLocalHost();
    this->localAddr->ip_address.sin_port = htons(port);

    this->connect(this->remoteAddr);

    };
//Cria um socket e o conecta para um número de porta e nome de host específico
Socket::Socket(string hostName, int port) throw (IOException, UnknownHostException){
    this->remotePort = port;

    this->remoteAddr  = InetAddress::getByName(hostName);
    this->remoteAddr->ip_address.sin_port = htons(port);

    this->localAddr = InetAddress::getLocalHost();
    this->localAddr->ip_address.sin_port = htons(port);


    this->connect(this->remoteAddr);

    };


void Socket::connect(InetAddress *remoteAddr)throw (IOException, UnknownHostException){
	this->descritorRemote = ::connect(this->descritor, (struct sockaddr *) &(this->localAddr)->ip_address, sizeof(remoteAddr->ip_address));
	if (this->descritorRemote == SOCKET_ERROR){
        throw IOException("Erro ao conectar");
    }
    system("cls");
    cout << "Conectado com o Servidor: " << remoteAddr->getHostName() << endl;

};

  //Envia os bytes armazenados no array msg, no intervalo [0 size], para o socket remoto.
int Socket::send(char * msg,int size) throw (IOException){
    //int message_length = strlen(msg);
    this->descritorRemote = ::send(this->descritor, msg, size,0);
        // envia a mensagem para o serverSocket
    if (this->descritorRemote == SOCKET_ERROR)
    // contem erro se o descritorRemote == -1
    {
        throw IOException("Erro");
    }
    return this->descritorRemote;

};

    //Ler size bytes do socket remoto e armazena no array msg
int Socket::recv(char * msg,int size) throw (IOException)
{
	
    int message_length = ::recv(this->descritor, msg, size, 0);
    if(message_length == SOCKET_ERROR){
    	throw IOException("Error in message");
	}
	
    return message_length;
};
    //Retorna o endereço em que o socket está conectado
InetAddress* Socket::getInetAddress(){
    return this->remoteAddr;
};

    //Retorna o endereço local (LOCALHOST)em que o socket está "Amarrado" (BIND)
InetAddress* Socket::getLocalAddress(){
    return this->localAddr;
};
    //Retorna o número porta local em que o socket está amarrado (BIND)
int Socket::getLocalPort(){
	
	localPort = htons(this->localPort);
	return localPort;
};
    //Retorna o número da porta remota em que o socket está conectado
int Socket::getPort(){
    return this->remotePort;
};

int Socket::getDescritor(){
        return this->descritor;
}
