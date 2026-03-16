char * get_string ( char * * to_ptr , char * * from_ptr , struct st_command * command ) {
 char c , sep ;
 char * to = * to_ptr , * from = * from_ptr , * start = to ;
 DBUG_ENTER ( "get_string" ) ;
 if ( * from == '"' || * from == '\'' ) sep = * from ++ ;
 else sep = ' ' ;
 for ( ;
 ( c = * from ) ;
 from ++ ) {
 if ( c == '\\' && from [ 1 ] ) {
 switch ( * ++ from ) {
 case 'n' : * to ++ = '\n' ;
 break ;
 case 't' : * to ++ = '\t' ;
 break ;
 case 'r' : * to ++ = '\r' ;
 break ;
 case 'b' : * to ++ = '\b' ;
 break ;
 case 'Z' : * to ++ = '\032' ;
 break ;
 default : * to ++ = * from ;
 break ;
 }
 }
 else if ( c == sep ) {
 if ( c == ' ' || c != * ++ from ) break ;
 * to ++ = c ;
 }
 else * to ++ = c ;
 }
 if ( * from != ' ' && * from ) die ( "Wrong string argument in %s" , command -> query ) ;
 while ( my_isspace ( charset_info , * from ) ) from ++ ;
 * to = 0 ;
 * to_ptr = to + 1 ;
 * from_ptr = from ;
 if ( * start == '$' ) {
 const char * end = to ;
 VAR * var = var_get ( start , & end , 0 , 1 ) ;
 if ( var && to == ( char * ) end + 1 ) {
 DBUG_PRINT ( "info" , ( "var: '%s' -> '%s'" , start , var -> str_val ) ) ;
 DBUG_RETURN ( var -> str_val ) ;
 }
 }
 DBUG_RETURN ( start ) ;
 }