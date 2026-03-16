static const UChar * u_file_translit ( UFILE * f , const UChar * src , int32_t * count , UBool flush ) {
 int32_t newlen ;
 int32_t junkCount = 0 ;
 int32_t textLength ;
 int32_t textLimit ;
 UTransPosition pos ;
 UErrorCode status = U_ZERO_ERROR ;
 if ( count == NULL ) {
 count = & junkCount ;
 }
 if ( ( ! f ) || ( ! f -> fTranslit ) || ( ! f -> fTranslit -> translit ) ) {
 return src ;
 }
 if ( f -> fTranslit -> length > f -> fTranslit -> pos ) {
 memmove ( f -> fTranslit -> buffer , f -> fTranslit -> buffer + f -> fTranslit -> pos , ( f -> fTranslit -> length - f -> fTranslit -> pos ) * sizeof ( UChar ) ) ;
 }
 f -> fTranslit -> length -= f -> fTranslit -> pos ;
 f -> fTranslit -> pos = 0 ;
 newlen = ( * count + f -> fTranslit -> length ) * 4 ;
 if ( newlen > f -> fTranslit -> capacity ) {
 if ( f -> fTranslit -> buffer == NULL ) {
 f -> fTranslit -> buffer = ( UChar * ) uprv_malloc ( newlen * sizeof ( UChar ) ) ;
 }
 else {
 f -> fTranslit -> buffer = ( UChar * ) uprv_realloc ( f -> fTranslit -> buffer , newlen * sizeof ( UChar ) ) ;
 }
 if ( f -> fTranslit -> buffer == NULL ) {
 return NULL ;
 }
 f -> fTranslit -> capacity = newlen ;
 }
 u_strncpy ( f -> fTranslit -> buffer + f -> fTranslit -> length , src , * count ) ;
 f -> fTranslit -> length += * count ;
 if ( flush == FALSE ) {
 textLength = f -> fTranslit -> length ;
 pos . contextStart = 0 ;
 pos . contextLimit = textLength ;
 pos . start = 0 ;
 pos . limit = textLength ;
 utrans_transIncrementalUChars ( f -> fTranslit -> translit , f -> fTranslit -> buffer , & textLength , f -> fTranslit -> capacity , & pos , & status ) ;
 * count = pos . start ;
 f -> fTranslit -> pos = pos . start ;
 f -> fTranslit -> length = pos . limit ;
 return f -> fTranslit -> buffer ;
 }
 else {
 textLength = f -> fTranslit -> length ;
 textLimit = f -> fTranslit -> length ;
 utrans_transUChars ( f -> fTranslit -> translit , f -> fTranslit -> buffer , & textLength , f -> fTranslit -> capacity , 0 , & textLimit , & status ) ;
 * count = textLimit ;
 f -> fTranslit -> pos = 0 ;
 f -> fTranslit -> length = 0 ;
 return f -> fTranslit -> buffer ;
 }
 }