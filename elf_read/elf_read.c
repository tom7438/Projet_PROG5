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

void usage(char *name) {
	fprintf(stderr, "Usage:\n"
		"%s [ -H | --help ] [ -h | -S ] file\n\n"
		"Display information about the contents of ELF format files\n"
		, name);
}

int main(int argc, char *argv[]) {
    int opt;

    /* à compléter */
	struct option longopts[] = {
		{ "header", required_argument, NULL, 'h' },
		{ "sections", required_argument, NULL, 'S' },
		{ "help", no_argument, NULL, 'H' },
		{ NULL, 0, NULL, 0 }
	};

    /* à compléter */
    while ((opt = getopt_long(argc, argv, "h:S:H", longopts, NULL)) != -1) {
		switch(opt) {
            case 'h':
                /** ici on devrait afficher le header du fichier ELF donné en argument **/
                printf("Fichier: %s\n", optarg);
                /* à compléter */
                break;
            case 'S':
                /** ici on devrait afficher les sections du fichier ELF donné en argument **/
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

}