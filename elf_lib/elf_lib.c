/***
 * elf_lib: mini librarie qui contient toutes les fonctions
 *          de lecture sur un fichier format ELF.
 * 
 * À remplir au fur et à mesure des étapes.
 * 
 * Voir elf_lib.h pour les structures.
**/

#include "elf_lib/elf_lib.h"

/* Étape 1 */
void init_header(FILE *f, void * elf_h) {

}

void write_elf (FILE *f, void * elf_h) {

} 

/* Étape 2 */
void read_sections(FILE *f, void * elf_h, void ** arr_elf_SH) {

}  

void read_section(FILE *f, void * elf_h, void * elf_SH) {

}

void print_sections_header(FILE *f, void ** arr_elf_SH) {

}

void print_section_header(FILE *f, void * elf_SH) {

}

/* Étape 3 */
/* readelf -x num */
void read_data_section(FILE *f, void * elf_SH) {

}

void print_data_section(FILE *f, void * elf_SH) {

}