TEST_F ( HistoryQuickProviderTest , VisitCountMatches ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://visitedest.com/y/a" ) ;
 expected_urls . push_back ( "http://visitedest.com/y/b" ) ;
 expected_urls . push_back ( "http://visitedest.com/x/c" ) ;
 RunTest ( ASCIIToUTF16 ( "visitedest" ) , false , expected_urls , true , ASCIIToUTF16 ( "visitedest.com/y/a" ) , ASCIIToUTF16 ( ".com/y/a" ) ) ;
 }