void output_check_banner ( bool live_check ) {
 if ( user_opts . check && live_check ) {
 pg_log ( PG_REPORT , "Performing Consistency Checks on Old Live Server\n" ) ;
 pg_log ( PG_REPORT , "------------------------------------------------\n" ) ;
 }
 else {
 pg_log ( PG_REPORT , "Performing Consistency Checks\n" ) ;
 pg_log ( PG_REPORT , "-----------------------------\n" ) ;
 }
 }