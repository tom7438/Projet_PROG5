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
#include "elf_lib/elf_lib.h"

/* Étape 1 */
void init_header(FILE *f, Elf32 * elf_h){
    size_t tmp; //Pour stocker la valeur de retour de fread
    unsigned char tab_e_ident[EI_NIDENT];
    tmp=fread(tab_e_ident, sizeof(unsigned char), EI_NIDENT, f);

    if (tab_e_ident[EI_MAG0] != ELFMAG0 || tab_e_ident[EI_MAG1] != ELFMAG1 || tab_e_ident[EI_MAG2] != ELFMAG2 || tab_e_ident[EI_MAG3] != ELFMAG3 || tab_e_ident[EI_CLASS]!=ELFCLASS32) {
        fprintf(stderr, "Erreur, le fichier n'est pas au format ELF32\n");
        exit(EXIT_FAILURE);
    }

    // copie de tab_e_ident dans elf_h->e_dient
    memcpy(elf_h->e_ident, tab_e_ident, EI_NIDENT);

    fread(&elf_h->e_type, 1, 1, f); // ca marche avec (?)

    tmp=fread(&elf_h->e_type, sizeof(uint16_t), 1, f);
    tmp=fread(&elf_h->e_machine, sizeof(uint16_t), 1, f);
    tmp=fread(&elf_h->e_version, sizeof(uint32_t), 1, f);
    tmp=fread(&elf_h->e_entry, sizeof(Elf32_Addr), 1, f);
    tmp=fread(&elf_h->e_phoff, sizeof(Elf32_Off), 1, f);
    tmp=fread(&elf_h->e_shoff, sizeof(Elf32_Off), 1, f);
    tmp=fread(&elf_h->e_flags, sizeof(uint32_t), 1, f);
    tmp=fread(&elf_h->e_ehsize, sizeof(uint16_t), 1, f);
    tmp=fread(&elf_h->e_phentsize, sizeof(uint16_t), 1, f);
    tmp=fread(&elf_h->e_phnum, sizeof(uint16_t), 1, f);
    tmp=fread(&elf_h->e_shentsize, sizeof(uint16_t), 1, f);
    tmp=fread(&elf_h->e_shnum, sizeof(uint16_t), 1, f);
    tmp=fread(&elf_h->e_shstrndx, sizeof(uint16_t), 1, f);

    fprintf(stdout,"Valeur de retour du dernier fread = %lu\n", tmp); //Test

}

