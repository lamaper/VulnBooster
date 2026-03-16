static int com_shell ( String * buffer __attribute__ ( ( unused ) ) , char * line __attribute__ ( ( unused ) ) ) {
 char * shell_cmd ;
 while ( my_isspace ( charset_info , * line ) ) line ++ ;
 if ( ! ( shell_cmd = strchr ( line , ' ' ) ) ) {
 put_info ( "Usage: \\! shell-command" , INFO_ERROR ) ;
 return - 1 ;
 }
 if ( system ( shell_cmd ) == - 1 ) {
 put_info ( strerror ( errno ) , INFO_ERROR , errno ) ;
 return - 1 ;
 }
 return 0 ;
 }