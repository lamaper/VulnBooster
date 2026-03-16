TEST_F ( HistoryQuickProviderTest , DeleteMatch ) {
 GURL test_url ( "http://slashdot.org/favorite_page.html" ) ;
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( test_url . spec ( ) ) ;
 RunTest ( ASCIIToUTF16 ( "slashdot" ) , false , expected_urls , true , ASCIIToUTF16 ( "slashdot.org/favorite_page.html" ) , ASCIIToUTF16 ( ".org/favorite_page.html" ) ) ;
 EXPECT_EQ ( 1U , ac_matches_ . size ( ) ) ;
 EXPECT_TRUE ( GetURLProxy ( test_url ) ) ;
 provider_ -> DeleteMatch ( ac_matches_ [ 0 ] ) ;
 WaitForURLsDeletedNotification ( client_ -> GetHistoryService ( ) ) ;
 EXPECT_FALSE ( GetURLProxy ( test_url ) ) ;
 expected_urls . clear ( ) ;
 RunTest ( ASCIIToUTF16 ( "slashdot" ) , false , expected_urls , true , ASCIIToUTF16 ( "NONE EXPECTED" ) , base : : string16 ( ) ) ;
 }