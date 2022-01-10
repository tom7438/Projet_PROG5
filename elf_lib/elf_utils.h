/****
 * elf_utils: fonctions auxiliaires
**/

#include "elf_lib/elf_lib.h"
#include <string.h>

extern int bread_isBigEndian;

size_t bread(void *ptr, size_t s, size_t n, FILE *f);
char* get_flags(uint32_t flags);
char * read_name_from_STable(FILE *f, Elf32_SH STable, uint32_t st_name);
