TEST_F ( HistoryQuickProviderTest , SingleMatchWithCursor ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://slashdot.org/favorite_page.html" ) ;
 RunTestWithCursor ( ASCIIToUTF16 ( "slashfavorite_page.html" ) , 5 , false , expected_urls , false , ASCIIToUTF16 ( "slashdot.org/favorite_page.html" ) , base : : string16 ( ) ) ;
 }