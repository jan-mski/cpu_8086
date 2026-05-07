bits 16

; Prints the following content to memory:
;
;  88888888  00000000  88888888  66666666
;  88    88  00    00  88    88  66
;  88    88  00    00  88    88  66
;  88888888  00    00  88888888  66666666
;  88    88  00    00  88    88  66    66
;  88    88  00    00  88    88  66    66
;  88888888  00000000  88888888  66666666

mov  di, 1024 ; Output
mov  si,  704 ; Constants
mov  sp,  768 ; Stack

; Constants
mov  word [si],       8 ; digit width
mov  word [si + 2],   2 ; digit thickness
mov  word [si + 4],   4 ; digit hollow space width
mov  word [si + 6],   2 ; delimiter width
mov  word [si + 8],  10 ; char: LF
mov  word [si + 10], 13 ; char: CR
mov  word [si + 12], 32 ; char: Space
mov  word [si + 14], 48 ; char: 0
mov  word [si + 16], 54 ; char: 6
mov  word [si + 18], 56 ; char: 8

call print_newline
call print_newline

call print_line_top_bottom
call print_line_upper_half
call print_line_upper_half
call print_line_middle
call print_line_bottom_half
call print_line_bottom_half
call print_line_top_bottom

call print_newline

jmp  end

print_newline:
    ; -- optional CR for Windows --
    ;mov al, [si + 10]
    ;mov byte [di], al
    ;inc di
    ; -- --
    mov  al, [si + 8]
    mov  byte [di], al
    inc  di

    ret

print_line_top_bottom:
    call print_delimiter

    push word [si + 18]
    call print_digit_wide
    add  sp, 2

    call print_delimiter

    push word [si + 14]
    call print_digit_wide
    add  sp, 2

    call print_delimiter

    push word [si + 18]
    call print_digit_wide
    add  sp, 2

    call print_delimiter

    push word [si + 16]
    call print_digit_wide
    add  sp, 2

    call print_newline

    ret

print_line_upper_half:
    call print_delimiter

    push word [si + 18]
    call print_digit_hollow
    add  sp, 2

    call print_delimiter

    push word [si + 14]
    call print_digit_hollow
    add  sp, 2

    call print_delimiter

    push word [si + 18]
    call print_digit_hollow
    add  sp, 2

    call print_delimiter

    push word [si + 16]
    call print_digit_side
    add  sp, 2

    call print_newline

    ret

print_line_middle:
    call print_delimiter

    push word [si + 18]
    call print_digit_wide
    add  sp, 2

    call print_delimiter

    push word [si + 14]
    call print_digit_hollow
    add  sp, 2

    call print_delimiter

    push word [si + 18]
    call print_digit_wide
    add  sp, 2

    call print_delimiter

    push word [si + 16]
    call print_digit_wide
    add  sp, 2

    call print_newline

    ret

print_line_bottom_half:
    call print_delimiter

    push word [si + 18]
    call print_digit_hollow
    add  sp, 2

    call print_delimiter

    push word [si + 14]
    call print_digit_hollow
    add  sp, 2

    call print_delimiter

    push word [si + 18]
    call print_digit_hollow
    add  sp, 2

    call print_delimiter

    push word [si + 16]
    call print_digit_hollow
    add  sp, 2

    call print_newline

    ret

print_digit_wide:
    push bp
    mov  bp, sp

    push word [si]
    push word [bp + 4]
    call print_n_chars
    add  sp, 4

    pop bp
    ret

print_digit_hollow:
    push bp
    mov  bp, sp
    mov  ax, [bp + 4] ; digit

    push ax
    call print_digit_side
    add  sp, 2

    push word [si + 4]
    push word [si + 12]
    call print_n_chars
    add  sp, 4

    push ax
    call print_digit_side
    add  sp, 2

    pop bp
    ret

print_digit_side:
    push bp
    mov  bp, sp

    push word [si + 2]
    push word [bp + 4] ; digit
    call print_n_chars
    add  sp, 4

    pop  bp
    ret

print_delimiter:
    ; Print "  "
    push word [si + 6]
    push word [si + 12]
    call print_n_chars
    add  sp, 4

    ret

print_n_chars:
    push bp
    mov  bp, sp

    mov  cl, [bp + 4] ; char value
    mov  ch, [bp + 6] ; num chars

    print_n_chars_loop:
        mov [di], cl
        inc di
        dec ch
        jnz print_n_chars_loop

    pop  bp
    ret

end:
; Terminate
