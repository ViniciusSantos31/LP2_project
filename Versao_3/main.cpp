#include <iostream>
#include "InetAddress.h"
#include "ServerSocket.h"
#include "Socket.h"
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
	
	char buffer[1024];
	
	try{
	

		int porta;
		Socket * socket;
		InetAddress * Serv_E;
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
					server = new ServerSocket(porta);
					socket = server->accept();
					while(true){
						socket->recv(buffer, 1024);
						if (strcmp(buffer, "falou") == 0)
							break;
						cout << buffer << endl;
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
				
				int n_i;
				
				cout << "1. Conectar por Nome\n2. Conectar por IP\n";
				cin >> n_i;
				switch (n_i){
				case 1:
					
					cout << "nome do server: ";
					cin >> ip;
					cout << "porta do server: ";
					cin >> porta;
					
					try{
						
						Serv_E = InetAddress::getByName(ip);
						socket = new Socket(Serv_E, porta);
						
						while (true){
							
							int c;
							
							
							cin.getline(buffer,1024);
							socket->send(buffer, strlen(buffer));
							if (strcmp(buffer, "falou") == 0)
								break;
							setbuf(stdin,NULL);
						}
						system("exit");
						
						
					}catch(UnknownHostException &uhe){
						
	                	cout << uhe.what() << endl;
	                	return 1;
	            	}catch(IOException &uhe){
	            		
	                	cout << uhe.what() << endl;
	                	return 1;
	            	}
	            	break;
	            case 2:
	            	
	            	
	            	cout << "IP do server: ";
					cin >> ip;
					cout << "porta do server: ";
					cin >> porta;
					
					try{
						
						Serv_E = InetAddress::getByAddress(ip);
						socket = new Socket(Serv_E, porta);
						
						
					}catch(UnknownHostException &uhe){
						
	                	cout << uhe.what() << endl;
	                	return 1;
	            	}catch(IOException &uhe){
	            		
	                	cout << uhe.what() << endl;
	                	return 1;
	            	}
	            	break;
	            	
            	break;
    			
				}
		}
				
	}catch (UnknownHostException &e){
		cout << e.what() << endl;
	}

		
	return 0;
}
