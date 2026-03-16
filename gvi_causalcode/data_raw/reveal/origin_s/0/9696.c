static void check_new_cluster_is_empty ( void ) {
 int dbnum ;
 for ( dbnum = 0 ;
 dbnum < new_cluster . dbarr . ndbs ;
 dbnum ++ ) {
 int relnum ;
 RelInfoArr * rel_arr = & new_cluster . dbarr . dbs [ dbnum ] . rel_arr ;
 for ( relnum = 0 ;
 relnum < rel_arr -> nrels ;
 relnum ++ ) {
 if ( strcmp ( rel_arr -> rels [ relnum ] . nspname , "pg_catalog" ) != 0 ) pg_fatal ( "New cluster database \"%s\" is not empty\n" , new_cluster . dbarr . dbs [ dbnum ] . db_name ) ;
 }
 }
 }