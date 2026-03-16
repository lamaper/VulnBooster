static const bfd_target * symbolsrec_object_p ( bfd * abfd ) {
 void * tdata_save ;
 char b [ 2 ] ;
 srec_init ( ) ;
 if ( bfd_seek ( abfd , ( file_ptr ) 0 , SEEK_SET ) != 0 || bfd_bread ( b , ( bfd_size_type ) 2 , abfd ) != 2 ) return NULL ;
 if ( b [ 0 ] != '$' || b [ 1 ] != '$' ) {
 bfd_set_error ( bfd_error_wrong_format ) ;
 return NULL ;
 }
 tdata_save = abfd -> tdata . any ;
 if ( ! srec_mkobject ( abfd ) || ! srec_scan ( abfd ) ) {
 if ( abfd -> tdata . any != tdata_save && abfd -> tdata . any != NULL ) bfd_release ( abfd , abfd -> tdata . any ) ;
 abfd -> tdata . any = tdata_save ;
 return NULL ;
 }
 if ( abfd -> symcount > 0 ) abfd -> flags |= HAS_SYMS ;
 return abfd -> xvec ;
 }