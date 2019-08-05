(0x06D2) jmp START_WITH_FIRE_FLOWER


(0x4089) START_WITH_FIRE_FLOWER:
  lda #$02  [A902]
  sta PlayerStatus  [8D5607]
  lda #$00  [A900]
  sta PlayerSize  [8D5407]
  jsr DrawPlayer_Intermediate  [20A4EF]  <-- For Infinite Lives, replace with jmp NoInter  [4CE086]
  jmp BACK_TO_CODE  [4CC586]



