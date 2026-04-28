bits 16

mov bh, cl
mov di, cx
mov dx, [19]
mov dx, [3066]
mov bh, [bp + di + 90]
mov bl, [bp + di]
mov bl, [bp + di + 4000]
mov cx, [bx + si]
mov cx, [bp + si - 44]
mov ax, [bp - 38]
mov ax, [bx]
mov cx, [4150]
mov [bx], bh
mov [bx + di], dl
mov [bp + si], dx
mov [3065], cx
mov [18], cx
mov [di - 360], dx
mov [bx + si], byte 8
mov [si + 1081], word 416
mov ax, -4738
mov ax, 4738
mov dx, -54
mov dx, 54
mov bh, -54
mov dl, 54

push cx
push ds
push [3600]
push [bx + di]
push [bp + si - 36]

pop di
pop es
pop [4]
pop [bx + di]
pop [bp + si - 3600]

xchg [bp + 60], sp
xchg cx, [bx - 1200]

xchg cx, ax
xchg cx, si
xchg cx, di
xchg cx, bp
xchg cx, cx

xchg dl, bh
xchg dx, ax
xchg di, dx

in al, dx
in ax, dx
in ax, 255

out dx, al
out 255, ax

xlat

lea cx, [bx - 60]
lea cx, [bp + si + 1704]
lea bp, [bx - 1204]
lea si, [bp + di - 8]

lds cx, [bx - 60]
lds cx, [bp + si + 1704]
lds bp, [bx - 1204]
lds si, [bp + di - 8]

les cx, [bx - 60]
les cx, [bp + si + 1704]
les bp, [bx - 1204]
les si, [bp + di - 8]

pushf
popf
lahf
sahf

add bh, bl
add dx, cx
add bl, 11
add bh, 36
add di, 6
add bp, 470
add cx, 1200
add [bx + si + 6000], bh
add [bp], bl
add dx, [bx]
add ax, [bp + di]

adc bh, bl
adc dx, cx
adc bl, 11
adc bh, 36
adc di, 6
adc bp, 470
adc cx, 1200
adc [bx + si + 6000], bh
adc [bp], bl
adc dx, [bx]
adc ax, [bp + di]

inc bh
inc bl
inc cx
inc dx
inc bp
inc byte [bx]
inc byte [bx + 1202]
inc byte [bp + di + 6]
inc word [11219]
inc word [bp + 47]
inc word [bx + si - 12053]

daa
aaa

sub di, 6
sub dx, cx
sub bh, bl
sub [bx + si + 6000], bh
sub bl, 11
sub cx, 1200
sub bp, 470
sub ax, [bp + di]
sub [bp], bl
sub dx, [bx]
sub bh, 36

sbb dx, cx
sbb bh, bl
sbb cx, 1200
sbb bl, 11
sbb bh, 36
sbb ax, [bp + di]
sbb dx, [bx]
sbb [bp], bl
sbb [bx + si + 6000], bh

dec cx
dec bl
dec bh
dec byte [bx]
dec byte [bp + di + 6]
dec byte [bx + 1202]
dec word [11219]
dec word [bx + si - 12053]
dec word [bp + 47]

neg cx
neg bh
neg bl
neg byte [bx]
neg byte [bx + 1202]
neg word [bx + si - 12053]
neg word [11219]
neg word [bp + 47]
neg byte [bp + di + 6]

cmp cx, 28691
cmp byte [bp], 41
cmp cx, dx
cmp [bx + 2], di
cmp bh, [bx + 468]
cmp cl, 24

das
aas

mul word [bx]
mul byte [bp + si + 600]
mul dx
mul bl

imul word [11380]
imul byte [bp]
imul bh
imul ax

aam

div bp
div word [bx + si + 1200]
div cl
div byte [bp + di + 3588]

div byte [bx + di]
div word [bp + 592]
idiv cx

cwd
aad
cbw

not bp
not di
not word [bx]
not byte [bx + 11886]
not cl
not bh

ror bh, 1
rol dx, 1
rcl bp, 1
rcr sp, 1
sar cx, 1
shl bh, 1
shr cx, 1

ror word [5926], cl
shl word [bx + 6], cl
rcr word [bp], cl
shr byte [bp + di - 239], cl
rcl byte [4], cl
sar byte [bp + si - 360], cl
rol word [bx], cl

rol dx, cl
sar cx, cl
shr cx, cl
rcr sp, cl
shl bh, cl
ror bh, cl
rcl bp, cl

rcr word [bp], cl
sar byte [bp + si - 360], cl
rol byte [bx], cl
rcl byte [4], cl
shl word [bx + 6], cl
ror byte [5926], cl
shr word [bp + di - 239], cl

and bl, 112
and [bx + di + 12], bh
and dx, [5261]
and byte [bx - 47], 255
and word [bp + di - 5198], 12394
and [bp + si + 1200], ax
and cx, 24470
and cx, [bx]
and si, bp
and bl, bh
and bh, dl

test [bx + 2], di
test byte [bp], 41
test cx, 28691
test cx, dx
test cl, 24
test bh, [bx + 468]

or [bp + si + 1200], ax
or word [bp + di - 5198], 12394
or cx, 24470
or byte [bx - 47], 255
or dx, [5261]
or sp, di
or bl, bh
or bh, dl
or [bx + di + 12], bh
or bl, 112
or cx, [bx]

xor sp, di
xor bl, bh
xor bh, dl
xor cx, [bx]
xor dx, [5261]
xor bl, 112
xor byte [bx - 47], 255
xor word [bp + di - 5198], 12394
xor cx, 24470
xor [bx + di + 12], bh
xor [bp + si + 1200], ax

movsb
cmpsb
scasb
lodsb
movsw
cmpsw
scasw
lodsw
rep movsb

call [bx - 120]
call bp
call cx
call [47041]

jmp si
jmp cx
jmp [5274]
jmp [14]

ret 600
ret
ret -8

some_label:
je some_label
jl some_label
jle some_label
jb some_label
jbe some_label
jp some_label
jo some_label
js some_label
jne some_label
jnl some_label
jg some_label
jnb some_label
ja some_label
jnp some_label
jno some_label
jns some_label
loop some_label
loopz some_label
loopnz some_label
jcxz some_label

int3
int 16

iret
into

clc
cmc
stc
cld
std
cli
sti
hlt
wait
