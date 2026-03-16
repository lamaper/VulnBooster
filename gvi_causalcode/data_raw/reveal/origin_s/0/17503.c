char * gcry_sexp_nth_string ( const gcry_sexp_t list , int number ) {
 const char * s ;
 size_t n ;
 char * buf ;
 s = sexp_nth_data ( list , number , & n ) ;
 if ( ! s || n < 1 || ( n + 1 ) < 1 ) return NULL ;
 buf = gcry_malloc ( n + 1 ) ;
 if ( ! buf ) return NULL ;
 memcpy ( buf , s , n ) ;
 buf [ n ] = 0 ;
 return buf ;
 }