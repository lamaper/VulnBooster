TEST_F ( ShortcutsProviderTest , DaysAgoMatches ) {
 base : : string16 text ( ASCIIToUTF16 ( "ago" ) ) ;
 ExpectedURLs expected_urls ;
 expected_urls . push_back ( ExpectedURLAndAllowedToBeDefault ( "http://www.daysagotest.com/a.html" , false ) ) ;
 expected_urls . push_back ( ExpectedURLAndAllowedToBeDefault ( "http://www.daysagotest.com/b.html" , false ) ) ;
 expected_urls . push_back ( ExpectedURLAndAllowedToBeDefault ( "http://www.daysagotest.com/c.html" , false ) ) ;
 RunShortcutsProviderTest ( provider_ , text , false , expected_urls , "http://www.daysagotest.com/a.html" , base : : string16 ( ) ) ;
 }