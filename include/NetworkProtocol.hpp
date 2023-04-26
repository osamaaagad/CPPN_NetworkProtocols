#ifndef NETWORK_PROTOCOL_H
#define NETWORK_PROTOCOL_H
#include <vector>
#include <cstdint>
#include <string>

using namespace std;

class INetworkProtocol {
public:
virtual void connect()=0;
virtual size_t send(string)=0;
virtual string recieve()=0;
virtual void disconnect()=0;


};

#endif//NETWORK_PROTOCOL_H