Jump from around here:
0x6005
jmp 0x40FD               ; [4CEDC0]


0x40FD
bne #$03 (ldy Enemy_ID,x); [D003]
jmp $E0E2                ; Jump absolute [4CE2E0]
ldy Enemy_ID,x           ; [B416]
cpy #Spiny               ;if enemy object is spiny, branch [C012]
bne #$03 (jmp 0x600A)    ; [D003]
jmp 0x5FE9               ; [4CD9DF]
jmp 0x600A               ; Jump absolute [4CFADF]


0x5FE9 = Where bounce code should point to
0x6007 = A jump to $E0E2. You may just want to jump directly there
0x600A = Normal code. Send non-spiny eggs here.
