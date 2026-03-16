static void fix_history ( String * final_command ) {
 int total_lines = 1 ;
 char * ptr = final_command -> c_ptr ( ) ;
 String fixed_buffer ;
 char str_char = '\0' ;
 while ( * ptr != '\0' ) {
 switch ( * ptr ) {
 case '"' : case '\'' : case '`' : if ( str_char == '\0' ) str_char = * ptr ;
 else if ( str_char == * ptr ) str_char = '\0' ;
 fixed_buffer . append ( ptr , 1 ) ;
 break ;
 case '\n' : fixed_buffer . append ( str_char == '\0' ? " " : "\n" ) ;
 total_lines ++ ;
 break ;
 case '\\' : fixed_buffer . append ( '\\' ) ;
 if ( str_char ) {
 ptr ++ ;
 if ( * ptr == '\'' || * ptr == '"' || * ptr == '\\' ) fixed_buffer . append ( ptr , 1 ) ;
 else ptr -- ;
 }
 break ;
 default : fixed_buffer . append ( ptr , 1 ) ;
 }
 ptr ++ ;
 }
 if ( total_lines > 1 ) add_history ( fixed_buffer . ptr ( ) ) ;
 }