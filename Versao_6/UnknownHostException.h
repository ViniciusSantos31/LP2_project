#ifndef _UnknownHostException_
#define _UnknownHostException_

#include <exception>
#include<iostream>
using namespace std;
//Classe de exceção
class UnknownHostException : public exception{

    public:
        UnknownHostException(string ms):msg(ms){}

        virtual const char *what()const throw(){
            return msg.c_str();
        }
        virtual ~UnknownHostException()throw (){}
    private:
        string msg;
};
#endif // _UnknownHostException_
