static int cmp_value_string ( const void * v1 , const void * v2 ) {
 const value_string * vs1 = ( const value_string * ) v1 ;
 const value_string * vs2 = ( const value_string * ) v2 ;
 return strcmp ( vs1 -> strptr , vs2 -> strptr ) ;
 }