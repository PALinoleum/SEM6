org 0
ljmp start

org 00bh
	inc R5
	cjne R5, #20, outp
	mov r5, #0
	inc r2
outp:
	mov th0, #3Ch
	mov tl0, #0B0h
	clr tf0
	reti

org 8100h

print:
	mov A, R4
	mov B, #10
	div AB
	orl A, #10h
	movx @DPTR, A
	mov A, B
	orl A, #20h
	movx @DPTR, A

	mov A, R2
	anl A, #1b
	jnz skip

	mov A, R3
	mov B, #10
	div AB
	orl A, #40h
	movx @DPTR, A
	mov A, B
	orl A, #80h
	movx @DPTR, A
skip:
	ret

start:
mov R5, #0
mov DPTR, #3
mov A, #82h
movx @DPTR, A
mov DPTR, #2

mov R2, #0
mov R3, #0
mov R4, #0

setb ea
setb et0
mov tmod, #00000001b
mov th0, #3Ch
mov tl0, #0B0h
setb tr0
overflow:
lcall print
cjne r2, #60, overflow
inc r3
mov r2, #0
cjne r3, #60, overflow
inc r4
mov r3, #0
cjne r4, #24, overflow
mov r4, #0
jmp overflow

end