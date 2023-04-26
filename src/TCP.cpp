#include "TCP.hpp"
#include "sockets.h"

using namespace std;

 unique_ptr<TCPClient> TCPClient::_instance;
 once_flag TCPClient::_flag;
 size_t TCPClient::_socketId;

unique_ptr<TCPClient> TCPClient::getInstance(){

    if(_instance == nullptr){
        call_once(_flag,[](){_instance.reset(new TCPClient());});
    }
    _socketId = ( socketCreate() );
    return std::move(_instance);
}

 void TCPClient::connect() {


    socketConnect( _socketId ,_ip.c_str(),_port , socket_network_t::E_SOCKET_TCP);

}
 size_t TCPClient::send(string message) {
   return socket_Send(_socketId, message.c_str() , message.length());
}
  string TCPClient::recieve() {


    string readVec;
    char data[512];
    
     socket_Receive(_socketId,data ,sizeof(data));

    readVec.assign(string(data));

    return readVec;
}

  void TCPClient::disconnect() {
    socket_close(_socketId);   
}

/* getters */
string TCPClient::getIp(void)const{
    return _ip;
}
size_t TCPClient::getPort(void)const{
    return _port;
}
size_t TCPClient::getSocketId(void)const{
    return _socketId;
}

/* setters */
void TCPClient::setIp(string ip){
    _ip = ip;
}
void TCPClient::setPort(size_t port){
    _port = port;

}
void TCPClient::setSocketId(size_t socId){
    _socketId = socId;
}

TCPClient::~TCPClient(){
    _ip.clear();
    _port = 0;
    socket_close(_socketId);
}
