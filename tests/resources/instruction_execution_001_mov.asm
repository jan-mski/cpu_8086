bits 16

; Registers
mov ax, 0x1111
mov al, 0x34
mov ah, 0x12

mov bx, 0x2222
mov bl, 0x45
mov bh, 0x23

mov cx, 0x3333
mov cl, 0x56
mov ch, 0x34

mov dx, 0x4444
mov dl, 0x67
mov dh, 0x45

mov sp, ax
mov bp, bx
mov si, cx
mov di, dx

mov ss, sp
mov ds, bp
mov es, si
mov cs, di

mov ax, cs
mov bx, es
mov cx, ds
mov dx, ss

; Memory
mov byte [1000], 10
mov byte [1001], 20
mov byte [1002], 30
mov byte [1003], 40

mov al, [1000]
mov ah, [1001]
mov cl, [1002]
mov ch, [1003]

mov word [1004], 10
mov word [1006], 20
mov word [1008], 30
mov word [1010], 40

mov dx, [1004]
mov bp, [1006]
mov sp, [1008]
mov di, [1010]

mov word [1012], 1000
mov word [1014], 2000
mov word [1016], 3000
mov word [1018], 4000

mov dx, [1012]
mov bp, [1014]
mov sp, [1016]
mov di, [1018]

mov bx, 1000
mov si, 20

mov [bx + 20], 10
mov [bx + si + 2], 20
mov word [bx + 24], 30
mov word [bx + si + 6], 40
mov word [bx + 28], 1000
mov word [bx + si + 10], 2000

mov dx, [bx + 20]
mov bp, [bx + si + 2]
mov sp, [bx + 24]
mov di, [bx + si + 6]
mov ss, [bx + 28]
mov cs, [bx + si + 10]
