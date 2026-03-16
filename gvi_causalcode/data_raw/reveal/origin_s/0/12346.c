static int test_stdout_behavior ( xd3_stream * stream , int ignore ) {
 int ret ;
 char buf [ TESTBUFSIZE ] ;
 test_setup ( ) ;
 snprintf_func ( buf , TESTBUFSIZE , "cp /devull %s" , TEST_TARGET_FILE ) ;
 if ( ( ret = do_cmd ( stream , buf ) ) ) {
 return ret ;
 }
 snprintf_func ( buf , TESTBUFSIZE , "%s -e %s %s" , program_name , TEST_TARGET_FILE , TEST_DELTA_FILE ) ;
 if ( ( ret = do_cmd ( stream , buf ) ) ) {
 return ret ;
 }
 snprintf_func ( buf , TESTBUFSIZE , "%s -e -c %s > %s" , program_name , TEST_TARGET_FILE , TEST_DELTA_FILE ) ;
 if ( ( ret = do_cmd ( stream , buf ) ) ) {
 return ret ;
 }
 snprintf_func ( buf , TESTBUFSIZE , "%s -q -d %s " , program_name , TEST_DELTA_FILE ) ;
 if ( ( ret = do_fail ( stream , buf ) ) ) {
 return ret ;
 }
 snprintf_func ( buf , TESTBUFSIZE , "%s -d -c %s > /devull" , program_name , TEST_DELTA_FILE ) ;
 if ( ( ret = do_cmd ( stream , buf ) ) ) {
 return ret ;
 }
 test_cleanup ( ) ;
 return 0 ;
 }