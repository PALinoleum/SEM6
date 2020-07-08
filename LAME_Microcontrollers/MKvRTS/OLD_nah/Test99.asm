org 0H
        ljmp start

org 8100H
start:
        mov DPTR, #3
        mov A, #82h ;A(0) - вывод, C(2) - вывод, B(1) -ввод
        movx @DPTR, A  
;ВЫВОД НА ИНДИКАТОР
        mov     A, #9
        mov     DPTR, #0
        lcall   printDigit

        mov     A, #9
        mov     DPTR, #2
        lcall   printDigit
        jmp     $
        ;FGEDCHBA
printDigit:
        cjne    A, #0, print1
        mov     A, #11011101b
        jmp     print
print1:
        cjne    A, #1, print2
        mov     A, #01010000b
        jmp     print
print2:
        cjne    A, #2, print3
        mov     A, #11001110b
        jmp     print
print3:
        cjne    A, #3, print4
        mov     A, #11011010b
        jmp     print
print4:
        cjne    A, #4, print5
        mov     A, #01010011b
        jmp     print
print5:
        cjne    A, #5, print6
        mov     A, #10011011b
        jmp     print
print6:
        cjne    A, #6, print7
        mov     A, #10011111b
        jmp     print
print7:
        cjne    A, #7, print8
        mov     A, #11010000b
        jmp     print
print8:
        cjne    A, #8, print9
        mov     A, #11011111b
        jmp     print
print9:
        cjne    A, #9, print
        mov     A, #11011011b

print:
        movx    @DPTR, A
ret

end