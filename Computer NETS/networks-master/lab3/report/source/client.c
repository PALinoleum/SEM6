#include <windows.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void intHandler(int dummy) {
    printf("Exit by keyboard interrupt\n");
    exit(0);
}

int main(){
    signal(SIGINT, intHandler);

    time_t t;
    srand((unsigned) time(&t));
    int data = rand();

    WSADATA wsaData = {0};
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

    //создаём сокет
    int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if(s < 0){
        perror("Socket creating error\n");
        return 1;
    };
    printf("Socket successfully created\n");

    struct sockaddr_in addr;
    //семейство IP
    addr.sin_family = AF_INET;
    //порт
    unsigned short port;
    printf("Input socket port: ");
    scanf("%hu",&port);
    addr.sin_port = htons(port);

    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    printf("\nSocket family: IP\n");    
    printf("Socket port: %hu\n",port);    
    printf("Socket address: 127.0.0.1\n\n");    
    
    printf("Press Enter to start transsmition...\n");
    getchar();
    getchar();
    printf("Sending identification packet to server\n");
    printf("Sending number: %d\n",data);
    int ret_val = sendto(s,&data, sizeof(int), 0, (SOCKADDR *) & addr, sizeof (addr));
    if (ret_val == SOCKET_ERROR) {
        wprintf(L"\nsendto failed with error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }
    printf("Await echo packet\n");
    int echo_data;
    struct sockaddr_in sender_addr;
    int sender_addr_size = sizeof(sender_addr);
    
    ret_val = recvfrom(s,&echo_data,sizeof(int),0,(SOCKADDR*)&sender_addr, &sender_addr_size);
        if (ret_val == SOCKET_ERROR) {
            wprintf(L"\nrecvfrom failed with error: %d\n", WSAGetLastError());
            closesocket(s);
            WSACleanup();
            return 1;
    };
    printf("Echo number: %d\n",echo_data);
    return 0;
}