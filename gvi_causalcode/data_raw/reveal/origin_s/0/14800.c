REGRESSION_TEST ( SDK_API_TSMimeHdrParse ) ( RegressionTest * test , int , int * pstatus ) {
 const char * parse_string = "field1:field1Value1,field1Value2\r\nfield2:10,-34,45\r\nfield3:field3Value1,23\r\nfield2: 2345, field2Value2\r\n\r\n" ;
 const char * DUPLICATE_FIELD_NAME = "field2" ;
 const char * REMOVE_FIELD_NAME = "field3" ;
 TSMimeParser parser ;
 TSMBuffer bufp1 = ( TSMBuffer ) nullptr ;
 TSMBuffer bufp2 = ( TSMBuffer ) nullptr ;
 TSMBuffer bufp3 = ( TSMBuffer ) nullptr ;
 TSMLoc mime_hdr_loc1 = ( TSMLoc ) nullptr ;
 TSMLoc mime_hdr_loc2 = ( TSMLoc ) nullptr ;
 TSMLoc mime_hdr_loc3 = ( TSMLoc ) nullptr ;
 TSMLoc field_loc1 = ( TSMLoc ) nullptr ;
 TSMLoc field_loc2 = ( TSMLoc ) nullptr ;
 const char * start ;
 const char * end ;
 char * temp ;
 TSParseResult retval ;
 int hdrLength ;
 bool test_passed_parser_create = false ;
 bool test_passed_parse = false ;
 bool test_passed_parser_clear = false ;
 bool test_passed_parser_destroy = false ;
 bool test_passed_mime_hdr_print = false ;
 bool test_passed_mime_hdr_length_get = false ;
 bool test_passed_mime_hdr_field_next_dup = false ;
 bool test_passed_mime_hdr_copy = false ;
 bool test_passed_mime_hdr_clone = false ;
 bool test_passed_mime_hdr_field_remove = false ;
 bool test_passed_mime_hdr_field_copy = false ;
 bool test_passed_mime_hdr_field_copy_values = false ;
 bool test_passed_handle_mloc_release = false ;
 bool test_passed_mime_hdr_field_find = false ;
 parser = TSMimeParserCreate ( ) ;
 SDK_RPRINT ( test , "TSMimeParserCreate" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_parser_create = true ;
 if ( test_passed_parser_create == true ) {
 bufp1 = TSMBufferCreate ( ) ;
 if ( TSMimeHdrCreate ( bufp1 , & mime_hdr_loc1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSMimeHdrParse" , "TestCase1" , TC_FAIL , "Cannot create Mime hdr for parsing" ) ;
 SDK_RPRINT ( test , "TSMimeHdrPrint" , "TestCase1" , TC_FAIL , "Cannot run test as unable to create Mime Header for parsing" ) ;
 SDK_RPRINT ( test , "TSMimeHdrLengthGet" , "TestCase1" , TC_FAIL , "Cannot run test as unable to create Mime Header for parsing" ) ;
 if ( TSMBufferDestroy ( bufp1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrParse" , "TestCase1" , TC_FAIL , "Error in Destroying MBuffer" ) ;
 }
 }
 else {
 start = parse_string ;
 end = parse_string + strlen ( parse_string ) + 1 ;
 if ( ( retval = TSMimeHdrParse ( parser , bufp1 , mime_hdr_loc1 , & start , end ) ) == TS_PARSE_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrParse" , "TestCase1" , TC_FAIL , "TSMimeHdrParse returns TS_PARSE_ERROR" ) ;
 SDK_RPRINT ( test , "TSMimeHdrPrint" , "TestCase1" , TC_FAIL , "Cannot run test as TSMimeHdrParse returned Error." ) ;
 SDK_RPRINT ( test , "TSMimeHdrLengthGet" , "TestCase1" , TC_FAIL , "Cannot run test as TSMimeHdrParse returned Error." ) ;
 }
 else {
 if ( retval == TS_PARSE_DONE ) {
 temp = convert_mime_hdr_to_string ( bufp1 , mime_hdr_loc1 ) ;
 if ( strcmp ( parse_string , temp ) == 0 ) {
 SDK_RPRINT ( test , "TSMimeHdrParse" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrPrint" , "TestCase1" , TC_PASS , "ok" ) ;
 hdrLength = TSMimeHdrLengthGet ( bufp1 , mime_hdr_loc1 ) ;
 if ( hdrLength == ( int ) strlen ( temp ) ) {
 SDK_RPRINT ( test , "TSMimeHdrLengthGet" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_mime_hdr_length_get = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrLengthGet" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 test_passed_parse = true ;
 test_passed_mime_hdr_print = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrParse|TSMimeHdrPrint" , "TestCase1" , TC_FAIL , "Incorrect parsing or incorrect Printing" ) ;
 SDK_RPRINT ( test , "TSMimeHdrLengthGet" , "TestCase1" , TC_FAIL , "Cannot run test as TSMimeHdrParse|TSMimeHdrPrint failed." ) ;
 }
 TSfree ( temp ) ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrParse" , "TestCase1" , TC_FAIL , "Parsing Error" ) ;
 SDK_RPRINT ( test , "TSMimeHdrPrint" , "TestCase1" , TC_FAIL , "Cannot run test as TSMimeHdrParse returned error." ) ;
 SDK_RPRINT ( test , "TSMimeHdrLengthGet" , "TestCase1" , TC_FAIL , "Cannot run test as TSMimeHdrParse returned error." ) ;
 }
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrParse" , "TestCase1" , TC_FAIL , "Cannot run test as unable to create a parser" ) ;
 SDK_RPRINT ( test , "TSMimeHdrPrint" , "TestCase1" , TC_FAIL , "Cannot run test as unable to create a parser" ) ;
 SDK_RPRINT ( test , "TSMimeHdrLengthGet" , "TestCase1" , TC_FAIL , "Cannot run test as unable to create a parser" ) ;
 }
 if ( test_passed_parser_create == true ) {
 TSMimeParserClear ( parser ) ;
 SDK_RPRINT ( test , "TSMimeParserClear" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_parser_clear = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeParserClear" , "TestCase1" , TC_FAIL , "Cannot run test as unable to create a parser" ) ;
 }
 if ( test_passed_parser_create == true ) {
 TSMimeParserDestroy ( parser ) ;
 SDK_RPRINT ( test , "TSMimeParserDestroy" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_parser_destroy = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeParserDestroy" , "TestCase1" , TC_FAIL , "Cannot run test as unable to create a parser" ) ;
 }
 if ( test_passed_parse == true ) {
 if ( ( field_loc1 = TSMimeHdrFieldFind ( bufp1 , mime_hdr_loc1 , DUPLICATE_FIELD_NAME , - 1 ) ) == TS_NULL_MLOC ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldNextDup" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldFind returns TS_NULL_MLOC" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldFind" , "TestCase1" , TC_PASS , "TSMimeHdrFieldFind returns TS_NULL_MLOC" ) ;
 }
 else {
 const char * fieldName ;
 int length ;
 fieldName = TSMimeHdrFieldNameGet ( bufp1 , mime_hdr_loc1 , field_loc1 , & length ) ;
 if ( strncmp ( fieldName , DUPLICATE_FIELD_NAME , length ) == 0 ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldFind" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_mime_hdr_field_find = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldFind" , "TestCase1" , TC_PASS , "TSMimeHdrFieldFind returns incorrect field pointer" ) ;
 }
 field_loc2 = TSMimeHdrFieldNextDup ( bufp1 , mime_hdr_loc1 , field_loc1 ) ;
 if ( compare_field_names ( test , bufp1 , mime_hdr_loc1 , field_loc1 , bufp1 , mime_hdr_loc1 , field_loc2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldNextDup" , "TestCase1" , TC_FAIL , "Incorrect Pointer" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldNextDup" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_mime_hdr_field_next_dup = true ;
 }
 if ( TSHandleMLocRelease ( bufp1 , mime_hdr_loc1 , field_loc1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase1" , TC_FAIL , "TSHandleMLocRelease returns TS_ERROR" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_handle_mloc_release = true ;
 }
 if ( field_loc2 != nullptr ) {
 if ( TSHandleMLocRelease ( bufp1 , mime_hdr_loc1 , field_loc2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase2" , TC_FAIL , "TSHandleMLocRelease returns TS_ERROR" ) ;
 test_passed_handle_mloc_release = false ;
 }
 else {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase2" , TC_PASS , "ok" ) ;
 }
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldNext" , "TestCase1" , TC_FAIL , "Unable to run test as parsing failed." ) ;
 }
 if ( test_passed_parse == true ) {
 bufp2 = TSMBufferCreate ( ) ;
 if ( TSMimeHdrCreate ( bufp2 , & mime_hdr_loc2 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSMimeHdrCopy" , "TestCase1" , TC_FAIL , "Cannot create Mime hdr for copying" ) ;
 if ( TSMBufferDestroy ( bufp2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrCopy" , "TestCase1" , TC_FAIL , "Error in Destroying MBuffer" ) ;
 }
 }
 else {
 if ( TSMimeHdrCopy ( bufp2 , mime_hdr_loc2 , bufp1 , mime_hdr_loc1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrCopy" , "TestCase1" , TC_FAIL , "TSMimeHdrCopy returns TS_ERROR" ) ;
 }
 else {
 temp = convert_mime_hdr_to_string ( bufp2 , mime_hdr_loc2 ) ;
 if ( strcmp ( parse_string , temp ) == 0 ) {
 SDK_RPRINT ( test , "TSMimeHdrCopy" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_mime_hdr_copy = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrCopy" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 TSfree ( temp ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrCopy" , "TestCase1" , TC_FAIL , "Unable to run test as parsing failed." ) ;
 }
 bufp3 = TSMBufferCreate ( ) ;
 TSMimeHdrCreate ( bufp3 , & mime_hdr_loc3 ) ;
 test_passed_mime_hdr_clone = true ;
 if ( test_passed_mime_hdr_copy == true ) {
 if ( ( field_loc1 = TSMimeHdrFieldFind ( bufp2 , mime_hdr_loc2 , REMOVE_FIELD_NAME , - 1 ) ) == TS_NULL_MLOC ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldRemove" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldFind returns TS_NULL_MLOC" ) ;
 }
 else {
 if ( TSMimeHdrFieldRemove ( bufp2 , mime_hdr_loc2 , field_loc1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldRemove" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldRemove returns TS_ERROR" ) ;
 }
 else {
 field_loc2 = TSMimeHdrFieldFind ( bufp2 , mime_hdr_loc2 , REMOVE_FIELD_NAME , - 1 ) ;
 if ( ( field_loc2 == TS_NULL_MLOC ) || ( field_loc1 != field_loc2 ) ) {
 test_passed_mime_hdr_field_remove = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldRemove" , "TestCase1" , TC_FAIL , "Field Not Removed" ) ;
 }
 if ( test_passed_mime_hdr_field_remove == true ) {
 if ( TSMimeHdrFieldAppend ( bufp2 , mime_hdr_loc2 , field_loc1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldRemove" , "TestCase1" , TC_FAIL , "Unable to readd the field to mime header. Probably destroyed" ) ;
 test_passed_mime_hdr_field_remove = false ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldRemove" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 }
 }
 if ( TSHandleMLocRelease ( bufp2 , mime_hdr_loc2 , field_loc1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase3" , TC_FAIL , "TSHandleMLocRelease returns TS_ERROR" ) ;
 test_passed_handle_mloc_release = false ;
 }
 else {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase3" , TC_PASS , "ok" ) ;
 }
 if ( field_loc2 != nullptr ) {
 if ( TSHandleMLocRelease ( bufp2 , mime_hdr_loc2 , field_loc2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase4" , TC_FAIL , "TSHandleMLocRelease returns TS_ERROR" ) ;
 test_passed_handle_mloc_release = false ;
 }
 else {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase4" , TC_PASS , "ok" ) ;
 }
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldNext" , "TestCase1" , TC_FAIL , "Unable to run test as parsing failed." ) ;
 }
 if ( test_passed_mime_hdr_copy == true ) {
 if ( TSMimeHdrFieldCreate ( bufp2 , mime_hdr_loc2 , & field_loc1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldCopy" , "TestCase1" , TC_FAIL , "Unable to create field for Copying" ) ;
 }
 else {
 if ( ( field_loc2 = TSMimeHdrFieldGet ( bufp1 , mime_hdr_loc1 , 0 ) ) == TS_NULL_MLOC ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldCopy" , "TestCase1" , TC_FAIL , "Unable to get source field for copying" ) ;
 }
 else {
 if ( TSMimeHdrFieldCopy ( bufp2 , mime_hdr_loc2 , field_loc1 , bufp1 , mime_hdr_loc1 , field_loc2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldCopy" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldCopy returns TS_ERROR" ) ;
 }
 else {
 if ( ( compare_field_names ( test , bufp2 , mime_hdr_loc2 , field_loc1 , bufp1 , mime_hdr_loc1 , field_loc2 ) == TS_ERROR ) || ( compare_field_values ( test , bufp2 , mime_hdr_loc2 , field_loc1 , bufp1 , mime_hdr_loc1 , field_loc2 ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldCopy" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldCopy" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_mime_hdr_field_copy = true ;
 }
 }
 }
 if ( TSHandleMLocRelease ( bufp2 , mime_hdr_loc2 , field_loc1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase5" , TC_FAIL , "TSHandleMLocRelease returns TS_ERROR" ) ;
 test_passed_handle_mloc_release = false ;
 }
 else {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase5" , TC_PASS , "ok" ) ;
 }
 if ( field_loc2 != nullptr ) {
 if ( TSHandleMLocRelease ( bufp1 , mime_hdr_loc1 , field_loc2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase6" , TC_FAIL , "TSHandleMLocRelease returns TS_ERROR" ) ;
 test_passed_handle_mloc_release = false ;
 }
 else {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase6" , TC_PASS , "ok" ) ;
 }
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldCopy" , "TestCase1" , TC_FAIL , "Unable to run test as bufp2 might not have been created" ) ;
 }
 if ( test_passed_mime_hdr_clone == true ) {
 field_loc1 = nullptr ;
 field_loc2 = nullptr ;
 if ( ( field_loc2 = TSMimeHdrFieldGet ( bufp1 , mime_hdr_loc1 , 0 ) ) == TS_NULL_MLOC ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldClone" , "TestCase1" , TC_FAIL , "Unable to get source field for copying" ) ;
 }
 else {
 if ( TSMimeHdrFieldClone ( bufp3 , mime_hdr_loc3 , bufp1 , mime_hdr_loc1 , field_loc2 , & field_loc1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldClone" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldClone returns TS_ERROR" ) ;
 }
 else {
 if ( ( compare_field_names ( test , bufp3 , mime_hdr_loc3 , field_loc1 , bufp1 , mime_hdr_loc1 , field_loc2 ) == TS_ERROR ) || ( compare_field_values ( test , bufp3 , mime_hdr_loc3 , field_loc1 , bufp1 , mime_hdr_loc1 , field_loc2 ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldClone" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldClone" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 }
 }
 if ( field_loc1 != nullptr ) {
 if ( TSHandleMLocRelease ( bufp3 , mime_hdr_loc3 , field_loc1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase7" , TC_FAIL , "TSHandleMLocRelease returns TS_ERROR" ) ;
 test_passed_handle_mloc_release = false ;
 }
 else {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase7" , TC_PASS , "ok" ) ;
 }
 }
 if ( field_loc2 != nullptr ) {
 if ( TSHandleMLocRelease ( bufp1 , mime_hdr_loc1 , field_loc2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase8" , TC_FAIL , "TSHandleMLocRelease returns TS_ERROR" ) ;
 test_passed_handle_mloc_release = false ;
 }
 else {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase8" , TC_PASS , "ok" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldClone" , "TestCase1" , TC_FAIL , "Unable to run test as bufp3 might not have been created" ) ;
 }
 if ( test_passed_mime_hdr_copy == true ) {
 if ( TSMimeHdrFieldCreate ( bufp2 , mime_hdr_loc2 , & field_loc1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldCopyValues" , "TestCase1" , TC_FAIL , "Unable to create field for Copying" ) ;
 }
 else {
 if ( ( field_loc2 = TSMimeHdrFieldGet ( bufp1 , mime_hdr_loc1 , 0 ) ) == TS_NULL_MLOC ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldCopyValues" , "TestCase1" , TC_FAIL , "Unable to get source field for copying" ) ;
 }
 else {
 if ( TSMimeHdrFieldCopyValues ( bufp2 , mime_hdr_loc2 , field_loc1 , bufp1 , mime_hdr_loc1 , field_loc2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldCopyValues" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldCopy returns TS_ERROR" ) ;
 }
 else {
 if ( compare_field_values ( test , bufp2 , mime_hdr_loc2 , field_loc1 , bufp1 , mime_hdr_loc1 , field_loc2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldCopyValues" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldCopyValues" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_mime_hdr_field_copy_values = true ;
 }
 }
 }
 if ( TSHandleMLocRelease ( bufp2 , mime_hdr_loc2 , field_loc1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase9" , TC_FAIL , "TSHandleMLocRelease returns TS_ERROR" ) ;
 test_passed_handle_mloc_release = false ;
 }
 else {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase9" , TC_PASS , "ok" ) ;
 }
 if ( field_loc2 != nullptr ) {
 if ( TSHandleMLocRelease ( bufp1 , mime_hdr_loc1 , field_loc2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase10" , TC_FAIL , "TSHandleMLocRelease returns TS_ERROR" ) ;
 test_passed_handle_mloc_release = false ;
 }
 else {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase10" , TC_PASS , "ok" ) ;
 }
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldCopy" , "TestCase1" , TC_FAIL , "Unable to run test as bufp2 might not have been created" ) ;
 }
 if ( ( TSMimeHdrDestroy ( bufp1 , mime_hdr_loc1 ) == TS_ERROR ) || ( TSMimeHdrDestroy ( bufp2 , mime_hdr_loc2 ) == TS_ERROR ) || ( TSMimeHdrDestroy ( bufp3 , mime_hdr_loc3 ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "" , "TestCase" , TC_FAIL , "TSMimeHdrDestroy returns TS_ERROR" ) ;
 }
 if ( TSHandleMLocRelease ( bufp1 , TS_NULL_MLOC , mime_hdr_loc1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase11|12|13" , TC_FAIL , "Unable to release mime_hdr_loc1 to Mime Hdrs" ) ;
 test_passed_handle_mloc_release = false ;
 }
 if ( TSHandleMLocRelease ( bufp2 , TS_NULL_MLOC , mime_hdr_loc2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase11|12|13" , TC_FAIL , "Unable to release mime_hdr_loc2 to Mime Hdrs" ) ;
 test_passed_handle_mloc_release = false ;
 }
 if ( TSHandleMLocRelease ( bufp3 , TS_NULL_MLOC , mime_hdr_loc3 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase11|12|13" , TC_FAIL , "Unable to release mime_hdr_loc3 to Mime Hdrs" ) ;
 test_passed_handle_mloc_release = false ;
 }
 if ( TSMBufferDestroy ( bufp1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "" , "TestCase" , TC_FAIL , "TSMBufferDestroy(bufp1) returns TS_ERROR" ) ;
 }
 if ( TSMBufferDestroy ( bufp2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "" , "TestCase" , TC_FAIL , "TSMBufferDestroy(bufp2) returns TS_ERROR" ) ;
 }
 if ( TSMBufferDestroy ( bufp3 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "" , "TestCase" , TC_FAIL , "TSMBufferDestroy(bufp3) returns TS_ERROR" ) ;
 }
 if ( ( test_passed_parser_create != true ) || ( test_passed_parse != true ) || ( test_passed_parser_clear != true ) || ( test_passed_parser_destroy != true ) || ( test_passed_mime_hdr_print != true ) || ( test_passed_mime_hdr_length_get != true ) || ( test_passed_mime_hdr_field_next_dup != true ) || ( test_passed_mime_hdr_copy != true ) || ( test_passed_mime_hdr_clone != true ) || ( test_passed_mime_hdr_field_remove != true ) || ( test_passed_mime_hdr_field_copy != true ) || ( test_passed_mime_hdr_field_copy_values != true ) || ( test_passed_handle_mloc_release != true ) || ( test_passed_mime_hdr_field_find != true ) ) {
 * pstatus = REGRESSION_TEST_FAILED ;
 }
 else {
 * pstatus = REGRESSION_TEST_PASSED ;
 }
 }