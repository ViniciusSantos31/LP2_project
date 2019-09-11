#include "ServerSocket.h"
#include "InetAddress.h"
#define MAX_CONECTIONS 3

ServerSocket::ServerSocket()throw (IOException){
	
	this->descritor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->descritor == -1) //Se o descritor for -1 deu erraldo a bagaça...kkk
	{
		throw IOException("error");
	}
}

ServerSocket::ServerSocket(int porta) throw (IOException){
	
	this->Local_Address = InetAddress::getLocalHost();
	
	this->descritor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if (descritor == -1)
	{
		throw IOException("error");
	}
	
	this->bind(porta);
	

}

void ServerSocket::bind(int porta) throw (IOException){ //amarra a porta

	this->Local_Address->ip_address.sin_port = htons(porta); //preenche o campo da porta do meu endereco local
	
	//esses 2 pontos antes do bind() significa que é pra usar a funcao do C que esta na biblioteca do winsock
	if (::bind(this->descritor, (struct sockaddr *)&(*this->Local_Address).ip_address, sizeof(this->Local_Address->ip_address)) == -1) //se o bind retorna -1 fudeo
/*	if (::bind(meu_socket, (SOCKADDR *)&sockaddr_in, sizeof(sockaddr_in) == -1) ISSO SERIA EM C
	meu_socket = descrtior da classe
	sockaddr_in = this->Local_Address.ip_address
	*/
	{
		throw IOException("Nao consegui dar o no");
	}	

}

void ServerSocket::listen() throw (IOException){
	
	if (::listen(this->descritor, MAX_CONECTIONS) == -1){
		
		throw IOException("To moco");
	}
}
