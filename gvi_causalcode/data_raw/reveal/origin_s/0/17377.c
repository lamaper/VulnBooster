static bfd_boolean srec_mkobject ( bfd * abfd ) {
 tdata_type * tdata ;
 srec_init ( ) ;
 tdata = ( tdata_type * ) bfd_alloc ( abfd , sizeof ( tdata_type ) ) ;
 if ( tdata == NULL ) return FALSE ;
 abfd -> tdata . srec_data = tdata ;
 tdata -> type = 1 ;
 tdata -> head = NULL ;
 tdata -> tail = NULL ;
 tdata -> symbols = NULL ;
 tdata -> symtail = NULL ;
 tdata -> csymbols = NULL ;
 return TRUE ;
 }