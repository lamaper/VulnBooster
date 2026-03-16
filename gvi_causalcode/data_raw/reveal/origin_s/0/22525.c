TEST_F ( ShortcutsProviderTest , MultiMatch ) {
 base : : string16 text ( ASCIIToUTF16 ( "NEWS" ) ) ;
 ExpectedURLs expected_urls ;
 expected_urls . push_back ( ExpectedURLAndAllowedToBeDefault ( "http://slashdot.org/" , false ) ) ;
 expected_urls . push_back ( ExpectedURLAndAllowedToBeDefault ( "http://sports.yahoo.com/" , false ) ) ;
 expected_urls . push_back ( ExpectedURLAndAllowedToBeDefault ( "http://www.cnn.com/index.html" , false ) ) ;
 RunShortcutsProviderTest ( provider_ , text , false , expected_urls , "http://slashdot.org/" , base : : string16 ( ) ) ;
 }