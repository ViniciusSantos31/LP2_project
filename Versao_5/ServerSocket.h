#include "Socket.h"
#include "IOException.h"
#include <ws2tcpip.h>
#include<winsock2.h>
#include <iostream>

#define MAX_CONECTIONS 3

class ServerSocket
{
public:
    //Cria um server socket desamarrado de qualquer porta.
    ServerSocket() throw (IOException);
    //Cria um server socket, amarrado na porta espec�fica.
    ServerSocket(int porta) throw (IOException);
    //Amarra o ServerSocket ao endere�o do host local e � porta espec�fica.
    void bind(int porta) throw (IOException);
    //Escuta a porta por conex�es a serem feitas neste socket e as aceita, retornando um objeto socket que representa o socket remoto conectado.
    void listen() throw (IOException);
    //O metodo � bloqueante enquanto a conexao � estabelecida.
    Socket *accept() throw (IOException);
    //Fecha este socket.
    void close() throw (IOException);

    //Retorna o n�mero da porta que este socket est� escutando.
    int getLocalPort();

    ~ServerSocket();//destrutor

private:
	
	InetAddress *Local_Address;
    int descritor;
    int localPort;

};
