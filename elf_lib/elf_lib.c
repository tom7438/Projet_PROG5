/***
 * elf_lib: mini librarie qui contient toutes les fonctions
 *          de lecture sur un fichier format ELF.
 *
 * À remplir au fur et à mesure des étapes.
 *
 * Voir elf_lib.h pour les structures.
**/

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "elf_lib/elf_lib.h"
#include "elf_lib/elf_utils.h"

/**
 * @brief Initialise et retourne l'en-tête du fichier ELF
 * 
 * @param f flux
 * @param elf_h pointeur en-tête ELF
 * @return en-tête ELF dans le pointeur spécifié
 */
void init_header(FILE *f, Elf32 * elf_h){
    size_t tmp; // pour la valeur de retour de fread

    // ---
    unsigned char tab_e_ident[EI_NIDENT];
    tmp = fread(&tab_e_ident, EI_NIDENT, 1, f);
    assert(tmp);

    if (tab_e_ident[EI_MAG0] != ELFMAG0 || tab_e_ident[EI_MAG1] != ELFMAG1 || tab_e_ident[EI_MAG2] != ELFMAG2 || tab_e_ident[EI_MAG3] != ELFMAG3 || tab_e_ident[EI_CLASS]!=ELFCLASS32) {
        fprintf(stderr, "Erreur, le fichier n'est pas au format ELF32\n");
        exit(EXIT_FAILURE);
    }

    // copie de tab_e_ident dans elf_h->e_dient
    memcpy(elf_h->e_ident, tab_e_ident, EI_NIDENT);

    // si on a du big endian!!
    if (elf_h->e_ident[EI_DATA] == ELFDATA2MSB) {
        bread_isBigEndian = 1;
    }

    tmp = bread(&elf_h->e_type, sizeof(uint16_t), 1, f);
    assert(tmp);
    tmp = bread(&elf_h->e_machine, sizeof(uint16_t), 1, f);
    assert(tmp);
    tmp = bread(&elf_h->e_version, sizeof(uint32_t), 1, f);
    assert(tmp);
    tmp = bread(&elf_h->e_entry, sizeof(Elf32_Addr), 1, f);
    assert(tmp);
    tmp = bread(&elf_h->e_phoff, sizeof(Elf32_Off), 1, f);
    assert(tmp);
    tmp = bread(&elf_h->e_shoff, sizeof(Elf32_Off), 1, f);
    assert(tmp);
    tmp = bread(&elf_h->e_flags, sizeof(uint32_t), 1, f);
    assert(tmp);
    tmp = bread(&elf_h->e_ehsize, sizeof(uint16_t), 1, f);
    assert(tmp);
    tmp = bread(&elf_h->e_phentsize, sizeof(uint16_t), 1, f);
    assert(tmp);
    tmp = bread(&elf_h->e_phnum, sizeof(uint16_t), 1, f);
    assert(tmp);
    tmp = bread(&elf_h->e_shentsize, sizeof(uint16_t), 1, f);
    assert(tmp);
    tmp = bread(&elf_h->e_shnum, sizeof(uint16_t), 1, f);
    assert(tmp);
    tmp = bread(&elf_h->e_shstrndx, sizeof(uint16_t), 1, f);
    assert(tmp);
}

/**
 * @brief Affiche dans la sortie spécifiée les
 *        informations de l'en-tête ELF
 * 
 * @param f flux
 * @param elf_h en-tête ELF
 */
