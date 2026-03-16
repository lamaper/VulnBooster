TEST_F ( ShortcutsProviderTest , TypedCountMatches ) {
 base : : string16 text ( ASCIIToUTF16 ( "just" ) ) ;
 ExpectedURLs expected_urls ;
 expected_urls . push_back ( ExpectedURLAndAllowedToBeDefault ( "http://www.testsite.com/b.html" , false ) ) ;
 expected_urls . push_back ( ExpectedURLAndAllowedToBeDefault ( "http://www.testsite.com/a.html" , false ) ) ;
 expected_urls . push_back ( ExpectedURLAndAllowedToBeDefault ( "http://www.testsite.com/c.html" , false ) ) ;
 RunShortcutsProviderTest ( provider_ , text , false , expected_urls , "http://www.testsite.com/b.html" , base : : string16 ( ) ) ;
 }