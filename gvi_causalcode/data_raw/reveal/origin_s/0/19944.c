TEST_F ( HistoryQuickProviderTest , SimpleSingleMatch ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://slashdot.org/favorite_page.html" ) ;
 RunTest ( ASCIIToUTF16 ( "slashdot" ) , false , expected_urls , true , ASCIIToUTF16 ( "slashdot.org/favorite_page.html" ) , ASCIIToUTF16 ( ".org/favorite_page.html" ) ) ;
 }