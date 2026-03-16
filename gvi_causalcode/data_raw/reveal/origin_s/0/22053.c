TEST_F ( HistoryQuickProviderTest , NonWordLastCharacterMatch ) {
 std : : string expected_url ( "http://slashdot.org/favorite_page.html" ) ;
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( expected_url ) ;
 RunTest ( ASCIIToUTF16 ( "slashdot.org/" ) , false , expected_urls , true , ASCIIToUTF16 ( "slashdot.org/favorite_page.html" ) , ASCIIToUTF16 ( "favorite_page.html" ) ) ;
 }