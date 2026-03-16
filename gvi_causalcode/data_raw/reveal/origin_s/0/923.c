void issue_warnings ( void ) {
 if ( GET_MAJOR_VERSION ( old_cluster . major_version ) <= 804 ) {
 start_postmaster ( & new_cluster , true ) ;
 new_9_0_populate_pg_largeobject_metadata ( & new_cluster , false ) ;
 stop_postmaster ( false ) ;
 }
 }