void write_elf(FILE *f, Elf32 elf_h) {
    fprintf(f, "Magic Number : ");
    for(int k = 0; k < EI_NIDENT; k++){
        fprintf(f, "%.2x ",elf_h.e_ident[k]);
    }
    fprintf(f,"\n");

    fprintf(f,"Class:\t\t\t\t   ");
    if (elf_h.e_ident[EI_CLASS] == ELFCLASS32) fprintf(f,"ELF32\n");
    else fprintf(f,"None\n");

    fprintf(f,"Data:\t\t\t\t   ");
    if (elf_h.e_ident[EI_DATA] == ELFDATA2LSB) fprintf(f, "2's complement, little endian\n");
    else if (elf_h.e_ident[EI_DATA] == ELFDATA2MSB) fprintf(f, "2's complement, big endian\n");
    else fprintf(f, "Unkonwn data format\n");

    fprintf(f,"Version:\t\t\t   ");
    if (elf_h.e_ident[EI_VERSION] == EV_CURRENT) fprintf(f, "1 (current)\n");
    else fprintf(f,"0 (invalid)\n");

    fprintf(f,"OS/ABI:\t\t\t\t   ");
    switch (elf_h.e_ident[EI_OSABI]) {
        case ELFOSABI_SYSV: fprintf(f,"UNIX - System V\n"); break;
        case ELFOSABI_HPUX: fprintf(f,"HP-UX ABI\n"); break;
        case ELFOSABI_NETBSD: fprintf(f,"NetBSD ABI\n"); break;
        case ELFOSABI_LINUX: fprintf(f,"Linux ABI\n"); break;
        case ELFOSABI_SOLARIS: fprintf(f,"Solaris ABI\n"); break;
        case ELFOSABI_IRIX: fprintf(f,"IRIX ABI\n"); break;
        case ELFOSABI_FREEBSD: fprintf(f,"FreeBSD ABI\n"); break;
        case ELFOSABI_TRU64: fprintf(f,"TRU64 UNIX ABI\n"); break;
        case ELFOSABI_ARM: fprintf(f,"ARM Architecture ABI\n"); break;
        case ELFOSABI_STANDALONE: fprintf(f,"Stand-alone (embedded) ABI\n"); break;
        default: fprintf(f,"Unknown OS/ABI\n"); break;
    }

    fprintf(f,"ABI Version:\t\t\t   %d\n", elf_h.e_ident[EI_ABIVERSION]);

    fprintf(f,"Type:\t\t\t\t   ");
    switch (elf_h.e_type){
    	case ET_NONE: fprintf(f,"No file type\n"); break;
    	case ET_REL: fprintf(f,"REL (Relocatable file)\n"); break;
        case ET_EXEC: fprintf(f,"EXEC (Executable file)\n"); break;
        case ET_DYN: fprintf(f,"SO (Shared object file)\n"); break;
        case ET_CORE: fprintf(f,"Core file\n"); break;
        case ET_LOPROC:
        case ET_HIPROC: fprintf(f,"Processor Specific\n"); break;
        default: fprintf(f,"Unknown type\n"); break;
    }

    fprintf(f,"Machine:\t\t\t   ");
    switch (elf_h.e_machine){
    	case EM_M32: fprintf(f,"AT&T WE 32100\n"); break;
    	case EM_SPARC: fprintf(f,"SPARC\n"); break;
    	case EM_386: fprintf(f,"Intel 80386\n"); break;
    	case EM_68K: fprintf(f,"Motorola 68000\n"); break;
    	case EM_88K: fprintf(f,"Motorola 88000\n"); break;
    	case EM_860: fprintf(f,"Intel 80860\n"); break;
    	case EM_MIPS: fprintf(f,"MIPS I Architecture\n"); break;
    	case EM_MIPS_RS4_BE: fprintf(f,"MIPS RS4000 Big-Endian\n"); break;
    	case EM_PARISC: fprintf(f,"Hewlett-Packard PA-RISC\n"); break;
    	case EM_SPARC32PLUS: fprintf(f,"Enhanced instruction set SPARC\n"); break;
    	case EM_PPC: fprintf(f,"PowerPC\n"); break;
    	case EM_PPC64: fprintf(f,"64-bit PowerPC\n"); break;
    	case EM_S390: fprintf(f,"IBM System/390 Processor\n"); break;
    	case EM_ARM: fprintf(f,"Advanced RISC Machines ARM\n"); break;
    	case EM_SH: fprintf(f,"Hitachi SH\n"); break;
    	case EM_SPARCV9: fprintf(f,"SPARC Version 9\n"); break;
    	case EM_IA_64: fprintf(f,"Intel IA-64 processor architecture\n"); break;
    	case EM_X86_64: fprintf(f,"AMD x86-64 architecture\n"); break;
    	case EM_VAX: fprintf(f,"Digital VAX\n"); break;
    	default: fprintf(f,"%#x\n", elf_h.e_machine); break;
    }

    fprintf(f,"Version:\t\t\t   %#x\n",elf_h.e_version);
    fprintf(f,"Entry point address:\t\t   0x%x\n",elf_h.e_entry);
    fprintf(f,"Start of program headers:\t   %d (bytes into file)\n",elf_h.e_phoff);
    fprintf(f,"Start of section headers:\t   %d (bytes into file)\n",elf_h.e_shoff);
    fprintf(f,"Flags:\t\t\t\t   %#x, Version5 EABI\n",elf_h.e_flags);
    fprintf(f,"Size of this header:\t\t   %d (bytes)\n",elf_h.e_ehsize);
    fprintf(f,"Size of program headers:\t   %d (bytes)\n",elf_h.e_phentsize);
    fprintf(f,"Number of program headers:\t   %d\n",elf_h.e_phnum);
    fprintf(f,"Size of section headers:\t   %d (bytes)\n",elf_h.e_shentsize);
    fprintf(f,"Number of section headers:\t   %d\n",elf_h.e_shnum);
    fprintf(f,"Section header string table index: %d\n",elf_h.e_shstrndx);
}

