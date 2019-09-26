#include <iostream>
#include "InetAddress.h"
#include "ServerSocket.h"
#include "Socket.h"
#include <ws2tcpip.h>
#include <winsock2.h>
#include <cstdlib>
#include <thread>
#include <string>
#include <vector>

using namespace std;


char buffer_send[512];
char buffer_recv[1024];

void cliente_t(void * buffer, void * clientes){
	
		Socket * socket;
		
		vector<Socket*> clientes = (vector<Socket*> *) clientes;
		char * buffer = (char*)buffer;
		
		for (int i = 0; i < clientes.size(); i++){
			
			socket = clientes[i];
			cout << socket->getDescritor() << endl; 
			
			socket->send(buffer, 1024);

		}
	
}

void recv_t(Socket * s){
	
	
	while(true){
	
		char buffer[1024];
		s->recv(buffer, 1024);
		
		cout << buffer << endl;
	
	}
}



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
	
	char buffer[1024];
	char * buffer2[1024];
	
	try{
	
		
		int porta;
		
		InetAddress * Serv_;
		Socket * socket;
		int menu;
		char ip[30];
		
		
		cout << "1. Servidor\n2. Cliente\n";
		cin >> menu;
		
		switch (menu){
		
			case 1:
				
				cout << "Qual a porta: ";
				cin >> porta;
				
				try{
					
					ServerSocket * server;
					vector<Socket*> clientes;
					
					if (porta > 8888 || porta < 8000){
						
						cerr << "Por favor insira uma porta entre 8000 e 8888" << endl;
						return 0;
						
					}
					
					server = new ServerSocket(porta);
					
					while(true){
					
						socket = server->accept();
						
						clientes.push_back(socket);
						
						socket->recv(buffer, 1024);
						
						thread cliente_(cliente_t, socket, clientes, buffer);
						
						cout << buffer << endl;
						
						if (strcmp(buffer, "falou") == 0){
							
							break;
							
						}
					}		
					
				}catch(UnknownHostException &e){
					
                	cout << e.what() << endl;
                	return 1;
				
				}catch (IOException &ioe){
					
					cout << ioe.what() << endl;
					return 1;
					
				}
				cout<<endl;
				system("pause");
				break;
				
			case 2:
				
				cout << "IP do server: ";
				cin >> ip;
				cout << "porta do server: ";
				cin >> porta;
				
				try{
					
					Serv_ = InetAddress::getByAddress(ip);
					socket = new Socket(Serv_, porta);
					
					thread recv_(recv_t, socket);
					
					while(true){
						
						memset(buffer, 0, 1024);
						cin.getline(buffer, 1024);
						
						socket->send(buffer, 1024);
						
						if (strcmp(buffer, "falou") == 0){
							break;
						}
					}	
					
				}catch(UnknownHostException &uhe){
					
                	cout << uhe.what() << endl;
                	return 1;
                	
            	}catch(IOException &uhe){
            		
                	cout << uhe.what() << endl;
                	return 1;
                	
			 	}
		}
				
	}catch (UnknownHostException &e){
		cout << e.what() << endl;
	}
	
	return 0;
}
