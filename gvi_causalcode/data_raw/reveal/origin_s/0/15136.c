int write_command_to_file ( char * cmd ) {
 char * buffer ;
 char * ip_address ;
 int dummy ;
 char * p ;
 FILE * fp ;
 struct stat statbuf ;
 char error_string [ MAX_INPUT_BUFFER ] ;
 if ( ! cmd || ! * cmd || strchr ( cmd , '\n' ) ) return ERROR ;
 if ( stat ( command_file , & statbuf ) ) {
 snprintf ( error_string , sizeof ( error_string ) , "Error: Could not stat() command file '%s'!" , command_file ) ;
 error_string [ sizeof ( error_string ) - 1 ] = '\x0' ;
 print_generic_error_message ( error_string , "The external command file may be missing, Icinga may not be running, and/or Icinga may not be checking external commands." , 2 ) ;
 return ERROR ;
 }
 fp = fopen ( command_file , "w" ) ;
 if ( fp == NULL ) {
 snprintf ( error_string , sizeof ( error_string ) , "Error: Could not open command file '%s' for update!" , command_file ) ;
 error_string [ sizeof ( error_string ) - 1 ] = '\x0' ;
 print_generic_error_message ( error_string , "The permissions on the external command file and/or directory may be incorrect. Read the FAQs on how to setup proper permissions." , 2 ) ;
 return ERROR ;
 }
 if ( use_logging == TRUE ) {
 p = strchr ( cmd , ']' ) ;
 if ( p != NULL ) p += 2 ;
 else p = & cmd [ 0 ] ;
 ip_address = strdup ( getenv ( "REMOTE_ADDR" ) ) ;
 dummy = asprintf ( & buffer , "EXTERNAL COMMAND: %s;
%s;
%s" , current_authdata . username , ( ip_address != NULL ) ? ip_address : "unknown remote address" , p ) ;
 write_to_cgi_log ( buffer ) ;
 if ( enforce_comments_on_actions == TRUE ) {
 my_free ( buffer ) ;
 dummy = asprintf ( & buffer , "FORCED COMMENT: %s;
%s;
%s;
%s" , current_authdata . username , ( ip_address != NULL ) ? ip_address : "unknown remote address" , comment_author , comment_data ) ;
 write_to_cgi_log ( buffer ) ;
 }
 my_free ( buffer ) ;
 }
 fprintf ( fp , "%s\n" , cmd ) ;
 fflush ( fp ) ;
 fclose ( fp ) ;
 return OK ;
 }