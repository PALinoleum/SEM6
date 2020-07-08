org 0h
	ljmp init

org 0bh
	ljmp prer

org 8100h
init:
	mov r0, #0 ;счётчик времени
	mov r1, #0 ;флаг периода шим
	mov r2, #0 ;установленное время
	mov r3, #0 ;флаг
    mov r4, #0 ;флаг
	mov r5, #0 ;флаг
	mov r7, #0 ;инверсия

	mov a, tmod
	orl a, #2
	mov tmod, a
	mov th0, #0FEh ;1мс
	mov tl0, #0
	setb ea
	setb et0
	setb tr0

	setb P1.5
	setb P1.7
    clr P1.4
	clr P1.6


start:

    mov R3, #60
    mov R1, #0
    mov R5, #0

    jmp $

prer:
    clr tr0
    cjne R5, #0, exit ;если стоит флаг - выход
    
    next:
    cjne R1, #0, cycle2 ;переход к состоянию шим в периоде
	
    cycle1: ;цикл включения вперёд
        mov A, R3 ;время 1 полупериода
        cjne A, 0, move ;сравнение со значением R0

    mov R1, #1 ;уставнока режима 1

    cycle2: ;цикл включения назад
        cjne R0, #100, reversMove;время 2 полупериода
    
    mov R1, #0 ;возвращаем в начало
    mov R0, #0
    jmp exit

    move: 
	setb P1.5
	setb P1.7
    clr P1.4
	clr P1.6
	inc R0 ;увеличиваем внутренний счетчик
    jmp exit


    reversMove:
    setb P1.4
	setb P1.6
	clr P1.5
	clr P1.7
    inc R0 ;увеличиваем внутренний счетчик
    jmp exit

exit:
    setb tr0
	reti

end