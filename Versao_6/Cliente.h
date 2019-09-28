#ifndef CLIENTE_H
#define CLIENTE_H
#include "Socket.h"
#include<thread>

void recebe_mensagem(Socket *socket_cliente);
class Cliente{
    private:
        string nome;
        Socket *socket_cliente;

    public:
        Cliente(string nome){
            this->nome = nome;
        }
        void conectar(InetAddress * host, int porta){
                this->socket_cliente = new Socket(host,porta);
                //Envia os dados do cliente:
                this->socket_cliente->send(this->nome.c_str(), strlen(this->nome.c_str()));
                cout<< endl;
                string msg;

                thread t(recebe_mensagem,this->socket_cliente);

                do{
                    cout << "Me: ";
                    getline(cin, msg);
                    this->socket_cliente->send(msg.c_str(),strlen(msg.c_str()));
                }while(strcmp(msg.c_str(),"falou"));

                this->socket_cliente->close();
                cout<<"Conexao finalizada!"<<endl;
        }
        ~Cliente(){
            delete this->socket_cliente;
        }
};
void recebe_mensagem(Socket *socket_cliente){

    char mensagem[256];
    while(strcmp(mensagem,"quit")){

        memset(&mensagem,0,256);
        socket_cliente->recv(mensagem,strlen(mensagem));
        cout<<mensagem<<": ";

        memset(&mensagem,0,256);
        socket_cliente->recv(mensagem,strlen(mensagem));
        cout<<mensagem<<endl;
    }

}

#endif // CLIENTE_H
