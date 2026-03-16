static void U_CALLCONV normalizationCorrectionsLineFn ( void * context , char * fields [ ] [ 2 ] , int32_t fieldCount , UErrorCode * pErrorCode ) {
 uint32_t mapping [ 40 ] ;
 char * end , * s ;
 uint32_t code ;
 int32_t length ;
 UVersionInfo version ;
 UVersionInfo thisVersion ;
 code = ( uint32_t ) uprv_strtoul ( fields [ 0 ] [ 0 ] , & end , 16 ) ;
 if ( U_FAILURE ( * pErrorCode ) ) {
 fprintf ( stderr , "gensprep: error parsing NormalizationCorrections.txt mapping at %s\n" , fields [ 0 ] [ 0 ] ) ;
 exit ( * pErrorCode ) ;
 }
 s = fields [ 1 ] [ 0 ] ;
 length = u_parseCodePoints ( s , mapping , sizeof ( mapping ) / 4 , pErrorCode ) ;
 u_versionFromString ( version , fields [ 3 ] [ 0 ] ) ;
 u_versionFromString ( thisVersion , "3.2.0" ) ;
 if ( U_FAILURE ( * pErrorCode ) ) {
 fprintf ( stderr , "gensprep error parsing NormalizationCorrections.txt of U+%04lx - %s\n" , ( long ) code , u_errorName ( * pErrorCode ) ) ;
 exit ( * pErrorCode ) ;
 }
 if ( version [ 0 ] > thisVersion [ 0 ] || ( ( version [ 0 ] == thisVersion [ 0 ] ) && ( version [ 1 ] > thisVersion [ 1 ] ) ) ) {
 storeMapping ( code , mapping , length , USPREP_MAP , pErrorCode ) ;
 }
 setUnicodeVersionNC ( version ) ;
 }