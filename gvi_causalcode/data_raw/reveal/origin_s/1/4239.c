static void TestHeapFunctions ( ) {
 UErrorCode status = U_ZERO_ERROR ;
 UResourceBundle * rb = NULL ;
 char * icuDataDir ;
 UVersionInfo unicodeVersion = {
 0 , 0 , 0 , 0 }
 ;
 icuDataDir = safeGetICUDataDirectory ( ) ;
 ctest_resetICU ( ) ;
 u_setMemoryFunctions ( & gContext , myMemAlloc , myMemRealloc , myMemFree , & status ) ;
 TEST_STATUS ( status , U_INVALID_STATE_ERROR ) ;
 u_cleanup ( ) ;
 status = U_ZERO_ERROR ;
 u_setMemoryFunctions ( & gContext , NULL , myMemRealloc , myMemFree , & status ) ;
 TEST_STATUS ( status , U_ILLEGAL_ARGUMENT_ERROR ) ;
 status = U_ZERO_ERROR ;
 u_setMemoryFunctions ( & gContext , myMemAlloc , NULL , myMemFree , & status ) ;
 TEST_STATUS ( status , U_ILLEGAL_ARGUMENT_ERROR ) ;
 status = U_ZERO_ERROR ;
 u_setMemoryFunctions ( & gContext , myMemAlloc , myMemRealloc , NULL , & status ) ;
 TEST_STATUS ( status , U_ILLEGAL_ARGUMENT_ERROR ) ;
 status = U_ZERO_ERROR ;
 u_setMemoryFunctions ( NULL , myMemAlloc , myMemRealloc , myMemFree , & status ) ;
 TEST_STATUS ( status , U_ZERO_ERROR ) ;
 u_setMemoryFunctions ( & gContext , myMemAlloc , myMemRealloc , myMemFree , & status ) ;
 TEST_STATUS ( status , U_ZERO_ERROR ) ;
 status = U_ZERO_ERROR ;
 u_setDataDirectory ( icuDataDir ) ;
 u_init ( & status ) ;
 TEST_STATUS ( status , U_ZERO_ERROR ) ;
 u_setMemoryFunctions ( NULL , myMemAlloc , myMemRealloc , myMemFree , & status ) ;
 TEST_STATUS ( status , U_INVALID_STATE_ERROR ) ;
 gBlockCount = 0 ;
 status = U_ZERO_ERROR ;
 rb = ures_open ( NULL , "es" , & status ) ;
 TEST_STATUS ( status , U_ZERO_ERROR ) ;
 if ( gBlockCount == 0 ) {
 log_err ( "Heap functions are not being called from ICU.\n" ) ;
 }
 ures_close ( rb ) ;
 ctest_resetICU ( ) ;
 u_getUnicodeVersion ( unicodeVersion ) ;
 if ( unicodeVersion [ 0 ] <= 0 ) {
 log_err ( "Properties doesn't reinitialize without u_init.\n" ) ;
 }
 status = U_ZERO_ERROR ;
 u_init ( & status ) ;
 TEST_STATUS ( status , U_ZERO_ERROR ) ;
 gBlockCount = 0 ;
 status = U_ZERO_ERROR ;
 rb = ures_open ( NULL , "fr" , & status ) ;
 TEST_STATUS ( status , U_ZERO_ERROR ) ;
 if ( gBlockCount != 0 ) {
 log_err ( "Heap functions did not reset after u_cleanup.\n" ) ;
 }
 ures_close ( rb ) ;
 free ( icuDataDir ) ;
 ctest_resetICU ( ) ;
 }