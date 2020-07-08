org 0
ljmp start

org 00bh
  inc r5        ; r5 - часть секунды (по 50000 мкс)
  cjne r5, #20, outp
  mov r5, #0    ; Когда пройдёт 20 частей, сбросим счётчик
  inc r2        ; и увеличим количество секунд
outp:
  mov th0, #3Ch     ; Запись в t0 15536,
  mov tl0, #0B0h    ; чтобы до прерывания прошло 50000 мкс
  clr tf0           ; Снятие бита переполнения t0
  reti

org 8100h

print:
; Вывод часов в 1 и 2 лампах
  mov A, r4
  mov B, #10
  div AB        ; В a - десятки, в b - единицы
  orl A, #10h   ; Светить в первой лампе, старший байт = 1. В млодшем десятки
  movx @dptr, A
  mov A, B
  orl A, #20h   ; Светить во второй лампе, старший байт = 2. В млодшем единицы
  movx @dptr, A

  mov A, r2
  anl A, #1b
  jnz skip
; Аналогично для минут в 3 и 4 лампах
  mov A, r3
  mov B, #10
  div AB
  orl A, #40h
  movx @dptr, A
  mov A, B
  orl A, #80h
  movx @dptr, A
skip:
  ret

start:
  mov r5, #0
  mov dptr, #3
  mov A, #82h
  movx @dptr, A
  mov dptr, #2  ; Адрес порта C

  mov r2, #0    ; Секунды
  mov r3, #0    ; Минуты
  mov r4, #0    ; Часы

  setb ea   ; Разрешить прерывания
  setb et0  ; Разрешить прерывание переполнения нулевого таймера
  ;mov ie, #10010010b
  mov tmod, #00000001b  ; Первый режим работы нулевого таймера
  mov th0, #3Ch         ; Запись в t0 15536,
  mov tl0, #0B0h        ; чтобы до прерывания прошло 50000 мкс
  setb tr0              ; Включение нулевого таймера
overflow:
; Вывод, затем изменение нужных единиц времени
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
