TEST_F ( ShortcutsBackendTest , SanitizeMatchCore ) {
 struct {
 std : : string input_contents_class ;
 std : : string input_description_class ;
 AutocompleteMatch : : Type input_type ;
 std : : string output_contents_class ;
 std : : string output_description_class ;
 AutocompleteMatch : : Type output_type ;
 }
 cases [ ] = {
 {
 "0,1,4,0" , "0,3,4,1" , AutocompleteMatchType : : URL_WHAT_YOU_TYPED , "0,1,4,0" , "0,1" , AutocompleteMatchType : : HISTORY_URL }
 , {
 "0,3,5,1" , "0,2,5,0" , AutocompleteMatchType : : NAVSUGGEST , "0,1" , "0,0" , AutocompleteMatchType : : HISTORY_URL }
 , {
 "0,1" , "0,0,11,2,15,0" , AutocompleteMatchType : : SEARCH_WHAT_YOU_TYPED , "0,1" , "0,0" , AutocompleteMatchType : : SEARCH_HISTORY }
 , {
 "0,1" , "0,0" , AutocompleteMatchType : : SEARCH_SUGGEST , "0,1" , "0,0" , AutocompleteMatchType : : SEARCH_HISTORY }
 , {
 "0,1" , "0,0" , AutocompleteMatchType : : SEARCH_SUGGEST_ENTITY , "" , "" , AutocompleteMatchType : : SEARCH_HISTORY }
 , {
 "0,1" , "0,0" , AutocompleteMatchType : : SEARCH_SUGGEST_TAIL , "" , "" , AutocompleteMatchType : : SEARCH_HISTORY }
 , {
 "0,1" , "0,0" , AutocompleteMatchType : : SEARCH_SUGGEST_PERSONALIZED , "" , "" , AutocompleteMatchType : : SEARCH_HISTORY }
 , {
 "0,1" , "0,0" , AutocompleteMatchType : : SEARCH_SUGGEST_PROFILE , "" , "" , AutocompleteMatchType : : SEARCH_HISTORY }
 , }
 ;
 for ( size_t i = 0 ;
 i < arraysize ( cases ) ;
 ++ i ) {
 ShortcutsDatabase : : Shortcut : : MatchCore match_core ( MatchCoreForTesting ( std : : string ( ) , cases [ i ] . input_contents_class , cases [ i ] . input_description_class , cases [ i ] . input_type ) ) ;
 EXPECT_EQ ( cases [ i ] . output_contents_class , match_core . contents_class ) << ":i:" << i << ":type:" << cases [ i ] . input_type ;
 EXPECT_EQ ( cases [ i ] . output_description_class , match_core . description_class ) << ":i:" << i << ":type:" << cases [ i ] . input_type ;
 EXPECT_EQ ( cases [ i ] . output_type , match_core . type ) << ":i:" << i << ":type:" << cases [ i ] . input_type ;
 }
 }