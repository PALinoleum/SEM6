#include <STDIO.H>
#include <STDLIB.H>
#include <CONIO.H>
#include <MEM.H>
#include <STRING.H>
#include <DOS.H>
#include "IPX.H"

#define BUFFER_SIZE 504

// -1 сегмент - начало передачи
//  0 сегмент - кол-во значащих сегментов
//1-n сегмент - значащие сегменты
//n+1 сегмент - конец передачи

typedef struct _file_segment
{
        long int segment_size;
        long int segment_num;
} file_segment;

unsigned char segment_buffer[BUFFER_SIZE];

long int get_file_size(FILE* stream){
        long int size;
        fseek(stream,0,SEEK_END);
        size = ftell(stream);
        fseek(stream,0,SEEK_SET);
        return size;
};

void main(void) {
        //размер файла в байтах
        long int file_size;
        //кол-во полных сегментов, всего сегментов
        long int full_segments_count, seg_counter;
        //размер неполного последнего сегмента (если 0 то сегмента нету)
        long int last_segment_size;
        FILE* file;
        FILE* check_file;
        file_segment temp_segment;
        
        static unsigned Socket = 0x4444;
        struct ECB ServerECB;
        struct IPX_HEADER InHeader, OutHeader;
        unsigned char OutBuffer[BUFFER_SIZE];
        int i;
        int progress_step;
        char filename[255] = "test_img.bpm";
        int value_delay = 0;

        printf("delay between seg - ");
        scanf("%i",&value_delay);

        printf("filename - ");
        scanf("%s",filename);
        if(ipx_init() != 0xff) {
                printf("IPX not loaded!\n");
                exit(-1);
        }else{
                printf("IPX loaded!\n");
        }

        if(IPXOpenSocket(SHORT_LIVED, &Socket)) {
                printf("IPX socket open error\n");
                exit(-1);
        }else{
                printf("IPX socket %x open\n",Socket);
        };
        memset(&ServerECB, 0, sizeof(ServerECB));

        //открытие файла и рассчет кол-ва сегментов
        file=fopen(filename,"rb+");
        if(file!=NULL){
                file_size = get_file_size(file);
                full_segments_count = file_size / (BUFFER_SIZE-8);
                last_segment_size = file_size % (BUFFER_SIZE-8);
                seg_counter = full_segments_count+1;
                printf("file size: %ld bytes\n",file_size);
                printf("full seg count: %ld\n",full_segments_count);
                printf("last seg size: %ld bytes\n",last_segment_size);
                fclose(file);
                file=fopen(filename,"rb+");
                check_file=fopen("IMG.bmp","wb+");
        }else{
                exit(1);
        };

        printf("Press Enter to start transmission\n");
        getch();

        clrscr();
        //Пакет "начало передачи"
        temp_segment.segment_size=0;
        temp_segment.segment_num=-1;
        segment_buffer[0]=0;
        //Тело        
        memcpy(OutBuffer,&segment_buffer,BUFFER_SIZE);
        //заголовок
        OutHeader.PacketType = 4;
        memset(OutHeader.DestNetwork, 0, 4);
        memset(OutHeader.DestNode, 0xFF, 6);
        OutHeader.DestSocket = IntSwap(Socket);
        //заполнение ECB
        ServerECB.Socket= IntSwap(Socket);
        ServerECB.FragmentCnt= 3;
        ServerECB.Packet[0].Address = &OutHeader;
        ServerECB.Packet[0].Size = sizeof(OutHeader);
        ServerECB.Packet[1].Address = OutBuffer;
        ServerECB.Packet[1].Size = BUFFER_SIZE;
        ServerECB.Packet[2].Address = &temp_segment;
        ServerECB.Packet[2].Size = 8;
        IPXSendPacket(&ServerECB);
        printf("Start.\n");

        //Пакет содержащий кол-во сегментов
        temp_segment.segment_num=0;
        temp_segment.segment_size=sizeof(seg_counter);
        memcpy(segment_buffer,&seg_counter,sizeof(seg_counter));
        memcpy(OutBuffer,&segment_buffer,BUFFER_SIZE);
        IPXSendPacket(&ServerECB);
        printf("Count of seg: %ld.\n",seg_counter);
        
        progress_step=seg_counter/70-1;
        printf("Start file translation.\n");
        for(i=1;i<=full_segments_count;i++){
                //установка номера сегмента файла
                temp_segment.segment_num=i;   
                //установка размера сегмента файла
                temp_segment.segment_size=BUFFER_SIZE; 
                //отправка пакета
                //шаг прогресса
                fread(OutBuffer,1,BUFFER_SIZE,file);
                fwrite(OutBuffer,1,BUFFER_SIZE,check_file);
                if(i%progress_step==0) printf("%c",219);
                IPXSendPacket(&ServerECB);
                delay(value_delay);
        };
                delay(value_delay);
                temp_segment.segment_num=seg_counter;   
                temp_segment.segment_size=last_segment_size;   
                fread(OutBuffer,1,last_segment_size,file);
                fwrite(OutBuffer,1,last_segment_size,check_file);
                IPXSendPacket(&ServerECB);
                printf("%i\n",i);
        printf("Transmit end.\n",seg_counter);

        fclose(file);
        fclose(check_file);
        IPXCloseSocket(&Socket);
        exit(0);
}