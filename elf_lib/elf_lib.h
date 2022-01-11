#include <stdint.h>
#include <stdio.h>
#ifndef __HEADER_ELF_H__
#define __HEADER_ELF_H__

/** e_ident[] **/
#define	EI_MAG0		    0
#define	EI_MAG1		    1
#define	EI_MAG2		    2
#define	EI_MAG3		    3
#define	EI_CLASS        4
#define	EI_DATA		    5
#define	EI_VERSION	    6
#define  EI_OSABI        7
#define  EI_ABIVERSION   8
#define	EI_PAD		    9
#define EI_NIDENT       16

/* EI_MAG */
#define	ELFMAG0		    0x7f
#define	ELFMAG1		    'E'
#define	ELFMAG2		    'L'
#define	ELFMAG3		    'F'

/* EI_CLASS */
#define	ELFCLASSNONE	0
#define	ELFCLASS32	    1
#define	ELFCLASS64	    2

/* EI_DATA */
#define ELFDATANONE	    0
#define ELFDATA2LSB	    1
#define ELFDATA2MSB	    2

/* EI_VERSION or EV_CURRENT */
#define EV_NONE		    0
#define EV_CURRENT	    1


/** e_type **/
#define ET_NONE         0
#define ET_REL          1
#define ET_EXEC         2
#define ET_DYN          3
#define ET_CORE         4
#define ET_LOPROC       0xff00
#define ET_HIPROC       0xffff

/** e_machine **/
/* #define ET_NONE      0 déjà défini dans le e_type */
#define EM_M32          1
#define EM_SPARC        2
#define EM_386          3
#define EM_68K          4
#define EM_88K          5
#define EM_860          7
#define EM_MIPS         8
#define EM_MIPS_RS4_BE  10
#define EM_PARISC       15
#define EM_SPARC32PLUS  18
#define EM_PPC          20
#define EM_PPC64        21
#define EM_S390         22
#define EM_ARM          40
#define EM_SH           42
#define EM_SPARCV9      43
#define EM_IA_64        50
#define EM_X86_64       62
#define EM_VAX          75

/** Special Section Indexes **/
#define SHN_UNDEF	    0
#define SHN_LORESERVE	0xff00
#define SHN_LOPROC	    0xff00
#define SHN_HIPROC	    0xff1f
#define SHN_ABS		    0xfff1
#define SHN_COMMON	    0xfff2
#define SHN_HIRESERVE	0xffff

/**  sh_type **/
#define SHT_NULL	    0
#define SHT_PROGBITS	1
#define SHT_SYMTAB	    2
#define SHT_STRTAB	    3
#define SHT_RELA	    4
#define SHT_HASH	    5
#define SHT_DYNAMIC	    6
#define SHT_NOTE	    7
#define SHT_NOBITS	    8
#define SHT_REL		    9
#define SHT_SHLIB	    10
#define SHT_DYNSYM	    11
#define SHT_LOPROC	    0x70000000
#define SHT_HIPROC 	    0x7fffffff
#define SHT_LOUSER	    0x80000000
#define SHT_HIUSER	    0xffffffff
#define SHT_ARM_ATTRIBUTES 0x70000003

/** sh_flags **/
#define SHF_WRITE		         0x1
#define SHF_ALLOC	            0x2
#define SHF_EXECINSTR	      0x4
#define SHF_MERGE             0x10
#define SHF_STRINGS	         0x20
#define SHF_INFO_LINK	      0x40
#define SHF_LINK_ORDER	      0x80
#define SHF_OS_NONCONFORMING	0x100
#define SHF_GROUP	            0x200
#define SHF_TLS	            0x400
#define STN_UNDEF             0

/**  **/
#define ELF32_ST_BIND(i)    ((i)>>4)
#define ELF32_ST_TYPE(i)    ((i)&0xf)
#define ELF32_ST_INFO(b,t)  (((b)<<4)+((t)&0xf))

#define ELF32_ST_VISIBILITY(o)       ((o)&0x3)
#define ELF64_ST_VISIBILITY(o)       ((o)&0x3)

#define ELF32_R_SYM(info)             ((info)>>8)
#define ELF32_R_TYPE(info)            ((unsigned char)(info))
#define ELF32_R_INFO(sym, type)       (((sym)<<8)+(unsigned char)(type))

/* ELF32_ST_BIND */
#define STB_LOCAL       0
#define STB_GLOBAL      1
#define STB_WEAK        2
#define STB_LOPROC      13
#define STB_HIPROC      15

/* ELF32_ST_TYPE */
#define STT_NOTYPE      0
#define STT_OBJECT      1
#define STT_FUNC        2
#define STT_SECTION     3
#define STT_FILE        4
#define STT_LOPROC      13
#define STT_HIPROC      15

/* ELF32_ST_VISIBILITY */

