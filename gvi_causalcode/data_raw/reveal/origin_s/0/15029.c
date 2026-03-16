static void get_system_identitier ( char * system_id , size_t size ) {

 uname ( & u ) ;
 strncpy ( system_id , u . sysname , size - 1 ) ;
 system_id [ size - 1 ] = '\0' ;

 system_id [ size - 1 ] = '\0' ;
