static void maybe_exit ( int error ) {
 if ( ! first_error ) first_error = error ;
 if ( ignore_errors ) return ;
 ignore_errors = 1 ;
 if ( opt_slave_data ) do_start_slave_sql ( mysql ) ;
 if ( mysql ) mysql_close ( mysql ) ;
 free_resources ( ) ;
 exit ( error ) ;
 }