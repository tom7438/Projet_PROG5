    .data
cc: @ ne pas modifier cette partie
    .byte 0x42
    .byte 0x4f
    .byte 0x4e
    .byte 0x4a
    .byte 0x4f
    .byte 0x55
    .byte 0x52
    .byte 0x00     @ code de fin de chaine
    @ la suite pourra etre modifiee 
    .word 12
    .word 0x11223344
    dd:
        .asciz "au revoir..."

    .text
    .global main
main:

@ impression de la chaine de caractere d'adresse cc
     ldr r1, LD_cc
     ldrb r2, [r1]
     add r2, r2, #0x20
     strb r2, [r1]
     add r1, r1, #1
     ldr r2, [r1]
     add r2, r2, #0x20
     strb r2, [r1]
     add r1, r1, #1
     ldr r2, [r1]
     add r2, r2, #0x20
     strb r2, [r1]
     add r1, r1, #1
     ldr r2, [r1]
     add r2, r2, #0x20
     strb r2, [r1]
     add r1, r1, #1
     ldr r2, [r1]
     add r2, r2, #0x20
     strb r2, [r1]
     add r1, r1, #1
     ldr r2, [r1]
     add r2, r2, #0x20
     strb r2, [r1]
     add r1, r1, #1
     ldr r2, [r1]
     add r2, r2, #0x20
     strb r2, [r1]
     ldr r1, LD_cc
     bl EcrChaine

@ modification de la chaine d'adresse cc
@ A COMPLETER
     ldr r1, LD_dd
     bl EcrChaine

fin: B exit  @ terminaison immédiate du processus (plus tard on saura faire mieux)

LD_cc: .word cc
LD_dd: .word dd
