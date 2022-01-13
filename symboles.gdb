b elf_lib/elf_lib.c:308
commands 1
echo SECTION N°
    p j
        echo st_name : 
        p/x elf_SYM.st_name
echo st_value : 
        p/x elf_SYM.st_value
echo st_size : 
        p/x elf_SYM.st_size
echo st_info : 
        p/x elf_SYM.st_info
echo st_other : 
        p/x elf_SYM.st_other
echo st_shndx : 
        p/x elf_SYM.st_shndx
end
