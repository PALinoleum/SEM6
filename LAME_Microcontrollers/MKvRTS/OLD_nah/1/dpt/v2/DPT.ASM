org 0000h
	jmp START

org 000Bh
	jmp COUNT
	
org 001Bh
	jmp TIMER
	
org 8100h

N EQU 28h ;skorost
Tarea EQU 29h ;vremya uchastka
etalon EQU 2Ah ;dlya zadaniya skvazhnosti
k EQU 2Bh ; 3 schetnyh peremennyh
i EQU 2Ch ;
j EQU 2Dh ;
REG0 EQU 40h
REG1 EQU 41h
REG2 EQU 42h
REG3 EQU 43h
REG4 EQU 44h
REG5 EQU 46h
REG6 EQU 52h
area EQU 45h
EDIN EQU 47h
NUL1 EQU 48h
DESTK EQU 49h
NUL2 EQU 4Ah
adr EQU 51h
sec1 EQU 53h
sec2 EQU 54h

START:
  ;zagruzka upravl slova
  setb P1.7
  setb P1.6
  setb P1.5
  setb P1.4
  mov DPTR, #3h
  mov A,  #10000010b
  movx @DPTR, A
  mov DPTR, #2h
  ;timer
  mov 55h, 2Fh
  mov 2Fh, TMOD
  setb 78h
  setb 79h
  setb 7Ah
  mov TMOD, 2Fh
  mov 2Fh, 55h
  setb ET0 ;dayem dobro na preryvanie
  setb ET1
  setb EA
  mov sec1, #0
  mov sec2, #0
  ;podgotovka chetchika
  mov N, #0
  mov NUL1, #0
  mov NUL2, #0
  mov adr, #47h
  mov TL0, #5
  setb TR0 ; go!
  ;setb TR1

BEGIN:
  mov area, #1
  mov Tarea, #3
    call AREA1
  mov area, #2
  mov Tarea, #6
    call AREA2
  mov area, #3
  mov Tarea, #2
  mov etalon, #1
    call AREA3
  mov area, #3
  mov Tarea, #2
  mov etalon, #2
    call AREA3
  mov area, #5
  mov Tarea, #3
	call AREA5
	
  setb P1.7
  setb P1.6
  setb P1.5
  setb P1.4
jmp $

VPERED:
  setb P1.7
  clr P1.6
RET

NAZAD:
  setb P1.6
  clr P1.7
RET

AREA1:
  call VPERED
  mov A, #0
  mov i, #0
  mov j, #0
  mov k, #0
  mov etalon, #0
  mov TH0, #5
  setb TR1 ;zapuskaem taymer
  met1:
    mov A, REG0
    setb P1.5
	clr P1.4
	cjne A, etalon, $
	clr P1.5
	setb P1.4
  cjne A, #100, $ ;100
  mov REG0, #0
  inc i
  inc REG4
  mov A, REG4
  cjne A, #3, met2
    inc etalon
	mov REG4, #0
  met2:
  mov A, i
  cjne A, #100, met1 ;100
  inc j
  mov i, #0
  mov A, j
  cjne A, Tarea, met1
  clr TR1
RET

AREA2:
  call VPERED
  mov A, #0
  mov i, #0
  mov j, #0
  mov k, #0
  mov etalon, #0
  mov TH0, #5
  setb TR1 ;zapuskaem taymer
  met3:
    mov A, REG0
    setb P1.4
	clr P1.5
	cjne A, etalon, $
	clr P1.4
	setb P1.5
  cjne A, #200, $ ;200
  mov REG0, #0
  inc i
  inc REG4
  mov A, REG4
  cjne A, #3, met4
    inc etalon
	mov REG4, #0
  met4:
  mov A, i
  cjne A, #100, met3 ;100
  inc j
  mov i, #0
  mov A, j
  cjne A, Tarea, met3
  clr TR1
RET

AREA3:
  call NAZAD
  mov A, #0
  mov i, #0
  mov j, #0
  mov k, #0
  mov TH0, #5
  setb TR1 ;zapuskaem taymer
  met5:
    mov A, REG0
    setb P1.4
	clr P1.5
	cjne A, etalon, $
	clr P1.4
	setb P1.5
  cjne A, #3, $
  mov REG0, #0
  inc i
  mov A, i
  cjne A, #100, met5 ;100
  inc j
  mov i, #0
  mov A, j
  cjne A, Tarea, met5
  clr TR1
RET

AREA5:
  call NAZAD
  mov A, #0
  mov i, #0
  mov j, #0
  mov k, #0
  mov TH0, #5
  setb TR1 ;zapuskaem taymer
  mov etalon, #0
  setb TR1 ;zapuskaem taymer
  met7:
    mov A, REG0
    setb P1.5
	clr P1.4
	cjne A, etalon, $
	clr P1.5
	setb P1.4
  cjne A, #100, $ ;100
  mov REG0, #0
  inc i
  inc REG4
  mov A, REG4
  cjne A, #3, met6
    inc etalon
	mov REG4, #0
  met6:
  mov A, i
  cjne A, #100, met7 ;100
  inc j
  mov i, #0
  mov A, j
  cjne A, Tarea, met7
  clr TR1
RET

SPEED:
  mov REG6, A
  mov A, N
  mov N, #0
  RL A ;nado umnozhit na 2, t.k. za odno perepoln. schetchika
          ; proishodit 2 oborota
  mov B, #10
  DIV AB
  ORL A, #01000000b
  mov DESTK, A
  mov A, B
  ORL A, #10000000b
  mov EDIN, A
  mov A, REG6
RET

COUNT:
  mov TL0, #7
  inc N
RETI

TIMER: 
  mov TH0, #7
  mov REG3, R0
  mov REG5, R1
  mov 55h, A
  ;naschitivayem sekundu
  inc sec1
  mov A, sec1
  cjne A, #0, metN
    inc sec2
  metN:
  mov A, sec2
  cjne A, #15, DALSHE
    call SPEED
    mov sec2, #0
  ;konec
  DALSHE:
  mov A, 55h
  mov R1, area
  inc k
  mov R0, k
  cjne R1, #1, uch2
    cjne R0, #4, exit1
    inc A
    mov k, #0
	jmp exit1
  uch2:
    cjne R1, #2, uch3
      cjne R0, #2, exit1
      inc A
      mov k, #0
	  jmp exit1  
  uch3:
    cjne R1, #3, uch5
	  cjne R0, #131, exit1
      inc A
      mov k, #0
	  jmp exit1  
  uch5:
    cjne R0, #4, exit1
    inc A
    mov k, #0
exit1:
;vivod skorosti
mov R0, A
mov R1, adr
mov A, @R1
movx @DPTR, A
cjne R1, #4Ah, exit2
  mov adr, #46h
exit2:
mov A, R0
inc adr
mov R0, REG3
mov R1, REG5
RETI

END
