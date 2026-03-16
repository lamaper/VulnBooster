TEST_F ( HQPOrderingTest , TEMatch ) {
 std : : vector < std : : string > expected_urls ;
 expected_urls . push_back ( "http://techmeme.com/" ) ;
 expected_urls . push_back ( "http://www.teamliquid.net/" ) ;
 expected_urls . push_back ( "http://www.teamliquid.net/tlpd" ) ;
 RunTest ( ASCIIToUTF16 ( "te" ) , false , expected_urls , true , ASCIIToUTF16 ( "techmeme.com" ) , ASCIIToUTF16 ( "chmeme.com" ) ) ;
 }