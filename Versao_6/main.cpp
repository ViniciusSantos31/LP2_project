#include <iostream>
#include<string.h>
#include <winsock.h>
#include <thread>
#include "Cliente.h"
#include "Servidor.h"

using namespace std;

int main(){
    Cliente * cliente = NULL;
    Servidor * servidor = NULL;
    InetAddress * ip;
    int op, port;
    string host, msg, nomeCliente;

    cout << "1-Server\n2-Cliente"<<endl;
    cin>>op;

    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        WSACleanup();
        cout<<"Error at WSAStartup()"<<endl;
    }
    try{
        switch(op){
            case 1:
                cout <<"Porta para o servidor: ";
                cin>>port;
                servidor = new Servidor("LOCALHOST",port);
                servidor->esperando_conexao();
            break;
            case 2:
                cout << "Nome do cliente: ";
                cin >> nomeCliente;
                cliente = new Cliente(nomeCliente);
                cout <<"IP do servidor: ";
                cin>>host;
                ip = InetAddress::getByAddress(host);
                cout <<"Porta do servidor: ";
                cin>>port;
                cin.ignore();
                cliente->conectar(ip,port);
            break;
        }
    }catch(IOException &ex){
        WSACleanup();
        cout<<ex.what()<<endl;
    }
    WSACleanup();
    return 0;
}
