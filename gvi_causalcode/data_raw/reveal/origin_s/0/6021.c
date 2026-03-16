void report_clusters_compatible ( void ) {
 if ( user_opts . check ) {
 pg_log ( PG_REPORT , "\n*Clusters are compatible*\n" ) ;
 stop_postmaster ( false ) ;
 exit ( 0 ) ;
 }
 pg_log ( PG_REPORT , "\n" "If pg_upgrade fails after this point, you must re-initdb the\n" "new cluster before continuing.\n" ) ;
 }