TEST ( AutocompleteMatchTest , SupportsDeletion ) {
 AutocompleteMatch m ( NULL , 0 , false , AutocompleteMatchType : : URL_WHAT_YOU_TYPED ) ;
 EXPECT_FALSE ( m . SupportsDeletion ( ) ) ;
 AutocompleteMatch m1 ( NULL , 0 , true , AutocompleteMatchType : : URL_WHAT_YOU_TYPED ) ;
 EXPECT_TRUE ( m1 . SupportsDeletion ( ) ) ;
 m . duplicate_matches . push_back ( AutocompleteMatch ( NULL , 0 , false , AutocompleteMatchType : : URL_WHAT_YOU_TYPED ) ) ;
 m . duplicate_matches . push_back ( AutocompleteMatch ( NULL , 0 , false , AutocompleteMatchType : : URL_WHAT_YOU_TYPED ) ) ;
 EXPECT_FALSE ( m . SupportsDeletion ( ) ) ;
 m . duplicate_matches . push_back ( AutocompleteMatch ( NULL , 0 , true , AutocompleteMatchType : : URL_WHAT_YOU_TYPED ) ) ;
 EXPECT_TRUE ( m . SupportsDeletion ( ) ) ;
 }