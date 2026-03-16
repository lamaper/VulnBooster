TEST_F ( HistoryQuickProviderTest , MultiMatch ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://foo.com/" ) ;
 expected_urls . push_back ( "http://foo.com/dir/another/" ) ;
 expected_urls . push_back ( "http://foo.com/dir/another/again/" ) ;
 RunTest ( ASCIIToUTF16 ( "foo" ) , false , expected_urls , true , ASCIIToUTF16 ( "foo.com" ) , ASCIIToUTF16 ( ".com" ) ) ;
 }