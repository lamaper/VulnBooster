static void srec_get_symbol_info ( bfd * ignore_abfd ATTRIBUTE_UNUSED , asymbol * symbol , symbol_info * ret ) {
 bfd_symbol_info ( symbol , ret ) ;
 }