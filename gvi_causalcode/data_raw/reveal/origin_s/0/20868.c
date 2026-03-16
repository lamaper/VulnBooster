static int log_test_handler ( TSCont contp , TSEvent event , void * ) {
 TSFile filep ;
 char buf [ 1024 ] ;
 bool str_found ;
 int retVal = 0 ;
 TSAssert ( event == TS_EVENT_TIMEOUT ) ;
 LogTestData * data = ( LogTestData * ) TSContDataGet ( contp ) ;
 TSAssert ( data -> magic == MAGIC_ALIVE ) ;
 if ( ( filep = TSfopen ( data -> fullpath_logname , "r" ) ) == nullptr ) {
 SDK_RPRINT ( data -> test , "TSTextLogObject" , "TestCase1" , TC_FAIL , "can not open log file %s" , data -> fullpath_logname ) ;
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 return - 1 ;
 }
 else {
 str_found = false ;
 while ( TSfgets ( filep , buf , 1024 ) != nullptr ) {
 if ( strstr ( buf , LOG_TEST_PATTERN ) != nullptr ) {
 str_found = true ;
 break ;
 }
 }
 TSfclose ( filep ) ;
 if ( str_found == false ) {
 SDK_RPRINT ( data -> test , "TSTextLogObject" , "TestCase1" , TC_FAIL , "can not find pattern %s in log file" , LOG_TEST_PATTERN ) ;
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 return - 1 ;
 }
 }
 retVal = TSTextLogObjectDestroy ( data -> log ) ;
 if ( retVal != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSTextLogObjectDestroy" , "TestCase1" , TC_FAIL , "can not destroy log object" ) ;
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 return - 1 ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSTextLogObjectDestroy" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 * ( data -> pstatus ) = REGRESSION_TEST_PASSED ;
 SDK_RPRINT ( data -> test , "TSTextLogObject" , "TestCase1" , TC_PASS , "ok" ) ;
 int i = - 1 , l = 0 ;
 char c ;
 while ( c = data -> fullpath_logname [ l ] , c != 0 ) {
 if ( c == '/' ) {
 i = l ;
 }
 ++ l ;
 }
 char * meta_filename = ( char * ) ats_malloc ( l + 7 ) ;
 if ( i < 0 ) {
 ink_string_concatenate_strings ( meta_filename , "." , data -> fullpath_logname , ".meta" , NULL ) ;
 }
 else {
 memcpy ( meta_filename , data -> fullpath_logname , i + 1 ) ;
 ink_string_concatenate_strings ( & meta_filename [ i + 1 ] , "." , & data -> fullpath_logname [ i + 1 ] , ".meta" , NULL ) ;
 }
 unlink ( data -> fullpath_logname ) ;
 unlink ( meta_filename ) ;
 TSfree ( data -> fullpath_logname ) ;
 TSfree ( meta_filename ) ;
 meta_filename = nullptr ;
 data -> magic = MAGIC_DEAD ;
 TSfree ( data ) ;
 data = nullptr ;
 return - 1 ;
 }