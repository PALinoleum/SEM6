org 0h

main:
	mov P1, #00111000b ;function set
	mov P0, #0 ; ser RS & E
	mov P1, #00001110b ;disp on
	mov P1, 00000110b ; entry mode
	setb P1.1
	mov P1, #01001000b ;write data H