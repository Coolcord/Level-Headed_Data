Enter into code from 0x60E6

4CF8C0

	lda Enemy_ID,x         ; [B516]
	cmp #$Spiny            ; [C912]
	bne NORMAL_CODE        ; [D005]
	lda #$05               ; [A905]
	sta Enemy_State,x      ; [951E]
	rts                    ; [60]

NORMAL_CODE:
	lda #$00               ; [A900]
	sta Enemy_State,x      ; [951E]
	rts                    ; [60]
