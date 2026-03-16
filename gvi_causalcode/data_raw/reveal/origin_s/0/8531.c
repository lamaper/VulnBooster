extern int main ( int argc , char * argv [ ] ) {


 const char * bundleName = NULL , * inputFileName = NULL ;
 char * basename = NULL ;
 int32_t sprepOptions = 0 ;
 UErrorCode errorCode = U_ZERO_ERROR ;
 U_MAIN_INIT_ARGS ( argc , argv ) ;
 options [ DESTDIR ] . value = u_getDataDirectory ( ) ;
 options [ SOURCEDIR ] . value = "" ;
 options [ UNICODE_VERSION ] . value = "0" ;
 options [ BUNDLE_NAME ] . value = DATA_NAME ;
 options [ NORMALIZE ] . value = "" ;
 argc = u_parseArgs ( argc , argv , UPRV_LENGTHOF ( options ) , options ) ;
 if ( argc < 0 ) {
 fprintf ( stderr , "error in command line argument \"%s\"\n" , argv [ - argc ] ) ;
 }
 if ( argc < 0 || options [ HELP ] . doesOccur || options [ HELP_QUESTION_MARK ] . doesOccur ) {
 return printHelp ( argc , argv ) ;
 }
 beVerbose = options [ VERBOSE ] . doesOccur ;
 haveCopyright = options [ COPYRIGHT ] . doesOccur ;
 srcDir = options [ SOURCEDIR ] . value ;
 destDir = options [ DESTDIR ] . value ;
 bundleName = options [ BUNDLE_NAME ] . value ;
 if ( options [ NORMALIZE ] . doesOccur ) {
 icuUniDataDir = options [ NORMALIZE ] . value ;
 }
 else {
 icuUniDataDir = options [ NORM_CORRECTION_DIR ] . value ;
 }
 if ( argc < 2 ) {
 return printHelp ( argc , argv ) ;
 }
 else {
 inputFileName = argv [ 1 ] ;
 }
 if ( ! options [ UNICODE_VERSION ] . doesOccur ) {
 return printHelp ( argc , argv ) ;
 }
 if ( options [ ICUDATADIR ] . doesOccur ) {
 u_setDataDirectory ( options [ ICUDATADIR ] . value ) ;
 }

 generateData ( destDir , bundleName ) ;

 filename = ( char * ) uprv_malloc ( uprv_strlen ( srcDir ) + uprv_strlen ( inputFileName ) + ( icuUniDataDir == NULL ? 0 : uprv_strlen ( icuUniDataDir ) ) + 40 ) ;
 if ( uprv_strchr ( srcDir , U_FILE_SEP_CHAR ) == NULL && uprv_strchr ( srcDir , U_FILE_ALT_SEP_CHAR ) == NULL ) {
 filename [ 0 ] = '.' ;
 filename [ 1 ] = U_FILE_SEP_CHAR ;
 uprv_strcpy ( filename + 2 , srcDir ) ;
 }
 else {
 uprv_strcpy ( filename , srcDir ) ;
 }
 basename = filename + uprv_strlen ( filename ) ;
 if ( basename > filename && * ( basename - 1 ) != U_FILE_SEP_CHAR ) {
 * basename ++ = U_FILE_SEP_CHAR ;
 }
 init ( ) ;
 uprv_strcpy ( basename , inputFileName ) ;
 parseMappings ( filename , FALSE , & errorCode ) ;
 if ( U_FAILURE ( errorCode ) ) {
 fprintf ( stderr , "Could not open file %s for reading. Error: %s \n" , filename , u_errorName ( errorCode ) ) ;
 return errorCode ;
 }
 if ( options [ NORMALIZE ] . doesOccur ) {
 uprv_strcpy ( filename , icuUniDataDir ) ;
 basename = filename + uprv_strlen ( filename ) ;
 if ( basename > filename && * ( basename - 1 ) != U_FILE_SEP_CHAR ) {
 * basename ++ = U_FILE_SEP_CHAR ;
 }
 * basename ++ = U_FILE_SEP_CHAR ;
 uprv_strcpy ( basename , NORM_CORRECTIONS_FILE_NAME ) ;
 parseNormalizationCorrections ( filename , & errorCode ) ;
 if ( U_FAILURE ( errorCode ) ) {
 fprintf ( stderr , "Could not open file %s for reading \n" , filename ) ;
 return errorCode ;
 }
 sprepOptions |= _SPREP_NORMALIZATION_ON ;
 }
 if ( options [ CHECK_BIDI ] . doesOccur ) {
 sprepOptions |= _SPREP_CHECK_BIDI_ON ;
 }
 setOptions ( sprepOptions ) ;
 if ( U_SUCCESS ( errorCode ) ) {
 generateData ( destDir , bundleName ) ;
 cleanUpData ( ) ;
 }
 uprv_free ( filename ) ;
 u_cleanup ( ) ;

 }