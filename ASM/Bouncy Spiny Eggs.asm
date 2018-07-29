Jump from around here:
0x6005
jmp 0x40FD               ; [4CEDC0]


0x40FD
bne #$03 (skip jmp)             ; [D003]
jmp $E0E2                       ; Jump absolute [4CE2E0]
ldy Enemy_ID,x                  ; [B416]
cpy #Spiny                      ; if enemy object is spiny, branch [C012]
bne #$03 (skip jmp)             ; [D003]
jmp 0x5FE9                      ; [4CD9DF]
jsr $E1B5                       ; [20AEE1]
beq -$11 (to jmp $E0E2)         ; [F0EF]
jmp 0x600F                      ; Jump absolute [4CFFDF]


0x5FE9 = Where bounce code should point to
0x6007 = A jump to $E0E2. You may just want to jump directly there
0x600F = Normal code. Send non-spiny eggs here.

