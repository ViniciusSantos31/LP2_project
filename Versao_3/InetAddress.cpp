#include "InetAddress.h"
#include <iostream>
#include <ws2tcpip.h>

using namespace std;

InetAddress *InetAddress::getByAddress(string hostAddr) throw (UnknownHostException){
	
	struct in_addr addr;
	
	addr.S_un.S_addr = inet_addr(hostAddr.c_str());
	hostent *he = gethostbyaddr((const char*)&addr, sizeof(addr), AF_INET);
	
	if (he == NULL){
		throw UnknownHostException(hostAddr + " nao e um enderceo conhecido!");
	}	
	
	return InetAddress::criar(he);
}

InetAddress *InetAddress::criar(struct hostent *he){
	
	InetAddress * address = new InetAddress();
    memset(&(*address).ip_address, 0, sizeof(address->ip_address));

    memcpy(&(*address).ip_address.sin_addr.s_addr, he->h_addr_list[0], he->h_length);
    address->ip_address.sin_family = AF_INET;

    address->hostAddr = string(inet_ntoa(*(struct in_addr*)he->h_addr));
    address->hostName = string(he->h_name);

    return address;
	
}

InetAddress *InetAddress::getLocalHost() throw (UnknownHostException){
	
	return InetAddress::getByName("localhost");
	
}

InetAddress *InetAddress::getByName(string host) throw (UnknownHostException){
	
	hostent *he = gethostbyname(host.c_str());

	if (he == NULL){
	throw UnknownHostException(host + " nao e um endereco conhecido!");
	}
	return InetAddress::criar(he);
	
}

string InetAddress::getHostAddress(){
	return this->hostAddr;
} 

string InetAddress::getHostName(){
	return this->hostName;
}
