struct st_replace_regex * init_replace_regex ( char * expr ) {
 struct st_replace_regex * res ;
 char * buf , * expr_end ;
 char * p ;
 char * buf_p ;
 uint expr_len = strlen ( expr ) ;
 char last_c = 0 ;
 struct st_regex reg ;
 res = ( struct st_replace_regex * ) my_malloc ( sizeof ( * res ) + expr_len , MYF ( MY_FAE + MY_WME ) ) ;
 my_init_dynamic_array ( & res -> regex_arr , sizeof ( struct st_regex ) , 128 , 128 ) ;
 buf = ( char * ) res + sizeof ( * res ) ;
 expr_end = expr + expr_len ;
 p = expr ;
 buf_p = buf ;
 while ( p < expr_end ) {
 bzero ( & reg , sizeof ( reg ) ) ;
 while ( p < expr_end ) {
 if ( * p == '/' ) break ;
 p ++ ;
 }
 if ( p == expr_end || ++ p == expr_end ) {
 if ( res -> regex_arr . elements ) break ;
 else goto err ;
 }
 reg . pattern = buf_p ;
 PARSE_REGEX_ARG if ( p == expr_end || ++ p == expr_end ) goto err ;
 reg . replace = buf_p ;
 PARSE_REGEX_ARG if ( p == expr_end ) goto err ;
 p ++ ;
 if ( p < expr_end && * p == 'i' ) reg . icase = 1 ;
 if ( insert_dynamic ( & res -> regex_arr , ( uchar * ) & reg ) ) die ( "Out of memory" ) ;
 }
 res -> odd_buf_len = res -> even_buf_len = 8192 ;
 res -> even_buf = ( char * ) my_malloc ( res -> even_buf_len , MYF ( MY_WME + MY_FAE ) ) ;
 res -> odd_buf = ( char * ) my_malloc ( res -> odd_buf_len , MYF ( MY_WME + MY_FAE ) ) ;
 res -> buf = res -> even_buf ;
 return res ;
 err : my_free ( res ) ;
 die ( "Error parsing replace_regex \"%s\"" , expr ) ;
 return 0 ;
 }