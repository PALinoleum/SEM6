org 0h
ljmp start

org 8100h
print:
	mov DPTR, #2
	mov R0, A ; количество у.е. напряжения
	anl A, #80h ; знак
	
	jnz plus
	
	mov A, #11; minus code
	jmp skip  
plus:
	mov A, #10
skip:
	orl A, #10h
	movx @DPTR, A 	
	
	mov A, R0
	anl A, #7Fh
	rl A

	mov B, #50
	div AB
	orl A, #20h
	movx @DPTR, A

	mov A, B
	mov B, #5
	div AB
	orl A, #40h
	movx @DPTR, A

	mov A, B
	rl A
	orl A, #80h
	movx @DPTR, A
	
	ret
start:
setb P1.0
mov DPTR, #3
mov A, #82h
movx @DPTR, A

mov DPTR, #0
mov A, #10000b
movx @DPTR, A

cycle:
	clr P1.0
	jb P1.1, $
	mov DPTR, #1
	movx A, @DPTR
	lcall print
	setb P1.0
	jmp cycle
; E1 = pa.4
; 1 = 40 mV 
end