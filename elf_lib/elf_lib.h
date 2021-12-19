#include <stdint.h>
#include <stdio.h>
#ifndef __HEADER_ELF_H__
#define __HEADER_ELF_H__

/** e_ident[] **/
#define	EI_MAG0		    0
#define	EI_MAG1		    1
#define	EI_MAG2		    2
#define	EI_MAG3		    3
#define	EI_CLASS	    4
#define	EI_DATA		    5
#define	EI_VERSION	    6
#define	EI_PAD		    8
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


/** e_type[] **/
#define ET_NONE         0
#define ET_REL          1
#define ET_EXEC         2
#define ET_DYN          3
#define ET_CORE         4
#define ET_LOPROC       0xff00
#define ET_HIPROC       0xffff

/** e_machine[] **/
/* #define ET_NONE      0 déjà défini dans le e_type */
#define EM_M32          1
#define EM_SPARC        2
#define EM_386          3
#define EM_68K          4
#define EM_88K          5
#define EM_860          7
#define EM_MIPS         8
#define EM_MIPS_RS4_BE  10

/** Special Section Indexes **/
#define SHN_UNDEF	    0
#define SHN_LORESERVE	0xff00
#define SHN_LOPROC	    0xff00
#define SHN_HIPROC	    0xff1f
#define SHN_ABS		    0xfff1
#define SHN_COMMON	    0xfff2
#define SHN_HIRESERVE	0xffff

/**  sh_type[] **/
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

/** sh_flags[] **/
#define SHF_WRITE		0x1
#define SHF_ALLOC	    0x2
#define SHF_EXECINSTR	0x4
#define SHF_MASKPROC	0xf0000000

#define STN_UNDEF       0


/**  **/
#define ELF32_ST_BIND(i)    ((i)>>4)
#define ELF32_ST_TYPE(i)    ((i)&0xf)
#define ELF32_ST_INFO(b,t)  (((b)<<4)+((t)&0xf))

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

/* p_type[] */
#define PT_NULL         0
#define PT_LOAD         1
#define PT_DYNAMIC      2
#define PT_INTERP       3
#define PT_NOTE         4
#define PT_SHLIB        5
#define PT_PHDR         6
#define PT_LOPROC       0x70000000
#define PT_HIPROC       0x7fffffff

/** p_flags[] **/
#define PF_X		    0x1
#define PF_W		    0x2
#define PF_R		    0x4
#define PF_MASKPROC     0xf0000000

/** d_tag[] **/
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
	
/* Etape 1 */
/* readelf -h */
void init_header(FILE *f, void * elf_h);
void write_elf (FILE *f, void * elf_h);

/* Etape 2 */
/* readelf -S */
void read_sections(FILE *f, void * elf_h, void ** arr_elf_SH);
void read_section(FILE *f, void * elf_h, void * elf_SH);
void print_sections_header(FILE *f, void ** arr_elf_SH);
void print_section_header(FILE *f, void * elf_SH);

/* Etape 3 */
/* readelf -x num */
void read_data_section(FILE *f, void * elf_SH);
void print_data_section(FILE *f, void * elf_SH);

#endif
