static bool str_array_contains ( ARRAY_TYPE ( const_string ) * arr , const char * str ) {
 const char * const * p ;
 array_foreach ( arr , p ) {
 if ( strcmp ( * p , str ) == 0 ) return TRUE ;
 }
 return FALSE ;
 }