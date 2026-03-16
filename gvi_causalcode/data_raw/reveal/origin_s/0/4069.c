static void field_escape ( DYNAMIC_STRING * in , const char * from ) {
 uint end_backslashes = 0 ;
 dynstr_append_checked ( in , "'" ) ;
 while ( * from ) {
 dynstr_append_mem_checked ( in , from , 1 ) ;
 if ( * from == '\\' ) end_backslashes ^= 1 ;
 else {
 if ( * from == '\'' && ! end_backslashes ) {
 dynstr_append_checked ( in , "\'" ) ;
 }
 end_backslashes = 0 ;
 }
 from ++ ;
 }
 if ( end_backslashes ) dynstr_append_checked ( in , "\\" ) ;
 dynstr_append_checked ( in , "'" ) ;
 }