void write_elf(FILE *f, Elf32 elf_h) {
    fprintf(f, "Magic Number : ");
    for(int k = 0; k < EI_NIDENT; k++){
        fprintf(f, "%d ",elf_h.e_ident[k]);
        }
    fprintf(f,"\n");
    
    fprintf(f,"Class:\t\t\t");
    if (elf_h.e_ident[EI_CLASS] == ELFCLASS32) fprintf(f,"ELF32\n");
    else fprintf(f,"None\n");
    
    fprintf(f,"Data:\t\t\t");
    if (elf_h.e_ident[EI_DATA] == ELFDATA2LSB) fprintf(f, "2's complement, little endian\n");
    else if (elf_h.e_ident[EI_DATA] == ELFDATA2MSB) fprintf(f, "2's complement, big endian\n");
    else fprintf(f, "Unkonwn data format\n");
    
    fprintf(f,"Version:\t\t\t");
    if (elf_h.e_ident[EI_VERSION] == EV_CURRENT) fprintf(f, "1 (current)\n");
    else fprintf(f,"0 (invalid)\n");
    
    fprintf(f,"OS/ABI:\t\t\t");
    switch (elf_h.e_ident[EI_OSABI]) {
    case ELFOSABI_SYSV :
    fprintf(f,"UNIX - System V\n");break;
    case ELFOSABI_HPUX:
    fprintf(f,"HP-UX ABI\n");break;
    case ELFOSABI_NETBSD:
    fprintf(f,"NetBSD ABI\n");break;
    case ELFOSABI_LINUX:
    fprintf(f,"Linux ABI\n");break;
    case ELFOSABI_SOLARIS :
    fprintf(f,"Solaris ABI\n");break;
    case ELFOSABI_IRIX:
    fprintf(f,"IRIX ABI\n");break;
    case ELFOSABI_FREEBSD :
    fprintf(f,"FreeBSD ABI\n");break;
    case ELFOSABI_TRU64:
    fprintf(f,"TRU64 UNIX ABI\n");break;
    case ELFOSABI_ARM:
    fprintf(f,"ARM Architecture ABI\n");break;
    case ELFOSABI_STANDALONE:
    fprintf(f,"Stand-alone (embedded) ABI\n");break;
    default:
    fprintf(f,"Unknown OS/ABI\n");
    }

    fprintf(f,"ABI Version:\t\t\t0\n"); //elf_h.e_ident[EI_ABIVERSION]

    fprintf(f,"Type:\t\t\t");
    switch (elf_h.e_type){
    	case ET_NONE:
    	fprintf(f,"No file type\n");break;
    	case ET_REL:
			fprintf(f,"REL (Relocatable file)\n");break;
			case ET_EXEC:
			fprintf(f,"EXEC (Executable file)\n");break;
			case ET_DYN:
			fprintf(f,"SO (Shared object file)\n");break;
			case ET_CORE:
			fprintf(f,"Core file\n");break;
			case ET_LOPROC:
			case ET_HIPROC:
			fprintf(f,"Processor Specific\n");break;
			default:
			fprintf(f,"Unknown type\n");
    }

    fprintf(f,"Machine:\t\t\t");
    switch (elf_h.e_machine){
    	case EM_M32:
    	fprintf(f,"AT&T WE 32100\n");break;
    	case EM_SPARC:
    	fprintf(f,"SPARC\n");break;
    	case EM_386:
    	fprintf(f,"Intel 80386\n");break;
    	case EM_68K:
    	fprintf(f,"Motorola 68000\n");break;
    	case EM_88K:
    	fprintf(f,"Motorola 88000\n");break;
    	case EM_860:
    	fprintf(f,"Intel 80860\n");break;
    	case EM_MIPS:
    	fprintf(f,"MIPS I Architecture\n");break;
    	case EM_MIPS_RS4_BE:
    	fprintf(f,"MIPS RS4000 Big-Endian\n");break;
    	case EM_PARISC:
    	fprintf(f,"Hewlett-Packard PA-RISC\n");break;
    	case EM_SPARC32PLUS:
    	fprintf(f,"Enhanced instruction set SPARC\n");break;
    	case EM_PPC:
    	fprintf(f,"PowerPC\n");break;
    	case EM_PPC64:
    	fprintf(f,"64-bit PowerPC\n");break;
    	case EM_S390:
    	fprintf(f,"IBM System/390 Processor\n");break;
    	case EM_ARM:
    	fprintf(f,"Advanced RISC Machines ARM\n");break;
    	case EM_SH:
    	fprintf(f,"Hitachi SH\n");break;
    	case EM_SPARCV9:
    	fprintf(f,"SPARC Version 9\n");break;
    	case EM_IA_64:
    	fprintf(f,"Intel IA-64 processor architecture\n");break;
    	case EM_X86_64:
    	fprintf(f,"AMD x86-64 architecture\n");break;
    	case EM_VAX:
    	fprintf(f,"Digital VAX\n");break;
    	default:
    	fprintf(f,"%#x\n", elf_h.e_machine);break; //Affichage avec le 0x devant la veleur héxa
    }

    fprintf(f,"Version:\t\t\t%#x\n",elf_h.e_version);

    fprintf(f,"Entry point address:\t\t%#x\n",elf_h.e_entry);

		fprintf(f,"Start of program headers:\t\t %d (bytes into file)\n",elf_h.e_phoff);

		fprintf(f,"Start of section headers:\t\t %d (bytes into file)\n",elf_h.e_shoff);

		fprintf(f,"Flags:\t\t\t %#x, Version5 EABI\n",elf_h.e_flags);

		fprintf(f,"Size of this header:\t\t\t %d (bytes)\n",elf_h.e_ehsize);

		fprintf(f,"Size of program headers:\t\t\t %d (bytes)\n",elf_h.e_phentsize);

		fprintf(f,"Number of program headers:\t\t\t %d\n",elf_h.e_phnum);

		fprintf(f,"Size of section headers:\t\t\t %d (bytes)\n",elf_h.e_shentsize);

		fprintf(f,"Number of section headers:\t\t\t %d\n",elf_h.e_shnum);

		fprintf(f,"Section header string table index:\t\t\t %d\n",elf_h.e_phnum);

} 

/* Etape 2 */
/* readelf -S */
void read_sections(FILE *f, Elf32 *elf_h, Elf32_SH **arr_elf_SH);
void read_section(FILE *f, Elf32 *elf_h, Elf32_SH *elf_SH);
void print_sections_header(FILE *f, Elf32_SH **arr_elf_SH);
void print_section_header(FILE *f, Elf32_SH *elf_SH);

/* Etape 3 */
/* readelf -x num */
void read_data_section(FILE *f, Elf32_SH *elf_SH);
void print_data_section(FILE *f, Elf32_SH *elf_SH);

/* Etape 5 */
void fnprototype(FILE *f, void * Elf32){

}
