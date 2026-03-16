TEST_F ( OmniboxEditTest , AlternateNavHasHTTP ) {
 const TestingOmniboxClient * client = static_cast < TestingOmniboxClient * > ( model ( ) -> client ( ) ) ;
 const AutocompleteMatch match ( model ( ) -> autocomplete_controller ( ) -> search_provider ( ) , 0 , false , AutocompleteMatchType : : SEARCH_WHAT_YOU_TYPED ) ;
 const GURL alternate_nav_url ( "http://abcd/" ) ;
 model ( ) -> OnSetFocus ( false ) ;
 model ( ) -> SetUserText ( base : : ASCIIToUTF16 ( "http://abcd" ) ) ;
 model ( ) -> OpenMatch ( match , WindowOpenDisposition : : CURRENT_TAB , alternate_nav_url , base : : string16 ( ) , 0 ) ;
 EXPECT_TRUE ( AutocompleteInput : : HasHTTPScheme ( client -> alternate_nav_match ( ) . fill_into_edit ) ) ;
 model ( ) -> SetUserText ( base : : ASCIIToUTF16 ( "abcd" ) ) ;
 model ( ) -> OpenMatch ( match , WindowOpenDisposition : : CURRENT_TAB , alternate_nav_url , base : : string16 ( ) , 0 ) ;
 EXPECT_TRUE ( AutocompleteInput : : HasHTTPScheme ( client -> alternate_nav_match ( ) . fill_into_edit ) ) ;
 }