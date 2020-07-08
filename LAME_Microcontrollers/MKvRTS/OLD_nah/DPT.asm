org 0h
	ljmp init

org 0bh
	ljmp prer

org 8100h
init:
	mov r0, #0 ;счётчик времени
	mov r1, #0 ;счётчик времени периода шим
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



start:
    mov R2, #15000 ;15 сек
    mov R3, #75 ;50% шим
    mov R7, 0; обнуляем глобальный счётчик

    cjne R5, #1, $


    mov R4, #75
    cycle_2uch:
        mov R2, #600 ;0.6 сек
        mov A, R4
        mov R3, A
        mov R7, 0; обнуляем глобальный счётчик 
        cjne R5, #1, $
        inc R4
    cjne R4, #101, cycle_2uch

    mov R4, #100
    cycle_2uch:
        mov R2, #600 ;0.6 сек
        mov A, R4
        mov R3, A
        mov R7, 0; обнуляем глобальный счётчик
        cjne R5, #1, $
        dec R4
    cjne R4, #101, cycle_2uch
        
    mov R2, #15000 ;15 сек
    mov R3, #75 ;50% шим
    mov R7, 0; обнуляем глобальный счётчик
    cjne R5, #1, $

    clr P1.4
	clr P1.6
	clr P1.5
	clr P1.7
    jmp $

prer:
	inc R0 ;увеличиваем внутренний счетчик

    mov A, R2 ;проверка глобального времени
    cjne A, 7, next
        mov R5, #1;установка флага выхода
        jmp exit
    
    next:
    inc R7 ;счётчик глобального времени
    cjne R1, #0, cycle2 ;переход к состоянию шим в периоде
	
    cycle1: ;цикл включения вперёд
        mov A, R3 ;время 1 полупериода
        cjne A, 0, move

    mov R1, #1 ;уставнока режима 1

    cycle2: ;цикл включения назад
        cjne R0, 100, reversMove;время 2 полупериода
    
    mov R1, #0 ;возвращаем в начало
    mov R0, #0
    jmp exit

    move: 
	setb P1.5
	setb P1.7
    clr P1.4
	clr P1.6

    jmp exit


    reversMove:
    setb P1.4
	setb P1.6
	clr P1.5
	clr P1.7
    jmp exit

exit:
	reti

end