static const UChar * fetchErrorName ( UErrorCode err ) {
 if ( ! gInfoMessages ) {
 gInfoMessages = ( UChar * * ) malloc ( ( U_ERROR_WARNING_LIMIT - U_ERROR_WARNING_START ) * sizeof ( UChar * ) ) ;
 memset ( gInfoMessages , 0 , ( U_ERROR_WARNING_LIMIT - U_ERROR_WARNING_START ) * sizeof ( UChar * ) ) ;
 }
 if ( ! gErrMessages ) {
 gErrMessages = ( UChar * * ) malloc ( U_ERROR_LIMIT * sizeof ( UChar * ) ) ;
 memset ( gErrMessages , 0 , U_ERROR_LIMIT * sizeof ( UChar * ) ) ;
 }
 if ( err >= 0 ) return gErrMessages [ err ] ;
 else return gInfoMessages [ err - U_ERROR_WARNING_START ] ;
 }