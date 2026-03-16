static void print_warnings ( ) {
 const char * query ;
 MYSQL_RES * result ;
 MYSQL_ROW cur ;
 my_ulonglong num_rows ;
 uint error = mysql_errno ( & mysql ) ;
 query = "show warnings" ;
 mysql_real_query_for_lazy ( query , strlen ( query ) ) ;
 mysql_store_result_for_lazy ( & result ) ;
 if ( ! result || ! ( num_rows = mysql_num_rows ( result ) ) ) goto end ;
 cur = mysql_fetch_row ( result ) ;
 if ( ! cur || ( num_rows == 1 && error == ( uint ) strtoul ( cur [ 1 ] , NULL , 10 ) ) ) goto end ;
 init_pager ( ) ;
 do {
 tee_fprintf ( PAGER , "%s (Code %s): %s\n" , cur [ 0 ] , cur [ 1 ] , cur [ 2 ] ) ;
 }
 while ( ( cur = mysql_fetch_row ( result ) ) ) ;
 end_pager ( ) ;
 end : mysql_free_result ( result ) ;
 }