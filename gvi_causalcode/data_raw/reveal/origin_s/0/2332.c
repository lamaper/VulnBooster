static void ustr_resize ( struct UString * s , int32_t len , UErrorCode * status ) {
 if ( U_FAILURE ( * status ) ) return ;
 s -> fChars = ( UChar * ) uprv_realloc ( s -> fChars , sizeof ( UChar ) * ( len + 1 ) ) ;
 if ( s -> fChars == 0 ) {
 * status = U_MEMORY_ALLOCATION_ERROR ;
 s -> fLength = s -> fCapacity = 0 ;
 return ;
 }
 s -> fCapacity = len ;
 }