/**
 * @brief Lit les en-têtes section ELF et les retournes
 *        dans un tableau
 * 
 * @param f flux
 * @param elf_h en-tête ELF
 * @param arr_elf_SH tableau d'en-têtes section
 */
void read_sections(FILE *f, Elf32 elf_h, Elf32_SH *arr_elf_SH) {
    fseek(f, elf_h.e_shoff, SEEK_SET);

    for (int i = 0; i < elf_h.e_shnum; i ++) {
        Elf32_SH sec;

        bread(&sec.sh_name, sizeof(uint32_t), 1, f);
        bread(&sec.sh_type, sizeof(uint32_t), 1, f);
        bread(&sec.sh_flags, sizeof(uint32_t), 1, f);
        bread(&sec.sh_addr, sizeof(uint32_t), 1, f);
        bread(&sec.sh_offset, sizeof(uint32_t), 1, f);
        bread(&sec.sh_size, sizeof(uint32_t), 1, f);
        bread(&sec.sh_link, sizeof(uint32_t), 1, f);
        bread(&sec.sh_info, sizeof(uint32_t), 1, f);
        bread(&sec.sh_addralign, sizeof(uint32_t), 1, f);
        bread(&sec.sh_entsize, sizeof(uint32_t), 1, f);
        arr_elf_SH[i] = sec;
    }
}

/**
 * @brief Affiche dans le flux spécifié les
 *        en-tête des sections ELF 
 * 
 * @param f flux
 * @param fout flux de sorite
 * @param elf_h en-tête ELF
 * @param arr_elf_SH tableau d'en-têtes section
 */
