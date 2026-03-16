static const UAmbiguousConverter * ucnv_getAmbiguous ( const UConverter * cnv ) {
 UErrorCode errorCode ;
 const char * name ;
 int32_t i ;
 if ( cnv == NULL ) {
 return NULL ;
 }
 errorCode = U_ZERO_ERROR ;
 name = ucnv_getName ( cnv , & errorCode ) ;
 if ( U_FAILURE ( errorCode ) ) {
 return NULL ;
 }
 for ( i = 0 ;
 i < UPRV_LENGTHOF ( ambiguousConverters ) ;
 ++ i ) {
 if ( 0 == uprv_strcmp ( name , ambiguousConverters [ i ] . name ) ) {
 return ambiguousConverters + i ;
 }
 }
 return NULL ;
 }