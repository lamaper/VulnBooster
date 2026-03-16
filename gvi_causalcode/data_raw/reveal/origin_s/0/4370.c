int main ( int argc , char * * argv ) {
 int printUsage = 0 ;
 int printVersion = 0 ;
 UBool useLongNames = 0 ;
 int optInd = 1 ;
 char * arg ;
 int32_t month = - 1 , year = - 1 ;
 UErrorCode status = U_ZERO_ERROR ;
 for ( optInd = 1 ;
 optInd < argc ;
 ++ optInd ) {
 arg = argv [ optInd ] ;
 if ( strcmp ( arg , "-v" ) == 0 || strcmp ( arg , "--version" ) == 0 ) {
 printVersion = 1 ;
 }
 else if ( strcmp ( arg , "-h" ) == 0 || strcmp ( arg , "--help" ) == 0 ) {
 printUsage = 1 ;
 }
 else if ( strcmp ( arg , "-l" ) == 0 || strcmp ( arg , "--long" ) == 0 ) {
 useLongNames = 1 ;
 }
 else if ( strcmp ( arg , "--" ) == 0 ) {
 ++ optInd ;
 break ;
 }
 else if ( strncmp ( arg , "-" , strlen ( "-" ) ) == 0 ) {
 printf ( "cal: invalid option -- %s\n" , arg + 1 ) ;
 printUsage = 1 ;
 }
 else {
 break ;
 }
 }
 if ( optInd != argc ) {
 if ( argc - optInd == 2 ) {
 sscanf ( argv [ optInd ] , "%d" , ( int * ) & month ) ;
 sscanf ( argv [ optInd + 1 ] , "%d" , ( int * ) & year ) ;
 if ( month < 0 || month > 12 ) {
 printf ( "icucal: Bad value for month -- %d\n" , ( int ) month ) ;
 printUsage = 1 ;
 }
 -- month ;
 }
 else {
 sscanf ( argv [ optInd ] , "%d" , ( int * ) & year ) ;
 }
 }
 if ( printUsage ) {
 usage ( ) ;
 return 0 ;
 }
 if ( printVersion ) {
 version ( ) ;
 return 0 ;
 }
 cal ( month , year , useLongNames , & status ) ;
 u_cleanup ( ) ;
 return ( U_FAILURE ( status ) ? 1 : 0 ) ;
 }