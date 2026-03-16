static void cleanup_and_exit ( int exit_code ) {
 free_used_memory ( ) ;
 if ( server_initialized ) mysql_server_end ( ) ;
 fclose ( stderr ) ;
 my_end ( my_end_arg ) ;
 if ( ! silent ) {
 switch ( exit_code ) {
 case 1 : printf ( "not ok\n" ) ;
 break ;
 case 0 : printf ( "ok\n" ) ;
 break ;
 case 62 : printf ( "skipped\n" ) ;
 break ;
 default : printf ( "unknown exit code: %d\n" , exit_code ) ;
 DBUG_ASSERT ( 0 ) ;
 }
 }
 sf_leaking_memory = 0 ;
 exit ( exit_code ) ;
 }