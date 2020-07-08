#include <stdlib.h>
#include <stdio.h>

#include "cross_sockets.h"
int main(){
    crs_init();
    int s = crs_socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    struct sockaddr_in adr;
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = inet_addr("127.0.0.1");
    for(int port=0;port<=1024;port++){
        printf("%d :",port);
        adr.sin_port = htons(port);
        if(crs_in_connect(s,&adr,sizeof(adr))){
            printf(" close\n");
        }else{
            printf(" open\n");
        };
    }
    crs_close_socket(s);
    crs_cleanup(); 
    return 0;
}