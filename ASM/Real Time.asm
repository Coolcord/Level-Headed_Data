Original Code:
ldy GameTimerDisplay       ;otherwise check first digit [ACF807]
dey                        ;if first digit not on 1, [88]
bne ResGTCtrl              ;branch to reset game timer control [D00C]
lda GameTimerDisplay+1     ;otherwise check second and third digits [ADF907]
ora GameTimerDisplay+2     ; [0DFA07]
bne ResGTCtrl              ;if timer not at 100, branch to reset game timer control [D004]
lda #TimeRunningOutMusic   ; [A940]
sta EventMusicQueue        ;otherwise load time running out music [85FC]


New Code Below:

IsTimeRunningOut: (0x3784)
lda GameTimerDisplay       ; [ADF807]
bne ResGTCtrl              ; [D00D]
lda GameTimerDisplay+1     ; [ADF907]
cmp #$04                   ; [C904]
bne ResGTCtrl              ; [D007]
lda GameTimerDisplay+2     ; [ADFA07]
jmp RemainingCode          ; [4CXXXX]
ResGTCtrl:

RemainingCode: (0x411B)
bne ResGTCtrl              ; [F004]
lda #TimeRunningOutMusic   ; [A940]
sta EventMusicQueue        ;otherwise load time running out music [85FC]
jmp ResGTCtrl ($B786)      ; [4C86B7]
