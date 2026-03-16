TEST_F ( ShortcutsProviderTest , RemoveDuplicates ) {
 base : : string16 text ( ASCIIToUTF16 ( "dupl" ) ) ;
 ExpectedURLs expected_urls ;
 expected_urls . push_back ( ExpectedURLAndAllowedToBeDefault ( "http://duplicate.com/" , true ) ) ;
 RunShortcutsProviderTest ( provider_ , text , false , expected_urls , "http://duplicate.com/" , ASCIIToUTF16 ( "icate.com" ) ) ;
 }