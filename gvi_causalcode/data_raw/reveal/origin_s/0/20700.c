static void dumpTimestamp ( ArchiveHandle * AH , const char * msg , time_t tim ) {
 char buf [ 64 ] ;
 if ( strftime ( buf , sizeof ( buf ) , PGDUMP_STRFTIME_FMT , localtime ( & tim ) ) != 0 ) ahprintf ( AH , "-- %s %s\n\n" , msg , buf ) ;
 }