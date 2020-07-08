org 0h
	mov P1, #0ffh
	mov R6, #0h
	mov R3, #0h
	
mR2:    mov R2, #0h
mR4:	mov R4, #0b
initP0:
	mov A, #239 ; А = 11101111b
	mov P0, A
	mov R0, #5h
start:
	jb P0.0, mP0
        mov A, R4
        clr c
        subb A, #1
	jnz mR2
	jmp mR4    
mP0: mov A, P0
	rr A
	dec R0
	mov P0, A
	;обработка только одной нажатой клавиши
	mov A, P1
	clr c
	subb A, #0feh
	jz continue
	mov A, P1
	clr c
	subb A, #0fdh
	jz continue
	mov A, P1
	clr c
	subb A, #0fbh
	jz continue
	mov A, P1
	clr c
	subb A, #0f7h
	jz continue
	mov A, P1
	clr c
	subb A, #0efh
	jz continue
	jmp start
continue:
	mov R4, #1
	mov A, P1
	xrl A,#0ffh 	
	mov R7,A 		
	mov R1, #0h 
	mov A, R0 		
	mov R5, A 		
	;N column
	mov A,R7 		
	jz start
j1:	inc R1
	mov B,#2h 		
	div AB
	jnz j1
	mov A, R1
	mov R6, A	
	;цифра или буква
	subb A, #4h
	jc digits 
	jmp liter 
tostart:
	jmp start
digits:
	mov A, R5
	subb A, #3h
	jc digit
	mov A, R6
	subb A, #1h
	jz digitA
	mov A, R6
	subb A, #2h
	jz digit0
	mov A, R6
	subb A, #3h
	jz digitB
	jmp start 
digitA: mov A, #41h
	jmp print
digit0: mov A, #30h
	jmp print
digitB: mov A, #42h
	jmp print
digit:
	mov B, #3h
	mov A, R5
	dec A
	mul AB
	add A, R6
	add A, #30h
	jmp print
liter:
	mov B, #2h
	mov A, R5
	dec A
	mul AB
	add A, R6
	subb A, #3h
	add A, #42h
	jmp print
print:
	mov R7, A
	xrl A, R2
	jz tostart
	mov A, R7
	mov R2, A		
	mov SCON,#01100010b  ; первый режим работы, запретить прием 
	orl TMOD,#00100000b  ;исп. внутренний г-р, разрешить режим автоподгрузки
	mov TH0, #0fdh       ; Настроить скорость на 9600
	mov TL0, #0fdh
	setb TR1  
	mov SBUF, A
	clr TI
	mov SBUF, #13
	clr TI
	mov SBUF, #10
	clr TI
	clr TR1
	jmp start
end
