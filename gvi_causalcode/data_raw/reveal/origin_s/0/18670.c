static bool restricted_shell ( const char * shellname ) {
 const char * line ;
 setusershell ( ) ;
 while ( ( line = getusershell ( ) ) != NULL ) {
 if ( ( '#' != * line ) && ( strcmp ( line , shellname ) == 0 ) ) {
 endusershell ( ) ;
 return false ;
 }
 }
 endusershell ( ) ;
 return true ;
 }