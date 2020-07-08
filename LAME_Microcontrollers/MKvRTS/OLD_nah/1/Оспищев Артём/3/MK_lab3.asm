org 0h
ljmp start

org 8100h
print:
	mov dptr, #2
	mov r0, A	; Количество у.е. напряжения
	anl A, #80h	; Знак

	jnz plus

	mov A, #11	; minus code
	jmp skip
plus:
	mov A, #10
skip:
	orl A, #10h
	movx @dptr, A

	mov A, r0
	anl A, #7Fh
	rl A

	mov B, #50
	div AB
	orl A, #20h
	movx @dptr, A

	mov A, B
	mov B, #5
	div AB
	orl A, #40h
	movx @dptr, A

	mov A, B
	rl A
	orl A, #80h
	movx @dptr, A
	ret


start:
	setb p1.0
	mov dptr, #3
	mov A, #82h
	movx @dptr, A

	mov dptr, #0		; Порт A
	mov A, #10000b
	movx @dptr, A

cycle:
	clr p1.0
	jb p1.1, $		; Пока единица, дальше не идём
	mov dptr, #1	; Порт B
	movx A, @dptr	; Из внешней памяти (порта B) считываем код напряжения в A
	lcall print
	setb p1.0
	jmp cycle
; E1 = pa.4
; 1 = 40 mV
end
