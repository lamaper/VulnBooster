TEST_F ( HQPOrderingTest , TEAMatch ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://www.teamliquid.net/" ) ;
 expected_urls . push_back ( "http://www.teamliquid.net/tlpd" ) ;
 expected_urls . push_back ( "http://www.teamliquid.net/tlpd/korean/players" ) ;
 RunTest ( ASCIIToUTF16 ( "tea" ) , false , expected_urls , true , ASCIIToUTF16 ( "www.teamliquid.net" ) , ASCIIToUTF16 ( "mliquid.net" ) ) ;
 }