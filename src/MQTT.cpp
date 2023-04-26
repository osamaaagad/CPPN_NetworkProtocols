#include "sockets.h"
#include "MQTT.hpp"
#include "MQTTPacket.h"
using namespace std;

 unique_ptr<MQTTClient> MQTTClient::_instance;
 once_flag MQTTClient::_flag;
 size_t MQTTClient::_socketId;

size_t MQTTClient:: SubscribeOn(){

	MQTTString topicString[1];
	int qos[1] = {0};
	int checkLen =0;
	unsigned char buffer[128] = { 0 };

	 topicString[0].cstring = (char *) this->_subscribeTopicName.c_str();

	checkLen = MQTTSerialize_subscribe(buffer, sizeof(buffer),0,1,1,topicString,qos);

	checkLen = socket_Send(_socketId,(const char *) buffer, checkLen);

	return checkLen;
}

unique_ptr<MQTTClient>  MQTTClient::getInstance(){

    if(_instance == nullptr){
        call_once(_flag,[](){_instance.reset(new MQTTClient());});
    }
    /*set initial values */
    _socketId = ( socketCreate() );
    _instance->_cleanSession = true;
    _instance->_QOS = 0;

    return std::move(_instance);
}

 void MQTTClient::connect() {

	unsigned char buffer[128] = { 0 };
    MQTTPacket_connectData connData = {0};
	size_t checkLen =0;

    socketConnect( _socketId ,_ip.c_str(),_port , socket_network_t::E_SOCKET_MQTT);


	// configure the MQTT parameters
	connData.keepAliveInterval = 10000;
    connData.cleansession = _cleanSession;
    connData.MQTTVersion = 3;
    if(!_clientID.empty()){
        connData.clientID.cstring = (char *) _clientID.c_str();
    }else{
        connData.clientID.cstring = (char *) "me";
    }

	checkLen = MQTTSerialize_connect(buffer, sizeof(buffer), &connData);

	checkLen = socket_Send(_socketId, (const char *)buffer, checkLen);

}

 size_t MQTTClient::send(string message) {

  	MQTTString topicString = MQTTString_initializer;
	size_t checkLen =0;
	unsigned char buffer[512] = { 0 };


	 topicString.cstring = (char *) this->_publishTopicName.c_str();


		checkLen = MQTTSerialize_publish(buffer, sizeof(buffer), 0, 0, 0, 0,
				topicString, (unsigned char*)message.c_str(), message.length());

		checkLen = socket_Send(_socketId,(const char *) buffer, checkLen);
   return checkLen;
}

  string MQTTClient::recieve() {

	int offset = 0;
    string readVec;
    char data[512];

     memset(data,0,sizeof(data));
     socket_Receive(_socketId,data ,sizeof(data));

	for(char ch : data){
		if(ch != '\0'){
			readVec+=(ch);
		}
	}
	offset = readVec.find(_subscribeTopicName);
	if(offset>=0){
		readVec = readVec.substr(offset + _subscribeTopicName.length());
	}else{
		readVec.assign("");
	}

    return readVec;
}

  void MQTTClient::disconnect() {
    socket_close(_socketId);   
}

/* getters */
string MQTTClient::getIp(void)const{
    return _ip;
}
size_t MQTTClient::getPort(void)const{
    return _port;
}
size_t MQTTClient::getSocketId(void)const{
    return _socketId;
}

size_t MQTTClient::getQOS(void)const{
    return _QOS;
}
bool MQTTClient::getCleanSession(void)const{
    return _cleanSession;
}
string MQTTClient::getCleintID(void)const{
    return _clientID;
}
string MQTTClient::getPublishTopicName(void)const{
    return _publishTopicName;
}
string MQTTClient::getSubscribeTopicName(void)const{
    return _subscribeTopicName;
}
string MQTTClient::getUserName(void)const{
    return _userName;
}
string MQTTClient::getUserPassword(void)const{
    return _userPassword;
}

/* setters */
void MQTTClient::setIp(string ip){
    _ip = ip;
}
void MQTTClient::setPort(size_t port){
    _port = port;

}
void MQTTClient::setSocketId(size_t socId){
    _socketId = socId;
}
void MQTTClient::setQOS(size_t qos){
    _QOS = qos;
}
void MQTTClient::setCleanSession(bool cleanSession){
    _cleanSession = cleanSession;
}
void MQTTClient::setCleintID(string cleintID ){
    _clientID = cleintID;
}
void MQTTClient::setPublishTopicName(string topicName){
    _publishTopicName = topicName;
}
void MQTTClient::setSubscribeTopicName(string topicName){
	_subscribeTopicName = topicName;
}
void MQTTClient::setUserName(string userName){
    _userName = userName;
}
void MQTTClient::setUserPassword(string userPass){
    _userPassword = userPass;
}

MQTTClient::~MQTTClient(){
    _ip.clear();
    _port = 0;
    _cleanSession = false;
    _clientID.clear();
    _userName.clear();
    _userPassword.clear();
    _QOS = 0;
    socket_close(_socketId);
}
