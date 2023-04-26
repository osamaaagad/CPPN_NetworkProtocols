#ifndef TCP_H
#define TCP_H

#include "NetworkProtocol.hpp"
#include <memory>
#include <mutex>
using namespace std;


class TCPClient : public INetworkProtocol {
public:

TCPClient(const TCPClient &obj)=delete; /* delete copy constructor*/
TCPClient& operator=(const TCPClient &obj)=delete; /* delete copy Assignment operator*/
~TCPClient();
static unique_ptr<TCPClient> getInstance();

virtual void connect() override;
virtual size_t send(string) override;
virtual string recieve() override;
virtual void disconnect() override;

/* getters */
string getIp(void)const;
size_t getPort(void)const;
size_t getSocketId(void)const;

/* setters */
void setIp(string);
void setPort(size_t);
void setSocketId(size_t);

private:

static unique_ptr<TCPClient> _instance;
static once_flag _flag;
string _ip;
size_t _port;
static size_t _socketId;

TCPClient()=default;

};

#endif//TCP_H