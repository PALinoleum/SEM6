; A - number of rotations
;R0 - 10 ms
;R1 - 1 sec
;R2 - 30 sec
;R3 - speed
;R4 - x
;R5 - x counter;
;R6 - save A
;R7 - switch

org 0h
ljmp start

org 0bh 
;counter
reti

org 1bh ;timer

jmp areas

org 8100h

areas:
cjne R7, #1, tim1

tim2:
	;clr p1.5
	;clr p1.7
	;cjne R3, #2, checkA2
	;mov R3, #0
	;setb p1.5
	;setb p1.7

	inc R5	
	mov R6, A	
	mov A, R4	
	clr C	
	subb A, R5	
	anl A, #80h
	jz checkA2
	setb p1.5
	setb p1.7
	cjne R5, #31, checkA2
	mov R5, #0

	inc R3	
	cjne R3, #2, checkA2
	mov R3, #0

	clr p1.5
	clr p1.7
checkA2:	
	
	mov A, R6	
	inc A
	cjne A, #40, skip2
	mov A, #0
	inc R0
	cjne R0, #100, skip2
	mov R0, #0
	inc R1
	dec R4
	cjne R1, #30, skip2
	inc R2
	skip2:
	mov th0, #5
	clr tf0
	reti

	tim1:
	inc R3	
	clr p1.5
	clr p1.7
	cjne R3, #3, checkA1
	mov R3, #0
	setb p1.5
	setb p1.7
	checkA1:	
		inc A
		cjne A, #40, skip1
		mov A, #0
		inc R0
		cjne R0, #100, skip1
		mov R0, #0
		inc R1
		cjne R1, #31, skip1
		inc R2
	skip1:
		mov th0, #5
		clr tf0
		reti

start:
	setb p1.7
	setb p1.6
	setb p1.5
	setb p1.4

	mov DPTR, #3
	mov A, #82h
	movx @DPTR, A
	mov A, TMOD
	orl A, #00000111b
	mov TMOD, A

	setb ea
	setb et0
	setb et1

	clr p1.5
	clr p1.7

	mov R7, #0

	mov tl0, #130
	mov th0, #5

	mov A, #0
	mov R0, #0
	mov R1, #0	
	mov R2, #0
	mov R3, #0
	setb tr1
	cycle1:
		cjne R2, #1, $

	mov R7, #1

	mov tl0, #130
	mov th0, #5

	mov A, #0
	mov R0, #0
	mov R1, #0
	mov R2, #0
	mov R3, #0
	mov R4, #30	
	mov R5, #0
	setb tr1
	cycle2:
		cjne R2, #1, $

	setb p1.5
	setb p1.7
end