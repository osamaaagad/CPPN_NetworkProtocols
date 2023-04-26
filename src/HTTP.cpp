#include "sockets.h"
#include "HTTP.hpp"
#include <string>
using namespace std;

 unique_ptr<HTTPClient> HTTPClient::_instance;
 once_flag HTTPClient::_flag;
 size_t HTTPClient::_socketId;

unique_ptr<HTTPClient> HTTPClient::getInstance(){

    if(_instance == nullptr){
        call_once(_flag,[](){_instance.reset(new HTTPClient());});
    }
    _socketId = ( socketCreate() );
    return std::move(_instance);
}

 void HTTPClient::connect() {


    socketConnect( _socketId ,_ip.c_str(),_port , socket_network_t::E_SOCKET_HTTP);

}
 size_t HTTPClient::send(string message) {

    string request;
    size_t contentLength = 0;


    request.assign(string("POST "));
    request.append(message);
    request.append(string(" HTTP/1.0\r\n"));
    request.append(string("Content-Length: "));
    contentLength = message.length();
    request.append(to_string(contentLength));
    request.append(string("\r\n\r\n"));
    socket_Send(_socketId, request.c_str() , request.length());

    /* send the request */   
   return 0;
}
  string HTTPClient::recieve() {


    string readVec;
    char data[1024];
    
     socket_Receive(_socketId,data ,sizeof(data));

    readVec.assign(string(data));
    /* after receiving the connection is dropped*/
    //    this->connect();

    return readVec;
}

  void HTTPClient::disconnect() {
    socket_close(_socketId);   
}

/* getters */
string HTTPClient::getIp(void)const{
    return _ip;
}
size_t HTTPClient::getPort(void)const{
    return _port;
}
size_t HTTPClient::getSocketId(void)const{
    return _socketId;
}

/* setters */
void HTTPClient::setIp(string ip){
    _ip = ip;
}
void HTTPClient::setPort(size_t port){
    _port = port;

}
void HTTPClient::setSocketId(size_t socId){
    _socketId = socId;
}

HTTPClient::~HTTPClient(){
    _ip.clear();
    _port = 0;
    socket_close(_socketId);
}
