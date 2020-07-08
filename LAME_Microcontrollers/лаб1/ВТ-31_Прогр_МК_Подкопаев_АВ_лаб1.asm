ORG 0h			;задание адреса размещения следующей части программы в памяти
jmp start		;безусловный переход к команде start

ORG 13h			;задание адреса размещения следующей части программы в памяти
call setP0
call check
call resetP0
call printRO
CLR IE1
RETI

org 0030h		;задание адреса размещения следующей части программы в памяти
start:
    mov IE, #10001100b	;
    mov IP, #00000100b	;
    mov r5, #0h		;

    clr sm0		;сброс sm0 в 0
    setb sm1   		;установка sm1 в 1
			;установка режима scon 8-ми битовый приемо-передатчик с изменяемой скоростью

    clr a		;установка удвоенной скорости передачи через pcon
    mov a, pcon		
    setb acc.7
    mov pcon, a  	;

    mov tmod, #20H         
    mov th1, #243       
    mov tl1, #243        
    setb tr1
    call resetP0
wait:
    jmp wait

resetP0:		;сброс p0 в 0
    CLR  p0.0
    CLR  p0.1
    CLR  p0.2
    CLR  p0.3
    ret

setP0:			;установка p0 в 1
    setb p0.0
    setb p0.1
    setb p0.2
    setb p0.3
    ret

check:			;опрос столбцов
    MOV R0, #0
    SETB P0.3
    CLR P0.0
    CALL colScan4
    SETB P0.0
    CLR P0.1
    CALL colScan3
    SETB P0.1
    CLR P0.2
    CALL colScan2
    SETB P0.2
    CLR P0.3
    CALL colScan1
    RET

colScan1:		;проверка первой строки
    JNB P0.4, gotKey3
    JNB P0.5, gotKey2
    JNB P0.6, gotKey1
    RET

colScan2:		;проверка второй строки
    JNB P0.4, gotKey6
    JNB P0.5, gotKey5
    JNB P0.6, gotKey4
    RET

colScan3:		;проверка третьей строки
    JNB P0.4, gotKey9
    JNB P0.5, gotKey8
    JNB P0.6, gotKey7
    RET

colScan4:		;проверка четвертой строки
    JNB P0.4, gotKeySharp
    JNB P0.5, gotKey0
    JNB P0.6, gotKeyAst
    RET
			;получение кода нажатой клавиши
gotKey0:
    mov r0, #48
    RET

gotKey1:
    mov r0, #49
    RET

gotKey2:
    mov r0, #50
    RET

gotKey3:
    mov r0, #51
    RET

gotKey4:
    mov r0, #52
    RET

gotKey5:
    mov r0, #53
    RET

gotKey6:
    mov r0, #54
    RET

gotKey7:
    mov r0, #55
    RET

gotKey8:
    mov r0, #56
    RET

gotKey9:
    mov r0, #57
    RET

gotKeyAst:
    mov r0, #42
    RET

gotKeySharp:
    mov r0, #35
    RET

printRO:		;вывод нажатой клавиши через sbuf
    mov a, r0 
    Jz printExit
    mov sbuf, a
    jnb ti, $
    clr ti

printExit:
    ret


