TEST_F ( ShortcutsProviderTest , FragmentLengthMatches ) {
 base : : string16 text ( ASCIIToUTF16 ( "just a" ) ) ;
 ExpectedURLs expected_urls ;
 expected_urls . push_back ( ExpectedURLAndAllowedToBeDefault ( "http://www.testsite.com/d.html" , false ) ) ;
 expected_urls . push_back ( ExpectedURLAndAllowedToBeDefault ( "http://www.testsite.com/e.html" , false ) ) ;
 expected_urls . push_back ( ExpectedURLAndAllowedToBeDefault ( "http://www.testsite.com/f.html" , false ) ) ;
 RunShortcutsProviderTest ( provider_ , text , false , expected_urls , "http://www.testsite.com/d.html" , base : : string16 ( ) ) ;
 }