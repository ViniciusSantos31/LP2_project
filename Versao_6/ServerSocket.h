#ifndef SS_H
#define SS_H

#include "Socket.h"
#include "InetAddress.h"
#include "IOException.h"

#include<iostream>
#include <winsock2.h>
#define BUFFER_SIZE 256
#define BACKLOG_MAX 50

class ServerSocket
{
public:
    //Cria um server socket desamarrado de qualquer porta.
    ServerSocket() throw (IOException);
    //Cria um server socket, amarrado na porta específica.
    ServerSocket(int port) throw (IOException);
    //Amarra o ServerSocket ao endereço do host local e à porta específica.
    void bind(int port) throw (IOException);
    //Escuta a porta por conexões a serem feitas neste socket e as aceita, retornando um objeto socket que representa o socket remoto conectado.
    void listen()throw (IOException);
    //O metodo é bloqueante enquanto a conexao é estabelecida.
    Socket *accept() throw (IOException);
    //Fecha este socket.
    void close() throw (IOException);

    //Retorna o número da porta que este socket está escutando.
    int getLocalPort();

    ~ServerSocket();//destrutor

private:
    int descritor;
    int localPort;
    InetAddress *Local_Address;

};
#endif // SS_H
