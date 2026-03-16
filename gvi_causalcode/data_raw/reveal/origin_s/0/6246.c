TEST_F ( HistoryQuickProviderTest , TypedCountMatches ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://typeredest.com/y/a" ) ;
 expected_urls . push_back ( "http://typeredest.com/y/b" ) ;
 expected_urls . push_back ( "http://typeredest.com/x/c" ) ;
 RunTest ( ASCIIToUTF16 ( "typeredest" ) , false , expected_urls , true , ASCIIToUTF16 ( "typeredest.com/y/a" ) , ASCIIToUTF16 ( ".com/y/a" ) ) ;
 }