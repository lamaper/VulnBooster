TSReturnCode compare_field_values ( RegressionTest * test , TSMBuffer bufp1 , TSMLoc hdr_loc1 , TSMLoc field_loc1 , TSMBuffer bufp2 , TSMLoc hdr_loc2 , TSMLoc field_loc2 ) {
 int no_of_values1 ;
 int no_of_values2 ;
 int i ;
 const char * str1 = nullptr ;
 const char * str2 = nullptr ;
 int length1 = 0 ;
 int length2 = 0 ;
 no_of_values1 = TSMimeHdrFieldValuesCount ( bufp1 , hdr_loc1 , field_loc1 ) ;
 no_of_values2 = TSMimeHdrFieldValuesCount ( bufp2 , hdr_loc2 , field_loc2 ) ;
 if ( no_of_values1 != no_of_values2 ) {
 SDK_RPRINT ( test , "compare_field_values" , "TestCase" , TC_FAIL , "Field Values not equal" ) ;
 return TS_ERROR ;
 }
 for ( i = 0 ;
 i < no_of_values1 ;
 i ++ ) {
 str1 = TSMimeHdrFieldValueStringGet ( bufp1 , hdr_loc1 , field_loc1 , i , & length1 ) ;
 str2 = TSMimeHdrFieldValueStringGet ( bufp2 , hdr_loc2 , field_loc2 , i , & length2 ) ;
 if ( ! ( ( length1 == length2 ) && ( strncmp ( str1 , str2 , length1 ) == 0 ) ) ) {
 SDK_RPRINT ( test , "compare_field_values" , "TestCase" , TC_FAIL , "Field Value %d differ from each other" , i ) ;
 return TS_ERROR ;
 }
 }
 return TS_SUCCESS ;
 }