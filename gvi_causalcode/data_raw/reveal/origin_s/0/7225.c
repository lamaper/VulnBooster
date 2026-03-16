static void dumpTimestamp ( const char * msg ) {
 char buf [ 64 ] ;
 time_t now = time ( NULL ) ;
 if ( strftime ( buf , sizeof ( buf ) , PGDUMP_STRFTIME_FMT , localtime ( & now ) ) != 0 ) fprintf ( OPF , "-- %s %s\n\n" , msg , buf ) ;
 }