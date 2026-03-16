TEST_F ( HistoryQuickProviderTest , DaysAgoMatches ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://daysagoest.com/y/a" ) ;
 expected_urls . push_back ( "http://daysagoest.com/y/b" ) ;
 expected_urls . push_back ( "http://daysagoest.com/x/c" ) ;
 RunTest ( ASCIIToUTF16 ( "daysagoest" ) , false , expected_urls , true , ASCIIToUTF16 ( "daysagoest.com/y/a" ) , ASCIIToUTF16 ( ".com/y/a" ) ) ;
 }