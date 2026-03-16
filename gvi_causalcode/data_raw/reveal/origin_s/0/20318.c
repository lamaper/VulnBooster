void append_field ( DYNAMIC_STRING * ds , uint col_idx , MYSQL_FIELD * field , char * val , ulonglong len , my_bool is_null ) {
 char null [ ] = "NULL" ;
 if ( col_idx < max_replace_column && replace_column [ col_idx ] ) {
 val = replace_column [ col_idx ] ;
 len = strlen ( val ) ;
 }
 else if ( is_null ) {
 val = null ;
 len = 4 ;
 }

 char * start = strchr ( val , 'e' ) ;
 if ( start && strlen ( start ) >= 5 && ( start [ 1 ] == '-' || start [ 1 ] == '+' ) && start [ 2 ] == '0' ) {
 start += 2 ;
 if ( field -> flags & ZEROFILL_FLAG ) {
 memmove ( val + 1 , val , start - val ) ;
 * val = '0' ;
 }
 else {
 memmove ( start , start + 1 , strlen ( start ) ) ;
 len -- ;
 }
 }
 }

 if ( col_idx ) dynstr_append_mem ( ds , "\t" , 1 ) ;
 replace_dynstr_append_mem ( ds , val , ( int ) len ) ;
 }
 else {
 dynstr_append ( ds , field -> name ) ;
 dynstr_append_mem ( ds , "\t" , 1 ) ;
 replace_dynstr_append_mem ( ds , val , ( int ) len ) ;
 dynstr_append_mem ( ds , "\n" , 1 ) ;
 }
 }