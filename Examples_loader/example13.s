@ Programme tabmult : Affiche les tables de multiplication de de 1 a 10
N_MAX= 10
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
    
    mov r2,#1 @n_lig
    mov r3,#1 @n_col
    mov r4,#N_MAX
    ldr r6,ptr_debutTab
    
debut_pour_remp_lig: cmp r2,#N_MAX
    @si n_lig>NMAX on sort de la boucle
    bhi fin_pour_remp_lig
    @on remet n_col a 0
    mov r3,#1

debut_pour_remp_col: cmp r3,#N_MAX
    bhi fin_pour_remp_col
    
@multiplication
    mov r7,#0 @resultat de la multiplication
    mov r8,#0 @compteur de boucle
debut_multi: cmp r8,r2
    beq fin_multi
    add r7,r7,r3
    add r8,r8,#1
    b debut_multi
fin_multi:
    
    @ici l adresse finale sera stockee dans r8
    MOV r8,r2 @on copie x
    MOV r9,r3 @on copie y
    SUB r8,r8,#1
    SUB r9,r9,#1
    MUL r0,r8,r4
    ADD r8,r0,r9
    MOV r10,#4 @on met 4 dans le registre 10 pour pouvoir faire la multiplication
    MUL r0,r8,r10 
    ADD r8,r0,r6 @on rajoute l adresse de debut de tableau
    STR r7,[r8]

    add r3,r3,#1
    b debut_pour_remp_col
fin_pour_remp_col:    

    add r2,r2,#1
    b debut_pour_remp_lig
fin_pour_remp_lig:




    @ affichage du tableau
        @ a completer...
    
    mov r2,#0 @n_lig
    mov r3,#0 @n_col
    mov r4,#N_MAX 
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
debut_pour_barre: cmp r8,#N_MAX
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
