TEST_F ( HistoryQuickProviderTest , StartRelativeMatch ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://xyzabcdefghijklmnopqrstuvw.com/a" ) ;
 RunTest ( ASCIIToUTF16 ( "xyza" ) , false , expected_urls , true , ASCIIToUTF16 ( "xyzabcdefghijklmnopqrstuvw.com/a" ) , ASCIIToUTF16 ( "bcdefghijklmnopqrstuvw.com/a" ) ) ;
 }