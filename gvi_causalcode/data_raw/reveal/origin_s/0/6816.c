uint get_errcode_from_name ( const char * error_name , const char * error_end , st_error * e ) {
 DBUG_ENTER ( "get_errcode_from_name" ) ;
 DBUG_PRINT ( "enter" , ( "error_name: %s" , error_name ) ) ;
 for ( ;
 e -> name ;
 e ++ ) {
 if ( ! strncmp ( error_name , e -> name , ( int ) ( error_end - error_name ) ) && ( uint ) strlen ( e -> name ) == ( uint ) ( error_end - error_name ) ) {
 DBUG_RETURN ( e -> code ) ;
 }
 }
 DBUG_RETURN ( 0 ) ;
 }