TEST_F ( AutocompleteResultTest , SortAndCullEmptyDestinationURLs ) {
 TestData data [ ] = {
 {
 1 , 1 , 500 , true }
 , {
 0 , 1 , 1100 , true }
 , {
 1 , 1 , 1000 , true }
 , {
 0 , 1 , 1300 , true }
 , {
 0 , 1 , 1200 , true }
 , }
 ;
 ACMatches matches ;
 PopulateAutocompleteMatches ( data , arraysize ( data ) , & matches ) ;
 matches [ 1 ] . destination_url = GURL ( ) ;
 matches [ 3 ] . destination_url = GURL ( ) ;
 matches [ 4 ] . destination_url = GURL ( ) ;
 AutocompleteInput input ( base : : string16 ( ) , base : : string16 : : npos , std : : string ( ) , GURL ( ) , OmniboxEventProto : : INVALID_SPEC , false , false , false , true , false , TestSchemeClassifier ( ) ) ;
 AutocompleteResult result ;
 result . AppendMatches ( input , matches ) ;
 result . SortAndCull ( input , std : : string ( ) , template_url_service_ . get ( ) ) ;
 ASSERT_EQ ( 4U , result . size ( ) ) ;
 EXPECT_TRUE ( result . match_at ( 0 ) -> destination_url . is_empty ( ) ) ;
 EXPECT_EQ ( 1300 , result . match_at ( 0 ) -> relevance ) ;
 EXPECT_TRUE ( result . match_at ( 1 ) -> destination_url . is_empty ( ) ) ;
 EXPECT_EQ ( 1200 , result . match_at ( 1 ) -> relevance ) ;
 EXPECT_TRUE ( result . match_at ( 2 ) -> destination_url . is_empty ( ) ) ;
 EXPECT_EQ ( 1100 , result . match_at ( 2 ) -> relevance ) ;
 EXPECT_EQ ( "http://b/" , result . match_at ( 3 ) -> destination_url . spec ( ) ) ;
 EXPECT_EQ ( 1000 , result . match_at ( 3 ) -> relevance ) ;
 }