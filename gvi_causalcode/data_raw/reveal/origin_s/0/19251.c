REGRESSION_TEST ( SDK_API_UUID ) ( RegressionTest * test , int , int * pstatus ) {
 TSUuid machine , uuid ;
 const char * str1 ;
 const char * str2 ;
 static const char uuid_v1 [ ] = "5de5f9ec-30f4-11e6-a073-002590a33e4e" ;
 static const char uuid_v4 [ ] = "0e95fe5f-295a-401d-9ae4-eb32756d73cb" ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 machine = TSProcessUuidGet ( ) ;
 if ( ! machine ) {
 SDK_RPRINT ( test , "TSProcessUuidGet" , "TestCase1" , TC_FAIL , "Returned a NULL pointer" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 else if ( ! ( ( ATSUuid * ) machine ) -> valid ( ) ) {
 SDK_RPRINT ( test , "TSProcessUuidGet" , "TestCase2" , TC_FAIL , "Returned an invalid UUID object" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 else {
 SDK_RPRINT ( test , "TSProcessUuidGet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSProcessUuidGet" , "TestCase2" , TC_PASS , "ok" ) ;
 }
 str1 = TSUuidStringGet ( machine ) ;
 if ( ! str1 || ( TS_UUID_STRING_LEN != strlen ( str1 ) ) ) {
 SDK_RPRINT ( test , "TSUuidStringGet" , "TestCase1" , TC_FAIL , "Did not return a valid UUID string representation" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 else {
 SDK_RPRINT ( test , "TSUuidStringGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 if ( ! ( uuid = TSUuidCreate ( ) ) ) {
 SDK_RPRINT ( test , "TSUuidCreate" , "TestCase1" , TC_FAIL , "Failed to crete a UUID object" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 else {
 SDK_RPRINT ( test , "TSUuidCreate" , "TestCase1" , TC_PASS , "ok" ) ;
 if ( TS_SUCCESS != TSUuidInitialize ( uuid , TS_UUID_V4 ) ) {
 SDK_RPRINT ( test , "TSUuidInitialize" , "TestCase1" , TC_FAIL , "Failed to Initialize a V4 UUID" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 goto cleanup ;
 }
 else {
 SDK_RPRINT ( test , "TSUuidInitialize" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 }
 if ( TS_UUID_V4 != TSUuidVersionGet ( uuid ) ) {
 SDK_RPRINT ( test , "TSUuidVersionGet" , "TestCase1" , TC_FAIL , "Failed to get the UUID version" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 goto cleanup ;
 }
 else {
 SDK_RPRINT ( test , "TSUuidVersionGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 if ( TS_SUCCESS != TSUuidCopy ( uuid , machine ) ) {
 SDK_RPRINT ( test , "TSUuidCopy" , "TestCase1" , TC_FAIL , "Failed to copy the Machine UUID object" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 goto cleanup ;
 }
 else {
 SDK_RPRINT ( test , "TSUuidCopy" , "TestCase1" , TC_PASS , "ok" ) ;
 str2 = TSUuidStringGet ( uuid ) ;
 if ( ! str2 || ( TS_UUID_STRING_LEN != strlen ( str2 ) ) || strcmp ( str1 , str2 ) ) {
 SDK_RPRINT ( test , "TSUuidCopy" , "TestCase2" , TC_FAIL , "The copied UUID strings are not identical" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 goto cleanup ;
 }
 else {
 SDK_RPRINT ( test , "TSUuidCopy" , "TestCase2" , TC_PASS , "ok" ) ;
 }
 }
 if ( TS_SUCCESS != TSUuidInitialize ( uuid , TS_UUID_V4 ) ) {
 SDK_RPRINT ( test , "TSUuidInitialize" , "TestCase2" , TC_FAIL , "Failed to re-initialize the UUID object" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 goto cleanup ;
 }
 else {
 SDK_RPRINT ( test , "TSUuidInitialize" , "TestCase2" , TC_PASS , "ok" ) ;
 str2 = TSUuidStringGet ( uuid ) ;
 if ( ! str2 || ( TS_UUID_STRING_LEN != strlen ( str2 ) ) || ! strcmp ( str1 , str2 ) ) {
 SDK_RPRINT ( test , "TSUuidInitialize" , "TestCase3" , TC_FAIL , "The re-initialized string is the same as before" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 goto cleanup ;
 }
 else {
 SDK_RPRINT ( test , "TSUuidInitialize" , "TestCase3" , TC_PASS , "ok" ) ;
 }
 }
 if ( ( TS_SUCCESS != TSUuidStringParse ( uuid , uuid_v1 ) ) || ( TS_UUID_V1 != TSUuidVersionGet ( uuid ) ) ) {
 SDK_RPRINT ( test , "TSUuidStringParse" , "TestCase1" , TC_FAIL , "Failed to parse the UUID v1 string" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 goto cleanup ;
 }
 else {
 SDK_RPRINT ( test , "TSUuidStringParse" , "TestCase1" , TC_PASS , "ok" ) ;
 str1 = TSUuidStringGet ( uuid ) ;
 if ( ! str1 || ( TS_UUID_STRING_LEN != strlen ( str1 ) ) || strcmp ( str1 , uuid_v1 ) ) {
 SDK_RPRINT ( test , "TSUuidStringString" , "TestCase2" , TC_FAIL , "The parse UUID v1 string does not match the original" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 goto cleanup ;
 }
 else {
 SDK_RPRINT ( test , "TSUuidStringParse" , "TestCase2" , TC_PASS , "ok" ) ;
 }
 }
 if ( ( TS_SUCCESS != TSUuidStringParse ( uuid , uuid_v4 ) ) || ( TS_UUID_V4 != TSUuidVersionGet ( uuid ) ) ) {
 SDK_RPRINT ( test , "TSUuidStringParse" , "TestCase3" , TC_FAIL , "Failed to parse the UUID v4 string" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 goto cleanup ;
 }
 else {
 SDK_RPRINT ( test , "TSUuidStringParse" , "TestCase3" , TC_PASS , "ok" ) ;
 str1 = TSUuidStringGet ( uuid ) ;
 if ( ! str1 || ( TS_UUID_STRING_LEN != strlen ( str1 ) ) || strcmp ( str1 , uuid_v4 ) ) {
 SDK_RPRINT ( test , "TSUuidStringParse" , "TestCase4" , TC_FAIL , "The parse UUID v4 string does not match the original" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 goto cleanup ;
 }
 else {
 SDK_RPRINT ( test , "TSUuidStringParse" , "TestCase4" , TC_PASS , "ok" ) ;
 }
 }
 * pstatus = REGRESSION_TEST_PASSED ;
 cleanup : TSUuidDestroy ( uuid ) ;
 return ;
 }