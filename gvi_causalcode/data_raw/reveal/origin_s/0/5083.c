static bfd_boolean srec_write_symbols ( bfd * abfd ) {
 int i ;
 int count = bfd_get_symcount ( abfd ) ;
 if ( count ) {
 bfd_size_type len ;
 asymbol * * table = bfd_get_outsymbols ( abfd ) ;
 len = strlen ( abfd -> filename ) ;
 if ( bfd_bwrite ( "$$ " , ( bfd_size_type ) 3 , abfd ) != 3 || bfd_bwrite ( abfd -> filename , len , abfd ) != len || bfd_bwrite ( "\r\n" , ( bfd_size_type ) 2 , abfd ) != 2 ) return FALSE ;
 for ( i = 0 ;
 i < count ;
 i ++ ) {
 asymbol * s = table [ i ] ;
 if ( ! bfd_is_local_label ( abfd , s ) && ( s -> flags & BSF_DEBUGGING ) == 0 ) {
 char buf [ 43 ] , * p ;
 len = strlen ( s -> name ) ;
 if ( bfd_bwrite ( " " , ( bfd_size_type ) 2 , abfd ) != 2 || bfd_bwrite ( s -> name , len , abfd ) != len ) return FALSE ;
 sprintf_vma ( buf + 2 , ( s -> value + s -> section -> output_section -> lma + s -> section -> output_offset ) ) ;
 p = buf + 2 ;
 while ( p [ 0 ] == '0' && p [ 1 ] != 0 ) p ++ ;
 len = strlen ( p ) ;
 p [ len ] = '\r' ;
 p [ len + 1 ] = '\n' ;
 * -- p = '$' ;
 * -- p = ' ' ;
 len += 4 ;
 if ( bfd_bwrite ( p , len , abfd ) != len ) return FALSE ;
 }
 }
 if ( bfd_bwrite ( "$$ \r\n" , ( bfd_size_type ) 5 , abfd ) != 5 ) return FALSE ;
 }
 return TRUE ;
 }