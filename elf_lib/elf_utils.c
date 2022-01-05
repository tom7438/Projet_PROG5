/****
 * elf_utils: fonctions auxiliaires
**/

#include "elf_lib/elf_utils.h"

char str_flags[5];
char nomSection[30];
int bread_isBigEndian = 0;

/**
 * @brief Lit un certain nombre d'octets à partir d'un flux.
 *        Si bread_isBigEndian vaut 0, la lecture se fait à partir de fread()
 *        sinon, on lit en "big endian" (inverse les caractères)
 * 
 * @param buffer pointeur
 * @param s taille (en octets) d'un bloc unitaire à lire.
 * @param n nombre de blocs unitaires à lire
 * @param f flux à partir duquel lire les octets
 * @return size_t 
 */
size_t bread(void * buffer, size_t s, size_t n, FILE *f) {
    if (bread_isBigEndian == 0) {
        return fread(buffer, s, n, f);
    } else {
        char buff[s];
        char c;

        for (int i = 0; i < s; i++) {
            c = fgetc(f);
            if (c == EOF) return 0;
            buff[i] = c;
        }

        for (int i = s-1; i >= 0; i--) {
            *((char *)buffer++) = buff[i];
        }
        return 1;
    }
}

/**
 * @brief Retourne les drapeaux sous forme de texte
 * 
 * @param flags drapeaux 
 * @return chaîne de caractères
 */
char* get_flags(uint32_t flags) {
    strcpy(str_flags, "");
    if (flags & SHF_WRITE) strcat(str_flags, "W");
    if (flags & SHF_ALLOC) strcat(str_flags, "A");
    if (flags & SHF_EXECINSTR) strcat(str_flags, "X");
    if (flags & SHF_MERGE) strcat(str_flags, "M");
    if (flags & SHF_STRINGS) strcat(str_flags, "S");
    if (flags & SHF_LINK_ORDER) strcat(str_flags, "L");
    if (flags & SHF_GROUP) strcat(str_flags, "G");
    if (flags & SHF_TLS) strcat(str_flags, "T");
    if (flags & SHF_OS_NONCONFORMING) strcat(str_flags, "O");
    if (flags & SHF_INFO_LINK) strcat(str_flags, "I");
    return str_flags;
}

/**
 * @brief Lit le nom de la section depuis la table
 *        des chaînes de caractères
 * 
 * @param f flux
 * @param elf_h en-tête ELF
 * @param STable section ELF .shstrtab
 * @param st_name index de la section désirée
 * @return châine de caractères
 */
char * read_name_from_STable(FILE *f, Elf32 elf_h, Elf32_SH STable, uint32_t st_name) {
    strcpy(nomSection, "");
    fseek(f, STable.sh_offset + st_name, SEEK_SET);
    bread(&nomSection[0], sizeof(char), 1, f);
    char c = ' ';
    int i = 1;

    while (c != '\0') { 
        bread(&nomSection[i], sizeof(char), 1, f);
        c = nomSection[i];
        i++;
    }
    return nomSection;
}
