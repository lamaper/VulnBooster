TEST_F ( AutocompleteResultTest , SortAndCullWithDemotionsByType ) {
 ACMatches matches ;
 const AutocompleteMatchTestData data [ ] = {
 {
 "http://history-url/" , AutocompleteMatchType : : HISTORY_URL }
 , {
 "http://search-what-you-typed/" , AutocompleteMatchType : : SEARCH_WHAT_YOU_TYPED }
 , {
 "http://history-title/" , AutocompleteMatchType : : HISTORY_TITLE }
 , {
 "http://search-history/" , AutocompleteMatchType : : SEARCH_HISTORY }
 , }
 ;
 PopulateAutocompleteMatchesFromTestData ( data , arraysize ( data ) , & matches ) ;
 matches . back ( ) . relevance = 500 ;
 {
 std : : map < std : : string , std : : string > params ;
 params [ std : : string ( OmniboxFieldTrial : : kDemoteByTypeRule ) + ":3:*" ] = "1:50,7:100,2:0" ;
 ASSERT_TRUE ( variations : : AssociateVariationParams ( OmniboxFieldTrial : : kBundledExperimentFieldTrialName , "A" , params ) ) ;
 }
 base : : FieldTrialList : : CreateFieldTrial ( OmniboxFieldTrial : : kBundledExperimentFieldTrialName , "A" ) ;
 AutocompleteInput input ( base : : string16 ( ) , base : : string16 : : npos , std : : string ( ) , GURL ( ) , OmniboxEventProto : : HOME_PAGE , false , false , false , true , false , TestSchemeClassifier ( ) ) ;
 AutocompleteResult result ;
 result . AppendMatches ( input , matches ) ;
 result . SortAndCull ( input , template_url_service_ . get ( ) ) ;
 ASSERT_EQ ( 3u , result . size ( ) ) ;
 EXPECT_EQ ( "http://search-what-you-typed/" , result . match_at ( 0 ) -> destination_url . spec ( ) ) ;
 EXPECT_EQ ( "http://history-url/" , result . match_at ( 1 ) -> destination_url . spec ( ) ) ;
 EXPECT_EQ ( "http://search-history/" , result . match_at ( 2 ) -> destination_url . spec ( ) ) ;
 }