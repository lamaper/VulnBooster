static UBool _isExtensionSubtags ( const char * s , int32_t len ) {
 const char * p = s ;
 const char * pSubtag = NULL ;
 if ( len < 0 ) {
 len = ( int32_t ) uprv_strlen ( s ) ;
 }
 while ( ( p - s ) < len ) {
 if ( * p == SEP ) {
 if ( pSubtag == NULL ) {
 return FALSE ;
 }
 if ( ! _isExtensionSubtag ( pSubtag , ( int32_t ) ( p - pSubtag ) ) ) {
 return FALSE ;
 }
 pSubtag = NULL ;
 }
 else if ( pSubtag == NULL ) {
 pSubtag = p ;
 }
 p ++ ;
 }
 if ( pSubtag == NULL ) {
 return FALSE ;
 }
 return _isExtensionSubtag ( pSubtag , ( int32_t ) ( p - pSubtag ) ) ;
 }