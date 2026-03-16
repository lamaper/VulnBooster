TEST ( AutocompleteMatchTest , MoreRelevant ) {
 struct RelevantCases {
 int r1 ;
 int r2 ;
 bool expected_result ;
 }
 cases [ ] = {
 {
 10 , 0 , true }
 , {
 10 , - 5 , true }
 , {
 - 5 , 10 , false }
 , {
 0 , 10 , false }
 , {
 - 10 , - 5 , false }
 , {
 - 5 , - 10 , true }
 , }
 ;
 AutocompleteMatch m1 ( NULL , 0 , false , AutocompleteMatchType : : URL_WHAT_YOU_TYPED ) ;
 AutocompleteMatch m2 ( NULL , 0 , false , AutocompleteMatchType : : URL_WHAT_YOU_TYPED ) ;
 for ( size_t i = 0 ;
 i < arraysize ( cases ) ;
 ++ i ) {
 m1 . relevance = cases [ i ] . r1 ;
 m2 . relevance = cases [ i ] . r2 ;
 EXPECT_EQ ( cases [ i ] . expected_result , AutocompleteMatch : : MoreRelevant ( m1 , m2 ) ) ;
 }
 }