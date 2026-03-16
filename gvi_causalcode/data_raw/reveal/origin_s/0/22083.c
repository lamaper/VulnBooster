REGRESSION_TEST ( SDK_API_TSMimeHdrField ) ( RegressionTest * test , int , int * pstatus ) {
 TSMBuffer bufp1 = ( TSMBuffer ) nullptr ;
 TSMLoc mime_loc1 = ( TSMLoc ) nullptr ;
 TSMLoc field_loc11 = ( TSMLoc ) nullptr ;
 TSMLoc field_loc12 = ( TSMLoc ) nullptr ;
 TSMLoc field_loc13 = ( TSMLoc ) nullptr ;
 TSMLoc field_loc14 = ( TSMLoc ) nullptr ;
 TSMLoc field_loc15 = ( TSMLoc ) nullptr ;
 const char * field1Name = "field1" ;
 const char * field2Name = "field2" ;
 const char * field3Name = "field3" ;
 const char * field4Name = "field4" ;
 const char * field5Name = "field5" ;
 const char * field1NameGet ;
 const char * field2NameGet ;
 const char * field3NameGet ;
 const char * field4NameGet ;
 const char * field5NameGet ;
 int field1NameGetLength ;
 int field2NameGetLength ;
 int field3NameGetLength ;
 int field4NameGetLength ;
 int field5NameGetLength ;
 int field1_length ;
 int field2_length ;
 int field3_length ;
 int field4_length ;
 TSMLoc test_field_loc11 = ( TSMLoc ) nullptr ;
 TSMLoc test_field_loc12 = ( TSMLoc ) nullptr ;
 TSMLoc test_field_loc13 = ( TSMLoc ) nullptr ;
 TSMLoc test_field_loc14 = ( TSMLoc ) nullptr ;
 TSMLoc test_field_loc15 = ( TSMLoc ) nullptr ;
 int actualNumberOfFields ;
 int numberOfFields ;
 const char * field1Value1 = "field1Value1" ;
 const char * field1Value2 = "field1Value2" ;
 const char * field1Value3 = "field1Value3" ;
 const char * field1Value4 = "field1Value4" ;
 const char * field1Value5 = "field1Value5" ;
 const char * field1ValueNew = "newfieldValue" ;
 const char * field1Value1Get ;
 const char * field1Value2Get ;
 const char * field1Value3Get ;
 const char * field1Value4Get ;
 const char * field1Value5Get ;
 const char * field1ValueAllGet ;
 const char * field1ValueNewGet ;
 int lengthField1Value1 ;
 int lengthField1Value2 ;
 int lengthField1Value3 ;
 int lengthField1Value4 ;
 int lengthField1Value5 ;
 int lengthField1ValueAll ;
 int lengthField1ValueNew ;
 time_t field2Value1 = time ( nullptr ) ;
 time_t field2Value1Get ;
 time_t field2ValueNew ;
 time_t field2ValueNewGet ;
 int field3Value1 = 31 ;
 int field3Value2 = 32 ;
 int field3Value3 = 33 ;
 int field3Value4 = 34 ;
 int field3Value5 = 35 ;
 int field3ValueNew = 30 ;
 int field3Value1Get ;
 int field3Value2Get ;
 int field3Value3Get ;
 int field3Value4Get ;
 int field3Value5Get ;
 int field3ValueNewGet ;
 unsigned int field4Value1 = 41 ;
 unsigned int field4Value2 = 42 ;
 unsigned int field4Value3 = 43 ;
 unsigned int field4Value4 = 44 ;
 unsigned int field4Value5 = 45 ;
 unsigned int field4ValueNew = 40 ;
 unsigned int field4Value1Get ;
 unsigned int field4Value2Get ;
 unsigned int field4Value3Get ;
 unsigned int field4Value4Get ;
 unsigned int field4Value5Get ;
 unsigned int field4ValueNewGet ;
 const char * field5Value1 = "field5Value1" ;
 const char * field5Value1Append = "AppendedValue" ;
 const char * fieldValueAppendGet ;
 int lengthFieldValueAppended ;
 int field5Value2 = 52 ;
 const char * field5Value3 = "DeleteValue" ;
 const char * fieldValueDeleteGet ;
 int lengthFieldValueDeleteGet ;
 unsigned int field5Value4 = 54 ;
 int numberOfValueInField ;
 TSMLoc field_loc ;
 bool test_passed_MBuffer_Create = false ;
 bool test_passed_Mime_Hdr_Create = false ;
 bool test_passed_Mime_Hdr_Field_Create = false ;
 bool test_passed_Mime_Hdr_Field_Name = false ;
 bool test_passed_Mime_Hdr_Field_Append = false ;
 bool test_passed_Mime_Hdr_Field_Get = false ;
 bool test_passed_Mime_Hdr_Field_Next = false ;
 bool test_passed_Mime_Hdr_Fields_Count = false ;
 bool test_passed_Mime_Hdr_Field_Value_String_Insert = false ;
 bool test_passed_Mime_Hdr_Field_Value_String_Get = false ;
 bool test_passed_Mime_Hdr_Field_Value_String_Set = false ;
 bool test_passed_Mime_Hdr_Field_Value_Date_Insert = false ;
 bool test_passed_Mime_Hdr_Field_Value_Date_Get = false ;
 bool test_passed_Mime_Hdr_Field_Value_Date_Set = false ;
 bool test_passed_Mime_Hdr_Field_Value_Int_Insert = false ;
 bool test_passed_Mime_Hdr_Field_Value_Int_Get = false ;
 bool test_passed_Mime_Hdr_Field_Value_Int_Set = false ;
 bool test_passed_Mime_Hdr_Field_Value_Uint_Insert = false ;
 bool test_passed_Mime_Hdr_Field_Value_Uint_Get = false ;
 bool test_passed_Mime_Hdr_Field_Value_Uint_Set = false ;
 bool test_passed_Mime_Hdr_Field_Value_Append = false ;
 bool test_passed_Mime_Hdr_Field_Value_Delete = false ;
 bool test_passed_Mime_Hdr_Field_Values_Clear = false ;
 bool test_passed_Mime_Hdr_Field_Values_Count = false ;
 bool test_passed_Mime_Hdr_Field_Destroy = false ;
 bool test_passed_Mime_Hdr_Fields_Clear = false ;
 bool test_passed_Mime_Hdr_Destroy = false ;
 bool test_passed_MBuffer_Destroy = false ;
 bool test_passed_Mime_Hdr_Field_Length_Get = false ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 bufp1 = TSMBufferCreate ( ) ;
 SDK_RPRINT ( test , "TSMBufferCreate" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_MBuffer_Create = true ;
 if ( test_passed_MBuffer_Create == true ) {
 if ( TSMimeHdrCreate ( bufp1 , & mime_loc1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSMimeHdrCreate" , "TestCase1" , TC_FAIL , "TSMimeHdrCreate Returns TS_ERROR" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrCreate" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Create = true ;
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrCreate" , "TestCase1" , TC_FAIL , "Cannot run test as Test for TSMBufferCreate Failed" ) ;
 }
 if ( test_passed_Mime_Hdr_Create == true ) {
 if ( ( TSMimeHdrFieldCreate ( bufp1 , mime_loc1 , & field_loc11 ) != TS_SUCCESS ) || ( TSMimeHdrFieldCreate ( bufp1 , mime_loc1 , & field_loc12 ) != TS_SUCCESS ) || ( TSMimeHdrFieldCreate ( bufp1 , mime_loc1 , & field_loc13 ) != TS_SUCCESS ) || ( TSMimeHdrFieldCreate ( bufp1 , mime_loc1 , & field_loc14 ) != TS_SUCCESS ) || ( TSMimeHdrFieldCreate ( bufp1 , mime_loc1 , & field_loc15 ) != TS_SUCCESS ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldCreate" , "TestCase1|2|3|4|5" , TC_FAIL , "TSMimeHdrFieldCreate Returns TS_ERROR" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldCreate" , "TestCase1|2|3|4|5" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Create = true ;
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldCreate" , "All Test Case" , TC_FAIL , "Cannot run test as Test for TSMimeHdrCreate Failed" ) ;
 }
 if ( test_passed_Mime_Hdr_Field_Create == true ) {
 if ( ( TSMimeHdrFieldNameSet ( bufp1 , mime_loc1 , field_loc11 , field1Name , - 1 ) == TS_ERROR ) || ( TSMimeHdrFieldNameSet ( bufp1 , mime_loc1 , field_loc12 , field2Name , - 1 ) == TS_ERROR ) || ( TSMimeHdrFieldNameSet ( bufp1 , mime_loc1 , field_loc13 , field3Name , - 1 ) == TS_ERROR ) || ( TSMimeHdrFieldNameSet ( bufp1 , mime_loc1 , field_loc14 , field4Name , - 1 ) == TS_ERROR ) || ( TSMimeHdrFieldNameSet ( bufp1 , mime_loc1 , field_loc15 , field5Name , - 1 ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldNameSet" , "TestCase1|2|3|4|5" , TC_FAIL , "TSMimeHdrFieldNameSet Returns TS_ERROR" ) ;
 }
 else {
 field1NameGet = TSMimeHdrFieldNameGet ( bufp1 , mime_loc1 , field_loc11 , & field1NameGetLength ) ;
 field2NameGet = TSMimeHdrFieldNameGet ( bufp1 , mime_loc1 , field_loc12 , & field2NameGetLength ) ;
 field3NameGet = TSMimeHdrFieldNameGet ( bufp1 , mime_loc1 , field_loc13 , & field3NameGetLength ) ;
 field4NameGet = TSMimeHdrFieldNameGet ( bufp1 , mime_loc1 , field_loc14 , & field4NameGetLength ) ;
 field5NameGet = TSMimeHdrFieldNameGet ( bufp1 , mime_loc1 , field_loc15 , & field5NameGetLength ) ;
 if ( ( ( strncmp ( field1NameGet , field1Name , field1NameGetLength ) == 0 ) && ( field1NameGetLength == ( int ) strlen ( field1Name ) ) ) && ( ( strncmp ( field2NameGet , field2Name , field2NameGetLength ) == 0 ) && ( field2NameGetLength == ( int ) strlen ( field2Name ) ) ) && ( ( strncmp ( field3NameGet , field3Name , field3NameGetLength ) == 0 ) && ( field3NameGetLength == ( int ) strlen ( field3Name ) ) ) && ( ( strncmp ( field4NameGet , field4Name , field4NameGetLength ) == 0 ) && ( field4NameGetLength == ( int ) strlen ( field4Name ) ) ) && ( ( strncmp ( field5NameGet , field5Name , field5NameGetLength ) == 0 ) && field5NameGetLength == ( int ) strlen ( field5Name ) ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldNameGet&Set" , "TestCase1&2&3&4&5" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Name = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldNameGet&Set" , "TestCase1|2|3|4|5" , TC_FAIL , "Values Don't Match" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldNameGet&Set" , "All Test Case" , TC_FAIL , "Cannot run test as Test for TSMBufferFieldCreate Failed" ) ;
 }
 if ( test_passed_Mime_Hdr_Field_Name == true ) {
 if ( ( TSMimeHdrFieldAppend ( bufp1 , mime_loc1 , field_loc11 ) != TS_SUCCESS ) || ( TSMimeHdrFieldAppend ( bufp1 , mime_loc1 , field_loc12 ) != TS_SUCCESS ) || ( TSMimeHdrFieldAppend ( bufp1 , mime_loc1 , field_loc13 ) != TS_SUCCESS ) || ( TSMimeHdrFieldAppend ( bufp1 , mime_loc1 , field_loc14 ) != TS_SUCCESS ) || ( TSMimeHdrFieldAppend ( bufp1 , mime_loc1 , field_loc15 ) != TS_SUCCESS ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend" , "TestCase1|2|3|4|5" , TC_FAIL , "TSMimeHdrFieldAppend Returns TS_ERROR" ) ;
 }
 else {
 if ( TS_NULL_MLOC == ( test_field_loc11 = TSMimeHdrFieldGet ( bufp1 , mime_loc1 , 0 ) ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend" , "TestCase1|2|3|4|5" , TC_FAIL , "TSMimeHdrFieldGet Returns TS_NULL_MLOC" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldNext" , "TestCase1" , TC_FAIL , "Cannot Test TSMimeHdrFieldNext as TSMimeHdrFieldGet Returns TS_NULL_MLOC" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldGet" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldGet Returns TS_NULL_MLOC" ) ;
 }
 else {
 if ( compare_field_names ( test , bufp1 , mime_loc1 , field_loc11 , bufp1 , mime_loc1 , test_field_loc11 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend" , "TestCase1" , TC_FAIL , "Values Don't match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldNext" , "TestCase1" , TC_FAIL , "Cannot Test TSMimeHdrFieldNext as Values don't match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldGet" , "TestCase1" , TC_FAIL , "Values Don't match" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldGet" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Append = true ;
 test_passed_Mime_Hdr_Field_Get = true ;
 }
 }
 if ( test_passed_Mime_Hdr_Field_Append == true ) {
 test_field_loc12 = TSMimeHdrFieldNext ( bufp1 , mime_loc1 , test_field_loc11 ) ;
 if ( compare_field_names ( test , bufp1 , mime_loc1 , field_loc12 , bufp1 , mime_loc1 , test_field_loc12 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend" , "TestCase2" , TC_PASS , "Values Don't match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldNext" , "TestCase2" , TC_PASS , "Values Don't match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldGet" , "TestCase2" , TC_PASS , "Values Don't match" ) ;
 test_passed_Mime_Hdr_Field_Append = false ;
 test_passed_Mime_Hdr_Field_Next = false ;
 test_passed_Mime_Hdr_Field_Get = false ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend" , "TestCase2" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldNext" , "TestCase2" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldGet" , "TestCase2" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Next = true ;
 }
 }
 if ( test_passed_Mime_Hdr_Field_Append == true ) {
 test_field_loc13 = TSMimeHdrFieldNext ( bufp1 , mime_loc1 , test_field_loc12 ) ;
 if ( compare_field_names ( test , bufp1 , mime_loc1 , field_loc13 , bufp1 , mime_loc1 , test_field_loc13 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend" , "TestCase3" , TC_FAIL , "Values Don't match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldNext" , "TestCase3" , TC_FAIL , "Values Don't match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldGet" , "TestCase3" , TC_FAIL , "Values Don't match" ) ;
 test_passed_Mime_Hdr_Field_Append = false ;
 test_passed_Mime_Hdr_Field_Next = false ;
 test_passed_Mime_Hdr_Field_Get = false ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend" , "TestCase3" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldNext" , "TestCase3" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldGet" , "TestCase3" , TC_PASS , "ok" ) ;
 }
 }
 if ( test_passed_Mime_Hdr_Field_Append == true ) {
 test_field_loc14 = TSMimeHdrFieldNext ( bufp1 , mime_loc1 , test_field_loc13 ) ;
 if ( compare_field_names ( test , bufp1 , mime_loc1 , field_loc14 , bufp1 , mime_loc1 , test_field_loc14 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend" , "TestCase4" , TC_FAIL , "Values Don't match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldNext" , "TestCase4" , TC_FAIL , "Values Don't match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldGet" , "TestCase4" , TC_FAIL , "Values Don't match" ) ;
 test_passed_Mime_Hdr_Field_Append = false ;
 test_passed_Mime_Hdr_Field_Next = false ;
 test_passed_Mime_Hdr_Field_Get = false ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend" , "TestCase4" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldNext" , "TestCase4" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldGet" , "TestCase4" , TC_PASS , "ok" ) ;
 }
 }
 if ( test_passed_Mime_Hdr_Field_Append == true ) {
 test_field_loc15 = TSMimeHdrFieldNext ( bufp1 , mime_loc1 , test_field_loc14 ) ;
 if ( compare_field_names ( test , bufp1 , mime_loc1 , field_loc15 , bufp1 , mime_loc1 , test_field_loc15 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend" , "TestCase5" , TC_FAIL , "Values Don't match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldNext" , "TestCase5" , TC_FAIL , "Values Don't match" ) ;
 test_passed_Mime_Hdr_Field_Append = false ;
 test_passed_Mime_Hdr_Field_Next = false ;
 test_passed_Mime_Hdr_Field_Get = false ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend" , "TestCase5" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldNext" , "TestCase5" , TC_PASS , "ok" ) ;
 }
 }
 if ( ( TSHandleMLocRelease ( bufp1 , mime_loc1 , test_field_loc11 ) == TS_ERROR ) || ( TSHandleMLocRelease ( bufp1 , mime_loc1 , test_field_loc12 ) == TS_ERROR ) || ( TSHandleMLocRelease ( bufp1 , mime_loc1 , test_field_loc13 ) == TS_ERROR ) || ( TSHandleMLocRelease ( bufp1 , mime_loc1 , test_field_loc14 ) == TS_ERROR ) || ( TSHandleMLocRelease ( bufp1 , mime_loc1 , test_field_loc15 ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend/Next/Get" , "" , TC_FAIL , "Unable to release handle using TSHandleMLocRelease. Can be bad handle." ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldAppend & TSMimeHdrFieldNext" , "All Test Case" , TC_FAIL , "Cannot run test as Test for TSMimeHdrFieldNameGet&Set Failed" ) ;
 }
 if ( test_passed_Mime_Hdr_Field_Create == true ) {
 if ( ( numberOfFields = TSMimeHdrFieldsCount ( bufp1 , mime_loc1 ) ) < 0 ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldsCount" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldsCount Returns TS_ERROR" ) ;
 }
 else {
 actualNumberOfFields = 0 ;
 if ( ( field_loc = TSMimeHdrFieldGet ( bufp1 , mime_loc1 , actualNumberOfFields ) ) == TS_NULL_MLOC ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldsCount" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldGet Returns TS_NULL_MLOC" ) ;
 }
 else {
 while ( field_loc != nullptr ) {
 TSMLoc next_field_loc ;
 actualNumberOfFields ++ ;
 next_field_loc = TSMimeHdrFieldNext ( bufp1 , mime_loc1 , field_loc ) ;
 if ( TSHandleMLocRelease ( bufp1 , mime_loc1 , field_loc ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldsCount" , "TestCase1" , TC_FAIL , "Unable to release handle using TSHandleMLocRelease" ) ;
 }
 field_loc = next_field_loc ;
 next_field_loc = nullptr ;
 }
 if ( actualNumberOfFields == numberOfFields ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldsCount" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Fields_Count = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldsCount" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldsCount" , "TestCase1" , TC_FAIL , "Cannot run Test as TSMimeHdrFieldCreate failed" ) ;
 }
 if ( test_passed_Mime_Hdr_Field_Create == true ) {
 if ( ( TSMimeHdrFieldValueStringInsert ( bufp1 , mime_loc1 , field_loc11 , - 1 , field1Value2 , - 1 ) == TS_ERROR ) || ( TSMimeHdrFieldValueStringInsert ( bufp1 , mime_loc1 , field_loc11 , 0 , field1Value1 , - 1 ) == TS_ERROR ) || ( TSMimeHdrFieldValueStringInsert ( bufp1 , mime_loc1 , field_loc11 , - 1 , field1Value5 , - 1 ) == TS_ERROR ) || ( TSMimeHdrFieldValueStringInsert ( bufp1 , mime_loc1 , field_loc11 , 2 , field1Value4 , - 1 ) == TS_ERROR ) || ( TSMimeHdrFieldValueStringInsert ( bufp1 , mime_loc1 , field_loc11 , 2 , field1Value3 , - 1 ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueStringInsert" , "TestCase1|2|3|4|5" , TC_FAIL , "TSMimeHdrFieldValueStringInsert Returns TS_ERROR" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueStringGet" , "TestCase1&2&3&4&5" , TC_FAIL , "Cannot run Test as TSMimeHdrFieldValueStringInsert returns TS_ERROR" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueStringSet" , "TestCase1" , TC_FAIL , "Cannot run Test as TSMimeHdrFieldValueStringInsert returns TS_ERROR" ) ;
 }
 else {
 field1Value1Get = TSMimeHdrFieldValueStringGet ( bufp1 , mime_loc1 , field_loc11 , 0 , & lengthField1Value1 ) ;
 field1Value2Get = TSMimeHdrFieldValueStringGet ( bufp1 , mime_loc1 , field_loc11 , 1 , & lengthField1Value2 ) ;
 field1Value3Get = TSMimeHdrFieldValueStringGet ( bufp1 , mime_loc1 , field_loc11 , 2 , & lengthField1Value3 ) ;
 field1Value4Get = TSMimeHdrFieldValueStringGet ( bufp1 , mime_loc1 , field_loc11 , 3 , & lengthField1Value4 ) ;
 field1Value5Get = TSMimeHdrFieldValueStringGet ( bufp1 , mime_loc1 , field_loc11 , 4 , & lengthField1Value5 ) ;
 field1ValueAllGet = TSMimeHdrFieldValueStringGet ( bufp1 , mime_loc1 , field_loc11 , - 1 , & lengthField1ValueAll ) ;
 if ( ( ( strncmp ( field1Value1Get , field1Value1 , lengthField1Value1 ) == 0 ) && lengthField1Value1 == ( int ) strlen ( field1Value1 ) ) && ( ( strncmp ( field1Value2Get , field1Value2 , lengthField1Value2 ) == 0 ) && lengthField1Value2 == ( int ) strlen ( field1Value2 ) ) && ( ( strncmp ( field1Value3Get , field1Value3 , lengthField1Value3 ) == 0 ) && lengthField1Value3 == ( int ) strlen ( field1Value3 ) ) && ( ( strncmp ( field1Value4Get , field1Value4 , lengthField1Value4 ) == 0 ) && lengthField1Value4 == ( int ) strlen ( field1Value4 ) ) && ( ( strncmp ( field1Value5Get , field1Value5 , lengthField1Value5 ) == 0 ) && lengthField1Value5 == ( int ) strlen ( field1Value5 ) ) && ( strstr ( field1ValueAllGet , field1Value1Get ) == field1Value1Get ) && ( strstr ( field1ValueAllGet , field1Value2Get ) == field1Value2Get ) && ( strstr ( field1ValueAllGet , field1Value3Get ) == field1Value3Get ) && ( strstr ( field1ValueAllGet , field1Value4Get ) == field1Value4Get ) && ( strstr ( field1ValueAllGet , field1Value5Get ) == field1Value5Get ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueStringInsert" , "TestCase1&2&3&4&5" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueStringGet" , "TestCase1&2&3&4&5" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueStringGet with IDX=-1" , "TestCase1&2&3&4&5" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Value_String_Insert = true ;
 test_passed_Mime_Hdr_Field_Value_String_Get = true ;
 if ( ( TSMimeHdrFieldValueStringSet ( bufp1 , mime_loc1 , field_loc11 , 3 , field1ValueNew , - 1 ) ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueStringSet" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueStringSet returns TS_ERROR" ) ;
 }
 else {
 field1ValueNewGet = TSMimeHdrFieldValueStringGet ( bufp1 , mime_loc1 , field_loc11 , 3 , & lengthField1ValueNew ) ;
 if ( ( strncmp ( field1ValueNewGet , field1ValueNew , lengthField1ValueNew ) == 0 ) && ( lengthField1ValueNew == ( int ) strlen ( field1ValueNew ) ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueStringSet" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Value_String_Set = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueStringSet" , "TestCase1" , TC_FAIL , "Value's Don't match" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueStringInsert" , "TestCase1|2|3|4|5" , TC_PASS , "Value's Don't Match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueStringGet" , "TestCase1|2|3|4|5" , TC_PASS , "Value's Don't Match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueStringSet" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueStringSet cannot be tested as TSMimeHdrFieldValueStringInsert|Get failed" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueStringInsert&Set&Get" , "All" , TC_FAIL , "Cannot run Test as TSMimeHdrFieldCreate failed" ) ;
 }
 if ( test_passed_Mime_Hdr_Field_Create == true ) {
 if ( TSMimeHdrFieldValueDateInsert ( bufp1 , mime_loc1 , field_loc12 , field2Value1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDateInsert" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueDateInsert Returns TS_ERROR" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDateGet" , "TestCase1" , TC_FAIL , "Cannot run Test as TSMimeHdrFieldValueDateInsert returns TS_ERROR" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDateSet" , "TestCase1" , TC_FAIL , "Cannot run Test as TSMimeHdrFieldValueDateInsert returns TS_ERROR" ) ;
 }
 else {
 field2Value1Get = TSMimeHdrFieldValueDateGet ( bufp1 , mime_loc1 , field_loc12 ) ;
 if ( field2Value1Get == field2Value1 ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDateInsert" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDateGet" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Value_Date_Insert = true ;
 test_passed_Mime_Hdr_Field_Value_Date_Get = true ;
 field2ValueNew = time ( nullptr ) ;
 if ( ( TSMimeHdrFieldValueDateSet ( bufp1 , mime_loc1 , field_loc12 , field2ValueNew ) ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDateSet" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueDateSet returns TS_ERROR" ) ;
 }
 else {
 field2ValueNewGet = TSMimeHdrFieldValueDateGet ( bufp1 , mime_loc1 , field_loc12 ) ;
 if ( field2ValueNewGet == field2ValueNew ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDateSet" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Value_Date_Set = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDateSet" , "TestCase1" , TC_FAIL , "Value's Don't match" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDateInsert" , "TestCase1" , TC_PASS , "Value's Don't Match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDateGet" , "TestCase1" , TC_PASS , "Value's Don't Match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDateSet" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueDateSet cannot be tested as TSMimeHdrFieldValueDateInsert|Get failed" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDateInsert&Set&Get" , "TestCase1" , TC_FAIL , "Cannot run Test as TSMimeHdrFieldCreate failed" ) ;
 }
 if ( test_passed_Mime_Hdr_Field_Create == true ) {
 if ( ( TSMimeHdrFieldValueIntInsert ( bufp1 , mime_loc1 , field_loc13 , - 1 , field3Value2 ) == TS_ERROR ) || ( TSMimeHdrFieldValueIntInsert ( bufp1 , mime_loc1 , field_loc13 , 0 , field3Value1 ) == TS_ERROR ) || ( TSMimeHdrFieldValueIntInsert ( bufp1 , mime_loc1 , field_loc13 , - 1 , field3Value5 ) == TS_ERROR ) || ( TSMimeHdrFieldValueIntInsert ( bufp1 , mime_loc1 , field_loc13 , 2 , field3Value4 ) == TS_ERROR ) || ( TSMimeHdrFieldValueIntInsert ( bufp1 , mime_loc1 , field_loc13 , 2 , field3Value3 ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueIntInsert" , "TestCase1|2|3|4|5" , TC_FAIL , "TSMimeHdrFieldValueIntInsert Returns TS_ERROR" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueIntGet" , "TestCase1&2&3&4&5" , TC_FAIL , "Cannot run Test as TSMimeHdrFieldValueIntInsert returns TS_ERROR" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueIntSet" , "TestCase1" , TC_FAIL , "Cannot run Test as TSMimeHdrFieldValueIntInsert returns TS_ERROR" ) ;
 }
 else {
 field3Value1Get = TSMimeHdrFieldValueIntGet ( bufp1 , mime_loc1 , field_loc13 , 0 ) ;
 field3Value2Get = TSMimeHdrFieldValueIntGet ( bufp1 , mime_loc1 , field_loc13 , 1 ) ;
 field3Value3Get = TSMimeHdrFieldValueIntGet ( bufp1 , mime_loc1 , field_loc13 , 2 ) ;
 field3Value4Get = TSMimeHdrFieldValueIntGet ( bufp1 , mime_loc1 , field_loc13 , 3 ) ;
 field3Value5Get = TSMimeHdrFieldValueIntGet ( bufp1 , mime_loc1 , field_loc13 , 4 ) ;
 if ( ( field3Value1Get == field3Value1 ) && ( field3Value2Get == field3Value2 ) && ( field3Value3Get == field3Value3 ) && ( field3Value4Get == field3Value4 ) && ( field3Value5Get == field3Value5 ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueIntInsert" , "TestCase1&2&3&4&5" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueIntGet" , "TestCase1&2&3&4&5" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Value_Int_Insert = true ;
 test_passed_Mime_Hdr_Field_Value_Int_Get = true ;
 if ( ( TSMimeHdrFieldValueIntSet ( bufp1 , mime_loc1 , field_loc13 , 3 , field3ValueNew ) ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueIntSet" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueIntSet returns TS_ERROR" ) ;
 }
 else {
 field3ValueNewGet = TSMimeHdrFieldValueIntGet ( bufp1 , mime_loc1 , field_loc13 , 3 ) ;
 if ( field3ValueNewGet == field3ValueNew ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueIntSet" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Value_Int_Set = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueIntSet" , "TestCase1" , TC_FAIL , "Value's Don't match" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueIntInsert" , "TestCase1|2|3|4|5" , TC_PASS , "Value's Don't Match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueIntGet" , "TestCase1|2|3|4|5" , TC_PASS , "Value's Don't Match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueIntSet" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueIntSet cannot be tested as TSMimeHdrFieldValueIntInsert|Get failed" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueIntInsert&Set&Get" , "All" , TC_FAIL , "Cannot run Test as TSMimeHdrFieldCreate failed" ) ;
 }
 if ( test_passed_Mime_Hdr_Field_Create == true ) {
 if ( ( TSMimeHdrFieldValueUintInsert ( bufp1 , mime_loc1 , field_loc14 , - 1 , field4Value2 ) == TS_ERROR ) || ( TSMimeHdrFieldValueUintInsert ( bufp1 , mime_loc1 , field_loc14 , 0 , field4Value1 ) == TS_ERROR ) || ( TSMimeHdrFieldValueUintInsert ( bufp1 , mime_loc1 , field_loc14 , - 1 , field4Value5 ) == TS_ERROR ) || ( TSMimeHdrFieldValueUintInsert ( bufp1 , mime_loc1 , field_loc14 , 2 , field4Value4 ) == TS_ERROR ) || ( TSMimeHdrFieldValueUintInsert ( bufp1 , mime_loc1 , field_loc14 , 2 , field4Value3 ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueUintInsert" , "TestCase1|2|3|4|5" , TC_FAIL , "TSMimeHdrFieldValueUintInsert Returns TS_ERROR" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueUintGet" , "TestCase1&2&3&4&5" , TC_FAIL , "Cannot run Test as TSMimeHdrFieldValueUintInsert returns TS_ERROR" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueUintSet" , "TestCase1" , TC_FAIL , "Cannot run Test as TSMimeHdrFieldValueUintInsert returns TS_ERROR" ) ;
 }
 else {
 field4Value1Get = TSMimeHdrFieldValueUintGet ( bufp1 , mime_loc1 , field_loc14 , 0 ) ;
 field4Value2Get = TSMimeHdrFieldValueUintGet ( bufp1 , mime_loc1 , field_loc14 , 1 ) ;
 field4Value3Get = TSMimeHdrFieldValueUintGet ( bufp1 , mime_loc1 , field_loc14 , 2 ) ;
 field4Value4Get = TSMimeHdrFieldValueUintGet ( bufp1 , mime_loc1 , field_loc14 , 3 ) ;
 field4Value5Get = TSMimeHdrFieldValueUintGet ( bufp1 , mime_loc1 , field_loc14 , 4 ) ;
 if ( ( field4Value1Get == field4Value1 ) && ( field4Value2Get == field4Value2 ) && ( field4Value3Get == field4Value3 ) && ( field4Value4Get == field4Value4 ) && ( field4Value5Get == field4Value5 ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueUintInsert" , "TestCase1&2&3&4&5" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueUintGet" , "TestCase1&2&3&4&5" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Value_Uint_Insert = true ;
 test_passed_Mime_Hdr_Field_Value_Uint_Get = true ;
 if ( ( TSMimeHdrFieldValueUintSet ( bufp1 , mime_loc1 , field_loc14 , 3 , field4ValueNew ) ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueUintSet" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueUintSet returns TS_ERROR" ) ;
 }
 else {
 field4ValueNewGet = TSMimeHdrFieldValueUintGet ( bufp1 , mime_loc1 , field_loc14 , 3 ) ;
 if ( field4ValueNewGet == field4ValueNew ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueUintSet" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Value_Uint_Set = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueUintSet" , "TestCase1" , TC_FAIL , "Value's Don't match" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueUintInsert" , "TestCase1|2|3|4|5" , TC_PASS , "Value's Don't Match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueUintGet" , "TestCase1|2|3|4|5" , TC_PASS , "Value's Don't Match" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueUintSet" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueUintSet cannot be tested as TSMimeHdrFieldValueUintInsert|Get failed" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueUintInsert&Set&Get" , "All" , TC_FAIL , "Cannot run Test as TSMimeHdrFieldCreate failed" ) ;
 }
 field1_length = TSMimeHdrFieldLengthGet ( bufp1 , mime_loc1 , field_loc11 ) ;
 field2_length = TSMimeHdrFieldLengthGet ( bufp1 , mime_loc1 , field_loc12 ) ;
 field3_length = TSMimeHdrFieldLengthGet ( bufp1 , mime_loc1 , field_loc13 ) ;
 field4_length = TSMimeHdrFieldLengthGet ( bufp1 , mime_loc1 , field_loc14 ) ;
 if ( ( field1_length == 0 ) || ( field2_length == 0 ) || ( field3_length == 0 ) || ( field4_length == 0 ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldLengthGet" , "TestCase1" , TC_FAIL , "Returned bad length" ) ;
 test_passed_Mime_Hdr_Field_Length_Get = false ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldLengthGet" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Length_Get = true ;
 }
 if ( test_passed_Mime_Hdr_Field_Create == true ) {
 if ( ( TSMimeHdrFieldValueStringInsert ( bufp1 , mime_loc1 , field_loc15 , - 1 , field5Value1 , - 1 ) == TS_ERROR ) || ( TSMimeHdrFieldValueIntInsert ( bufp1 , mime_loc1 , field_loc15 , - 1 , field5Value2 ) == TS_ERROR ) || ( TSMimeHdrFieldValueStringInsert ( bufp1 , mime_loc1 , field_loc15 , - 1 , field5Value3 , - 1 ) == TS_ERROR ) || ( TSMimeHdrFieldValueUintInsert ( bufp1 , mime_loc1 , field_loc15 , - 1 , field5Value4 ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueAppend" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueString|Int|UintInsert returns TS_ERROR. Cannot create field for testing." ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDelete" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueString|Int|UintInsert returns TS_ERROR. Cannot create field for testing." ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValuesCount" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueString|Int|UintInsert returns TS_ERROR. Cannot create field for testing." ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValuesClear" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueString|Int|UintInsert returns TS_ERROR. Cannot create field for testing." ) ;
 }
 else {
 if ( TSMimeHdrFieldValueAppend ( bufp1 , mime_loc1 , field_loc15 , 0 , field5Value1Append , - 1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueAppend" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueAppend returns TS_ERROR" ) ;
 }
 else {
 fieldValueAppendGet = TSMimeHdrFieldValueStringGet ( bufp1 , mime_loc1 , field_loc15 , 0 , & lengthFieldValueAppended ) ;
 char * expected_value ;
 size_t len = strlen ( field5Value1 ) + strlen ( field5Value1Append ) + 1 ;
 expected_value = ( char * ) TSmalloc ( len ) ;
 memset ( expected_value , 0 , len ) ;
 ink_strlcpy ( expected_value , field5Value1 , len ) ;
 ink_strlcat ( expected_value , field5Value1Append , len ) ;
 if ( ( strncmp ( fieldValueAppendGet , expected_value , lengthFieldValueAppended ) == 0 ) && ( lengthFieldValueAppended = strlen ( expected_value ) ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueAppend" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Value_Append = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueAppend" , "TestCase1" , TC_FAIL , "Values mismatch" ) ;
 }
 TSfree ( expected_value ) ;
 }
 numberOfValueInField = TSMimeHdrFieldValuesCount ( bufp1 , mime_loc1 , field_loc15 ) ;
 if ( numberOfValueInField == 4 ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValuesCount" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Values_Count = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValuesCount" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 if ( TSMimeHdrFieldValueDelete ( bufp1 , mime_loc1 , field_loc15 , 2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDelete" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValueDelete Returns TS_ERROR" ) ;
 }
 else {
 fieldValueDeleteGet = TSMimeHdrFieldValueStringGet ( bufp1 , mime_loc1 , field_loc15 , 2 , & lengthFieldValueDeleteGet ) ;
 if ( ( strncmp ( fieldValueDeleteGet , field5Value3 , lengthFieldValueDeleteGet ) == 0 ) && ( lengthFieldValueDeleteGet == ( int ) strlen ( field5Value3 ) ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDelete" , "TestCase1" , TC_FAIL , "Value not deleted from field or incorrect index deleted from field." ) ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDelete" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Value_Delete = true ;
 }
 }
 if ( TSMimeHdrFieldValuesClear ( bufp1 , mime_loc1 , field_loc15 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValuesClear" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldValuesClear returns TS_ERROR" ) ;
 }
 else {
 numberOfValueInField = TSMimeHdrFieldValuesCount ( bufp1 , mime_loc1 , field_loc15 ) ;
 if ( numberOfValueInField == 0 ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldValuesClear" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Values_Clear = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValuesClear" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 }
 }
 if ( TSMimeHdrFieldDestroy ( bufp1 , mime_loc1 , field_loc15 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldDestroy" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldDestroy returns TS_ERROR" ) ;
 }
 else {
 if ( ( test_field_loc15 = TSMimeHdrFieldFind ( bufp1 , mime_loc1 , field5Name , - 1 ) ) == TS_NULL_MLOC ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldDestroy" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Field_Destroy = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldDestroy" , "TestCase1" , TC_FAIL , "Field not destroyed" ) ;
 if ( TSHandleMLocRelease ( bufp1 , mime_loc1 , test_field_loc15 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldDestroy" , "TestCase1" , TC_FAIL , "Unable to release handle using TSHandleMLocRelease" ) ;
 }
 }
 if ( TSHandleMLocRelease ( bufp1 , mime_loc1 , field_loc15 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldDestroy" , "TestCase2" , TC_FAIL , "Unable to release handle using TSHandleMLocRelease" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldValueAppend" , "TestCase1" , TC_FAIL , "Cannot run test as TSMimeHdrFieldCreate has failed" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValueDelete" , "TestCase1" , TC_FAIL , "Cannot run test as TSMimeHdrFieldCreate has failed" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValuesCount" , "TestCase1" , TC_FAIL , "Cannot run test as TSMimeHdrFieldCreate has failed" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldValuesClear" , "TestCase1" , TC_FAIL , "Cannot run test as TSMimeHdrFieldCreate has failed" ) ;
 SDK_RPRINT ( test , "TSMimeHdrFieldDestroy" , "TestCase1" , TC_FAIL , "Cannot run test as TSMimeHdrFieldCreate has failed" ) ;
 }
 if ( test_passed_Mime_Hdr_Field_Append == true ) {
 if ( TSMimeHdrFieldsClear ( bufp1 , mime_loc1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldsClear" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldsClear returns TS_ERROR" ) ;
 }
 else {
 if ( ( numberOfFields = TSMimeHdrFieldsCount ( bufp1 , mime_loc1 ) ) < 0 ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldsClear" , "TestCase1" , TC_FAIL , "TSMimeHdrFieldsCount returns TS_ERROR" ) ;
 }
 else {
 if ( numberOfFields == 0 ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldsClear" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Fields_Clear = true ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldsClear" , "TestCase1" , TC_FAIL , "Fields still exist" ) ;
 }
 }
 if ( ( TSHandleMLocRelease ( bufp1 , mime_loc1 , field_loc11 ) == TS_ERROR ) || ( TSHandleMLocRelease ( bufp1 , mime_loc1 , field_loc12 ) == TS_ERROR ) || ( TSHandleMLocRelease ( bufp1 , mime_loc1 , field_loc13 ) == TS_ERROR ) || ( TSHandleMLocRelease ( bufp1 , mime_loc1 , field_loc14 ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "TSMimeHdrFieldsDestroy" , "" , TC_FAIL , "Unable to release handle using TSHandleMLocRelease" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrFieldsClear" , "TestCase1" , TC_FAIL , "Cannot run test as Fields have not been inserted in the mime header" ) ;
 }
 if ( test_passed_Mime_Hdr_Create == true ) {
 if ( TSMimeHdrDestroy ( bufp1 , mime_loc1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMimeHdrDestroy" , "TestCase1" , TC_FAIL , "TSMimeHdrDestroy return TS_ERROR" ) ;
 SDK_RPRINT ( test , "TSMimeHdrDestroy" , "TestCase1" , TC_FAIL , "Probably TSMimeHdrCreate failed." ) ;
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrDestroy" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Mime_Hdr_Destroy = true ;
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrDestroy" , "TestCase1" , TC_FAIL , "Cannot run test as TSMimeHdrCreate failed" ) ;
 }
 if ( test_passed_MBuffer_Create == true ) {
 if ( TSMBufferDestroy ( bufp1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMBufferDestroy" , "TestCase1" , TC_FAIL , "TSMBufferDestroy return TS_ERROR" ) ;
 SDK_RPRINT ( test , "TSMBufferDestroy" , "TestCase1" , TC_FAIL , "Probably TSMBufferCreate failed." ) ;
 }
 else {
 SDK_RPRINT ( test , "TSMBufferDestroy" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_MBuffer_Destroy = true ;
 }
 }
 else {
 SDK_RPRINT ( test , "TSMimeHdrDestroy" , "TestCase1" , TC_FAIL , "Cannot run test as TSMimeHdrCreate failed" ) ;
 }
 if ( ( test_passed_MBuffer_Create == true ) && ( test_passed_Mime_Hdr_Create == true ) && ( test_passed_Mime_Hdr_Field_Create == true ) && ( test_passed_Mime_Hdr_Field_Name == true ) && ( test_passed_Mime_Hdr_Field_Append == true ) && ( test_passed_Mime_Hdr_Field_Get == true ) && ( test_passed_Mime_Hdr_Field_Next == true ) && ( test_passed_Mime_Hdr_Fields_Count == true ) && ( test_passed_Mime_Hdr_Field_Value_String_Insert == true ) && ( test_passed_Mime_Hdr_Field_Value_String_Get == true ) && ( test_passed_Mime_Hdr_Field_Value_String_Set == true ) && ( test_passed_Mime_Hdr_Field_Value_Date_Insert == true ) && ( test_passed_Mime_Hdr_Field_Value_Date_Get == true ) && ( test_passed_Mime_Hdr_Field_Value_Date_Set == true ) && ( test_passed_Mime_Hdr_Field_Value_Int_Insert == true ) && ( test_passed_Mime_Hdr_Field_Value_Int_Get == true ) && ( test_passed_Mime_Hdr_Field_Value_Int_Set == true ) && ( test_passed_Mime_Hdr_Field_Value_Uint_Insert == true ) && ( test_passed_Mime_Hdr_Field_Value_Uint_Get == true ) && ( test_passed_Mime_Hdr_Field_Value_Uint_Set == true ) && ( test_passed_Mime_Hdr_Field_Value_Append == true ) && ( test_passed_Mime_Hdr_Field_Value_Delete == true ) && ( test_passed_Mime_Hdr_Field_Values_Clear == true ) && ( test_passed_Mime_Hdr_Field_Values_Count == true ) && ( test_passed_Mime_Hdr_Field_Destroy == true ) && ( test_passed_Mime_Hdr_Fields_Clear == true ) && ( test_passed_Mime_Hdr_Destroy == true ) && ( test_passed_MBuffer_Destroy == true ) && ( test_passed_Mime_Hdr_Field_Length_Get == true ) ) {
 * pstatus = REGRESSION_TEST_PASSED ;
 }
 else {
 * pstatus = REGRESSION_TEST_FAILED ;
 }
 return ;
 }