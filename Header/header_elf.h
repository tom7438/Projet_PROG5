#ifndef __HEADER_ELF_H__
#define __HEADER_ELF_H__

#define EI_NIDENT 16

typedef uint32_t Elf32_Addr
typedef uint64_t Elf64_Addr

typedef uint32_t Elf32_Off
typedef uint64_t Elf64_Off

typedef struct {
   unsigned char e_ident[EI_NIDENT];
   uint16_t      e_type;
   uint16_t      e_machine;
   uint32_t      e_version;
   uint32_t      e_entry;
   uint32_t      e_phoff;
   uint32_t      e_shoff;
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
   uint64_t      e_entry;
   uint64_t      e_phoff;
   uint64_t      e_shoff;
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
void write_elf (FILE *f, void * elf_h); //

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
