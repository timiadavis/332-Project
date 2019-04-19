#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <cstdlib>

using namespace std;

int main(){
    // This is client side
    // -----------------This may be used as a template--------------------
    int clientSocket, portNum, nBytes;
    char input_buffer[1024];
    char received_msg[1024];
    char port_string[10];
    char ip_string[17];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    serverAddr.sin_family = AF_INET;
    cout << "Please enter your buddy's port:";
    cin >> port_string;
    //Assign integer into port number variable
    portNum = atoi(port_string);
    //Port number comes from user
    serverAddr.sin_port = htons(portNum);

    cout << "PLease enter your buddy's IP:";
    cin >> ip_string;
    serverAddr.sin_addr.s_addr = inet_addr(ip_string);
    memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
    addr_size = sizeof serverAddr;

    do{
        cout << "Type a sentence to send to your buddy: ";
        cin.getline(input_buffer, 1024, '\n');
        nBytes = strlen(input_buffer)+1;
        cout << input_buffer << " " << nBytes << endl;
        sendto(clientSocket, input_buffer, nBytes, 0, 
        (struct sockaddr * )&serverAddr, addr_size);
        nBytes = recvfrom(clientSocket, received_msg, 1024, 0, NULL, NULL);
        cout << received_msg << endl;

    }while(strncmp(input_buffer, "Quit", strlen(input_buffer)-1) != 0);

    return 0;
}