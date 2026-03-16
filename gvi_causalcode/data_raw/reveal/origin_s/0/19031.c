TEST_F ( HistoryQuickProviderTest , EncodingMatch ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://spaces.com/path%20with%20spaces/foo.html" ) ;
 RunTest ( ASCIIToUTF16 ( "path with spaces" ) , false , expected_urls , false , ASCIIToUTF16 ( "spaces.com/path with spaces/foo.html" ) , base : : string16 ( ) ) ;
 }