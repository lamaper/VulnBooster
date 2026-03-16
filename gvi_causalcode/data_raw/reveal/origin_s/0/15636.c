static void check_databases_are_compatible ( void ) {
 int newdbnum ;
 int olddbnum ;
 DbInfo * newdbinfo ;
 DbInfo * olddbinfo ;
 for ( newdbnum = 0 ;
 newdbnum < new_cluster . dbarr . ndbs ;
 newdbnum ++ ) {
 newdbinfo = & new_cluster . dbarr . dbs [ newdbnum ] ;
 for ( olddbnum = 0 ;
 olddbnum < old_cluster . dbarr . ndbs ;
 olddbnum ++ ) {
 olddbinfo = & old_cluster . dbarr . dbs [ olddbnum ] ;
 if ( strcmp ( newdbinfo -> db_name , olddbinfo -> db_name ) == 0 ) {
 check_locale_and_encoding ( olddbinfo , newdbinfo ) ;
 break ;
 }
 }
 }
 }