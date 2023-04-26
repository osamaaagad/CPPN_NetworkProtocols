#ifndef HTTP_H
#define HTTP_H

#include "NetworkProtocol.hpp"
#include <memory>
#include <mutex>
using namespace std;


class HTTPClient : public INetworkProtocol {
public:

HTTPClient(const HTTPClient &obj)=delete; /* delete copy constructor*/
HTTPClient& operator=(const HTTPClient &obj)=delete; /* delete copy Assignment operator*/
~HTTPClient();
static unique_ptr<HTTPClient> getInstance();

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

static unique_ptr<HTTPClient> _instance;
static once_flag _flag;
string _ip;
size_t _port;
static size_t _socketId;

HTTPClient()=default;

};

#endif//HTTP_H