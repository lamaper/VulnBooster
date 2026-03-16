gcry_sexp_t gcry_sexp_find_token ( const gcry_sexp_t list , const char * tok , size_t toklen ) {
 const byte * p ;
 DATALEN n ;
 if ( ! list ) return NULL ;
 if ( ! toklen ) toklen = strlen ( tok ) ;
 p = list -> d ;
 while ( * p != ST_STOP ) {
 if ( * p == ST_OPEN && p [ 1 ] == ST_DATA ) {
 const byte * head = p ;
 p += 2 ;
 memcpy ( & n , p , sizeof n ) ;
 p += sizeof n ;
 if ( n == toklen && ! memcmp ( p , tok , toklen ) ) {
 gcry_sexp_t newlist ;
 byte * d ;
 int level = 1 ;
 for ( p += n ;
 level ;
 p ++ ) {
 if ( * p == ST_DATA ) {
 memcpy ( & n , ++ p , sizeof n ) ;
 p += sizeof n + n ;
 p -- ;
 }
 else if ( * p == ST_OPEN ) {
 level ++ ;
 }
 else if ( * p == ST_CLOSE ) {
 level -- ;
 }
 else if ( * p == ST_STOP ) {
 BUG ( ) ;
 }
 }
 n = p - head ;
 newlist = gcry_malloc ( sizeof * newlist + n ) ;
 if ( ! newlist ) {
 return NULL ;
 }
 d = newlist -> d ;
 memcpy ( d , head , n ) ;
 d += n ;
 * d ++ = ST_STOP ;
 return normalize ( newlist ) ;
 }
 p += n ;
 }
 else if ( * p == ST_DATA ) {
 memcpy ( & n , ++ p , sizeof n ) ;
 p += sizeof n ;
 p += n ;
 }
 else p ++ ;
 }
 return NULL ;
 }