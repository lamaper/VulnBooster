static int test_appheader ( xd3_stream * stream , int ignore ) {
 int i ;
 int ret ;
 char buf [ TESTBUFSIZE ] ;
 char bogus [ TESTBUFSIZE ] ;
 xoff_t ssize , tsize ;
 test_setup ( ) ;
 if ( ( ret = test_make_inputs ( stream , & ssize , & tsize ) ) ) {
 return ret ;
 }
 snprintf_func ( buf , TESTBUFSIZE , "%s -q -f -e -s %s %s %s" , program_name , TEST_SOURCE_FILE , TEST_TARGET_FILE , TEST_DELTA_FILE ) ;
 if ( ( ret = do_cmd ( stream , buf ) ) ) {
 return ret ;
 }
 if ( ( ret = test_copy_to ( program_name , TEST_RECON2_FILE ) ) ) {
 return ret ;
 }
 snprintf_func ( buf , TESTBUFSIZE , "chmod 0700 %s" , TEST_RECON2_FILE ) ;
 if ( ( ret = do_cmd ( stream , buf ) ) ) {
 return ret ;
 }
 if ( ( ret = test_save_copy ( TEST_TARGET_FILE ) ) ) {
 return ret ;
 }
 if ( ( ret = test_copy_to ( TEST_SOURCE_FILE , TEST_TARGET_FILE ) ) ) {
 return ret ;
 }
 if ( ( ret = test_compare_files ( TEST_TARGET_FILE , TEST_COPY_FILE ) ) == 0 ) {
 return XD3_INVALID ;
 }
 snprintf_func ( buf , TESTBUFSIZE , "(cd /tmp && %s -q -f -d %s)" , TEST_RECON2_FILE , TEST_DELTA_FILE ) ;
 if ( ( ret = do_cmd ( stream , buf ) ) ) {
 return ret ;
 }
 if ( ( ret = test_compare_files ( TEST_TARGET_FILE , TEST_COPY_FILE ) ) != 0 ) {
 return ret ;
 }
 for ( i = 0 ;
 i < TESTBUFSIZE / 4 ;
 ++ i ) {
 bogus [ 2 * i ] = 'G' ;
 bogus [ 2 * i + 1 ] = '/' ;
 }
 bogus [ TESTBUFSIZE / 2 - 1 ] = 0 ;
 snprintf_func ( buf , TESTBUFSIZE , "%s -q -f -A=%s -e -s %s %s %s" , program_name , bogus , TEST_SOURCE_FILE , TEST_TARGET_FILE , TEST_DELTA_FILE ) ;
 if ( ( ret = do_cmd ( stream , buf ) ) ) {
 return ret ;
 }
 snprintf_func ( buf , TESTBUFSIZE , "(cd /tmp && %s -q -f -d %s)" , TEST_RECON2_FILE , TEST_DELTA_FILE ) ;
 if ( ( ret = do_cmd ( stream , buf ) ) == 0 ) {
 return XD3_INVALID ;
 }
 if ( ! WIFEXITED ( ret ) ) {
 return XD3_INVALID ;
 }
 return 0 ;
 }