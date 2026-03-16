static long srec_canonicalize_symtab ( bfd * abfd , asymbol * * alocation ) {
 bfd_size_type symcount = bfd_get_symcount ( abfd ) ;
 asymbol * csymbols ;
 unsigned int i ;
 csymbols = abfd -> tdata . srec_data -> csymbols ;
 if ( csymbols == NULL && symcount != 0 ) {
 asymbol * c ;
 struct srec_symbol * s ;
 csymbols = ( asymbol * ) bfd_alloc ( abfd , symcount * sizeof ( asymbol ) ) ;
 if ( csymbols == NULL ) return - 1 ;
 abfd -> tdata . srec_data -> csymbols = csymbols ;
 for ( s = abfd -> tdata . srec_data -> symbols , c = csymbols ;
 s != NULL ;
 s = s -> next , ++ c ) {
 c -> the_bfd = abfd ;
 c -> name = s -> name ;
 c -> value = s -> val ;
 c -> flags = BSF_GLOBAL ;
 c -> section = bfd_abs_section_ptr ;
 c -> udata . p = NULL ;
 }
 }
 for ( i = 0 ;
 i < symcount ;
 i ++ ) * alocation ++ = csymbols ++ ;
 * alocation = NULL ;
 return symcount ;
 }