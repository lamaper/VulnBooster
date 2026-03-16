gcry_sexp_t gcry_sexp_cdr ( const gcry_sexp_t list ) {
 const byte * p ;
 const byte * head ;
 DATALEN n ;
 gcry_sexp_t newlist ;
 byte * d ;
 int level = 0 ;
 int skip = 1 ;
 if ( ! list || list -> d [ 0 ] != ST_OPEN ) return NULL ;
 p = list -> d ;
 while ( skip > 0 ) {
 p ++ ;
 if ( * p == ST_DATA ) {
 memcpy ( & n , ++ p , sizeof n ) ;
 p += sizeof n + n ;
 p -- ;
 if ( ! level ) skip -- ;
 }
 else if ( * p == ST_OPEN ) {
 level ++ ;
 }
 else if ( * p == ST_CLOSE ) {
 level -- ;
 if ( ! level ) skip -- ;
 }
 else if ( * p == ST_STOP ) {
 return NULL ;
 }
 }
 p ++ ;
 head = p ;
 level = 0 ;
 do {
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
 return NULL ;
 }
 p ++ ;
 }
 while ( level ) ;
 n = p - head ;
 newlist = gcry_malloc ( sizeof * newlist + n + 2 ) ;
 if ( ! newlist ) return NULL ;
 d = newlist -> d ;
 * d ++ = ST_OPEN ;
 memcpy ( d , head , n ) ;
 d += n ;
 * d ++ = ST_CLOSE ;
 * d ++ = ST_STOP ;
 return normalize ( newlist ) ;
 }