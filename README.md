# CPPND: Capstone Network Protocols Repo
This is a project has been done using a wide range of C++ features.

# Concept
This project is intended to send or receive messages via network protocols [TCP,MQTT and HTTP] 

-prosedures:
  *user should select which protocol needs to be used.
  *default configuration of the protocol "stored in a txt file" is printed to the user and the user also can change it.
  
  *setup of protocols:
    1.TCP:
      -if the server is local on debian system which it is in the default config "127.0.0.1" as ip and "444" as port, you should run the server by the following command 
       sudo apt-get install net-tools
       nc -l 444
      -if the server will be in the windows you can download the hercules to test the session between the server and the client and check the server ip from Network and internet
       https://www.hw-group.com/software/hercules-setup-utility
    2.MQTT:
      - you can test the publish and subscribe processes by using online MQTT client test with a specific broker such as "91.121.93.94"/"test.mosquitto.org" as ip/url and "1883" as port
      by download MQTTLens or MQTTBox
      - after a successful connection you can use the default publish topic and subscribe topic or changing them.
    3.HTTP
      - in this case we will use an exist http server which the Ip is "41.38.102.53" and port is "35617" and the message must be like that "/api/Readers/lastActive/73420935-90a6-4f48-9505-08db29f69806" 


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.`
3. Compile: `cd ./Debug && make all`
4. Run it: `./CppND-Capstone-NetworkProtocols`.

## The list of the rubric points

1. Loops, Functions, I/O :  
  - The project accepts user input and processes the input:
    File: src/main.cpp ,----> line: 128,131
  -The project reads data from a file and process the data, or the program writes data to a file.
    File: src/main.cpp ,----> line: 114
  -The project demonstrates an understanding of C++ functions and control structures:
    File: src/MQTT.cpp ,----> line: 10,39.64,81

2. Object Oriented Programming:
  -The project uses Object Oriented Programming techniques:
    File: include/NetworkProtocol.hpp , TCP.hpp ,MQTT.hpp,HTTP.hpp
  -Classes use appropriate access specifiers for class members:  
    File: include/MQTT.hpp ,----> line: 10
  -Classes abstract implementation details from their interfaces:  
    File: include/MQTT.hpp ,----> line: 13,14,17,20,21,22,23
  -Classes encapsulate behavior:  
    File: include/MQTT.hpp ,----> line: 25,37
  -Classes follow an appropriate inheritance hierarchy:
    File: include/NetworkProtocol.hpp ,----> line: 11:14
  -Overloaded functions allow the same function to operate on different parameters:
    File: src/main.cpp ,----> line: 25,145  
  -Derived class functions override virtual base class functions:
    File: include/MQTT.hpp ,----> line: 20,21,22,23
  -Templates generalize functions in the project:
    File: src/main.cpp ,----> line: 25,59  

3. Memory Management:
  -The project makes use of references in function declarations:
    File: include/MQTT.hpp ,----> line: 13,14
  -The project uses destructors appropriately:
    File: src/MQTT.cpp ,----> line: 175
  -The project uses move semantics to move data, instead of copying it, where possible:
    File: src/MQTT.cpp ,----> line: 175
  -The project uses smart pointers instead of raw pointers:
    File: src/MQTT.cpp ,----> line: 6,26  

3. Concurrency:
  -The project uses multithreading:
    File: src/main.cpp ,----> line: 145,146,201,202,248,249
  -A promise and future is used in the project:         
    File: src/main.cpp ,----> line: 145,146,201,202,248,249
  -A mutex or lock is used in the project:
    File: src/main.cpp ,----> line: 65
  -A condition variable is used in the project:
    File: src/main.cpp ,----> line: 52,67    