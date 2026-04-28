bits 16

mov cl, 5

; Shr
mov al, 254
shr al, 1
shr al, cl

mov bx, 65535
shr bx, 1
shr bx, cl

; Sar
mov ah, 254
sar ah, 1
sar ah, cl

mov ah, -76
sar ah, 1
sar ah, cl

mov dx, 1000
sar dx, 1
sar dx, cl

mov dx, -1000
sar dx, 1
sar dx, cl

; Shl
mov bl, 254
shl bl, 1
shl bl, cl

mov sp, 65535
shl sp, 1
shl sp, cl
