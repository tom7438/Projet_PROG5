/****
 * elf_utils: fonctions auxiliaires
**/

#include "elf_lib/elf_utils.h"
#include <unistd.h>
#include <stdlib.h>

char str_flags[5];
int bread_isBigEndian = 0;

char shstrtab[MAX_STRTAB_LEN];
char symstrtab[MAX_STRTAB_LEN];

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
 * @brief Lit le nom de la section d'index st_name depuis 
 *        la table des chaînes de caractères correspondante
 * 
 * @param st_name index de la section désirée
 * @return châine de caractères
 */
char * read_from_shstrtab(uint32_t st_name) {
    int i = st_name;
    char *nSection = malloc(MAX_STRTAB_LEN);

    while (shstrtab[i] != '\0') {
        nSection[i - st_name] = shstrtab[i];
        i++;
    }
    return nSection;
}

/**
 * @brief Lit le nom de symbole d'index st_name depuis 
 *        la table des chaînes de caractères correspondante
 * 
 * @param st_name index du nom de symbole
 * @return châine de caractères
 */
char * read_from_symtab(uint32_t st_name) {
    int i = st_name;
    char *nSection = malloc(MAX_STRTAB_LEN);

    while (symstrtab[i] != '\0') {
        nSection[i - st_name] = symstrtab[i];
        i++;
    }
    return nSection;
}

/**
 * @brief Lit tt les noms de sections depuis la section
 *        spécfiée et les renvoi dans le tableau `shstrtab`
 * 
 * @param f flux
 * @param STable section `shstrtab`
 * @return
 */
void read_section_names(FILE *f, Elf32_SH STable) {
    int s = 0;
    fseek(f, STable.sh_offset, SEEK_SET);
    while (s != STable.sh_size) {
        bread(&shstrtab[s], sizeof(char), 1, f);
        s++;
    }
}

/**
 * @brief Lit tt les noms de symboles depuis la section
 *        spécfiée et les renvoi dans le tableau `symstrtab`
 * 
 * @param f flux
 * @param STable section `shstrtab`
 * @return
 */
void read_symbol_names(FILE *f, Elf32_SH STable) {
    int s = 0;
    fseek(f, STable.sh_offset, SEEK_SET);
    while (s != STable.sh_size) {
        bread(&symstrtab[s], sizeof(char), 1, f);
        s++;
    }
}

/**
 * @brief Recherche une section par son type
 * 
 * @param type type de la section recherché
 * @param shnum nombre de sections totales
 * @param sections tableau des sections
 * @param section  section retournée
 * @return int (1 si trouvée, 0 sinon)
 */
int get_section_by_type(int type, int shnum, Elf32_SH *sections, Elf32_SH *section) {
    int i = 0;
    for (i = 0; i < shnum; i++) {
        if (sections[i].sh_type == type) {
            *section = sections[i];
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Recherche une section par son nom
 * 
 * @param name nom de la section recherchée
 * @param shnum nombre de sections totales
 * @param sections tableau des sections
 * @param section  section retournée
 * @return int (1 si trouvée, 0 sinon)
 */
int get_section_by_name(char *name, int shnum, Elf32_SH *sections, Elf32_SH *section) {
    int i = 0;
    for (i = 0; i < shnum; i++) {
        if (strcmp(read_from_shstrtab(sections[i].sh_name), name) == 0) {
            *section = sections[i];
            return 1;
        }
    }
    return 0;
}