#define STV_DEFAULT     0
#define STV_INTERNAL    1
#define STV_HIDDEN      2
#define STV_PROTECTED   3

/* p_type */
#define PT_NULL         0
#define PT_LOAD         1
#define PT_DYNAMIC      2
#define PT_INTERP       3
#define PT_NOTE         4
#define PT_SHLIB        5
#define PT_PHDR         6
#define PT_LOPROC       0x70000000
#define PT_HIPROC       0x7fffffff

/** p_flags **/
#define PF_X		    0x1
#define PF_W		    0x2
#define PF_R		    0x4
#define PF_MASKPROC     0xf0000000

/** d_tag **/
#define DT_NULL		    0
#define DT_NEEDED	    1
#define DT_PLTRELSZ	    2
#define DT_PLTGOT	    3
#define DT_HASH		    4
#define DT_STRTAB	    5
#define DT_SYMTAB	    6
#define DT_RELA		    7
#define DT_RELASZ	    8
#define DT_RELAENT	    9
#define DT_STRSZ	    10
#define DT_SYMENT	    11
#define DT_INIT		    12
#define DT_FINI		    13
#define DT_SONAME	    14
#define DT_RPATH 	    15
#define DT_SYMBOLIC	    16
#define DT_REL	        17
#define DT_RELSZ	    18
#define DT_RELENT	    19
#define DT_PLTREL	    20
#define DT_DEBUG	    21
#define DT_TEXTREL	    22
#define DT_JMPREL	    23
#define DT_BIND_NOW     24
#define DT_LOPROC	    0x70000000
#define DT_HIPROC	    0x7fffffff

/** Relocation type **/
#define R_386_NONE      0
#define R_386_32        1
#define R_386_PC32      2
#define R_386_GOT32     3
#define R_386_PLT32     4
#define R_386_COPY      5
#define R_386_GLOB_DAT  6
#define R_386_JMP_SLOT  7
#define R_386_RELATIVE  8
#define R_386_GOTOFF    9
#define R_386_GOTPC     10

/** Machine **/
#define EM_M32          1
#define EM_SPARC        2
#define EM_386          3
#define EM_68K          4
#define EM_88K          5
#define EM_860          7
#define EM_MIPS         8
#define EM_MIPS_RS4_BE  10
#define EM_PARISC       15
#define EM_SPARC32PLUS  18
#define EM_PPC          20
#define EM_PPC64        21
#define EM_S390         22
#define EM_ARM          40
#define EM_SH            42
#define EM_SPARCV9        43
#define EM_IA_64        50
#define EM_X86_64       62
#define EM_VAX            75

/** EI OS/ABI **/
#define ELFOSABI_NONE	      0	/* UNIX System V ABI */
#define ELFOSABI_SYSV	      0	/* UNIX System V ABI */
#define ELFOSABI_HPUX	      1	/* HP-UX operating system */
#define ELFOSABI_NETBSD	      2	/* NetBSD */
#define ELFOSABI_LINUX	      3	/* GNU/Linux */
#define ELFOSABI_HURD	      4	/* GNU/Hurd */
#define ELFOSABI_SOLARIS      6	/* Solaris */
#define ELFOSABI_AIX	      7	/* AIX */
#define ELFOSABI_IRIX	      8	/* IRIX */
#define ELFOSABI_FREEBSD      9	/* FreeBSD */
#define ELFOSABI_TRU64	     10	/* TRU64 UNIX */
#define ELFOSABI_MODESTO     11	/* Novell Modesto */
#define ELFOSABI_OPENBSD     12	/* OpenBSD */
#define ELFOSABI_OPENVMS     13	/* OpenVMS */
#define ELFOSABI_NSK	     14	/* Hewlett-Packard Non-Stop Kernel */
#define ELFOSABI_AROS	     15	/* Amiga Research OS */
#define ELFOSABI_ARM	     97	/* ARM */
#define ELFOSABI_STANDALONE 255	/* Standalone (embedded) application */

#define 	R_ARM_NONE   0 
#define 	R_ARM_PC24   1
#define 	R_ARM_ABS32   2 
#define 	R_ARM_CALL   28
#define 	R_ARM_JUMP24   29
#define 	R_ARM_V4BX   40
#define 	R_ARM_PREL31   42
#define 	R_ARM_MOVW_ABS_NC   43
#define 	R_ARM_MOVT_ABS   44
#define 	R_ARM_THM_CALL   10
#define 	R_ARM_THM_JUMP24   30
#define 	R_ARM_THM_MOVW_ABS_NC   47
#define 	R_ARM_THM_MOVT_ABS   48

#define SH_TABLE_MAX 100

typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Off;

typedef uint64_t Elf64_Addr;
typedef uint64_t Elf64_Off;

