static void prepare_vacuum_command ( PQExpBuffer sql , PGconn * conn , vacuumingOptions * vacopts , const char * table ) {
 resetPQExpBuffer ( sql ) ;
 if ( vacopts -> analyze_only ) {
 appendPQExpBufferStr ( sql , "ANALYZE" ) ;
 if ( vacopts -> verbose ) appendPQExpBufferStr ( sql , " VERBOSE" ) ;
 }
 else {
 appendPQExpBufferStr ( sql , "VACUUM" ) ;
 if ( PQserverVersion ( conn ) >= 90000 ) {
 const char * paren = " (" ;
 const char * comma = ", " ;
 const char * sep = paren ;
 if ( vacopts -> full ) {
 appendPQExpBuffer ( sql , "%sFULL" , sep ) ;
 sep = comma ;
 }
 if ( vacopts -> freeze ) {
 appendPQExpBuffer ( sql , "%sFREEZE" , sep ) ;
 sep = comma ;
 }
 if ( vacopts -> verbose ) {
 appendPQExpBuffer ( sql , "%sVERBOSE" , sep ) ;
 sep = comma ;
 }
 if ( vacopts -> and_analyze ) {
 appendPQExpBuffer ( sql , "%sANALYZE" , sep ) ;
 sep = comma ;
 }
 if ( sep != paren ) appendPQExpBufferChar ( sql , ')' ) ;
 }
 else {
 if ( vacopts -> full ) appendPQExpBufferStr ( sql , " FULL" ) ;
 if ( vacopts -> freeze ) appendPQExpBufferStr ( sql , " FREEZE" ) ;
 if ( vacopts -> verbose ) appendPQExpBufferStr ( sql , " VERBOSE" ) ;
 if ( vacopts -> and_analyze ) appendPQExpBufferStr ( sql , " ANALYZE" ) ;
 }
 }
 if ( table ) appendPQExpBuffer ( sql , " %s" , table ) ;
 appendPQExpBufferChar ( sql , ';
' ) ;
 }