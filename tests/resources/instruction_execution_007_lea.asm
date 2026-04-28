bits 16

mov bx, 0x1234
mov si, 0x2345

mov word [0x1234], 9999
mov word [0x2345], 9999

lea ax, [10]
lea cx, [1000]

lea dx, [bx]
lea bp, [bx + si]

lea sp, [bx + 10]
lea di, [bx - 10]

lea ax, [bx + 1000]
lea cx, [bx - 1000]

lea dx, [bx + si + 10]
lea bp, [bx + si - 10]

lea sp, [bx + si + 1000]
lea di, [bx + si - 1000]

mov bx, 0xFFFF
mov si, 2

lea ax, [bx + si]
