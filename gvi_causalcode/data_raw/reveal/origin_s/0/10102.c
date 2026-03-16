TEST_F ( HistoryQuickProviderTest , WordBoundariesWithPunctuationMatch ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://popularsitewithpathonly.com/moo" ) ;
 RunTest ( ASCIIToUTF16 ( "/moo" ) , false , expected_urls , false , ASCIIToUTF16 ( "popularsitewithpathonly.com/moo" ) , base : : string16 ( ) ) ;
 }