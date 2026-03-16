gcry_sexp_t gcry_sexp_nth ( const gcry_sexp_t list , int number ) {
 const byte * p ;
 DATALEN n ;
 gcry_sexp_t newlist ;
 byte * d ;
 int level = 0 ;
 if ( ! list || list -> d [ 0 ] != ST_OPEN ) return NULL ;
 p = list -> d ;
 while ( number > 0 ) {
 p ++ ;
 if ( * p == ST_DATA ) {
 memcpy ( & n , ++ p , sizeof n ) ;
 p += sizeof n + n ;
 p -- ;
 if ( ! level ) number -- ;
 }
 else if ( * p == ST_OPEN ) {
 level ++ ;
 }
 else if ( * p == ST_CLOSE ) {
 level -- ;
 if ( ! level ) number -- ;
 }
 else if ( * p == ST_STOP ) {
 return NULL ;
 }
 }
 p ++ ;
 if ( * p == ST_DATA ) {
 memcpy ( & n , p , sizeof n ) ;
 p += sizeof n ;
 newlist = gcry_malloc ( sizeof * newlist + n + 1 ) ;
 if ( ! newlist ) return NULL ;
 d = newlist -> d ;
 memcpy ( d , p , n ) ;
 d += n ;
 * d ++ = ST_STOP ;
 }
 else if ( * p == ST_OPEN ) {
 const byte * head = p ;
 level = 1 ;
 do {
 p ++ ;
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
 while ( level ) ;
 n = p + 1 - head ;
 newlist = gcry_malloc ( sizeof * newlist + n ) ;
 if ( ! newlist ) return NULL ;
 d = newlist -> d ;
 memcpy ( d , head , n ) ;
 d += n ;
 * d ++ = ST_STOP ;
 }
 else newlist = NULL ;
 return normalize ( newlist ) ;
 }