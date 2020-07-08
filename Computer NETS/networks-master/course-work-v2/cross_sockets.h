#ifndef SCAN_FUNCTIONS_H
#define SCAN_FUNCTIONS_H
//stdout messages
//#define LOGS_ENABLE

//OS independed includes
#include <stdio.h>
//OS depended includes
#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <winsock2.h>
#else 
    #include <unistd.h>
    #include <socket.h>
    #include <errno.h>
    #pragma message "UNIX sockets API isn\'t fully implemented ...\n"
#endif

int crs_init();
int crs_get_last_error();
int crs_socket(int domain,int type,int protocol);
int crs_cleanup();
int crs_close_socket(int socket);
int crs_in_connect(int sock,const struct sockaddr_in *adr,int adr_len);

int last_error_code = 0;
//sockets API functions wrappers
int crs_init(){
    #ifdef _WIN32
        #ifdef LOGS_ENABLE
            printf("Winsock init: ");
        #endif
        WSADATA wsaData = {0};
        WORD versionRequested = MAKEWORD(2,2); 
        int startupResult = WSAStartup(versionRequested,&wsaData);
        if(startupResult != 0){
            #ifdef LOGS_ENABLE
                printf("Winsock startup failed with error: %d\n",startupResult);
            #endif
            exit(1);
        };
    #else
        #ifdef LOGS_ENABLE 
            printf("UNIX sockets init: ");
        #endif
    #endif
    #ifdef LOGS_ENABLE 
        printf("OK!\n");
    #endif
    last_error_code = 0;
    return 0;
};

int crs_get_last_error(){
    int last_error = 0;
    #ifdef _WIN32
        last_error = WSAGetLastError();
        #ifdef LOGS_ENABLE
            printf("Program failed with error: %d (Winsock Error)\n",last_error);
        #endif
    #else
        last_error = errno;
        #ifdef LOGS_ENABLE
            printf("Program failed with error: %d (Unix ErrNo)\n",last_error);
        #endif
    #endif
    last_error_code = last_error;
    return last_error;
};

int crs_socket(int domain,int type,int protocol){
    int result_socket = (int)socket(domain,type,protocol);
    #ifdef _WIN32
        if(result_socket == INVALID_SOCKET){
    #else
        if(result_socket == -1){
    #endif
            crs_get_last_error();
            return(-1);
        }
    return(result_socket);
};



int crs_cleanup(){
    #ifdef LOGS_ENABLE
        printf("Cleanup: ");
    #endif
    #ifdef _WIN32
        WSACleanup();
    #else
    #endif
    #ifdef LOGS_ENABLE
        printf("OK!\n");
    #endif
    return 0;
};

int crs_close_socket(int socket){
    int return_value = 0;
    #ifdef _WIN32
        return_value = closesocket((SOCKET)socket);
    #else
        return_value = close(socket);
    #endif
    if(return_value == -1){
        crs_get_last_error();
        return(2);
    }
    return(0);
};

int crs_in_connect(int sock,const struct sockaddr_in *adr,int adr_len){
    int return_value = 0;
    #ifdef _WIN32
        return_value = connect((SOCKET)sock,(struct sockaddr*)adr,adr_len);
    #else
        return_value = connect(sock,(struct sockaddr*)adr,adr_len);
    #endif
    if(return_value == -1){
        crs_get_last_error();
        return(3);
    }
    #ifdef LOGS_ENABLE
        printf("OK!\n");
    #endif
    return 0;
};
#endif
