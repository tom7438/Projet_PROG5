b bread if headerDebug == 1
command 1
    up
    up
    echo ident : 
    p/x header.e_ident[0]@16
echo type : 
    p/x header.e_type
echo machine : 
    p/x header.e_machine
echo version : 
    p/x header.e_version
echo entry : 
    p/x header.e_entry
echo phoff : 
    p/x header.e_phoff
echo shoff : 
    p/x header.e_shoff
echo flags : 
    p/x header.e_flags
echo ehsize : 
    p/x header.e_ehsize
echo phentsize : 
    p/x header.e_phentsize
echo phnum : 
    p/x header.e_phnum
echo shentsize : 
    p/x header.e_shentsize
echo shnum : 
    p/x header.e_shnum
echo shstrndx : 
    p/x header.e_shstrndx
end
