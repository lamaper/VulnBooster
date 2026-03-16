static void print_version ( void ) {
 set_server_version ( ) ;
 printf ( "%s Ver %s for %s on %s (%s)\n" , my_progname , server_version , SYSTEM_TYPE , MACHINE_TYPE , MYSQL_COMPILATION_COMMENT ) ;
 }