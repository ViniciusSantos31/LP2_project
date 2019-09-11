#include <iostream>
#include "InetAddress.h"
#include "ServerSocket.h"
#include <ws2tcpip.h>
#include <winsock2.h>
#include <cstdlib>

using namespace std;

int main(){
	
	WSADATA wsadata;
	WORD wVersionRequested;
	
	int error;
	
	wVersionRequested = MAKEWORD(2, 2);
	
	error = WSAStartup(wVersionRequested, &wsadata);
	if (error != 0){
		cout << "Falha ao Iniciar\n Error: " << error << endl;
		return 1;
	}
	
	try{
		
		string host;
		string host_addr;
		
		cout << "(get by name)Digite o host: ";
		cin >> host;
		
		cout << "(get by address)Digite o endereco do host: ";
		cin >> host_addr;
		
		InetAddress *myHost = InetAddress::getLocalHost();
		InetAddress *otherHost = InetAddress::getByName(host); //byname
		InetAddress *otherHost_addr = InetAddress::getByAddress(host_addr); //byaddress
		
		cout << "My localhost" << endl;
		cout << endl <<"Meu Host: " << myHost->getHostAddress() << endl;
		cout << "Nome: " << myHost->getHostName() << endl << endl;
		
		cout << "Get by Name" << endl;
		cout << "Nome: " << otherHost->getHostName() << endl;
		cout << "Endereço: " << otherHost->getHostAddress() << endl << endl;
		
		cout << "Get by Address" << endl;
		cout << "Endereco: " << otherHost_addr->getHostAddress() << endl;
		cout << "Nome: " << otherHost_addr->getHostName() << endl;
				
	}catch (UnknownHostException &e){
		cout << e.what() << endl;
	}

		
	return 0;
}
