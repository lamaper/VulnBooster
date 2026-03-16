void kadmin_getprivs ( int argc , char * argv [ ] ) {
 static char * privs [ ] = {
 "INQUIRE" , "ADD" , "MODIFY" , "DELETE" }
 ;
 krb5_error_code retval ;
 size_t i ;
 long plist ;
 if ( argc != 1 ) {
 fprintf ( stderr , _ ( "usage: get_privs\n" ) ) ;
 return ;
 }
 retval = kadm5_get_privs ( handle , & plist ) ;
 if ( retval ) {
 com_err ( "get_privs" , retval , _ ( "while retrieving privileges" ) ) ;
 return ;
 }
 printf ( _ ( "current privileges:" ) ) ;
 for ( i = 0 ;
 i < sizeof ( privs ) / sizeof ( char * ) ;
 i ++ ) {
 if ( plist & 1 << i ) printf ( " %s" , privs [ i ] ) ;
 }
 printf ( "\n" ) ;
 }