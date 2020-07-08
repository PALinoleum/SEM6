org 00h

mov dph, #1
mov dpl, #0
clr p0.7

loop:
	mov a, #0
	movc a, @a+dptr
	mov p1, a
	inc dpl
	jmp loop

org 0100h
;синусоида
db  07fh, 065h, 04dh, 036h, 023h, 013h, 08h, 01h, 00h, 04h, 0dh, 01bh, 02ch, 041h, 059h, 072h, 08ch, 0a5h, 0bdh, 0d2h, 0e3h, 0f1h, 0fah, 0feh, 0fdh, 0f6h, 0ebh, 0dbh, 0c8h, 0b1h, 099h, 07fh, 07fh, 065h, 04dh, 036h, 023h, 013h, 08h, 01h, 00h, 04h, 0dh, 01bh, 02ch, 041h, 059h, 072h, 08ch, 0a5h, 0bdh, 0d2h, 0e3h, 0f1h, 0fah, 0feh, 0fdh, 0f6h, 0ebh, 0dbh, 0c8h, 0b1h, 099h, 07fh, 07fh, 065h, 04dh, 036h, 023h, 013h, 08h, 01h, 00h, 04h, 0dh, 01bh, 02ch, 041h, 059h, 072h, 08ch, 0a5h, 0bdh, 0d2h, 0e3h, 0f1h, 0fah, 0feh, 0fdh, 0f6h, 0ebh, 0dbh, 0c8h, 0b1h, 099h, 07fh, 07fh, 065h, 04dh, 036h, 023h, 013h, 08h, 01h, 00h, 04h, 0dh, 01bh, 02ch, 041h, 059h, 072h, 08ch, 0a5h, 0bdh, 0d2h, 0e3h, 0f1h, 0fah, 0feh, 0fdh, 0f6h, 0ebh, 0dbh, 0c8h, 0b1h, 099h, 07fh, 07fh, 065h, 04dh, 036h, 023h, 013h, 08h, 01h, 00h, 04h, 0dh, 01bh, 02ch, 041h, 059h, 072h, 08ch, 0a5h, 0bdh, 0d2h, 0e3h, 0f1h, 0fah, 0feh, 0fdh, 0f6h, 0ebh, 0dbh, 0c8h, 0b1h, 099h, 07fh, 07fh, 065h, 04dh, 036h, 023h, 013h, 08h, 01h, 00h, 04h, 0dh, 01bh, 02ch, 041h, 059h, 072h, 08ch, 0a5h, 0bdh, 0d2h, 0e3h, 0f1h, 0fah, 0feh, 0fdh, 0f6h, 0ebh, 0dbh, 0c8h, 0b1h, 099h, 07fh, 07fh, 065h, 04dh, 036h, 023h, 013h, 08h, 01h, 00h, 04h, 0dh, 01bh, 02ch, 041h, 059h, 072h, 08ch, 0a5h, 0bdh, 0d2h, 0e3h, 0f1h, 0fah, 0feh, 0fdh, 0f6h, 0ebh, 0dbh, 0c8h, 0b1h, 099h, 07fh




;треугольный
;db 00h, 02h, 04h, 06h, 08h, 0ah, 0ch, 0eh, 010h, 012h, 014h, 016h, 018h, 01ah, 01ch, 01eh, 020h, 022h, 024h, 026h, 028h, 02ah, 02ch, 02eh, 030h, 032h, 034h, 036h, 038h, 03ah, 03ch, 03eh, 040h, 042h, 044h, 046h, 048h, 04ah, 04ch, 04eh, 050h, 052h, 054h, 056h, 058h, 05ah, 05ch, 05eh, 060h, 062h, 064h, 066h, 068h, 06ah, 06ch, 06eh, 070h, 072h, 074h, 076h, 078h, 07ah, 07ch, 07eh, 080h, 082h, 084h, 086h, 088h, 08ah, 08ch, 08eh, 090h, 092h, 094h, 096h, 098h, 09ah, 09ch, 09eh, 0a0h, 0a2h, 0a4h, 0a6h, 0a8h, 0aah, 0ach, 0aeh, 0b0h, 0b2h, 0b4h, 0b6h, 0b8h, 0bah, 0bch, 0beh, 0c0h, 0c2h, 0c4h, 0c6h, 0c8h, 0cah, 0cch, 0ceh, 0d0h, 0d2h, 0d4h, 0d6h, 0d8h, 0dah, 0dch, 0deh, 0e0h, 0e2h, 0e4h, 0e6h, 0e8h, 0eah, 0ech, 0eeh, 0f0h, 0f2h, 0f4h, 0f6h, 0f8h, 0fah, 0fch, 0feh, 0feh, 0fch, 0fah, 0f8h, 0f6h, 0f4h, 0f2h, 0f0h, 0eeh, 0ech, 0eah, 0e8h, 0e6h, 0e4h, 0e2h, 0e0h, 0deh, 0dch, 0dah, 0d8h, 0d6h, 0d4h, 0d2h, 0d0h, 0ceh, 0cch, 0cah, 0c8h, 0c6h, 0c4h, 0c2h, 0c0h, 0beh, 0bch, 0bah, 0b8h, 0b6h, 0b4h, 0b2h, 0b0h, 0aeh, 0ach, 0aah, 0a8h, 0a6h, 0a4h, 0a2h, 0a0h, 09eh, 09ch, 09ah, 098h, 096h, 094h, 092h, 090h, 08eh, 08ch, 08ah, 088h, 086h, 084h, 082h, 080h, 07eh, 07ch, 07ah, 078h, 076h, 074h, 072h, 070h, 06eh, 06ch, 06ah, 068h, 066h, 064h, 062h, 060h, 05eh, 05ch, 05ah, 058h, 056h, 054h, 052h, 050h, 04eh, 04ch, 04ah, 048h, 046h, 044h, 042h, 040h, 03eh, 03ch, 03ah, 038h, 036h, 034h, 032h, 030h, 02eh, 02ch, 02ah, 028h, 026h, 024h, 022h, 020h, 01eh, 01ch, 01ah, 018h, 016h, 014h, 012h, 010h, 0eh, 0ch, 0ah, 08h, 06h, 04h, 02h, 00h

;квадратный
;db  192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h, 192h, 63h
