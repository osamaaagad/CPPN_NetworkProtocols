#ifndef MQTT_H
#define MQTT_H

#include "NetworkProtocol.hpp"
#include <memory>
#include <mutex>
using namespace std;


class MQTTClient : public INetworkProtocol {
public:

MQTTClient(const MQTTClient &obj)=delete; /* delete copy constructor*/
MQTTClient& operator=(const MQTTClient &obj)=delete; /* delete copy Assignment operator*/
~MQTTClient();

static unique_ptr<MQTTClient> getInstance();
size_t SubscribeOn();

virtual void connect() override;
virtual size_t send(string) override;
virtual string recieve() override;
virtual void disconnect() override;

/* getters */
string getIp(void)const;
size_t getPort(void)const;
size_t getSocketId(void)const;
size_t getQOS(void)const;
bool getCleanSession(void)const;
string getCleintID(void)const;
string getPublishTopicName(void)const;
string getSubscribeTopicName(void)const;
string getUserName(void)const;
string getUserPassword(void)const;

/* setters */
void setIp(string);
void setPort(size_t);
void setSocketId(size_t);
void setQOS(size_t);
void setCleanSession(bool);
void setCleintID(string);
void setPublishTopicName(string);
void setSubscribeTopicName(string);
void setUserName(string);
void setUserPassword(string);

private:

static unique_ptr<MQTTClient> _instance;
static once_flag _flag;
string _ip;
size_t _port;
bool _cleanSession;
size_t _QOS;
string _clientID;
string _userName;
string _userPassword;
string _publishTopicName;
string _subscribeTopicName;



static size_t _socketId;

MQTTClient()=default;

};

#endif//MQTT_H