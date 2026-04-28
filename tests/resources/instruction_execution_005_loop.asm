bits 16

mov ax, 4
mov bx, 100

mov cx, 5
mov di, 0
init_loop:
    add cx, di
	mov [bx + di], cx
	add di, 2
	cmp di, ax
	jnz init_loop

mov cx, 0
mov di, 0
add_loop:
	add cx, [bx + di]
	add di, 2
	cmp di, ax
	jnz add_loop
