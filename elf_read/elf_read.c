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

	struct option longopts[] = {
		{ "header", no_argument, NULL, 'h' },
		{ "sections", no_argument, NULL, 'S' },
		{ "section", required_argument, NULL, 'x' },
		{ "symbols", no_argument, NULL, 's' },
		{ "relocations", no_argument, NULL, 'r' },
		{ "help", no_argument, NULL, 'H' },
		{ NULL, 0, NULL, 0 }
	};

    char *ELF_filename;
    int showHeader = 0, showSectionsH = 0, showSymbolTable = 0, showRelocs = 0;

    while ((opt = getopt_long(argc, argv, "hSsrx:H", longopts, NULL)) != -1) {
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
            case 'r': {
                showRelocs = 1;
                break;
            }
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
        Elf32_Sym symbols[SH_TABLE_MAX];
        size_t nbSymboles;
        init_header(f, &header);
        read_sections(f, header, sections);
        // -- lecture des noms de sections
        read_section_names(f, sections[header.e_shstrndx]);
        read_symbol_section(f, header, sections, symbols, &nbSymboles);

        if (showHeader) {
            print_elf(stdout, header);
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
                    Elf32_SH section;
                    if (get_section_by_name(nom_sec, header.e_shnum, sections, &section)) print_data_section(f, stdout, header, sections, &section);
                    else printf("-- No section named '%s' was found", nom_sec);
                }
                printf("\n");
            }
        }

        if (showSymbolTable) {
            Elf32_SH strtab;
            if (get_section_by_name(".strtab", header.e_shnum, sections, &strtab)) {
                // -- lecture des noms de symboles avant affichage 
                read_symbol_names(f, strtab);
                print_symbols(f, stdout, header, nbSymboles, symbols);
                printf("\n");
            }
        }

        if (showRelocs) {
            Elf32_RelArray rel_array[SH_TABLE_MAX];
            Elf32_RelaArray rela_array[SH_TABLE_MAX];
            size_t nbRelocs;
            size_t nbRela;

            Elf32_SH strtab;
            if (get_section_by_name(".strtab", header.e_shnum, sections, &strtab)) {
                // -- lecture des noms de symboles avant affichage 
                read_symbol_names(f, strtab);
                read_relocsa(f, header, sections, rel_array, rela_array, &nbRelocs, &nbRela);
                print_relocs(f, header, sections, symbols, rel_array, rela_array, nbRelocs, nbRela);
            }
        }
        
    }

}
