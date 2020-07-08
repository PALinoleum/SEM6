org 0H
            ljmp start


org 8100H
start:
            mov DPTR, #3
            mov A, #82h ;A(0) - вывод, C(2) - вывод, B(1) -ввод
            movx @DPTR, A
integrator:
;ИНТЕГРАТОР:
            mov     TMOD, #1
            mov     TH0, #0FCh
            mov     TL0, #017h
;УСТАНОВКА НАЧАЛЬНОГО СОСТОЯНИЯ
            setb    P1.1            ;!!!подключаем при отицательном выходе компаратора
            setb    P1.0            ;подача ЕОП на вход интегратора (поменять при случае)

WAIT:       jb      P1.1, WAIT      ;Ожидание появления на выходе интегратора отрицательного уровня
            clr     P1.0            ;Подача на вход интегратора Uвх

;ОЖИДАНИЕ СОСТОЯНИЯ T0
WAIT_T0:    jnb     P1.1, WAIT_T0   ;Ожидание момента T0

;ИНТЕГРИРОВАНИЕ T1
            setb    TR0             ;Старт таймера
WAIT_T1:    jnb     TF0,  WAIT_T1   ;Ожидание момента T1

;ИНТЕГРИРОВАНИЕ T2
            setb    P1.0            ;Подача Еоп на вход интегратора (поменять при случае)
WAIT_T2:    jb      P1.1, WAIT_T2   ;Ожидание момента T2
            clr     TR0             ;Конец интегрирования
            clr     TF0
;ВЫВОД
            mov     B, TH0
            mov     A, TL0

;ВЫВОД НА ИНДИКАТОР
        mov     DPTR, #0
        lcall   printDigit

        mov     
        mov     DPTR, #2
        lcall   printDigit
        ;FGEDCHBA
printDigit:
        cjne    A, #0, print1
        mov     A, #10111011b
        jmp     print
print1:
        cjne    A, #1, print2
        mov     A, #00001010b
        jmp     print
print2:
        cjne    A, #2, print3
        mov     A, #01110011b
        jmp     print
print3:
        cjne    A, #3, print4
        mov     A, #01011011b
        jmp     print
print4:
        cjne    A, #4, print5
        mov     A, #11001010b
        jmp     print
print5:
        cjne    A, #5, print6
        mov     A, #11011001b
        jmp     print
print6:
        cjne    A, #6, print7
        mov     A, #11111001b
        jmp     print
print7:
        cjne    A, #7, print8
        mov     A, #00001011b
        jmp     print
print8:
        cjne    A, #8, print9
        mov     A, #11111011b
        jmp     print
print9:
        cjne    A, #9, print
        mov     A, #11011011b
printA:
        cjne    A, #10, print
        mov     A, #11110111b
printB:
        cjne    A, #11, print
        mov     A, #11111111b
printC:
        cjne    A, #12, print
        mov     A, #11111111b ;ПЕРЕДЕЛАТЬ
printD:
        cjne    A, #13, print
        mov     A, #11111111b ;ПЕРЕДЕЛАТЬ
printE:
        cjne    A, #13, print
        mov     A, #11111111b;ПЕРЕДЕЛАТЬ
printF:
        cjne    A, #13, print
        mov     A, #11111111b;ПЕРЕДЕЛАТЬ
print:
        movx    @DPTR, A
ret

end