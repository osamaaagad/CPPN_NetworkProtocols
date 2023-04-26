#include <iostream>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <dirent.h>

#include "TCP.hpp"
#include "HTTP.hpp"
#include "MQTT.hpp"

constexpr const char * blueText = "\x1B[34m"; /* used for TCP*/
constexpr const char * greenText = "\x1B[32m";/* used for MQTT*/
constexpr const char * yellowText = "\x1B[33m";/* used for HTTP*/
constexpr const char * redText = "\x1B[31m"; /* used for Errors*/

std::mutex g_console_mutex;  // protects consle
std::condition_variable g_recv_cond; //wait sending then receiving

template <typename T>
void networkClient_Handler (T * tempClient, string protocol, string color ){
    
    string message;
    size_t sendBytes;

    std::cout<<yellowText<<"Enter the message to be sent over " << protocol << " otherwise enter exit to terminate!"<<std::endl;


   while(1){

        do{
        	std::cout<<yellowText;
        	std::getline(std::cin,message);
        }while(message.empty() || string("") == message);
        //print on consle the message that has been sent in specific color for every network protocol.

        if( message == string("exit") ){
            exit(__LINE__);
        }
        sendBytes = tempClient->send(message);

        if (sendBytes > 0 && message.length() > 0){

            std::cout<<color<< protocol << "::SEND:: client --> server :"<<message<<std::endl;
            message.clear();
        }
        /* notify the sender to send another message */
        g_recv_cond.notify_one();
    	this_thread::sleep_for(std::chrono::milliseconds(1000));
   }

}

template<typename T>
void networkRecieve(T * tempClient, string protocol, string color){
    string message;


    while(1){

        std::unique_lock<std::mutex> ul(g_console_mutex);
        /* wait until you receive an aknlowedge */
        g_recv_cond.wait(ul);

        message = tempClient->recieve();
        if(! message.empty() && message.length() > 0 ){

            //print on consle the message that has been sent in specific color for every network protocol.
            std::cout<<color<< protocol << "::RECEIVE:: client <-- server :"<<message<<std::endl;
            message.clear();
        }

    }
}

