@ Programme tabmult : Affiche les tables de multiplication de de 1 a 10
N_MAX= 100
   .data
barre :  .byte '|'
         .byte 0
espace : .byte ' '
         .byte 0
tirets : .asciz "---"

debutTab:    .skip N_MAX*N_MAX*4   @ adresse du debut du tableau

   .text
   .global main
main: push {lr}

    @ remplissage du tableau
        @ a completer...
    
    MOV r0,#N_MAX @r0 contient N_MAX
    LDR r1, ptr_debutTab @r1 contient l’adresse du tableau 
    MOV r2,#0 @variable i
    MOV r3,#0 @variable valeur
    MOV r4,#0 @variable compteur
    MOV r5,#1 @variable deplacement

debut_pour : cmp r2,r0
    beq fin_pour
debut_si : cmp r4,#10
    beq si
    ADD r3,r3,r5 @sinon
    b fin_si
si : ADD r5,r5,#1 @si
    MOV r4,#0
    MOV r3,r5
fin_si :
    ADD r4,r4,#1
    MOV r7,r1 @on copie l’adresse de debut de tableau
    ADD r7,r7,r2,lsl#2 @adresse en fonction de i
    STR r3,[r7]
    ADD r2,r2,#1
    b debut_pour
fin_pour : 





    @ affichage du tableau
        @ a completer...
    
    mov r2,#0 @n_lig
    mov r3,#0 @n_col
    mov r4,#10 @normalement on devrait avoir N_MAX mais vu que l'affichage etait fait pour un tableau de 2 dimensions
               @on remplace N_MAX par 10 
    mov r5,#0 @indice pour avancer dans le tableau

@boucle pour sur les lignes
debut_pour_lig: cmp r2,r4
    beq fin_pour_lig
    mov r3,#0

@boucle pour sur les colonnes
debut_pour_col: cmp r3,r4
    beq fin_pour_col
    ldr r1,adr_barre
    bl EcrChn 
    ldr r6,ptr_debutTab
    add r6,r6,r5,lsl #2 @on incremente l'adresse à partir de debutTab pour avoir le bon indice
    ldr r7,[r6]

@premier si    
debut_si_100: cmp r7,#100
    bhs fin_si_100 @ici on utilise bhs car on pourrait avoir des nombres plus grand que 100 et on entrait alors dans la boucle ce 
                   @n'est pas ce que l'on voudrait
    ldr r1,adr_espace
    bl EcrChn
fin_si_100:

@deuxieme si
debut_si_10: cmp r7,#10
    bhs fin_si_10
    ldr r1,adr_espace
    bl EcrChn
fin_si_10:

    mov r1,r7
    bl EcrNdecim32
    add r3,r3,#1
    add r5,r5,#1
    b debut_pour_col
fin_pour_col:

    ldr r1,adr_barre
    bl EcrChn
    bl AlaLigne

@faire les lignes de tirets
    mov r8,#0
debut_pour_barre: cmp r8,r4
    beq fin_pour_barre
    ldr r1,adr_barre
    bl EcrChn
    ldr r1,adr_tirets
    bl EcrChn
    add r8,r8,#1
    b debut_pour_barre 
fin_pour_barre:
    
    ldr r1,adr_barre
    bl EcrChn
    bl AlaLigne    
    add r2,r2,#1
    b debut_pour_lig
fin_pour_lig:

fin: pop {lr}
     bx lr

ptr_debutTab : .word debutTab
adr_barre :    .word barre
adr_espace :   .word espace
adr_tirets :   .word tirets
