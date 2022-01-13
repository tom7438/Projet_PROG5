b elf_lib/elf_lib.c:175
commands 1
echo SECTION N°
    p i
        echo sh_name : 
        p/x sec.sh_name
echo sh_type : 
        p/x sec.sh_type
echo sh_flags : 
        p/x sec.sh_flags
echo sh_addr : 
        p/x sec.sh_addr
echo sh_offset : 
        p/x sec.sh_offset
echo sh_size : 
        p/x sec.sh_size
echo sh_link : 
        p/x sec.sh_link
echo sh_info : 
        p/x sec.sh_info
echo sh_addralign : 
        p/x sec.sh_addralign
echo sh_entsize : 
        p/x sec.sh_entsize
end