int main() {

    string protocolName;
    string serverIp;
    size_t serverPort;
    size_t nwProtocolType;
    unique_ptr<TCPClient> tcpClient = nullptr;
    unique_ptr<MQTTClient> mqttClient = nullptr;
    unique_ptr<HTTPClient> httpClient = nullptr;
    string pubTopicName;
    string subTopicName;
    string clientFlag;
    string configPath;
    string value1;
    size_t value2;
    string value3;
    string value4;

    configPath.assign(cwd);
    configPath.append("/ProtoConfig.txt");

    do{
        std::cout<<"Select the Network Protocol from [1:3]:\n 1.TCP\n 2.MQTT\n 3.HTTP"<<std::endl;
        std::cin>>nwProtocolType;
        system("clear");
        
        switch(nwProtocolType-1){

            case(0):

                
                if(nullptr == tcpClient){
                    tcpClient = TCPClient::getInstance();
                    
                    std::ifstream protocolConfig (configPath);
                    if(protocolConfig.is_open()){
                        string line;
                        while(getline(protocolConfig,line)){
                            std::istringstream linestream (line);
                            linestream>> protocolName >> value1 >> value2;
                            if(protocolName== "TCP"){
                                serverIp = value1;
                                serverPort = value2;
                                std::cout<<"default config is (protocol name,ip,port)=" << line <<std::endl;
                            }
                        }
                    }

                    std::cout<<"write (y) if you want to change default config or (n) if you don't want change"<<std::endl;
                    std::cin>>clientFlag;

                    if(clientFlag == "y"){
                        std::cout<<"Enter TCP Server Ip :"<<std::endl;
                        std::cin>>serverIp;
                    
                        std::cout<<"Enter TCP Server Port :"<<std::endl;
                        std::cin>>serverPort;
                        
                    }
                    //setting protocol configs
                    tcpClient->setIp(serverIp);
                    tcpClient->setPort(serverPort);
                    tcpClient->connect();

                    auto ptr = tcpClient.get();
                    std::future<void> ftr = std::async(std::launch::async,[ptr](){networkClient_Handler<TCPClient>(ptr,"TCP",blueText);});
                    std::future<void> ftr1 = std::async(std::launch::async,[ptr](){networkRecieve<TCPClient>(ptr,"TCP",greenText);});
                    /* free ptr*/
                    ptr = nullptr;
                }
            break;

            case(1):

                if(nullptr == mqttClient){

                    mqttClient = MQTTClient::getInstance();

                    std::ifstream protocolConfig (configPath);
                    if(protocolConfig.is_open()){
                        string line;
                        while(getline(protocolConfig,line)){
                            std::istringstream linestream (line);
                            linestream>> protocolName >> value1 >> value2 >> value3 >> value4;
                            if(protocolName== "MQTT"){
                                serverIp = value1;
                                serverPort = value2;
                                pubTopicName = value3;
                                subTopicName = value4;
                                std::cout<<"default config is (protocol name,ip,port)=" << line <<std::endl;
                            }
                        }
                    }

                    std::cout<<"write (y) if you want to change default config or (n) if you don't want change"<<std::endl;
                    std::cin>>clientFlag;

                    if(clientFlag == "y"){
                        std::cout<<"Enter MQTT Server Ip :"<<std::endl;
                        std::cin>>serverIp;

                        std::cout<<"Enter MQTT Server Port :"<<std::endl;
                        std::cin>>serverPort;

                        std::cout<<"Enter MQTT Publish Topic name :"<<std::endl;
                        std::cin>>pubTopicName;
                        std::cout<<"Enter MQTT Subscribe Topic name :"<<std::endl;
                        std::cin>>subTopicName;

                    }

                    //setting protocol configs
                    mqttClient->setIp(serverIp);
                    mqttClient->setPort(serverPort);
                    mqttClient->setPublishTopicName(pubTopicName);
                    mqttClient->setSubscribeTopicName(subTopicName); 

                    mqttClient->connect();
                    mqttClient->SubscribeOn();

                    auto ptr = mqttClient.get();
                    std::future<void> ftr2 = std::async(std::launch::async,[ptr](){networkClient_Handler<MQTTClient>(ptr,"MQTT",blueText);});
                    std::future<void> ftr3 = std::async(std::launch::async,[ptr](){networkRecieve<MQTTClient>(ptr,"MQTT",greenText);});
                    /* free ptr*/
                    ptr = nullptr;
                }
            break;

            case(2):

				if(nullptr == httpClient){

                	httpClient = HTTPClient::getInstance();

                    std::ifstream protocolConfig (configPath);

                    if(protocolConfig.is_open()){
                        string line;
                        while(getline(protocolConfig,line)){
                            std::istringstream linestream (line);
                            linestream>> protocolName >> value1 >> value2;
                            if(protocolName== "HTTP"){
                                serverIp = value1;
                                serverPort = value2;
                                std::cout<<"default config is (protocol name,ip,port)=" << line <<std::endl;
                            }
                        }
                    }

                    std::cout<<"write (y) if you want to change default config or (n) if you don't want change"<<std::endl;
                    std::cin>>clientFlag;

                    if(clientFlag == "y"){
                        std::cout<<"Enter HTTP Server Ip :"<<std::endl;
                        std::cin>>serverIp;

                        std::cout<<"Enter HTTP Server Port :"<<std::endl;
                        std::cin>>serverPort;
                    }

                    //setting protocol configs
                    httpClient->setIp(serverIp);
                    httpClient->setPort(serverPort);


                    httpClient->connect();

                    auto ptr = httpClient.get();
                    std::future<void> ftr4 = std::async(std::launch::async,[ptr](){networkClient_Handler<HTTPClient>(ptr,"HTTP",blueText);});
                    std::future<void> ftr5 = std::async(std::launch::async,[ptr](){networkRecieve<HTTPClient>(ptr,"HTTP",greenText);});
                    /* free ptr*/
                    ptr = nullptr;
                }
            
            break;

            default:
                system(redText);
                std::cout<<"Error:: bad choise"<<std::endl;
            break;

        }
    }while(1);

    
    return 0;
}
