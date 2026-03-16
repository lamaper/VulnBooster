static bfd_boolean srec_new_symbol ( bfd * abfd , const char * name , bfd_vma val ) {
 struct srec_symbol * n ;
 n = ( struct srec_symbol * ) bfd_alloc ( abfd , sizeof ( * n ) ) ;
 if ( n == NULL ) return FALSE ;
 n -> name = name ;
 n -> val = val ;
 if ( abfd -> tdata . srec_data -> symbols == NULL ) abfd -> tdata . srec_data -> symbols = n ;
 else abfd -> tdata . srec_data -> symtail -> next = n ;
 abfd -> tdata . srec_data -> symtail = n ;
 n -> next = NULL ;
 ++ abfd -> symcount ;
 return TRUE ;
 }