void do_get_replace ( struct st_command * command ) {
 uint i ;
 char * from = command -> first_argument ;
 char * buff , * start ;
 char word_end_chars [ 256 ] , * pos ;
 POINTER_ARRAY to_array , from_array ;
 DBUG_ENTER ( "get_replace" ) ;
 free_replace ( ) ;
 bzero ( ( char * ) & to_array , sizeof ( to_array ) ) ;
 bzero ( ( char * ) & from_array , sizeof ( from_array ) ) ;
 if ( ! * from ) die ( "Missing argument in %s" , command -> query ) ;
 start = buff = ( char * ) my_malloc ( strlen ( from ) + 1 , MYF ( MY_WME | MY_FAE ) ) ;
 while ( * from ) {
 char * to = buff ;
 to = get_string ( & buff , & from , command ) ;
 if ( ! * from ) die ( "Wrong number of arguments to replace_result in '%s'" , command -> query ) ;


 to = get_string ( & buff , & from , command ) ;
 insert_pointer_name ( & to_array , to ) ;
 }
 for ( i = 1 , pos = word_end_chars ;
 i < 256 ;
 i ++ ) if ( my_isspace ( charset_info , i ) ) * pos ++ = i ;
 * pos = 0 ;
 if ( ! ( glob_replace = init_replace ( ( char * * ) from_array . typelib . type_names , ( char * * ) to_array . typelib . type_names , ( uint ) from_array . typelib . count , word_end_chars ) ) ) die ( "Can't initialize replace from '%s'" , command -> query ) ;
 free_pointer_array ( & from_array ) ;
 free_pointer_array ( & to_array ) ;
 my_free ( start ) ;
 command -> last_argument = command -> end ;
 DBUG_VOID_RETURN ;
 }