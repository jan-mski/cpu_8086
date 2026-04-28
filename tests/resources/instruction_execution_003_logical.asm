bits 16

; Not
mov al, 254
not al

mov bx, 0
not bx

; And
mov cl, 1
mov ch, 254
and cl, ch

mov dx, 0
mov sp, 65280
and sp, dx

; Or
mov cl, 253
mov ch, 254
or cl, ch

mov dx, 65535
mov sp, 65280
or sp, dx

; Xor
mov cl, 253
mov ch, 254
xor cl, ch

mov dx, 65535
mov sp, 65280
xor sp, dx

; Test
mov cl, 1
mov ch, 254
test cl, ch

mov dx, 0
mov sp, 65280
test sp, dx
