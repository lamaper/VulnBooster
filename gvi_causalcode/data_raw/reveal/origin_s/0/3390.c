static void get_rela_elf64 ( Dwarf_Small * data , unsigned int i , int endianness , int machine , struct Dwarf_Elf_Rela * relap ) {

 relap -> r_offset = relp -> r_offset ;

 relap -> r_type = ELF64MIPS_REL_TYPE ( relp -> r_info ) ;
 relap -> r_symidx = ELF64MIPS_REL_SYM ( relp -> r_info ) ;

 else {
 relap -> r_type = ELF64_R_TYPE ( relp -> r_info ) ;
 relap -> r_symidx = ELF64_R_SYM ( relp -> r_info ) ;
 }
 relap -> r_addend = relp -> r_addend ;
