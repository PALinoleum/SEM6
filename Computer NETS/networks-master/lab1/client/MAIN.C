#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <mem.h>
#include <string.h>
#include "ipx.h"
#include <time.h>


#define BUFFER_SIZE 504
#define RANDOM_CHAR() rand()%35+55
typedef struct _file_segment
{
        long int segment_size;
        long int segment_num;
} file_segment;
unsigned char segment_buffer[BUFFER_SIZE];

void main(void) {
        //обьявление переменных до вызова процедур.
        //размер файла в байтах
        long int file_size;
        //кол-во полных сегментов, всего сегментов
        long int full_segments_count, seg_counter;
        //размер неполного последнего сегмента (если 0 то сегмента нету)
        long int last_segment_size;
        int i,j;
        FILE* file;
        file_segment temp_segment;
        int progress_step;
        
        static unsigned Socket = 0x4444;
        struct ECB RxECB;
        struct IPX_HEADER RxHeader;
        unsigned char RxBuffer[BUFFER_SIZE];
        
        unsigned int sval;
        time_t t;
        char name[9];
        
        sval=(unsigned)time(&t);
        srand(sval);

        //рандом имени файла
        name[0]=RANDOM_CHAR(); name[1]=RANDOM_CHAR(); name[2]=RANDOM_CHAR(); name[3]=RANDOM_CHAR();
        name[4]='.'; name[5]='j'; name[6]='p'; name[7]='g'; name[8]='\0';

        printf("temp filename - %s\n",name);
        file = fopen(name,"wb+");
        if(file==NULL){
                exit(-1);
        }
        if(ipx_init() != 0xff) {
                printf("IPX not loaded!\n"); exit(-1);
        }

        if(IPXOpenSocket(SHORT_LIVED, &Socket)) {
                printf("Socket open error\n");
                exit(-1);
        };

        memset(&RxECB, 0, sizeof(RxECB));
        RxECB.Socket            = IntSwap(Socket);
        RxECB.FragmentCnt= 3;
        RxECB.Packet[0].Address = &RxHeader;
        RxECB.Packet[0].Size = sizeof(RxHeader);
        RxECB.Packet[1].Address = RxBuffer;
        RxECB.Packet[1].Size = BUFFER_SIZE;
        RxECB.Packet[2].Address = &temp_segment;
        RxECB.Packet[2].Size = 8;
        
        //ожидание первого пакета
        IPXListenForPacket(&RxECB);
        printf("Await server response..");
        while(1) {
                if(RxECB.InUse){
                        printf(".");
                        printf("\b");
                }else{
                        printf("\nResponse accepted.\n");
                        break;
                };
        }
        clrscr();

        //ожидание пакета с размером файла
        IPXListenForPacket(&RxECB);
        while(RxECB.InUse){}
        memcpy(&seg_counter,RxBuffer,temp_segment.segment_size);
        printf("seg num - %ld, seg_size = %ld, seg counter - %ld\n",temp_segment.segment_num,temp_segment.segment_size,seg_counter);
        progress_step=seg_counter/70-1;

        for(i=0;i<=seg_counter;i++){
                IPXListenForPacket(&RxECB);
                while(RxECB.InUse){}
                for(j=0;j<temp_segment.segment_size;j++){
                        fputc(RxBuffer[j],file);
                };
                if(i%progress_step==0) printf("%c",219);
                if(temp_segment.segment_num==seg_counter){
                        break;
                };
        }
        fclose(file);
        printf("ready.\n");
        IPXCloseSocket(&Socket);
        
        exit(0);
}