static void U_CALLCONV strprepProfileLineFn ( void * context , char * fields [ ] [ 2 ] , int32_t fieldCount , UErrorCode * pErrorCode ) {
 uint32_t mapping [ 40 ] ;
 char * end , * map ;
 uint32_t code ;
 int32_t length ;
 const char * typeName ;
 uint32_t rangeStart = 0 , rangeEnd = 0 ;
 const char * filename = ( const char * ) context ;
 const char * s ;
 s = u_skipWhitespace ( fields [ 0 ] [ 0 ] ) ;
 if ( * s == '@' ) {
 s ++ ;
 length = fields [ 0 ] [ 1 ] - s ;
 if ( length >= NORMALIZE_DIRECTIVE_LEN && uprv_strncmp ( s , NORMALIZE_DIRECTIVE , NORMALIZE_DIRECTIVE_LEN ) == 0 ) {
 options [ NORMALIZE ] . doesOccur = TRUE ;
 return ;
 }
 else if ( length >= CHECK_BIDI_DIRECTIVE_LEN && uprv_strncmp ( s , CHECK_BIDI_DIRECTIVE , CHECK_BIDI_DIRECTIVE_LEN ) == 0 ) {
 options [ CHECK_BIDI ] . doesOccur = TRUE ;
 return ;
 }
 else {
 fprintf ( stderr , "gensprep error parsing a directive %s." , fields [ 0 ] [ 0 ] ) ;
 }
 }
 typeName = fields [ 2 ] [ 0 ] ;
 map = fields [ 1 ] [ 0 ] ;
 if ( uprv_strstr ( typeName , usprepTypeNames [ USPREP_UNASSIGNED ] ) != NULL ) {
 u_parseCodePointRange ( s , & rangeStart , & rangeEnd , pErrorCode ) ;
 if ( U_FAILURE ( * pErrorCode ) ) {
 fprintf ( stderr , "Could not parse code point range. Error: %s\n" , u_errorName ( * pErrorCode ) ) ;
 return ;
 }
 storeRange ( rangeStart , rangeEnd , USPREP_UNASSIGNED , pErrorCode ) ;
 }
 else if ( uprv_strstr ( typeName , usprepTypeNames [ USPREP_PROHIBITED ] ) != NULL ) {
 u_parseCodePointRange ( s , & rangeStart , & rangeEnd , pErrorCode ) ;
 if ( U_FAILURE ( * pErrorCode ) ) {
 fprintf ( stderr , "Could not parse code point range. Error: %s\n" , u_errorName ( * pErrorCode ) ) ;
 return ;
 }
 storeRange ( rangeStart , rangeEnd , USPREP_PROHIBITED , pErrorCode ) ;
 }
 else if ( uprv_strstr ( typeName , usprepTypeNames [ USPREP_MAP ] ) != NULL ) {
 code = ( uint32_t ) uprv_strtoul ( s , & end , 16 ) ;
 if ( end <= s || end != fields [ 0 ] [ 1 ] ) {
 fprintf ( stderr , "gensprep: syntax error in field 0 at %s\n" , fields [ 0 ] [ 0 ] ) ;
 * pErrorCode = U_PARSE_ERROR ;
 exit ( U_PARSE_ERROR ) ;
 }
 length = u_parseCodePoints ( map , mapping , sizeof ( mapping ) / 4 , pErrorCode ) ;
 storeMapping ( code , mapping , length , USPREP_MAP , pErrorCode ) ;
 }
 else {
 * pErrorCode = U_INVALID_FORMAT_ERROR ;
 }
 if ( U_FAILURE ( * pErrorCode ) ) {
 fprintf ( stderr , "gensprep error parsing %s line %s at %s. Error: %s\n" , filename , fields [ 0 ] [ 0 ] , fields [ 2 ] [ 0 ] , u_errorName ( * pErrorCode ) ) ;
 exit ( * pErrorCode ) ;
 }
 }