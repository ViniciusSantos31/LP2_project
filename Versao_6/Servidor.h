#ifndef SERVIDOR_H
#define SERVIDOR_H
#include "Socket.h"
#include "ServerSocket.h"
#include <thread>
#include<vector>
#include<iostream>
using namespace std;

void nova_conexao();

static vector<Socket*> remote_sockets;

class Servidor{
    private:
        int porta;
        string nome;
        ServerSocket *server;
        //vector<Socket*>;
        vector<thread*> threads;

    public:
        friend void nova_conexao();

        Servidor(string nome, int porta){
            this->nome =  nome;
            this->porta = porta;
            this->server =  new ServerSocket(porta);

        }
        void esperando_conexao(){
            while(1){

                Socket *remote_socket = this->server->accept();// Socket aguardando conexao
                remote_sockets.push_back(remote_socket);


                this->threads.push_back(new thread(nova_conexao));
            }

        }
        ~Servidor(){
            delete this->server;
        }

};

void nova_conexao(){

        char nomeCliente[50];
        Socket *remote = remote_sockets.back();     // Pega o ultimo socket

        memset(&nomeCliente, 0, 50);
        remote->recv(nomeCliente, strlen(nomeCliente));
        cout << "\n\n" << nomeCliente <<" Esta Conectado!\n\n";
        cout << remote_sockets.size() << " Pessoa(s) Conectada(s)!" << endl;

        char mensagem[256];

        do{
            memset(&mensagem,0,256);//Limpa buffer

            remote->recv(mensagem, strlen(mensagem));

            for(int i=0; i<remote_sockets.size();i++){

                if (!(remote == remote_sockets[i])){

                    remote_sockets[i]->send(nomeCliente,strlen(nomeCliente));
                    remote_sockets[i]->send(mensagem,strlen(mensagem));
                }
            }

         }while(strcmp(mensagem,"falou"));

         remote->close();
         cout << "\n\n"<< nomeCliente << " Desconectou-se\n" <<  endl;
}

#endif // CLIENTE_H
