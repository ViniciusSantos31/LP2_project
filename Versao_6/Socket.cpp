#include "Socket.h"
#include "InetAddress.h"
#include "IOException.h"
#include<string>
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#define BUFFER_SIZE 128
#include<iostream>

using namespace std;

//Só cria um socket vazio
Socket::Socket(){
    this->descritor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}
//Cria e conecta socket a um servidor
Socket::Socket(InetAddress *addr , int port) throw (IOException){
    this->descritor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//Cria socket

    if(this->descritor == INVALID_SOCKET){
        this->close();
        throw IOException("Erro ao criar o socket");
    }
    this->remotePort = port;//Porta para se conecter
    this->remoteAddr = addr;//InetAddress para se conecter
    this->remoteAddr->ip_address.sin_port = htons(port);

    this->localAddr = InetAddress::getLocalHost();//InetAddress local
    this->localAddr->ip_address.sin_port = htons(port);
    //Conecta socket a um servidor
    int aux = connect(this->descritor, (struct sockaddr*)&(this->remoteAddr->ip_address),sizeof(this->remoteAddr->ip_address));

    if (aux == SOCKET_ERROR){
        this->close();
        throw IOException("Erro ao conectar");
    }
}
//Cria um socket e o conecta para um número de porta e nome de host específico.
Socket::Socket(string hostName, int port) throw (IOException, UnknownHostException){

    this->descritor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//Cria socket

    if(this->descritor == INVALID_SOCKET){
        this->close();
        throw IOException("Erro ao criar o socket");
    }

    this->remotePort = port;
    this->remoteAddr = InetAddress::getByName(hostName);
    this->remoteAddr->ip_address.sin_port = htons(port);

    this->localAddr = InetAddress::getLocalHost();
    this->localAddr->ip_address.sin_port = htons(port);

    //Conecta socket a um servidor
    int aux = connect(this->descritor, (struct sockaddr *)&(this->remoteAddr->ip_address),sizeof(this->remoteAddr->ip_address));

    if (aux == SOCKET_ERROR){
        this->close();
        throw IOException("Erro ao conectar");
    }
}
//Envia os bytes armazenados no array msg, no intervalo [0 size], para o socket remoto.
int Socket::send(const char* msg, int size) throw (IOException){
    // envia a mensagem para o servidor
    int aux = ::send(this->descritor, msg, strlen(msg), 0);
    if (aux == SOCKET_ERROR){
        throw IOException("Erro no Send");
    }
    return aux;
}
//Ler size bytes do socket remoto e armazena no array msg.
int Socket::recv(char *msg, int size) throw (IOException){
    // recebe a mensagem do cliente
    int message_length = ::recv(this->descritor, msg, BUFFER_SIZE, 0);

    if (message_length == SOCKET_ERROR){
        throw IOException("Erro no recv");
    }
    return message_length;
}
//Envia a string no array msg para o socket remoto.
void Socket::operator<<(char* msg) throw (IOException){
    if(Socket::send(msg,strlen(msg))){
        throw IOException("Erro no send");
    }
}
//Ler a string do socket remoto e armazena no array msg.
void Socket::operator>>(char* msg) throw (IOException){
    if(Socket::recv(msg,strlen(msg))){
        throw IOException("Erro no recv");
    }
}
//Encerra o socket
void Socket::close() throw (IOException){
    closesocket(this->descritor);
}
//Retorna o endereço em que o socket está conectado.
InetAddress * Socket::getInetAddress(){
    return this->remoteAddr;
}
//Retorna o endereço local em que o socket está amarrado.
InetAddress * Socket::getLocalAddress(){
    return this->localAddr;
}
//Retorna o número porta local em que o socket está amarrado.
int Socket::getLocalPort(){
    return this->localPort;
};
//Retorna o número da porta remota em que o socket está conectado.
int Socket::getPort(){
    return this->remotePort;
};

Socket::~Socket(){
    delete localAddr;
    delete remoteAddr;
}

int Socket::getDescritor(){
    return this->descritor;
}




