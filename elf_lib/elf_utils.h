/****
 * elf_utils: fonctions auxiliaires
**/

#include "elf_lib/elf_lib.h"
#include <string.h>
#define MAX_STRTAB_LEN 300

extern int bread_isBigEndian;

size_t bread(void *ptr, size_t s, size_t n, FILE *f);
char* get_flags(uint32_t flags);

void read_section_names(FILE *f, Elf32_SH STable);
void read_symbol_names(FILE *f, Elf32_SH STable);
char * read_from_shstrtab(uint32_t st_name);
char * read_from_symtab(uint32_t st_name);