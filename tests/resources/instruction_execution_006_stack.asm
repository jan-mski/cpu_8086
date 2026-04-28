bits 16

mov sp, 256

mov ax, 4660
push ax
mov ax, 0
pop dx

mov bx, func
call bx
call func

jmp end

func:
    mov ax, 30583
    ret

end:
; terminate
