.286
.MODEL SMALL

; Структура для вызова драйвера
IPXSPX_REGS struc
    rax     dw ?
    rbx     dw      ?
    rcx     dw      ?
    rdx     dw      ?
    rsi     dw      ?
    rdi     dw      ?
    res     dw      ?
IPXSPX_REGS ends

.DATA
; Точка входа в драйвер
_ipxspx_drv_entry       dd ?

.CODE
;Обьявление процедур
PUBLIC  _ipxspx_entry, _ipx_init
PUBLIC  _ipxspx_drv_entry

;Вызов драйвера
_ipxspx_entry PROC FAR

;Переносим адрес вершины стека в bp для обращения к аргументам 
    push    bp
    mov     bp,sp

;Сохраняем регистры в стек
    push    es
    push    di
    push    si
    push    dx
    push    cx
    push    bx
    push    ax

;Загружаем регистры из структуры, которая передана как аргумент функции
    push    ds
    mov     bx, [bp+6]   ;смещение
    mov     ds, [bp+8]   ;сегмент
    mov     es, ds:[bx].res
    mov     di, ds:[bx].rdi
    mov     si, ds:[bx].rsi
    mov     dx, ds:[bx].rdx
    mov     cx, ds:[bx].rcx
    mov     ax, ds:[bx].rax
    mov     bx, ds:[bx].rbx
    pop     ds

;Вызываем драйвер
    call    [dword ptr _ipxspx_drv_entry]

;Сохраняем регистры
    push    ds
    push    dx
    mov     dx, bx

;Записываем в структуры возвращенные драйвером
    mov     bx, [bp+6]   ;смещение
    mov     ds, [bp+8]   ;сегмент
    mov     ds:[bx].rax, ax
    mov     ds:[bx].rcx, cx
    mov     ds:[bx].rbx, dx
    pop     dx
    mov     ds:[bx].rdx, dx
    pop     ds

; Восстанавливаем регистры
    pop     ax
    pop     bx
    pop     cx
    pop     dx
    pop     si
    pop     di
    pop     es

    pop     bp
    retf
_ipxspx_entry ENDP


;Инициализация драйвера и получение точки входа
_ipx_init PROC NEAR

;Сохранение вершины стека
    push    bp
    mov     bp,sp

;Переносим в ax значение отвечающее за драйвер IPX
    mov     ax, 7a00h

;Вызываем мультиплексорное прерывание
    int     2fh

;Прерывание возращает в al точку входа в драйвер или 0xFF если драйвер не обнаружен.
    cmp     al, 0ffh
    jne     _ipx_init_exit

;Сохраняем адрес точки входа в переменную
    mov     word ptr _ipxspx_drv_entry+2, es
    mov     word ptr _ipxspx_drv_entry, di

_ipx_init_exit:
    ;В регистре ax прерывание помещает код выхода
        mov     ah, 0
        pop     bp
        ret
_ipx_init ENDP
end