#include <iostream>
using namespace std;

int x=200;
int y=5;
int ret = 0;

short ipx_init_flag;
int ipx_driver_entry;

int _ipx_init(){
    asm(
        "mov ax, 0x7a00\n"
        "int 0x2fh\n"
        "mov _ipx_init_flag, al\n"
    );
    if(ipx_driver_entry!=0xff){
        return;
    }else{
        asm(
            "mov _ipx_driver_entry"
        );
    }
    return ret;
}

int main(int argc, char *argv[])
{

    cout << asm_test();
}