typedef struct {
   unsigned char e_ident[EI_NIDENT];
   uint16_t      e_type;
   uint16_t      e_machine;
   uint32_t      e_version;
   Elf32_Addr    e_entry;
   Elf32_Off     e_phoff;
   Elf32_Off     e_shoff;
   uint32_t      e_flags;
   uint16_t      e_ehsize;
   uint16_t      e_phentsize;
   uint16_t      e_phnum;
   uint16_t      e_shentsize;
   uint16_t      e_shnum;
   uint16_t      e_shstrndx;
} Elf32;

typedef struct {
   unsigned char e_ident[EI_NIDENT];
   uint16_t      e_type;
   uint16_t      e_machine;
   uint32_t      e_version;
   Elf64_Addr    e_entry;
   Elf64_Off     e_phoff;
   Elf64_Off     e_shoff;
   uint32_t      e_flags;
   uint16_t      e_ehsize;
   uint16_t      e_phentsize;
   uint16_t      e_phnum;
   uint16_t      e_shentsize;
   uint16_t      e_shnum;
   uint16_t      e_shstrndx;
} Elf64;

typedef struct {
   uint32_t   sh_name;
   uint32_t   sh_type;
   uint32_t   sh_flags;
   Elf32_Addr sh_addr;
   Elf32_Off  sh_offset;
   uint32_t   sh_size;
   uint32_t   sh_link;
   uint32_t   sh_info;
   uint32_t   sh_addralign;
   uint32_t   sh_entsize;
} Elf32_SH;

typedef struct {
   uint32_t   sh_name;
   uint32_t   sh_type;
   uint64_t   sh_flags;
   Elf64_Addr sh_addr;
   Elf64_Off  sh_offset;
   uint64_t   sh_size;
   uint32_t   sh_link;
   uint32_t   sh_info;
   uint64_t   sh_addralign;
   uint64_t   sh_entsize;
} Elf64_SH;

// SYMBOLES

typedef struct {
    uint32_t      st_name;
    Elf32_Addr    st_value;
    uint32_t      st_size;
    unsigned char st_info;
    unsigned char st_other;
    uint16_t      st_shndx;
} Elf32_Sym;

typedef struct {
    uint32_t      st_name;
    Elf64_Addr    st_value;
    uint64_t      st_size;
    unsigned char st_info;
    unsigned char st_other;
    uint16_t      st_shndx;
} Elf64_Sym;

// RELOCATIONS 

typedef struct {
   Elf32_Addr     r_offset;
   uint32_t       r_info;
} Elf32_Rel; 

typedef struct {
   int s_index;
   int rnum;
   Elf32_Rel *relocations;
} Elf32_RelArray;

// ---

typedef struct {
   Elf32_Addr    r_offset;
   uint32_t    r_info;
   int32_t   r_addend;
} Elf32_Rela;

typedef struct {
   int s_index;
   int rnum;
   Elf32_Rela *relocations;
} Elf32_RelaArray;

/* Etape 1 */

void init_header(FILE *f, Elf32 *elf_h);
void print_elf (FILE *f, Elf32 elf_h);

/* Etape 2 */

void read_sections(FILE *f, Elf32 elf_h, Elf32_SH *arr_elf_SH);
void print_sections_header(FILE *f, FILE *fout, Elf32 elf_h, Elf32_SH *arr_elf_SH);

/* Etape 3 */

void read_data_section(FILE *f, FILE *fout, Elf32 elf_h, Elf32_SH *arr_elf_SH, Elf32_SH *elf_SH);
void print_data_section(FILE *f, FILE *fout, Elf32 elf_h, Elf32_SH *arr_elf_SH, Elf32_SH *elf_SH);

/* Etape 4 */
/* Essai pour push sur VScode */

void read_symbol_section(FILE *f, Elf32 elf_h, Elf32_SH *arr_elf_SH, Elf32_Sym *arr_elf_SYM, size_t *nbSymboles);
void print_symbol(FILE *fout, Elf32_Sym elf_SYM);
void print_symbols(FILE *fout, Elf32 elf_h, size_t nbSymboles, Elf32_Sym * arr_elf_SYM);

/* Etape 5 */

void read_reloc(FILE *f, Elf32_Rel *elf_REL);
void read_reloca(FILE *f, Elf32_Rela *elf_RELA);
void read_relocsa(FILE *f, Elf32 elf_h, Elf32_SH *arr_elf_SH, Elf32_RelArray *arr_elf_REL, Elf32_RelaArray *arr_elf_RELA, size_t *nbRel, size_t *nbRela);
void print_relocs(Elf32 elf_h, Elf32_SH *arr_elf_SH, Elf32_Sym *arr_elf_SYM, Elf32_RelArray *arr_elf_REL, Elf32_RelaArray *arr_elf_RELA, size_t nbRel, size_t nbRela);
#endif
