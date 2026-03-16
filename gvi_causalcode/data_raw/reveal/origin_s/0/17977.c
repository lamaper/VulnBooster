static bool is_valid_host_port ( const char * host , const char * port ) {
 for ( const char * p = host ;
 * p ;
 p ++ ) if ( ! isalnum ( * p ) && * p != '-' && * p != '.' ) {
 return false ;
 }
 for ( const char * p = port ;
 * p ;
 p ++ ) if ( ! isalnum ( * p ) ) {
 return false ;
 }
 return true ;
 }