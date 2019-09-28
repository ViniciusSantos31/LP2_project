#include "Socket.h"
#include "ServerSocket.h"
#include "InetAddress.h"
#include "IOException.h"

#include<iostream>
#include <winsock2.h>

//Cria um server socket desamarrado de qualquer porta.
ServerSocket::ServerSocket() throw (IOException){
    this->descritor = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}
//Cria um server socket, amarrado na porta específica.
ServerSocket::ServerSocket(int port) throw (IOException){

    this->Local_Address = InetAddress::getLocalHost();

    this->descritor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(this->descritor == SOCKET_ERROR){
        throw IOException("Erro ServerSocket port ");
    }

    this->bind(port);
    this->listen();

}
//Amarra o ServerSocket ao endereço do host local e à porta específica.
void ServerSocket::bind(int port) throw (IOException){

    this->Local_Address->ip_address.sin_port = htons(port);

    if(::bind(this->descritor, (struct sockaddr *) &(*this->Local_Address).ip_address, sizeof(this->Local_Address->ip_address)) == SOCKET_ERROR){
        this->close();
        throw IOException("Erro no bind");
    }
}
 // coloca o socket para escutar as conexoes
void ServerSocket::listen()throw (IOException){

    if (::listen(this->descritor, BACKLOG_MAX) == SOCKET_ERROR){
        this->close();
		throw IOException("Erro no listen!");
	}

}
//O metodo é bloqueante enquanto a conexao é estabelecida.
Socket *ServerSocket::accept() throw (IOException){

    Socket *remote_socket = new Socket();

    int remote_length = sizeof(remote_socket->remoteAddr->ip_address);

    remote_socket->remoteAddr = InetAddress::getLocalHost();

    cout<<"Aguardando alguma conexao..."<<endl;
    remote_socket->descritor = ::accept(this->descritor, (struct sockaddr *) &(remote_socket->remoteAddr->ip_address), &remote_length);

    if(remote_socket->descritor == INVALID_SOCKET){
        this->close();
        throw IOException("Erro accept!");
    }
    return remote_socket;
}
//Retorna o número da porta que este socket está escutando.
int ServerSocket::getLocalPort(){
    return this->localPort;
}
//Fecha este socket.
void ServerSocket::close() throw (IOException){
    closesocket(this->descritor);
}
