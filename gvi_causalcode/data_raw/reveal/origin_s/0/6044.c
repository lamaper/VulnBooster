static int put_info ( const char * str , INFO_TYPE info_type , uint error , const char * sqlstate ) {
 FILE * file = ( info_type == INFO_ERROR ? stderr : stdout ) ;
 static int inited = 0 ;
 if ( status . batch ) {
 if ( info_type == INFO_ERROR ) {
 ( void ) fflush ( file ) ;
 fprintf ( file , "ERROR" ) ;
 if ( error ) {
 if ( sqlstate ) ( void ) fprintf ( file , " %d (%s)" , error , sqlstate ) ;
 else ( void ) fprintf ( file , " %d" , error ) ;
 }
 if ( status . query_start_line && line_numbers ) {
 ( void ) fprintf ( file , " at line %lu" , status . query_start_line ) ;
 if ( status . file_name ) ( void ) fprintf ( file , " in file: '%s'" , status . file_name ) ;
 }
 ( void ) fprintf ( file , ": %s\n" , str ) ;
 ( void ) fflush ( file ) ;
 if ( ! ignore_errors ) return 1 ;
 }
 else if ( info_type == INFO_RESULT && verbose > 1 ) tee_puts ( str , file ) ;
 if ( unbuffered ) fflush ( file ) ;
 return info_type == INFO_ERROR ? - 1 : 0 ;
 }
 if ( ! opt_silent || info_type == INFO_ERROR ) {
 if ( ! inited ) {

 have_curses = setupterm ( ( char * ) 0 , 1 , & errret ) != ERR ;

 }
 if ( info_type == INFO_ERROR ) {
 if ( ! opt_nobeep ) {



 my_vidattr ( A_STANDOUT ) ;
 if ( error ) {
 if ( sqlstate ) ( void ) tee_fprintf ( file , "ERROR %d (%s)" , error , sqlstate ) ;
 else ( void ) tee_fprintf ( file , "ERROR %d" , error ) ;
 }
 else tee_fputs ( "ERROR" , file ) ;
 if ( status . query_start_line && line_numbers ) {
 ( void ) fprintf ( file , " at line %lu" , status . query_start_line ) ;
 if ( status . file_name ) ( void ) fprintf ( file , " in file: '%s'" , status . file_name ) ;
 }
 tee_fputs ( ": " , file ) ;
 }
 else my_vidattr ( A_BOLD ) ;
 ( void ) tee_puts ( str , file ) ;
 my_vidattr ( A_NORMAL ) ;
 }
 if ( unbuffered ) fflush ( file ) ;
 return info_type == INFO_ERROR ? ( ignore_errors ? - 1 : 1 ) : 0 ;
 }