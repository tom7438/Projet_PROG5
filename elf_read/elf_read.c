/***
 * elf_read: programme principal
 * ----
 * Celui-ci réalisera les différentes opérations de lecture
 * possibles sur un fichier format ELF de la même façon que
 * la commande readelf.
 *
 * Elle réutilisera les fonctions définies dans elf_lib.
 * Utilisation depuis la racine du projet:
 * > ./read_elf <arguments>
***/

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "elf_lib/elf_lib.h"
#include "elf_lib/elf_utils.h"

void usage(char *name) {
	fprintf(stderr, "Usage:\n"
		"%s [ -H | --help ] [ -h | -S | -x | -r ] file\n\n"
		"Display information about the contents of ELF format files\n"
		, name);
}

int sectionsAAfficher_s = 0;
char *sectionsAAfficher[100];

int main(int argc, char *argv[]) {
    int opt;

    /* à compléter */
	struct option longopts[] = {
		{ "header", no_argument, NULL, 'h' },
		{ "sections", no_argument, NULL, 'S' },
		{ "section", required_argument, NULL, 'x' },
		{ "symbols", no_argument, NULL, 's' },
		{ "relocations", required_argument, NULL, 'r' },
		{ "help", no_argument, NULL, 'H' },
		{ NULL, 0, NULL, 0 }
	};

    char *ELF_filename;
    int showHeader = 0, showSectionsH = 0, showSymbolTable = 0;

    /* à compléter */
    while ((opt = getopt_long(argc, argv, "hSsx:r:H", longopts, NULL)) != -1) {
		switch(opt) {
            case 'h': {
                showHeader = 1;
                break;
            }
            case 'S': {
                showSectionsH = 1;
                break;
            }
            case 'x': {
                if (sectionsAAfficher_s < 100) {
                    sectionsAAfficher[sectionsAAfficher_s] = optarg;
                    sectionsAAfficher_s++;
                }
                break;
            }
            case 's': {
                showSymbolTable = 1;
                break;
            }
            case 'r':
                /** ici on devrait afficher les rellocations du fichier ELF donné en argument **/
                printf("Fichier: %s\n", optarg);
                /* à compléter */
                break;
            case 'H':
                usage(argv[0]);
                exit(0);
            default:
                fprintf(stderr, "Unrecognized option %c\n", opt);
                usage(argv[0]);
                exit(1);
		}
	}

    if (argc-optind <= 0) {
        // Si aucun fichier fourni
        exit(1);
    } else {
        ELF_filename = argv[optind];
        FILE *f = fopen(ELF_filename, "rb");

        if (f == NULL) exit(1);

        Elf32 header;
        Elf32_SH sections[SH_TABLE_MAX];
        init_header(f, &header);
        read_sections(f, header, sections);

        if (showHeader) {
            write_elf(stdout, header);
            printf("\n");
        }

        if (showSectionsH) {
            print_sections_header(f, stdout, header, sections);
            printf("\n");
        }

        if (sectionsAAfficher_s > 0) {
            for (int i = 0; i < sectionsAAfficher_s; i++) {
                char *nom_sec = sectionsAAfficher[i];
                int num = 0;
                int result = sscanf(nom_sec, "%d", &num);
                if (result == 1) {
                    if (num >= 0 && num < header.e_shnum) print_data_section(f, stdout, header, sections, &sections[num]);
                    else printf("-- No section number %d was found", num);
                } else {
                    // si chaîne de caractères, on cherche l'index de la section nom_sec
                    // dans le tableau
                    int found = 0;
                    int j = 0; 
                    for (j = 0; j < header.e_shnum; j++) {
                        if (strcmp(read_name_from_STable(f, header, sections[header.e_shstrndx], sections[j].sh_name), nom_sec) == 0) {
                            found = 1;
                            break;
                        }
                    }
                    if (found == 1) print_data_section(f, stdout, header, sections, &sections[j]);
                    else printf("-- No section named '%s' was found", nom_sec);
                }
                printf("\n");
            }
        }

        if (showSymbolTable) {
            Elf32_Sym symbols[SH_TABLE_MAX];
            read_symbol_section(f, &header, sections, symbols);
            print_symbols_header(stdout, symbols); 
        }
    }

}
