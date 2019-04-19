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
    // This is server side
    // -----------------This may be used as a template--------------------
    int udpSocket, nBytes;
    char buffer[1024], return_msg[1024];

    struct sockaddr_in serverAddr, clientAddr;
    struct sockaddr_storage serverStorage;

    socklen_t addr_size, client_addr_size;

    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
    serverAddr.sin_family = AF_INET;
    cout << "Please enter your listening port: ";
    cin >> buffer;
    serverAddr.sin_port = htons(atoi(buffer));
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    bind(udpSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    
    addr_size = sizeof serverStorage;
    do{
        nBytes = recvfrom(udpSocket, buffer, 1024, 0, 
            (struct sockaddr *)&serverStorage, &addr_size);
        cout << "I received: " << buffer << "size:" << nBytes << endl;
        // Convert data in either upper or lowercase for standardization
        for(int i = 0; i < nBytes-1; i++)
            return_msg[i] = toupper(buffer[i]);
        
        return_msg[strlen(buffer)] = 0;
        // When wanting to send back to server/client, always use sendto()
        sendto(udpSocket, return_msg, strlen(return_msg), 0, 
        (struct sockaddr *)&serverStorage, addr_size);
    }while(strncmp(buffer, "Quit", strlen(buffer)-1) != 0);
    cout << "Exit..." << endl;

    return 0;
}