void print_sections_header(FILE *f, FILE *fout, Elf32 elf_h, Elf32_SH *arr_elf_SH) {
    
    fprintf(fout, "Section Headers (%d), starting at offset 0x%X:\n", elf_h.e_shnum, elf_h.e_shoff);
    fprintf(fout, " [Nr]\tName\t\t\tType\t\tAddr\tOff\tSize\tES\tFlg\tLk\tInf\tAl");
    fprintf(fout, "\n");

    for (int i = 0; i < elf_h.e_shnum; i ++) {

        Elf32_SH sectionHeader = arr_elf_SH[i];

        if (i > 9) fprintf(fout, " [%d]", i);
        else fprintf(fout, " [ %d]", i);

        fprintf(fout, "\t");
        fprintf(fout, "%-15.15s", read_name_from_STable(f, elf_h, arr_elf_SH[elf_h.e_shstrndx], sectionHeader.sh_name));
        fprintf(fout, "\t\t");
        switch (sectionHeader.sh_type) {
            case SHT_NULL: fprintf(fout, "%-10s", "NULL"); break;
            case SHT_PROGBITS: fprintf(fout, "%-10s", "PROGBITS"); break;
            case SHT_SYMTAB: fprintf(fout, "%-10s", "SYMTAB"); break;
            case SHT_STRTAB: fprintf(fout, "%-10s", "STRTAB"); break;
            case SHT_RELA: fprintf(fout, "%-10s", "RELA"); break;
            case SHT_HASH: fprintf(fout, "%-10s", "HASH"); break;
            case SHT_DYNAMIC: fprintf(fout, "%-10s", "DYNAMIC"); break;
            case SHT_NOTE: fprintf(fout, "%-10s", "NOTE"); break;
            case SHT_NOBITS: fprintf(fout, "%-10s", "NOBITS"); break;
            case SHT_REL: fprintf(fout, "%-10s", "REL"); break;
            case SHT_SHLIB: fprintf(fout, "%-10s", "SHLIB"); break;
            case SHT_DYNSYM: fprintf(fout, "%-10s", "DYNSYM"); break;
            case SHT_LOPROC: fprintf(fout, "%-10s", "LOPROC"); break;
            case SHT_HIPROC: fprintf(fout, "%-10s", "HIPROC"); break;
            case SHT_LOUSER: fprintf(fout, "%-10s", "LOUSER"); break;
            case SHT_HIUSER: fprintf(fout, "%-10s", "HIUSER"); break;
            case SHT_ARM_ATTRIBUTES: fprintf(fout, "%-10s", "ARM_ATTRIBUTES"); break;
            default: fprintf(fout, "%x", sectionHeader.sh_type); break;
        }
        fprintf(fout, "\t");
        fprintf(fout, "%06x", sectionHeader.sh_addr);
        fprintf(fout, "\t");
        fprintf(fout, "%06x", sectionHeader.sh_offset);
        fprintf(fout, "\t");
        fprintf(fout, "%06x", sectionHeader.sh_size);
        fprintf(fout, "\t");
        fprintf(fout, "%02x", sectionHeader.sh_entsize);
        fprintf(fout, "\t");
        fprintf(fout, "%s", get_flags(sectionHeader.sh_flags));
        fprintf(fout, "\t");
        fprintf(fout, "%d", sectionHeader.sh_link);
        fprintf(fout, "\t");
        fprintf(fout, "%d", sectionHeader.sh_info);
        fprintf(fout, "\t");
        fprintf(fout, "%d", sectionHeader.sh_addralign);
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n Key to Flags:\n");
    fprintf(fout, "\tW (write), A (alloc), X (execute), M (merge), S (strings), I (info),\n");
    fprintf(fout, "\tL (link order), O (extra OS processing required), G (group), T (TLS)\n");
} 

/**
 * @brief Retourne dans le flux de sortie, le contenu en héxadecimal
 *        de la section spécifiée en argument, depuis le flux spécifié
 * 
 * @param f flux
 * @param fout flux de sortie
 * @param elf_h en-tête EFL
 * @param arr_elf_SH tableau d'en-têtes section
 * @param elf_SH en-tête section
 */
void read_data_section(FILE *f, FILE *fout, Elf32 elf_h, Elf32_SH *arr_elf_SH, Elf32_SH *elf_SH) {
    fseek(f, elf_SH->sh_offset, SEEK_SET);
    
    for (int i = 0; i < elf_SH->sh_size; i++) {
        if (i%4 == 0) fprintf(fout, " ");
        if (i%16 == 0) fprintf(fout, "\n0x%08x ", i);
        fprintf(fout, "%.2x", fgetc(f));
    }
}

/**
 * @brief Affiche le contenu en héxadecimal de la section 
 *        spécifiée en argument
 * 
 * @param f flux
 * @param fout flux de sortie
 * @param elf_h en-tête EFL
 * @param arr_elf_SH tableau d'en-têtes section
 * @param elf_SH en-tête section
 */
void print_data_section(FILE *f, FILE *fout, Elf32 elf_h, Elf32_SH *arr_elf_SH, Elf32_SH *elf_SH) {
    fprintf(fout, "\n");
    fprintf(fout, "Hex dump of section '%s':", read_name_from_STable(f, elf_h, arr_elf_SH[elf_h.e_shstrndx], elf_SH->sh_name));
    fprintf(fout, "\n");

    read_data_section(f, fout, elf_h, arr_elf_SH, elf_SH);
    fprintf(fout, "\n");
}


/*  Etape 4 */

/*
typedef struct {
    uint32_t      st_name;
    Elf32_Addr    st_value;
    uint32_t      st_size;
    unsigned char st_info;
    unsigned char st_other;
    uint16_t      st_shndx;
} Elf32_SYM;
*/

/* Elf32 *elf récupéré dans l'étape 1 et Elf32_SH * arr_elf_SH récupéré à l'étape 2 */
void read_symbol_section(FILE *f, Elf32 *elf_h, Elf32_SH *arr_elf_SH, Elf32_Sym *arr_elf_SYM){

    int i;
    int found = 0;
    for (i=0; i<elf_h->e_shnum; i++){
        if(arr_elf_SH[i].sh_type == SHT_SYMTAB){
            found = 1;
            break;
        }
    }
    // si pas de .symtab, erreur
    if (found == 0) exit(1);
  
    fseek(f, arr_elf_SH[i].sh_offset, SEEK_SET);
    Elf32_Sym elf_SYM;
    for (int j=0; j<arr_elf_SH[i].sh_size; j++){
        bread(&elf_SYM.st_name,sizeof(uint32_t),1,f);
        bread(&elf_SYM.st_value,sizeof(Elf32_Addr),1,f);
        bread(&elf_SYM.st_size,sizeof(uint32_t),1,f);
        bread(&elf_SYM.st_info,sizeof(unsigned char),1,f);
        bread(&elf_SYM.st_other,sizeof(unsigned char),1,f);
        bread(&elf_SYM.st_shndx,sizeof(uint16_t),1,f);
        arr_elf_SYM[j]=elf_SYM;
    }
}

void print_symbol_header(FILE *f, Elf32_Sym elf_SYM) {
	fprintf(f," %08x",elf_SYM.st_value);

	fprintf(f,"\n");
}

void print_symbols_header(FILE *f, Elf32_Sym * arr_elf_SYM) {
	size_t taille=sizeof(arr_elf_SYM);
	fprintf(f,"\n");
	fprintf(f, "Symbol table '.symtab' contains %lu entries:\n",taille);
	fprintf(f,"   Num:    Value  Size Type    Bind   Vis      Ndx Name\n");
    for(int i=0; i<taille; i++){
    	fprintf(f,"     %d:",i);
    	print_symbol_header(f,arr_elf_SYM[i]);
    }
}



/* Etape 5 */
void fnprototype(FILE *f, void * Elf32){

}
