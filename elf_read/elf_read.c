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
		"%s [ -H | --help ] [ -h | -S | -s | -x <num|text> | -r ] file\n\n"
		"Display information about the contents of ELF format files\n"
		, name);
}


void calculation (int* buff, int S, int A , int P, int T, int type) {
	switch (type) {
					case R_ARM_NONE: break;
					//case R_ARM_ABS8:  *buff = S + A; break; //Add to MACRO
					//case R_ARM_ABS16: *buff =  S + A ; break; //Add to MACRO
					case R_ARM_ABS32: *buff = (S+A) | T; break;
					case R_ARM_CALL:  *buff = ((S + A) | T) - P ; break;
					case R_ARM_JUMP24: *buff = ((S + A) | T) - P; break;
					default: printf("R_UNKNOWN"); break;
	}
}

int reloc (FILE *f, Elf32_Sym *arr_elf_SYM, Elf32_RelArray rel_Arr,Elf32_SH* arr_elf_sh ) {
	
	Elf32_SH sec = arr_elf_sh[rel_Arr.s_index];
	Elf32_Rel r;
	Elf32_Sym sym;
	int debut_sym;
	int debut_sec;
	uint32_t reloc_data;
	get_section_by_name(read_from_shstrtab(sec.sh_name)+4,10,arr_elf_sh,&sec);
	int S,A,P,T;


	for (int k = 0; k < SH_TABLE_MAX; k++) {
		// Initialiser pour l'instance de reloc
		r = rel_Arr.relocations[k];
		sym = arr_elf_SYM[ELF32_R_SYM(r.r_info)];
		debut_sym = arr_elf_sh[sym.st_shndx].sh_offset + sym.st_value; 
		debut_sec = sec.sh_offset + r.r_offset;
		if (strcmp ("" , read_from_shstrtab(arr_elf_sh[sym.st_shndx].sh_name)) == 0) return 0;
		
		// Trouver la table du symbole et la où il se trouve 
		S = debut_sym;
		A = 0; // Calcul de A (Pas compris): https://developer.arm.com/documentation/ihi0044/latest
		P = debut_sec;
		T = 0;
		if (ELF32_ST_TYPE(sym.st_info) == STT_FUNC) T = 1;
		calculation(&debut_sym,S,A,P,T,ELF32_R_TYPE(r.r_info));
		
		//Lire la donnée à reloc
		fseek(f, debut_sym, SEEK_SET); // Addresse à copier 
		reloc_data = fread(&reloc_data,sizeof(uint32_t),1,f);
		
		//debug
		printf("sec à reloc = %s\n",read_from_shstrtab(sec.sh_name));
		printf("sec contenant la data = %s\n",read_from_shstrtab(arr_elf_sh[sym.st_shndx].sh_name));
		printf("symbole = %.8x\n",reloc_data);
		printf("Offset = %d\n",r.r_offset);
		fseek(f, debut_sec -16, SEEK_SET);// On regarde les modifs uniquement le premier mot de la seconde ligne changé
		printf("\nAVANT\n");
		for (int i = 0; i < 32; i++) {
			if (i%4 == 0) printf(" ");
			if (i%16 == 0) printf(" \n0x%08x ", i);
			printf("%.2x", fgetc(f));
			
		}    printf("\nAVANT\n");
		
		// Reecrire la donnée à relocaliser		
		fseek(f, debut_sec, SEEK_SET);//addresse à réecrire
		fwrite(&reloc_data,sizeof(uint32_t),1,f);
		fflush(f);
		fseek(f, debut_sec -16, SEEK_SET);

		//debug
		printf("\nAPRES\n");
		for (int i = 0; i < 32; i++) {
			if (i%4 == 0) printf(" ");
			if (i%16 == 0) printf(" \n0x%08x ", i);
			printf("%.2x", fgetc(f));
			
		}    printf("\nAPRES \n");

		
	}
    
    return 1;
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
        // -- lecture de l'en-tête
        init_header(f, &header);
        // -- lecture des sections
        read_sections(f, header, sections);
        // -- lecture des noms de sections
        read_section_names(f, sections[header.e_shstrndx]);
        // -- lecture des symboles
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
                print_symbols(stdout, header, nbSymboles, symbols);
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
                print_relocs(header, sections, symbols, rel_array, rela_array, nbRelocs, nbRela);
                
                FILE *f2 = fopen(ELF_filename, "r+");
                for (int k =0; k<nbRelocs;k++){ 
					reloc (f2, symbols,rel_array[k],sections );
				} 
            }
        }
    }
}