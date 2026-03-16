static gboolean memiszero ( const void * ptr , size_t count ) {
 const guint8 * p = ( const guint8 * ) ptr ;
 while ( count != 0 ) {
 if ( * p != 0 ) return FALSE ;
 p ++ ;
 count -- ;
 }
 return TRUE ;
 }