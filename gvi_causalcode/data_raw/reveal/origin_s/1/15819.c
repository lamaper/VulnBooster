TEST_F ( AutocompleteResultTest , SortAndCullWithMatchDupsAndDemotionsByType ) {
 ACMatches matches ;
 const AutocompleteMatchTestData data [ ] = {
 {
 "http://search-what-you-typed/" , AutocompleteMatchType : : SEARCH_WHAT_YOU_TYPED }
 , {
 "http://dup-url/" , AutocompleteMatchType : : HISTORY_URL }
 , {
 "http://dup-url/" , AutocompleteMatchType : : NAVSUGGEST }
 , {
 "http://search-url/" , AutocompleteMatchType : : SEARCH_SUGGEST }
 , {
 "http://history-url/" , AutocompleteMatchType : : HISTORY_URL }
 , }
 ;
 PopulateAutocompleteMatchesFromTestData ( data , arraysize ( data ) , & matches ) ;
 {
 std : : map < std : : string , std : : string > params ;
 params [ std : : string ( OmniboxFieldTrial : : kDemoteByTypeRule ) + ":8:*" ] = "1:50" ;
 ASSERT_TRUE ( variations : : AssociateVariationParams ( OmniboxFieldTrial : : kBundledExperimentFieldTrialName , "C" , params ) ) ;
 }
 base : : FieldTrialList : : CreateFieldTrial ( OmniboxFieldTrial : : kBundledExperimentFieldTrialName , "C" ) ;
 {
 AutocompleteInput input ( base : : string16 ( ) , base : : string16 : : npos , std : : string ( ) , GURL ( ) , OmniboxEventProto : : INSTANT_NTP_WITH_FAKEBOX_AS_STARTING_FOCUS , false , false , false , true , false , TestSchemeClassifier ( ) ) ;
 AutocompleteResult result ;
 result . AppendMatches ( input , matches ) ;
 result . SortAndCull ( input , std : : string ( ) , template_url_service_ . get ( ) ) ;
 ASSERT_EQ ( 4u , result . size ( ) ) ;
 EXPECT_EQ ( "http://search-what-you-typed/" , result . match_at ( 0 ) -> destination_url . spec ( ) ) ;
 EXPECT_EQ ( "http://dup-url/" , result . match_at ( 1 ) -> destination_url . spec ( ) ) ;
 EXPECT_EQ ( AutocompleteMatchType : : NAVSUGGEST , result . match_at ( 1 ) -> type ) ;
 EXPECT_EQ ( "http://search-url/" , result . match_at ( 2 ) -> destination_url . spec ( ) ) ;
 EXPECT_EQ ( "http://history-url/" , result . match_at ( 3 ) -> destination_url . spec ( ) ) ;
 }
 }