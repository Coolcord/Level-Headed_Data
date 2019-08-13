      cmp #Goomba               ;if enemy object not goomba, branch ahead of this routine  [C906]
      bne CheckSpiny            ; [D003]
      jsr KillEnemyAboveBlock   ;if enemy object IS goomba, do this sub  [208EE1]

      jmp CheckSpiny            ; [4CF9C0]

CheckSpiny:
      cmp #Spiny                ;if enemy object not spiny, branch ahead of this routine  [C912]
      bne GiveOEPoints          ; [D003]
      jsr KillEnemyAboveBlock   ;if enemy object IS spiny, do this sub  [208EE1]

GiveOEPoints:
      lda #$01                  ;award 100 points for hitting block beneath enemy  [A901]
      jsr SetupFloateyNumber    ; [2011DA]

      jmp ChkToStunEnemies      ; [4C1BE0]


0x4109-0x4117





Fireballs go through fire:

cmp #BuzzyBeetle           ; [C902]
beq RTS                    ; [F007]
cmp #Spiny                 ; [C912]
beq RTS                    ; [F003]
jmp BACK_TO_CODE           ; [4C58D7]
RTS                        ; [60]

Total Bytes: 14


0x40FD-0x4108