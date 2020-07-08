#include <windows.h>
#include <winsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

typedef struct _thread_arg{
    struct sockaddr_in adr;
    int data;
} thread_arg;

void send_echo_adr(thread_arg *arg){
    printf("\nReceived packet from client\n");
    printf("Creating thread for response\n");
    printf("Received number: %d\n",arg->data);
    printf("Send echo packet\n");
    int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
    if(s < 0){
        perror("Socket creating error\n");
        return 1;
    };
    int ret_val = sendto(s,&arg->data, sizeof(int), 0, (SOCKADDR *) &arg->adr, sizeof (arg->adr));
    if (ret_val == SOCKET_ERROR) {
        wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return 1;
    }
    printf("Close thread\n\n");
    closesocket(s);
    return;
}

void intHandler(int dummy) {
    printf("Exit by keyboard interrupt\n");
    exit(0);
}

int main(){
    signal(SIGINT, intHandler);
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
    //слушаем всю сеть 
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    printf("\nSocket family: IP\n");    
    printf("Socket port: %hu\n",port);    
    printf("Socket address: any\n\n");    
    
    //назначаем сокету адрес
    if(bind(s, (SOCKADDR *)&addr, sizeof(addr)) < 0){
        printf(L"bind failed with error %d\n", WSAGetLastError());
        return 2;
    };

    printf("Server waiting client packet...\n");
    int rec_data;
    while(1){
        struct sockaddr_in sender_addr;
        int sender_addr_size = sizeof(sender_addr);
        int ret_val = recvfrom(s,&rec_data,sizeof(int),0,(SOCKADDR*)&sender_addr,&sender_addr_size);
        if (ret_val == SOCKET_ERROR) {
            wprintf(L"recvfrom failed with error: %d\n", WSAGetLastError());
            closesocket(s);
            WSACleanup();
            return 1;
        }else{
            thread_arg arg;
            arg.data = rec_data;
            arg.adr = sender_addr;
            HANDLE thread = CreateThread(NULL,0,send_echo_adr,&arg,0,NULL);
        };
    };

    return 0;
}