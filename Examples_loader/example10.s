    .data
D1:    .word  266
D2:    .hword 42
D3:    .byte 12

    .text
    .global main
main:
      LDR r3, LD_D1
      LDR r4, [r3]
      MOV r1, r3
      BL EcrHexa32
      MOV r1, r4
      BL EcrNdecimal32

      LDR r5, LD_D2
      LDRH r6, [r5]
      MOV r1, r5
      BL EcrHexa32
      MOV r1, r6
      BL EcrNdecimal16

      LDR r7, LD_D3
      LDRB r8, [r7]
      MOV r1, r7
      BL EcrHexa32
      MOV r1, r8
      BL EcrNdecimal8

fin:  B exit  @ terminaison immédiate du processus (plus tard on saura faire mieux)

LD_D1:   .word D1
LD_D2:   .word D2
LD_D3:   .word D3

