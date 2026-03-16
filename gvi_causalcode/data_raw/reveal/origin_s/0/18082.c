static int collated_compare ( const void * a , const void * b ) {
 const char * const s1 = * ( const char * const * const ) a ;
 const char * const s2 = * ( const char * const * const ) b ;
 if ( s1 == s2 ) return 0 ;
 if ( s1 == NULL ) return 1 ;
 if ( s2 == NULL ) return - 1 ;
 return strcoll ( s1 , s2 ) ;
 }