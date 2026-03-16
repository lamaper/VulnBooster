static long srec_get_symtab_upper_bound ( bfd * abfd ) {
 return ( bfd_get_symcount ( abfd ) + 1 ) * sizeof ( asymbol * ) ;
 }