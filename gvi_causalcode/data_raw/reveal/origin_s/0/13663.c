TEST_F ( HistoryQuickProviderTest , MultiTermTitleMatch ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://cda.com/Dogs%20Cats%20Gorillas%20Sea%20Slugs%20and%20Mice" ) ;
 RunTest ( ASCIIToUTF16 ( "mice other animals" ) , false , expected_urls , false , ASCIIToUTF16 ( "cda.com/Dogs Cats Gorillas Sea Slugs and Mice" ) , base : : string16 ( ) ) ;
 }